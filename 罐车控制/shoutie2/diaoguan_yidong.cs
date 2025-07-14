
using shoutie;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
//using System.Threading.Tasks;
using System.Threading;
using System.Timers;
using System.Windows.Forms;

	namespace diaoguan_yidong//向吊包位移动
	{


	public class Diaoguan_yidong
		{



			//窗体变量定义处
			shoutie_chuangti.CustomMessageBox customMessageBox1 = new shoutie_chuangti.CustomMessageBox();//单按钮窗体

			public void chushihuao(object global_var,int CarNum)//初始化程序
			{
            Thread zhuchengxu = new Thread(() => MyThreadMethod(global_var, CarNum));
            zhuchengxu.Start(global_var);//启动主线程


			}
		public void MyThreadMethod(object global_var1,int CarNum)//主程序
		{
			yemian yemian = new yemian();

			shoutie.global_var global_var = (shoutie.global_var)global_var1;
			int chehao = CarNum;
			int key = global_var.priority_key;
            int duice_b1 = 3;
			int xiaoche_bianhao = (int)chehao; //根据上次来判断
			if ((int)chehao > 2)
			{ 
				 duice_b1 = 1; 
			}
			if (global_var.over_proj == 1) { return; } Thread.Sleep(100);
			float leida1, zhongliangji1;
			leida1 = yemian.duqu_leida(xiaoche_bianhao);
			zhongliangji1 = yemian.duqu_zhongliangji(xiaoche_bianhao);
			customMessageBox1.i = 0;
			while (leida1 == -1 && zhongliangji1 != -1 && customMessageBox1.i == 0)//确认重量计故障后任然运行
			{
				try
				{
					customMessageBox1.Text = $"{xiaoche_bianhao}重量计故障，是否仅使用雷达计判断？";
					customMessageBox1.ShowDialog();
				}
				catch { }
				if (global_var.over_proj == 1) { return; }
				Thread.Sleep(100);
			}
			customMessageBox1.i = 0;
			while (leida1 != -1 && zhongliangji1 == -1 && customMessageBox1.i == 0)//确认雷达计故障后任然运行
			{
				try
				{
					customMessageBox1.Text = $"{xiaoche_bianhao}雷达计故障，是否仅使用重量计判断？";
					customMessageBox1.ShowDialog();
				}
				catch { }
				if (global_var.over_proj == 1) { return; }
				Thread.Sleep(100);
			}
			while (leida1 == -1 && zhongliangji1 == -1)//确认重量计故障后任然运行
            {
                customMessageBox1.Text = $"{xiaoche_bianhao}雷达计故障，重量计故障，等待检修";
				customMessageBox1.ShowDialog();
				if (global_var.over_proj == 1) { return; }
				Thread.Sleep(100);
			}
            global_var.zhuangtai_xie(xiaoche_bianhao, 5, $"{xiaoche_bianhao}等待铁水液面到达80%");
            while (yemian.Yemian_shuzhi < 80)
			{ 
                yemian.yemian_shuchu(xiaoche_bianhao);//读取液面
				if (global_var.over_proj == 1) { return; }
				Thread.Sleep(1000);
			}
			if (global_var.cans == 4)//最后一罐
			{
                global_var.zhuangtai_xie(xiaoche_bianhao, 5, $"{xiaoche_bianhao}等待铁水液面到达90%");
                while (yemian.Yemian_shuzhi < 90)//受铁90%了
				{                    
                    yemian.yemian_shuchu(xiaoche_bianhao);//读取液面
					if (global_var.over_proj == 1) { return; }
					Thread.Sleep(1000);
				}
				customMessageBox1.Text = $"{xiaoche_bianhao}最后一罐，停止出铁";
				customMessageBox1.ShowDialog();
				if (global_var.over_proj == 1) { return; }
				Thread.Sleep(100);
			}
			if (global_var.cans != 4)//不是最后一罐
			{
                //对侧常用车规定时间内可以就位
				//液面是百分制，拿100减去当前值，比上速率，得到时间；小车时间是位置减去受铁位的距离后，比上车的固定速度V，这样就不用考虑车是不是在原位，后面还要&&一下，避免备用车在备用车位，距离值位负数
				if (   (xiaoche_bianhao>2) && ((float)(100 - yemian.Yemian_shuzhi) / (float)yemian.Yemian_shuzhi_biahualv > ((float )global_var.zhuangtai_du(1,2) - 0) / 1) || (xiaoche_bianhao < 3) && ((float)(100 - yemian.Yemian_shuzhi) / yemian.Yemian_shuzhi_biahualv > ((float)global_var.zhuangtai_du(3, 2) - 0) / 1)   )//对侧空罐车（b1或b2）在t1时间内能就绪
				{
                    if (xiaoche_bianhao <3)
                    {                        
                        shoutie.AffectedIron yuhao = new shoutie.AffectedIron();
                        yuhao.chushihuao(global_var, 3);//启动对侧轨道常用车线程
                    }
                    if (xiaoche_bianhao >2)
                    {
                        shoutie.AffectedIron yuhao = new shoutie.AffectedIron();
                        yuhao.chushihuao(global_var, 1);//启动对侧轨道常用车线程
                    }

                    global_var.zhuangtai_xie(xiaoche_bianhao, 5, $"{xiaoche_bianhao}等待铁水液面到达95%");
                    while (yemian.Yemian_shuzhi < 95)//受铁快完了
					{                        
                        yemian.yemian_shuchu(xiaoche_bianhao);//读取液面
						if (global_var.over_proj == 1) { return; }
						Thread.Sleep(1000);
					}
					if (  ((xiaoche_bianhao > 2)&&shoutie.xiaoche_b1.duqu_weizhi(1, global_var) == 2 )  || ((xiaoche_bianhao <3) && shoutie.xiaoche_b1.duqu_weizhi(3, global_var) == 2)) //对侧常用车空罐车就绪
					{
                        global_var.zhuangtai_xie(xiaoche_bianhao, 5, $"{xiaoche_bianhao}等待铁水液面到达100%");
                        while (yemian.Yemian_shuzhi < 95)//受铁完毕
						{                          
                            yemian.yemian_shuchu(xiaoche_bianhao);//读取液面
							if (global_var.over_proj == 1) { return; }
							Thread.Sleep(1000);
						}
                        
                    }
					else//对侧车无法就绪
					{
							customMessageBox1.Text = $"{xiaoche_bianhao}对侧车时间内无法返回，堵住出铁口";
							customMessageBox1.ShowDialog();
                            goto Lable;
                    }
				}
				else//规定时间内，返回途中的车不能就绪
				{ 
					if((xiaoche_bianhao > 2) && shoutie.xiaoche_b1.duqu_weizhi(2, global_var) == 1 || (xiaoche_bianhao < 3) && shoutie.xiaoche_b1.duqu_weizhi(4, global_var) == 1)//对侧B2车在位,启动备用车线程
					{
                        if (xiaoche_bianhao < 3)
                        {
                            shoutie.AffectedIron yuhao = new shoutie.AffectedIron();
                            yuhao.chushihuao(global_var, 4);//启动对侧轨道备用车线程
                        }
                        if (xiaoche_bianhao > 2)
                        {

                            shoutie.AffectedIron yuhao = new shoutie.AffectedIron();
                            yuhao.chushihuao(global_var, 2);//启动对侧轨道备用车线程
                        }
                        global_var.zhuangtai_xie(xiaoche_bianhao, 5, $"{xiaoche_bianhao}等待铁水液面到达95%");
                        while (yemian.Yemian_shuzhi < 95)
                        {
                            yemian.yemian_shuchu(xiaoche_bianhao);//读取液面
                            if (global_var.over_proj == 1) { return; }
                            Thread.Sleep(1000);
                        }
                        global_var.zhuangtai_xie(xiaoche_bianhao, 5, $"{xiaoche_bianhao}铁水液面到达95%");
                    }
					else//对侧B2车不在位
					{
						customMessageBox1.Text = $"{xiaoche_bianhao}对侧无车，堵住出铁口";
						customMessageBox1.ShowDialog();
                        goto Lable;
                    }
				}

            }

                customMessageBox1.Text = $"{xiaoche_bianhao}即将摆动溜槽";
                customMessageBox1.ShowDialog();

			global_var.chute_allow = 1;//溜槽摆动发命令
            global_var.zhuangtai_xie(xiaoche_bianhao, 5, $"{xiaoche_bianhao}等待溜槽摆动到指定位置");
			if (xiaoche_bianhao < 3)//车为1或2，等溜槽摆动到3，4号车的方向
			{
				while (shoutie.receve_iron.du_liucao_baidong_wancheng(3, global_var.LineID1, global_var.LineID2) != 1)//等待溜槽摆动到指定位置
				{
					if (global_var.over_proj == 1) { return; }
					Thread.Sleep(100);
				}
			}
			if (xiaoche_bianhao > 2)//车为3或4，等溜槽摆动到1，2号车的方向
			{
				while (shoutie.receve_iron.du_liucao_baidong_wancheng(1, global_var.LineID1, global_var.LineID2) != 1)//等待溜槽摆动到指定位置
				{
					if (global_var.over_proj == 1) { return; }
					Thread.Sleep(100);
				}
			}
			global_var.zhuangtai_xie(xiaoche_bianhao, 5, $"{xiaoche_bianhao}溜槽已经摆动到指定位置，车解锁");
			global_var.zhuangtai_xie(xiaoche_bianhao, 12, 0);//解锁
			global_var.zhuangtai_xie(xiaoche_bianhao, 5, $"{xiaoche_bianhao}等待操作员确认溜槽摆动完成");
            try
			{
				customMessageBox1.Text = $"{xiaoche_bianhao}确认溜槽摆动完成，即将发车";
				customMessageBox1.ShowDialog();
			}
			catch { }
            global_var.zhuangtai_xie(xiaoche_bianhao, 5, $"{xiaoche_bianhao}操作员已经确认溜槽摆动完成");
            Lable:
            global_var.zhuangtai_xie(xiaoche_bianhao,3,1);//更新状态，车上_have_iron
            guanchedida.diaoguan yuhao2 = new guanchedida.diaoguan();//进函数
			yuhao2.MyThreadMethod(global_var1, xiaoche_bianhao);
		}


		}



}

