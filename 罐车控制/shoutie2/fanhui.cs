using shoutie_chuangti;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Threading;
using shoutie;
namespace fanhui

{


	public class fanhui
	{

										
		
		//窗体变量定义处
		public shoutie_chuangti.CustomMessageBox customMessageBox1 = new shoutie_chuangti.CustomMessageBox();//单按钮窗体

		public void chushihuao(object global_var, int CarNum)//初始化程序
		{


            shoutie.global_var global_var1 = (shoutie.global_var)global_var;
            if (((float)global_var1.zhuangtai_du(CarNum, 2) == 2 && (CarNum == 1 || CarNum == 3)) || ((float)global_var1.zhuangtai_du(CarNum, 2) == 1 && (CarNum == 2 || CarNum == 4)))
            {
                if ((int)global_var1.zhuangtai_du(CarNum, 1) == 1 && (int)global_var1.zhuangtai_du(CarNum, 3) == 1)//车上_have_can子,无铁水
                {
                    Thread zhuchengxu = new Thread(() => MyThreadMethod(global_var, CarNum));
                    zhuchengxu.Start(global_var);//启动主线程	
                }
            }

        }

		public void MyThreadMethod(object global_var1,int chehao)//主程序
		{
			shoutie.global_var global_var = (shoutie.global_var)global_var1;
			int key = global_var.priority_key;
			int baidong_shouquan = global_var.chute_allow;
			int xiaoche_bianhao = (int)chehao; //根据上次来判断
            global_var.zhuangtai_xie(xiaoche_bianhao, 5, $"{xiaoche_bianhao}等待小车控制PLC工况正常");
            while (shoutie.xiaoche_b1.xintiao(xiaoche_bianhao, global_var.LineID1, global_var.LineID2) != 1)//小车控制PLC工况正常,公用的PLC
			{
				if (global_var.over_proj == 1) { return; }Thread.Sleep(100);
			}
            global_var.zhuangtai_xie(xiaoche_bianhao, 5, $"{xiaoche_bianhao}确认小车控制PLC工况正常");
            if (xiaoche_bianhao == 1|| xiaoche_bianhao==3)//当前为常用车
			{
                global_var.zhuangtai_xie(xiaoche_bianhao, 5, $"{xiaoche_bianhao}后退，等待回到等待位");
                while (shoutie.xiaoche_b1.duqu_weizhi(xiaoche_bianhao, global_var) != 6)//常用车回到等待位
                {
						if (global_var.over_proj == 1) { return; }
						Thread.Sleep(100);
						shoutie.xiaoche_b1.xianche_houtui(xiaoche_bianhao, xiaoche_bianhao, global_var.priority_key, global_var.LineID1, global_var.LineID2, global_var);//向常用车停车位返回					
				}
                global_var.zhuangtai_xie(xiaoche_bianhao, 5, $"{xiaoche_bianhao}确认已经回到等待位");
                shoutie.xiaoche_b1.xianche_tingzhi(xiaoche_bianhao, global_var.LineID1, global_var.LineID2);//刹车，已到达

				if (shoutie.xiaoche_b1.duqu_weizhi(xiaoche_bianhao + 1, global_var) != 1)//备用车不在原位
                {
                    return;
                }
                global_var.zhuangtai_xie(xiaoche_bianhao, 5, $"{xiaoche_bianhao}后退，等待回到停车位");
                while (shoutie.xiaoche_b1.duqu_weizhi(xiaoche_bianhao, global_var) != 2)//常用车回到停车位
                {
                    if (global_var.over_proj == 1) { return; }
                    Thread.Sleep(100);
                    shoutie.xiaoche_b1.xianche_houtui(xiaoche_bianhao, xiaoche_bianhao, global_var.priority_key, global_var.LineID1, global_var.LineID2, global_var);//向常用车停车位返回
                    if(shoutie.xiaoche_b1.duqu_weizhi(xiaoche_bianhao + 1, global_var) != 1)//返回途中启动了备用车
                    {
                        global_var.zhuangtai_xie(xiaoche_bianhao, 5, $"{xiaoche_bianhao}后退被打断，前进，等待回到等待位");
                        while (shoutie.xiaoche_b1.duqu_weizhi(xiaoche_bianhao, global_var) != 6)//常用车回到等待位
                        {
                            if (global_var.over_proj == 1) { return; }
                            Thread.Sleep(100);
                            shoutie.xiaoche_b1.xianche_qianjing(xiaoche_bianhao, xiaoche_bianhao, global_var.priority_key, global_var.LineID1, global_var.LineID2, global_var);//向常用车停车位返回					
                        }
						shoutie.xiaoche_b1.xianche_tingzhi(xiaoche_bianhao, global_var.LineID1, global_var.LineID2);//刹车，已到达
                        global_var.zhuangtai_xie(xiaoche_bianhao, 5, $"{xiaoche_bianhao}后退被打断，确认已经回到等待位");
                        return;
                    }

                }
                global_var.zhuangtai_xie(xiaoche_bianhao, 5, $"{xiaoche_bianhao}确认回到停车位");
                shoutie.xiaoche_b1.xianche_tingzhi(xiaoche_bianhao, global_var.LineID1, global_var.LineID2);//刹车，已到达

				return;
            }
            if (xiaoche_bianhao == 2 || xiaoche_bianhao == 4)
            {
                global_var.zhuangtai_xie(xiaoche_bianhao, 5, $"{xiaoche_bianhao}等待备用车先回到停车位");
                while (shoutie.xiaoche_b1.duqu_weizhi(xiaoche_bianhao, global_var) != 1)//备用车回到停车位
                {
                    if (global_var.over_proj == 1) { return; }
                    Thread.Sleep(100);
                    shoutie.xiaoche_b1.xianche_houtui(xiaoche_bianhao, xiaoche_bianhao, global_var.priority_key, global_var.LineID1, global_var.LineID2, global_var);//向常用车停车位返回					
                }
                global_var.zhuangtai_xie(xiaoche_bianhao, 5, $"{xiaoche_bianhao}确认备用车已经先回到停车位");
                shoutie.xiaoche_b1.xianche_tingzhi(xiaoche_bianhao - 1, global_var.LineID1, global_var.LineID2);//刹车，已到达
				global_var.zhuangtai_xie(xiaoche_bianhao, 5, $"{xiaoche_bianhao}后退，备用车等待常用车回到停车位");
                while (shoutie.xiaoche_b1.duqu_weizhi(xiaoche_bianhao-1, global_var) != 2)//常用车回停车位
                {
                    if (global_var.over_proj == 1) { return; }
                    Thread.Sleep(100);
                    shoutie.xiaoche_b1.xianche_houtui(xiaoche_bianhao-1, xiaoche_bianhao, global_var.priority_key, global_var.LineID1, global_var.LineID2, global_var);//向常用车停车位返回					
                }
                global_var.zhuangtai_xie(xiaoche_bianhao, 5, $"{xiaoche_bianhao}备用车确认常用车回到停车位");
                shoutie.xiaoche_b1.xianche_tingzhi(xiaoche_bianhao-1, global_var.LineID1, global_var.LineID2);//刹车，已到达

			}



        }
		
	}


}
