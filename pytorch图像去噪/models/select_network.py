import functools
import torch
from torch.nn import init


"""
# --------------------------------------------
# select the network of G, D and F
# --------------------------------------------
"""


# --------------------------------------------
# Generator, netG, G
# --------------------------------------------
def define_G(opt):
    opt_net = opt['netG']
    net_type = opt_net['net_type']


    # ----------------------------------------
    # denoising task
    # ----------------------------------------

    if net_type == 'brdnet':
        from models.network_brdnet import BRDNet as net
        netG = net(in_nc=opt_net['in_nc'],
                   out_nc=opt_net['out_nc'],
                   nc=opt_net['nc'],
                   nb=opt_net['nb'],  # total number of conv layers
                   act_mode=opt_net['act_mode'])
    elif net_type == 'resbrd':
        from models.network_resbrd import ResBRD as net
        netG = net(in_nc=opt_net['in_nc'],
                   out_nc=opt_net['out_nc'],
                   nc=opt_net['nc'],
                   nb=opt_net['nb'],  # total number of conv layers
                   act_mode=opt_net['act_mode'])
    elif net_type == 'drnet':
        from models.network_drnet import DRNet as net
        netG = net(in_nc=opt_net['in_nc'],
                   out_nc=opt_net['out_nc'],
                   nc=opt_net['nc'],
                   nb=opt_net['nb'],  # total number of conv layers
                   act_mode=opt_net['act_mode'])
    elif net_type == 'drnet_crc':
        from models.network_drnet_crc import DRNet_CRC as net
        netG = net(in_nc=opt_net['in_nc'],
                   out_nc=opt_net['out_nc'],
                   nc=opt_net['nc'],
                   nb=opt_net['nb'],  # total number of conv layers
                   act_mode=opt_net['act_mode'])
    elif net_type == 'drnet_ccr':
        from models.network_drnet_ccr import DRNet_CCR as net
        netG = net(in_nc=opt_net['in_nc'],
                   out_nc=opt_net['out_nc'],
                   nc=opt_net['nc'],
                   nb=opt_net['nb'],  # total number of conv layers
                   act_mode=opt_net['act_mode'])
    elif net_type == 'drnet_crd':
        from models.network_drnet_crd import DRNet_CRD as net
        netG = net(in_nc=opt_net['in_nc'],
                   out_nc=opt_net['out_nc'],
                   nc=opt_net['nc'],
                   nb=opt_net['nb'],  # total number of conv layers
                   act_mode=opt_net['act_mode'])
    elif net_type == 'drnet_cdcc':
        from models.network_drnet_cdcc import DRNet_CDCC as net
        netG = net(in_nc=opt_net['in_nc'],
                   out_nc=opt_net['out_nc'],
                   nc=opt_net['nc'],
                   nb=opt_net['nb'],  # total number of conv layers
                   act_mode=opt_net['act_mode'])
    elif net_type == 'drnet_color':
        from models.network_drnet_color import DRNet as net
        netG = net(in_nc=opt_net['in_nc'],
                   out_nc=opt_net['out_nc'],
                   nc=opt_net['nc'],
                   nb=opt_net['nb'],  # total number of conv layers
                   act_mode=opt_net['act_mode'])
    elif net_type == 'resdncnn':
        from models.network_resdncnn import DnCNN_ResCDC as net
        netG = net(in_nc=opt_net['in_nc'],
                   out_nc=opt_net['out_nc'],
                   nc=opt_net['nc'],
                   nb=opt_net['nb'],  # total number of conv layers
                   act_mode=opt_net['act_mode'])
    # ----------------------------------------
    # others
    # ----------------------------------------
    # TODO

    else:
        raise NotImplementedError('netG [{:s}] is not found.'.format(net_type))

    # ----------------------------------------
    # initialize weights
    # ----------------------------------------
    if opt['is_train']:
        init_weights(netG,
                     init_type=opt_net['init_type'],
                     init_bn_type=opt_net['init_bn_type'],
                     gain=opt_net['init_gain'])

    return netG

"""
# --------------------------------------------
# weights initialization
# --------------------------------------------
"""


