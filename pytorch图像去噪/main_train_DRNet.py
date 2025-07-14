import os.path
import math
import argparse
import time
import random
import numpy as np
from collections import OrderedDict
import logging
import torch
from torch.utils.data import DataLoader

from utils import utils_logger
from utils import utils_image as util
from utils import utils_option as option

from data.select_dataset import define_Dataset
from models.select_model import define_Model



def main(json_path='options/train_drnet.json'):

    '''
    # ----------------------------------------
    # Step--1 (prepare opt)
    # ----------------------------------------
    '''

    parser = argparse.ArgumentParser()
    parser.add_argument('-opt', type=str, default=json_path, help='Path to option JSON file.')

    opt = option.parse(parser.parse_args().opt, is_train=True)
    util.mkdirs((path for key, path in opt['path'].items() if 'pretrained' not in key))

    # ----------------------------------------
    # update opt
    # ----------------------------------------
    # -->-->-->-->-->-->-->-->-->-->-->-->-->-
    init_iter, init_path_G = option.find_last_checkpoint(opt['path']['models'], net_type='G')
    opt['path']['pretrained_netG'] = init_path_G

    current_step = init_iter

    border = 0
    # --<--<--<--<--<--<--<--<--<--<--<--<--<-

    # ----------------------------------------
    # save opt to  a '../option.json' file
    # ----------------------------------------
    option.save(opt)

    # ----------------------------------------
    # return None for missing key
    # ----------------------------------------
    opt = option.dict_to_nonedict(opt)

    # ----------------------------------------
    # configure logger
    # ----------------------------------------
    logger_name = 'train'
    utils_logger.logger_info(logger_name, os.path.join(opt['path']['log'], logger_name+'.log'))
    logger = logging.getLogger(logger_name)
    logger.info(option.dict2str(opt))

    # ----------------------------------------
    # seed
    # ----------------------------------------
    seed = opt['train']['manual_seed']
    if seed is None:
        seed = random.randint(1, 10000)
    logger.info('Random seed: {}'.format(seed))
    random.seed(seed)
    np.random.seed(seed)
    torch.manual_seed(seed)
    torch.cuda.manual_seed_all(seed)

    '''
    # ----------------------------------------
    # Step--2 (creat dataloader)
    # ----------------------------------------
    '''

    # ----------------------------------------
    # 1) create_dataset
    # 2) creat_dataloader for train and test
    # ----------------------------------------
    dataset_type = opt['datasets']['train']['dataset_type']
    for phase, dataset_opt in opt['datasets'].items():#从json文件读取数据
        if phase == 'train':#如果是训练阶段
            train_set = define_Dataset(dataset_opt)#取出drnet后使用数据dataset_drnet
            train_size = int(math.ceil(len(train_set) / dataset_opt['dataloader_batch_size']))#计算训练数据集的迭代次数
            logger.info('Number of train images: {:,d}, iters: {:,d}'.format(len(train_set), train_size))
            train_loader = DataLoader(train_set,
                                      batch_size=dataset_opt['dataloader_batch_size'],#从JSON读取数据
                                      shuffle=dataset_opt['dataloader_shuffle'],
                                      num_workers=dataset_opt['dataloader_num_workers'],
                                      drop_last=True,
                                      pin_memory=True)
        elif phase == 'test':
            test_set = define_Dataset(dataset_opt)
            test_loader = DataLoader(test_set, batch_size=1,
                                     shuffle=False, num_workers=1,
                                     drop_last=False, pin_memory=True)
        else:
            raise NotImplementedError("Phase [%s] is not recognized." % phase)

    '''
    # ----------------------------------------
    # Step--3 (initialize model)
    # ----------------------------------------
    '''

    model = define_Model(opt)####################################从这选择模型和框架

    if opt['merge_bn'] and current_step > opt['merge_bn_startpoint']:
        logger.info('^_^ -----merging bnorm----- ^_^')
        model.merge_bnorm_test()

    logger.info(model.info_network())
    model.init_train()
    logger.info(model.info_params())

    '''
    # ----------------------------------------
    # Step--4 (main training)
    # ----------------------------------------
    '''
    rrrr=2000000
    for epoch in range(1000000):  # keep
        print('epoch', epoch)
        if epoch==rrrr+1:
            break
        for i, train_data in enumerate(train_loader):

            current_step += 1
            print('current_step',current_step)
            if dataset_type == 'dnpatch' and current_step % 20000 == 0:  # for 'train400'不满足dnpatch
                train_loader.dataset.update_data()
            # -------------------------------
            # 1) update learning rate
            # -------------------------------
            model.update_learning_rate(current_step)#更新学习率
            if current_step==900000:
                print("程序已退出。")
                rrrr=epoch
                break
            # -------------------------------
            # 2) feed patch pairs
            # -------------------------------
            model.feed_data(train_data)# model.feed_data(train_data)
            # -------------------------------
            # 3) optimize parameters
            # -------------------------------
            model.optimize_parameters(current_step)
            #visuals = model.current_visuals()
            #L_img = util.tensor2uint(visuals['E'])
            #H_img = util.tensor2uint(visuals['H'])
            #util.imsave(H_img, "sd.png")
            #util.imsave(L_img, "sd2.png")
            #print('3')
            #model.kancanshu()  ##############################################
            # -------------------------------
            # merge bnorm通过梯度下降等优化算法来调整模型的参数，使得模型的输出尽量接近目标值。
            # -------------------------------
            if opt['merge_bn'] and opt['merge_bn_startpoint'] == current_step:
                logger.info('^_^ -----merging bnorm----- ^_^')
                model.merge_bnorm_train()#主要目的是在训练过程中执行批量归一化的融合操作。
                model.print_network()

            # -------------------------------
            # 4) training information
            # -------------------------------
            if current_step % opt['train']['checkpoint_print'] == 0:
                logs = model.current_log()  # such as loss
                message = '<epoch:{:3d}, iter:{:8,d}, lr:{:.3e}> '.format(epoch, current_step, model.current_learning_rate())
                for k, v in logs.items():  # merge log information into message
                    message += '{:s}: {:.3e} '.format(k, v)
                logger.info(message)
            # -------------------------------
            # 5) save model
            # -------------------------------
            if current_step % opt['train']['checkpoint_save'] == 0:
                logger.info('Saving the model.')
                model.save(current_step)

            # -------------------------------
            # 6) testing
            # -------------------------------
            if current_step % opt['train']['checkpoint_test'] == 0:

                avg_psnr = 0.0
                idx = 0

                for test_data in test_loader:
                    idx += 1
                    image_name_ext = os.path.basename(test_data['L_path'][0])
                    img_name, ext = os.path.splitext(image_name_ext)

                    img_dir = os.path.join(opt['path']['images'], img_name)
                    util.mkdir(img_dir)

                    model.feed_data(test_data)
                    model.test()

                    visuals = model.current_visuals()
                    E_img = util.tensor2uint(visuals['E'])
                    H_img = util.tensor2uint(visuals['H'])

                    # -----------------------
                    # save estimated image E
                    # -----------------------
                    #save_img_path = os.path.join(img_dir, '{:s}_{:d}.png'.format(img_name, current_step))
                    #util.imsave(E_img, save_img_path)

                    # -----------------------
                    # calculate PSNR
                    # -----------------------
                    current_psnr = util.calculate_psnr(E_img, H_img, border=border)

                    logger.info('{:->4d}--> {:>10s} | {:<4.2f}dB'.format(idx, image_name_ext, current_psnr))

                    avg_psnr += current_psnr

                avg_psnr = avg_psnr / idx

                # testing log
                logger.info('<epoch:{:3d}, iter:{:8,d}, Average PSNR : {:<.2f}dB\n'.format(epoch, current_step, avg_psnr))

    logger.info('Saving the final model.')
    model.save('latest')
    logger.info('End of training.')
    time.sleep(5)

if __name__ == '__main__':
    main()
