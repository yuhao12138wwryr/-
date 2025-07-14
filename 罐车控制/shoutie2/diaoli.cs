using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Threading;
using shoutie;
namespace diaoli
{

	public  class diaoli
	{

		public shoutie_chuangti.CustomMessageBox customMessageBox1 = new shoutie_chuangti.CustomMessageBox();

		public void chushihuao(object global_var,int CarNum)
		{
            shoutie.global_var global_var1 = (shoutie.global_var)global_var;
            if (((float)global_var1.zhuangtai_du(CarNum, 2) == 2 && (CarNum == 1 || CarNum == 3)) || ((float)global_var1.zhuangtai_du(CarNum, 2) == 1 && (CarNum == 2 || CarNum == 4)))
            {
                if ((int)global_var1.zhuangtai_du(CarNum, 1) == 1 && (int)global_var1.zhuangtai_du(CarNum, 3) == 1)//车上_have_can子,_have_iron
                {
                    Thread zhuchengxu = new Thread(() => MyThreadMethod(global_var, CarNum));
                    zhuchengxu.Start(global_var);//启动主线程	
                }
            }

        }
		public void MyThreadMethod(object global_var1,int CarNum)//主程序
		{
			shoutie.global_var global_var = (shoutie.global_var)global_var1;
			int chehao = CarNum;
			if (global_var.over_proj == 1) { return; }
			Thread.Sleep(100);
			int xiaoche_bianhao = (int)chehao; //根据上次来判断
			global_var.zhuangtai_xie(xiaoche_bianhao, 12,1);//锁车
			shijue.tongzhi_xingche_diaoguan(xiaoche_bianhao, global_var.LineID1, global_var.LineID2);//通知调罐
			int guanhao = shijue.gunhao(xiaoche_bianhao, global_var);//获取罐号
            global_var.zhuangtai_xie(xiaoche_bianhao, 5, $"{xiaoche_bianhao}等待调离完成");
            while (shijue.zhongggun_diaoli(xiaoche_bianhao, global_var) != 1)//等待调离完成
			{
				if (global_var.over_proj == 1) { return; }
				Thread.Sleep(1000);
			}
            global_var.zhuangtai_xie(xiaoche_bianhao, 5, $"{xiaoche_bianhao}确认调离完成");
            global_var.zhuangtai_xie(xiaoche_bianhao, 1, 0);//更新状态，车上无罐
            global_var.zhuangtai_xie(xiaoche_bianhao, 3, 0);//更新状态，车上无铁水
            shijue.tongzhi_xingche_luoguan (xiaoche_bianhao, global_var.LineID1, global_var.LineID2);//通知落罐
            global_var.zhuangtai_xie(xiaoche_bianhao, 5, $"{xiaoche_bianhao}等待落罐完成");
            while (shijue.qingguan_luogun (xiaoche_bianhao, global_var) != 1)//等待落罐完成
			{
				if (global_var.over_proj == 1) { return; }
				Thread.Sleep(1000);
			}
            global_var.zhuangtai_xie(xiaoche_bianhao, 5, $"{xiaoche_bianhao}确认落罐完成");
            global_var.zhuangtai_xie(xiaoche_bianhao, 5, $"{xiaoche_bianhao}等待脱钩完成");
            while (shijue.tuogou (xiaoche_bianhao, global_var) != 1)//等待脱钩完成
			{
				if (global_var.over_proj == 1) { return; }
				Thread.Sleep(1000);
			}
            global_var.zhuangtai_xie(xiaoche_bianhao, 5, $"{xiaoche_bianhao}确认脱钩完成");
            global_var.zhuangtai_xie(xiaoche_bianhao, 5, $"{xiaoche_bianhao}等待集控人员确认脱钩完成");
            while (customMessageBox1.i == 0)//集控人员确认脱钩完成，车准备返回
			{
				customMessageBox1.Text = $"{xiaoche_bianhao}确认脱钩完成？";
				try { customMessageBox1.ShowDialog(); } catch { }
				if (global_var.over_proj == 1) { return; }
				Thread.Sleep(100);
                global_var.zhuangtai_xie(xiaoche_bianhao, 5, $"{xiaoche_bianhao}集控人员已经确认脱钩完成");
            }
			global_var.zhuangtai_xie(xiaoche_bianhao, 12, 0);//解锁
			global_var.zhuangtai_xie(xiaoche_bianhao, 1, 1);//更新状态，车上_have_can
            fanhui.fanhui yuhao = new fanhui.fanhui();
            yuhao .MyThreadMethod(global_var1, xiaoche_bianhao);
        }
	}


}