def init_weights(net, init_type='xavier_uniform', init_bn_type='uniform', gain=1):
    """
    # Kai Zhang, https://github.com/cszn/KAIR
    #
    # Args:
    #   init_type:
    #       normal; normal; xavier_normal; xavier_uniform;
    #       kaiming_normal; kaiming_uniform; orthogonal
    #   init_bn_type:
    #       uniform; constant
    #   gain:
    #       0.2
    """
    print('Initialization method [{:s} + {:s}], gain is [{:.2f}]'.format(init_type, init_bn_type, gain))
    import torch
    import torch.nn as nn
    import torch.nn.init as init
    import functools
    def init_fn(m, init_type='xavier_uniform', init_bn_type='uniform', gain=1):
        """
        初始化函数，支持所有子模块的权重初始化
        :param m: 模块
        :param init_type: 权重初始化类型
        :param init_bn_type: BatchNorm 初始化类型
        :param gain: 增益参数
        """
        classname = m.__class__.__name__

        # 处理卷积层和全连接层
        if isinstance(m, (nn.Conv2d, nn.Linear)):
            if init_type == 'normal':
                init.normal_(m.weight.data, 0, 0.1)
                m.weight.data.clamp_(-1, 1).mul_(gain)
            elif init_type == 'uniform':
                init.uniform_(m.weight.data, -0.2, 0.2)
                m.weight.data.mul_(gain)
            elif init_type == 'xavier_normal':
                init.xavier_normal_(m.weight.data, gain=gain)
                m.weight.data.clamp_(-1, 1)
            elif init_type == 'xavier_uniform':
                init.xavier_uniform_(m.weight.data, gain=gain)
            elif init_type == 'kaiming_normal':
                init.kaiming_normal_(m.weight.data, a=0, mode='fan_in', nonlinearity='relu')
                m.weight.data.clamp_(-1, 1).mul_(gain)
            elif init_type == 'kaiming_uniform':
                init.kaiming_uniform_(m.weight.data, a=0, mode='fan_in', nonlinearity='relu')
                m.weight.data.mul_(gain)
            elif init_type == 'orthogonal':
                init.orthogonal_(m.weight.data, gain=gain)
            else:
                raise NotImplementedError(f'初始化方法 [{init_type}] 未实现')

            # 初始化偏置
            if m.bias is not None:
                m.bias.data.zero_()

        # 处理自定义模块（如 Conv2d_cd）
        elif hasattr(m, 'conv') and isinstance(m.conv, (nn.Conv2d, nn.Linear)):
            if init_type == 'normal':
                init.normal_(m.conv.weight.data, 0, 0.1)
                m.conv.weight.data.clamp_(-1, 1).mul_(gain)
            elif init_type == 'uniform':
                init.uniform_(m.conv.weight.data, -0.2, 0.2)
                m.conv.weight.data.mul_(gain)
            elif init_type == 'xavier_normal':
                init.xavier_normal_(m.conv.weight.data, gain=gain)
                m.conv.weight.data.clamp_(-1, 1)
            elif init_type == 'xavier_uniform':
                init.xavier_uniform_(m.conv.weight.data, gain=gain)
            elif init_type == 'kaiming_normal':
                init.kaiming_normal_(m.conv.weight.data, a=0, mode='fan_in', nonlinearity='relu')
                m.conv.weight.data.clamp_(-1, 1).mul_(gain)
            elif init_type == 'kaiming_uniform':
                init.kaiming_uniform_(m.conv.weight.data, a=0, mode='fan_in', nonlinearity='relu')
                m.conv.weight.data.mul_(gain)
            elif init_type == 'orthogonal':
                init.orthogonal_(m.conv.weight.data, gain=gain)
            else:
                raise NotImplementedError(f'初始化方法 [{init_type}] 未实现')

            # 初始化偏置
            if m.conv.bias is not None:
                m.conv.bias.data.zero_()

        # 处理 BatchNorm 层
        elif classname.find('BatchNorm2d') != -1:
            if init_bn_type == 'uniform':  # preferred
                if m.affine:
                    init.uniform_(m.weight.data, 0.1, 1.0)
                    init.constant_(m.bias.data, 0.0)
            elif init_bn_type == 'constant':
                if m.affine:
                    init.constant_(m.weight.data, 1.0)
                    init.constant_(m.bias.data, 0.0)
            else:
                raise NotImplementedError(f'初始化方法 [{init_bn_type}] 未实现')

    def init_weights(net, init_type='xavier_uniform', init_bn_type='uniform', gain=1):
        """
        初始化网络权重
        :param net: 网络模型
        :param init_type: 权重初始化类型
        :param init_bn_type: BatchNorm 初始化类型
        :param gain: 增益参数
        """
        fn = functools.partial(init_fn, init_type=init_type, init_bn_type=init_bn_type, gain=gain)
        net.apply(fn)

