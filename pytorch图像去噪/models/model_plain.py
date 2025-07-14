from collections import OrderedDict
import torch
import torch.nn as nn
from torch.optim import lr_scheduler
from torch.optim import Adam
from torch.nn.parallel import DataParallel  # , DistributedDataParallel

from models.select_network import define_G
from models.model_base import ModelBase
from models.loss_ssim import SSIMLoss

from utils.utils_model import test_mode
from utils.utils_regularizers import regularizer_orth, regularizer_clip


class ModelPlain(ModelBase):
    """Train with pixel loss"""

    def __init__(self, opt):
        super(ModelPlain, self).__init__(opt)
        # ------------------------------------
        # define network
        # ------------------------------------
        self.netG = define_G(opt).to(self.device)
        self.netG1 = self.netG
        self.netG = DataParallel(self.netG)  # 多GPU并行处理

    """
    # ----------------------------------------
    # Preparation before training with data
    # Save model during training
    # ----------------------------------------
    """

    # ----------------------------------------
    # initialize training
    # ----------------------------------------
    def init_train(self):
        self.opt_train = self.opt['train']  # training option
        self.load()  # load model
        self.netG.train()  # set training mode,for BN PyTorch 中模型训练状态设置的方法，这对于那些在训练和评估模式下行为不同的模块，如 Dropout、BatchNorm 等是非常重要的。
        self.define_loss()  # define loss
        self.define_optimizer()  # define optimizer于定义优化器的方法
        self.define_scheduler()  # define scheduler定义学习率调度器的方法
        self.log_dict = OrderedDict()  # log一个用于记录日志信息的有序字典（OrderedDict）。有序字典是一种可以维护元素插入顺序的字典类型，与普通字典不同，它会按照元素插入的先后顺序进行迭代。

    def kancanshu(self):
        for name, param in self.netG.named_parameters():
            if 'conv2' in name:  # 判断是否为卷积层的参数
                print(f'Parameter name: {name}, Size: {param.size()}')
                print(f'Parameter values: {param.data}')
                print("\n")
        conv2_grad = self.netG1.fc1.weight.grad
        print("Gradient of conv2 layer:")
        print(conv2_grad)

    # ----------------------------------------
    # load pre-trained G model#断是否存在预训练模型路径获取预训练生成器模型的路径：从配置参数 self.opt['path']['pretrained_netG'] 中获取预训练模型的路径 load_path_G
    # ----------------------------------------
    def load(self):
        load_path_G = self.opt['path']['pretrained_netG']
        if load_path_G is not None:
            print('Loading model for G [{:s}] ...'.format(load_path_G))
            self.load_network(load_path_G, self.netG)

    """
    # ----------------------------------------
    # save model
    获取保存模型的迭代标签：方法的参数
    iter_label
    表示模型的迭代标签，通常用于区分不同保存状态的模型。
    调用 save_network 方法：调用 self.save_network 方法，将生成器模型（self.netG）保存到指定路径。方法中使用了 save_dir、'G'（表示生成器模型）和 iter_label 来构建保存模型的文件名。
    # ----------------------------------------
       """

    def save(self, iter_label):
        self.save_network(self.save_dir, self.netG, 'G', iter_label)

    # ----------------------------------------
    # define loss
    # 获取训练配置中的损失函数类型：从训练配置参数 self.opt_train['G_lossfn_type'] 中获取生成器损失函数的类型 G_lossfn_type。
    # 根据损失函数类型选择相应的损失函数：
    # ----------------------------------------
    def define_loss(self):
        G_lossfn_type = self.opt_train['G_lossfn_type']
        if G_lossfn_type == 'l1':
            self.G_lossfn = nn.L1Loss().to(self.device)
        elif G_lossfn_type == 'l2':
            self.G_lossfn = nn.MSELoss().to(self.device)
        elif G_lossfn_type == 'l2sum':
            self.G_lossfn = nn.MSELoss(reduction='sum').to(self.device)
        elif G_lossfn_type == 'ssim':
            self.G_lossfn = SSIMLoss().to(self.device)
        elif G_lossfn_type == 'PRP':
            self.G_lossfn = SSIMLoss().to(self.device)
        else:
            raise NotImplementedError('Loss type [{:s}] is not found.'.format(
                G_lossfn_type))  # 如果 G_lossfn_type 不属于上述类型，则抛出 NotImplementedError 异常，表示损失函数类型未找到。
        self.G_lossfn_weight = self.opt_train['G_lossfn_weight']

    # 获取训练配置中的损失函数权重：从训练配置参数 self.opt_train['G_lossfn_weight'] 中获取生成器损失函数的权重 G_lossfn_weight。
    # 这个权重参数用于调整不同损失函数对总体生成器损失的贡献。在训练过程中，生成器的总体损失会被计算为各个损失函数的加权和，其中权重由 G_lossfn_weight 决定。
    # ----------------------------------------
    # define optimizer在遍历网络参数时，对于不需要进行梯度更新的参数，输出提示信息，指明这些参数不会进行优化。
    # ----------------------------------------
    def define_optimizer(self):
        G_optim_params = []
        for k, v in self.netG.named_parameters():
            if v.requires_grad:
                G_optim_params.append(v)
            else:
                print('Params [{:s}] will not optimize.'.format(k))
        self.G_optimizer = Adam(G_optim_params, lr=self.opt_train['G_optimizer_lr'], weight_decay=0)

    # ----------------------------------------
    # define scheduler, 定义学习率调度器的方法
    # ----------------------------------------
    def define_scheduler(self):
        self.schedulers.append(lr_scheduler.MultiStepLR(self.G_optimizer,
                                                        self.opt_train['G_scheduler_milestones'],
                                                        self.opt_train['G_scheduler_gamma']
                                                        ))

    """
    # ----------------------------------------
    # Optimization during training with data
    # Testing/evaluation
    # ----------------------------------------
    """

    # ----------------------------------------
    # feed L/H data
    # 这段代码定义了两个方法用于向模型输入数据：
    # eed_data(self, data, need_H=True) 方法将输入数据 data 中的低分辨率图像 L 和高分辨率图像 H 分别移到 GPU 上（如果可用），并存储在模型中。need_H 参数表示是否需要处理高分辨率图像。
    # feed_data_cpu方法与上述方法类似，但是将图像存储在 CPU 上而不是 GPU。
    # ----------------------------------------
    def feed_data(self, data, need_H=True):
        self.L = data['L'].to(self.device)
        # print("Shape of L:", data['L'].shape)
        if need_H:
            self.H = data['H'].to(self.device)

    def feed_data_cpu(self, data, need_H=True):
        self.L = data['L']
        if need_H:
            self.H = data['H']

    # ----------------------------------------
    # update parameters and get loss定义了模型的优化步骤。主要步骤如下
    # ----------------------------------------
    # G_optimizer.zero_grad()清零梯度
    def optimize_parameters(self, current_step):
        self.G_optimizer.zero_grad()
        self.E = self.netG1.forward(
            self.L)  # 通过生成器模型 (self.netG) 对低分辨率图像 (self.L) 进行前向传播，得到生成的高分辨率图像 (self.E)。可以改成forward2
        G_loss = self.G_lossfn_weight * self.G_lossfn(self.E,
                                                      self.H)  # 计算生成器的损失：根据预定义的损失函数类型 (self.G_lossfn_type) 和权重 (self.G_lossfn_weight)，计算生成器的损失。
        G_loss.backward()  # 对生成器的损失进行反向传播，计算梯度。

        # ------------------------------------
        # clip_grad执行了梯度裁剪操作会检查是否设置了梯度裁剪的阈值 G_optimizer_clipgrad，如果设置了且大于零，则对模型的参数进行梯度裁剪。
        # ------------------------------------
        # `clip_grad_norm` helps prevent the exploding gradient problem.
        G_optimizer_clipgrad = self.opt_train['G_optimizer_clipgrad'] if self.opt_train['G_optimizer_clipgrad'] else 0
        if G_optimizer_clipgrad > 0:
            torch.nn.utils.clip_grad_norm_(self.parameters(), max_norm=self.opt_train['G_optimizer_clipgrad'],
                                           norm_type=2)

        self.G_optimizer.step()

        # ------------------------------------
        # regularizer正则化（regularization）的逻辑。正则化是一种用于控制模型复杂性的技术，目的是防止模型过度拟合训练数据。在这里，包括两种正则化方法：正交正则化（orthogonal regularization）和剪切正则化（clip regularization）。
        # 不用改
        # ------------------------------------
        G_regularizer_orthstep = self.opt_train['G_regularizer_orthstep'] if self.opt_train[
            'G_regularizer_orthstep'] else 0
        if G_regularizer_orthstep > 0 and current_step % G_regularizer_orthstep == 0 and current_step % \
                self.opt['train']['checkpoint_save'] != 0:
            self.netG.apply(regularizer_orth)
        G_regularizer_clipstep = self.opt_train['G_regularizer_clipstep'] if self.opt_train[
            'G_regularizer_clipstep'] else 0
        if G_regularizer_clipstep > 0 and current_step % G_regularizer_clipstep == 0 and current_step % \
                self.opt['train']['checkpoint_save'] != 0:
            self.netG.apply(regularizer_clip)

        # self.log_dict['G_loss'] = G_loss.item()/self.E.size()[0]  # if `reduction='sum'`
        self.log_dict['G_loss'] = G_loss.item()

    # ----------------------------------------
    # test / inference
    # ----------------------------------------
    def test(self):
        self.netG.eval()  # 将生成器网络设置为评估模式（eval）。
        with torch.no_grad():  # 禁用梯度计算，使用 torch.no_grad() 上下文管理器。
            self.E = self.netG1.forward(self.L)  # 通过生成器网络（self.netG）传递输入 self.L，得到生成的输出 self.可以改成forword2
        self.netG.train()  # 将生成器网络设置回训练模式（train）。

    def test_cpu(self):
        self.netG.eval()
        self.netG = self.netG.cpu()
        with torch.no_grad():
            self.E = self.netG(self.L)
        self.netG = self.netG.to(self.device)
        self.netG.train()

    # ----------------------------------------
    # test / inference x8用于在测试阶段进行多尺度（8倍放大）的推理。有助于评估模型在不同分辨率下的性能。
    # ----------------------------------------
    def testx8(self):
        self.netG.eval()
        with torch.no_grad():
            self.E = test_mode(self.netG, self.L, mode=3, sf=self.opt['scale'],
                               modulo=1)  # 调用 test_mode 函数进行多尺度测试。该函数的参数包括生成器网络（self.netG）、输入（self.L）、模式（mode=3 表示8倍放大）、缩放因子（sf=self.opt['scale']）和模数（modulo=1）。
        self.netG.train()

    # ----------------------------------------
    # get log_dict 返回当前的日志字典 log_dict，其中记录了训练过程中的损失等信息。
    # ----------------------------------------
    def current_log(self):
        return self.log_dict

    # ----------------------------------------
    # get L, E, H image返回包含当前输入图像 L、生成图像 E 以及目标图像 H（如果需要）的有序字典 out_dict。这用于可视化当前训练或测试步骤的图像数据。
    # ----------------------------------------
    def current_visuals(self, need_H=True):
        out_dict = OrderedDict()
        out_dict['L'] = self.L.detach()[0].float().cpu()
        out_dict['E'] = self.E.detach()[0].float().cpu()
        if need_H:
            out_dict['H'] = self.H.detach()[0].float().cpu()
        return out_dict

    # ----------------------------------------
    # get L, E, H batch images这两个方法用于获取当前训练或测试步骤的图像数据
    # ----------------------------------------
    def current_results(self, need_H=True):
        out_dict = OrderedDict()
        out_dict['L'] = self.L.detach().float().cpu()
        out_dict['E'] = self.E.detach().float().cpu()
        if need_H:
            out_dict['H'] = self.H.detach().float().cpu()
        return out_dict

    """
    # ----------------------------------------
    # Information of netG
    # ----------------------------------------
    """

    # ----------------------------------------
    # print network打印生成器网络的信息。
    # ----------------------------------------
    def print_network(self):
        msg = self.describe_network(self.netG)
        print(msg)

    # ----------------------------------------
    # print params: 打印生成器网络的参数信息。
    # ----------------------------------------
    def print_params(self):
        msg = self.describe_params(self.netG)
        print(msg)

    # ----------------------------------------
    # network information获取生成器网络的信息（字符串形式）。
    # ----------------------------------------
    def info_network(self):
        msg = self.describe_network(self.netG)
        return msg

    # ----------------------------------------
    # params information获取生成器网络的参数信息（字符串形式）。
    # ----------------------------------------
    def info_params(self):
        msg = self.describe_params(self.netG)
        return msg
