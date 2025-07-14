
using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
//using System.Threading.Tasks;
using System.Threading;
using System.Timers;
using System.Windows.Forms;
using shoutie;
using System.Drawing;

namespace shoutie
{
	public class AffectedIron//受铁
	{
		//定时器变量定义处	
		//	static System.Timers.Timer timer1;//液面检测定时器




		//窗体变量定义处
		public shoutie_chuangti.CustomMessageBox3 customMessageBox = new shoutie_chuangti.CustomMessageBox3();//双按钮窗体
		public shoutie_chuangti.CustomMessageBox customMessageBox1 = new shoutie_chuangti.CustomMessageBox();//单按钮窗体

		//窗体变量定义处
		public void chushihuao(object global_var, int CarNum)//初始化程序
		{
			shoutie.global_var global_var1 = (shoutie.global_var)global_var;
			// if (  ((float)global_var1.zhuangtai_du(CarNum,2) ==2&&(CarNum==1|| CarNum == 3))  || ((float)global_var1.zhuangtai_du(CarNum, 2) == 1 && (CarNum == 2 || CarNum == 4)))
			{
				// if ((int)global_var1.zhuangtai_du(CarNum, 1) == 1&& (int)global_var1.zhuangtai_du(CarNum, 3)==0)//车上_have_can子,没铁水
				{
					Thread zhuchengxu = new Thread(() => MyThreadMethod(global_var, CarNum));
					zhuchengxu.Start();//启动主线程	
				}
			}

		}

		public void MyThreadMethod(object global_var1, int CarNum)//主程序
		{

			shoutie.global_var global_var = (shoutie.global_var)global_var1;
			int xiaoche_bianhao = CarNum;
			global_var.cans = global_var.cans + 1;

			if (global_var.over_proj == 1) { return; }
			Thread.Sleep(1000);
			if (xiaoche_bianhao == 2)
			{
				global_var.priority_key = global_var.priority_key | 0b01;//低位置1
				xiaoche_b1.xianche_tingzhi(1, global_var.LineID1, global_var.LineID2);
			}//当前是轨道1备用车，期间要锁定轨道1常用车移动的线程
			if (xiaoche_bianhao == 4)
			{
				global_var.priority_key = global_var.priority_key | 0b10;//高位置1
				xiaoche_b1.xianche_tingzhi(3, global_var.LineID1, global_var.LineID2);
			}//当前是轨道2备用车，期间要锁定轨道2常用车移动的线程
			global_var.zhuangtai_xie(xiaoche_bianhao, 5, $"等待{xiaoche_bianhao}到达受铁位");

			if ((float)global_var.zhuangtai_du(xiaoche_bianhao, 2) < global_var.zuobiao_huoqu(xiaoche_bianhao, 2))//受铁位坐标的编号是2
			{
				while (xiaoche_b1.duqu_weizhi(xiaoche_bianhao, global_var) != 2 )//等待车归位
				{
					xiaoche_b1.xianche_qianjing(xiaoche_bianhao, xiaoche_bianhao, global_var.priority_key, global_var.LineID1, global_var.LineID2, global_var);
					if (global_var.over_proj == 1) { return; }
					Thread.Sleep(500);
				}
			}
			else 
			{
				while (xiaoche_b1.duqu_weizhi(xiaoche_bianhao, global_var) != 2 )//等待车归位
				{
					xiaoche_b1.xianche_houtui(xiaoche_bianhao, xiaoche_bianhao, global_var.priority_key, global_var.LineID1, global_var.LineID2, global_var);
					if (global_var.over_proj == 1) { return; }
					Thread.Sleep(500);
				}
			}
            xiaoche_b1.xianche_tingzhi(xiaoche_bianhao, global_var.LineID1, global_var.LineID2);
			global_var.zhuangtai_xie(xiaoche_bianhao, 5, $"{xiaoche_bianhao}已经到达受铁位，锁车");
			global_var.zhuangtai_xie(xiaoche_bianhao,12,1);//锁车
			if (xiaoche_bianhao == 2)
			{
				global_var.priority_key = global_var.priority_key & 10;//低位置0
			}//当前是备用车，解除锁定常用车移动的线程

			if (xiaoche_bianhao == 4)
			{
				global_var.priority_key = global_var.priority_key & 01;//高位置0
			}//当前是备用车，解除锁定常用车移动的线程
			if (global_var.over_proj == 1) { return; }
            int xintiao_jishu=0;
			global_var.zhuangtai_xie(xiaoche_bianhao, 5, $"等待{xiaoche_bianhao}受铁心跳");
		//	while (receve_iron.xintiao(global_var.LineID1, global_var.LineID2) != 1)//心跳判断
			//{
            //    xintiao_jishu = receve_iron.xintiao(global_var.LineID1, global_var.LineID2) + xintiao_jishu;

           //     if (global_var.over_proj == 1) { return; }
			//	Thread.Sleep(500);
			//}

			if (global_var.over_proj == 1) { return; }
			if (global_var.first_can == 1)//first_can，记得清零
			{
				global_var.chute_allow = 0;
				if (global_var.over_proj == 1) { return; }
				receve_iron.liucao_baidong(xiaoche_bianhao, global_var.LineID1, global_var.LineID2);//溜槽选择方向,xiaoche_bianhao是1或2摆一个方向，3或4摆一个方向
				global_var.first_can = 0;
			}
			else//不是first_can
			{
				global_var.zhuangtai_xie(xiaoche_bianhao, 5, $"{xiaoche_bianhao}等待溜槽摆动命令");
				while (global_var.chute_allow != 1) //等待对侧受铁完毕后的溜槽摆动命令
				{
					if (global_var.over_proj == 1) { return; }
					Thread.Sleep(100);
				}
				global_var.chute_allow = 0;
				receve_iron.liucao_baidong(xiaoche_bianhao, global_var.LineID1, global_var.LineID2);//溜槽选择方向,xiaoche_bianhao是1或2摆一个方向，3或4摆一个方向
			}
			global_var.zhuangtai_xie(xiaoche_bianhao, 5, $"{xiaoche_bianhao}等待溜槽摆动到指定位置");
			while (receve_iron.du_liucao_baidong_wancheng(xiaoche_bianhao, global_var.LineID1, global_var.LineID2) != 1)//等待溜槽摆动到指定位置
			{

				if (global_var.over_proj == 1) { return; }
				Thread.Sleep(100);
			}
            global_var.zhuangtai_xie(xiaoche_bianhao, 5, $"{xiaoche_bianhao}溜槽已经摆动到指定位置");
            if (global_var.over_proj == 1) { return; }
			global_var.zhuangtai_xie(xiaoche_bianhao, 5, $"{xiaoche_bianhao}等待操作员确认溜槽摆动的方向正确");
			while (customMessageBox1.i == 0)//读操作员—方向确认
			{
                customMessageBox1.Text = $"{xiaoche_bianhao}操作员确认溜槽摆动的方向正确";
                try { customMessageBox1.ShowDialog(); } catch { }
				if (global_var.over_proj == 1) { return; }
			}
            global_var.zhuangtai_xie(xiaoche_bianhao, 5, $"{xiaoche_bianhao}操作员已经确认溜槽摆动的方向正确");
            // 注入贴水
            if (global_var.over_proj == 1) { return; }

			diaoguan_yidong.Diaoguan_yidong diaoguan = new diaoguan_yidong.Diaoguan_yidong();
			diaoguan.MyThreadMethod(global_var1, xiaoche_bianhao);


		}

	}//主程序//////////////////////////////////////////////////////////////////////////////////////////////////
	public class global_var//全局变量
	{
		public int priority_key = 0;//优先级
		public int cans = 0;//罐数
		public int chute_allow;//溜槽摆动授权
		public int over_proj;//结束

		public int first_can = 1;//首罐
		public int LineID1 = 16;//轨道号1
		public int LineID2 = 17;//轨道号2
		public float  position_differ_qianjing = 1;//前进时的位置差值
		public float position_differ_houtui =1;//后退时的位置差值

		public float b1_position;//b1_position
		public float b2_position;
		public float b3_position;
		public float b4_position;

		public int b1_luck;//锁车标记，为1锁车
		public int b2_luck;//锁车标记，为1锁车
		public int b3_luck;//锁车标记，为1锁车
		public int b4_luck;//锁车标记，为1锁车

		public int b1_position_num;//b1_position编号
		public int b2_position_num;//b1_position编号
		public int b3_position_num;//b3_position编号
		public int b4_position_num;

		public int b1_qianjing_zhuangtai = 1;//车的前进状态，为1表示车最近的状态是前进
		public int b2_qianjing_zhuangtai = 1;
		public int b3_qianjing_zhuangtai = 1;
		public int b4_qianjing_zhuangtai = 1;


		public int b1_have_can = 1;//b1有罐
		public int b2_have_can = 1;
		public int b3_have_can = 1;
		public int b4_have_can = 1;

		public int b1_have_iron;//有铁水
		public int b2_have_iron;
		public int b3_have_iron;
		public int b4_have_iron;

		public int b1zengzai_shoutie;//正在受铁
		public int b2zengzai_shoutie;
		public int b3zengzai_shoutie;
		public int b4zengzai_shoutie;

		public string b1curent_mession;//b1当前任务
		public string b2curent_mession;
		public string b3curent_mession;
		public string b4curent_mession;

		public string b1wait_state;//等待状态
		public string b2wait_state;
		public string b3wait_state;
		public string b4wait_state;

		public int b1bzd_stop;//半自动停车
		public int b2bzd_stop;
		public int b3bzd_stop;
		public int b4bzd_stop;

		public int b1bzd_busy;//半自动线程忙标志
		public int b2bzd_busy;
		public int b3bzd_busy;
		public int b4bzd_busy;

		public float erro_b1;//车位置矫正,编码器的
		public float erro_b2;
		public float erro_b3;
		public float erro_b4;

		public float jerro_b1;//车位置矫正,激光测距用的
		public float jerro_b2;
		public float jerro_b3;
		public float jerro_b4;

		public float g1b1_shoutiewei_zuobiao = weizhi.weizhi.g1b1_e2;//车位置坐标，用户输入，轨道1常用车
		public float g1b1_dengdaiwei_zuobiao = weizhi.weizhi.g1b1_e6;
		public float g1b1_diaoguanwei_zuobiao = weizhi.weizhi.g1b1_e9;
		public float g1b1_kuadiaowei_zuobiao = weizhi.weizhi.g1b1_e10;
		public float g1b1_beiyongche_tingchewei_zuobiao = weizhi.weizhi.g1b1_e1;

		public float g1b2_shoutiewei_zuobiao = weizhi.weizhi.g1b2_e2;//车位置坐标，用户输入，轨道1备用车
		public float g1b2_dengdaiwei_zuobiao = weizhi.weizhi.g1b2_e6;
		public float g1b2_diaoguanwei_zuobiao = weizhi.weizhi.g1b2_e9;
		public float g1b2_kuadiaowei_zuobiao = weizhi.weizhi.g1b2_e10;
		public float g1b2_beiyongche_tingchewei_zuobiao = weizhi.weizhi.g1b2_e1;

		public float g2b1_shoutiewei_zuobiao = weizhi.weizhi.g2b1_e2;//车位置坐标，用户输入，轨道2常用车
		public float g2b1_dengdaiwei_zuobiao = weizhi.weizhi.g2b1_e6;
		public float g2b1_diaoguanwei_zuobiao = weizhi.weizhi.g2b1_e9;
		public float g2b1_kuadiaowei_zuobiao = weizhi.weizhi.g2b1_e10;
		public float g2b1_beiyongche_tingchewei_zuobiao = weizhi.weizhi.g2b1_e1;

		public float g2b2_shoutiewei_zuobiao = weizhi.weizhi.g2b2_e2;//车位置坐标，用户输入，轨道2备用车
		public float g2b2_dengdaiwei_zuobiao = weizhi.weizhi.g2b2_e6;
		public float g2b2_diaoguanwei_zuobiao = weizhi.weizhi.g2b2_e9;
		public float g2b2_kuadiaowei_zuobiao = weizhi.weizhi.g2b2_e10;
		public float g2b2_beiyongche_tingchewei_zuobiao = weizhi.weizhi.g2b2_e1;

		//public HKVisionCamera M_ca1 = null;//17#1号相机
		//public HKVisionCamera M_ca2 = null;//17#2号相机
		//public HKVisionCamera M_ca3 = null;//17#3号相机
		//public HKVisionCamera M_ca4 = null;//16
		//public HKVisionCamera M_ca5 = null;
		//public HKVisionCamera M_ca6 = null;
		public float  zuobiao_huoqu(int chehao,int weizhi1)
		{

         g1b1_shoutiewei_zuobiao = weizhi.weizhi.g1b1_e2;//车位置坐标，用户输入，轨道1常用车
      g1b1_dengdaiwei_zuobiao = weizhi.weizhi.g1b1_e6;
       g1b1_diaoguanwei_zuobiao = weizhi.weizhi.g1b1_e9;
        g1b1_kuadiaowei_zuobiao = weizhi.weizhi.g1b1_e10;
       g1b1_beiyongche_tingchewei_zuobiao = weizhi.weizhi.g1b1_e1;

       g1b2_shoutiewei_zuobiao = weizhi.weizhi.g1b2_e2;//车位置坐标，用户输入，轨道1备用车
       g1b2_dengdaiwei_zuobiao = weizhi.weizhi.g1b2_e6;
        g1b2_diaoguanwei_zuobiao = weizhi.weizhi.g1b2_e9;
        g1b2_kuadiaowei_zuobiao = weizhi.weizhi.g1b2_e10;
       g1b2_beiyongche_tingchewei_zuobiao = weizhi.weizhi.g1b2_e1;

        g2b1_shoutiewei_zuobiao = weizhi.weizhi.g2b1_e2;//车位置坐标，用户输入，轨道2常用车
         g2b1_dengdaiwei_zuobiao = weizhi.weizhi.g2b1_e6;
       g2b1_diaoguanwei_zuobiao = weizhi.weizhi.g2b1_e9;
        g2b1_kuadiaowei_zuobiao = weizhi.weizhi.g2b1_e10;
         g2b1_beiyongche_tingchewei_zuobiao = weizhi.weizhi.g2b1_e1;

       g2b2_shoutiewei_zuobiao = weizhi.weizhi.g2b2_e2;//车位置坐标，用户输入，轨道2备用车
        g2b2_dengdaiwei_zuobiao = weizhi.weizhi.g2b2_e6;
        g2b2_diaoguanwei_zuobiao = weizhi.weizhi.g2b2_e9;
        g2b2_kuadiaowei_zuobiao = weizhi.weizhi.g2b2_e10;
        g2b2_beiyongche_tingchewei_zuobiao = weizhi.weizhi.g2b2_e1;
            switch (chehao)
			{
				case 1:switch (weizhi1) 
						{
						case 1:return g1b1_beiyongche_tingchewei_zuobiao;
						case 2:return g1b1_shoutiewei_zuobiao;
						case 3:return g1b1_dengdaiwei_zuobiao;
						case 4:return g1b1_diaoguanwei_zuobiao;
						case 5:return g1b1_kuadiaowei_zuobiao;
						}
					break;
				case 2:
					switch (weizhi1)
					{
						case 1: return g1b2_beiyongche_tingchewei_zuobiao;
						case 2: return g1b2_shoutiewei_zuobiao;
						case 3: return g1b2_dengdaiwei_zuobiao;
						case 4: return g1b2_diaoguanwei_zuobiao;
						case 5: return g1b2_kuadiaowei_zuobiao;
					}
					break;
				case 3:
					switch (weizhi1)
					{
						case 1: return g2b1_beiyongche_tingchewei_zuobiao;
						case 2: return g2b1_shoutiewei_zuobiao;
						case 3: return g2b1_dengdaiwei_zuobiao;
						case 4: return g2b1_diaoguanwei_zuobiao;
						case 5: return g2b1_kuadiaowei_zuobiao;
					}
					break;
				case 4:
					switch (weizhi1)
					{
						case 1: return g2b2_beiyongche_tingchewei_zuobiao;
						case 2: return g2b2_shoutiewei_zuobiao;
						case 3: return g2b2_dengdaiwei_zuobiao;
						case 4: return g2b2_diaoguanwei_zuobiao;
						case 5: return g2b2_kuadiaowei_zuobiao;
					}
					break;
			}
			return 0;

		}

		public void zhuangtai_xie(int chehao, int xuhao, object neirong)
		{
			switch (chehao)
			{
				case 1:
					switch (xuhao)
					{
						case 1:
							b1_have_can = (int)neirong; break;
						case 2:
							b1_position = (float)neirong; break;
						case 3:
							b1_have_iron = (int)neirong; break;
						case 4:
							b1curent_mession = (string)neirong; break;
						case 5:
							b1wait_state = (string)neirong; break;
						case 6:
							b1_position_num = (int)neirong; break;
						case 7:
							b1zengzai_shoutie = (int)neirong; break;
						case 8:
							b1bzd_stop = (int)neirong; break;
						case 9:
							b1bzd_busy = (int)neirong; break;
						case 10:
							erro_b1 = (float)neirong; break;
						case 11:
							jerro_b1 = (float)neirong; break;
						case 12:
							b1_luck = (int )neirong; break;
					}
					break;
				case 2:
					switch (xuhao)
					{
						case 1:
							b2_have_can = (int)neirong; break;
						case 2:
							b2_position = (float)neirong; break;
						case 3:
							b2_have_iron = (int)neirong; break;
						case 4:
							b2curent_mession = (string)neirong; break;
						case 5:
							b2wait_state = (string)neirong; break;
						case 6:
							b2_position_num = (int)neirong; break;
						case 7:
							b2zengzai_shoutie = (int)neirong; break;
						case 8:
							b2bzd_stop = (int)neirong; break;
						case 9:
							b2bzd_busy = (int)neirong; break;
						case 10:
							erro_b2 = (float)neirong; break;
						case 11:
							jerro_b2 = (float)neirong; break;
						case 12:
							b2_luck = (int)neirong; break;
					}
					break;
				case 3:
					switch (xuhao)
					{
						case 1:
							b3_have_can = (int)neirong; break;
						case 2:
							b3_position = (float)neirong; break;
						case 3:
							b3_have_iron = (int)neirong; break;
						case 4:
							b3curent_mession = (string)neirong; break;
						case 5:
							b3wait_state = (string)neirong; break;
						case 6:
							b3_position_num = (int)neirong; break;
						case 7:
							b3zengzai_shoutie = (int)neirong; break;
						case 8:
							b3bzd_stop = (int)neirong; break;
						case 9:
							b3bzd_busy = (int)neirong; break;
						case 10:
							erro_b3 = (float)neirong; break;
						case 11:
							jerro_b3 = (float)neirong; break;
						case 12:
							b3_luck = (int)neirong; break;
					}
					break;
				case 4:
					switch (xuhao)
					{
						case 1:
							b4_have_can = (int)neirong; break;
						case 2:
							b4_position = (float)neirong; break;
						case 3:
							b4_have_iron = (int)neirong; break;
						case 4:
							b4curent_mession = (string)neirong; break;
						case 5:
							b4wait_state = (string)neirong; break;
						case 6:
							b4_position_num = (int)neirong; break;
						case 7:
							b4zengzai_shoutie = (int)neirong; break;
						case 8:
							b4bzd_stop = (int)neirong; break;
						case 9:
							b4bzd_busy = (int)neirong; break;
						case 10:
							erro_b4 = (float)neirong; break;
						case 11:
							jerro_b4 = (float)neirong; break;
						case 12:
							b4_luck = (int)neirong; break;
					}
					break;
			}
		}
		public object zhuangtai_du(int chehao, int xuhao)
		{
			switch (chehao)
			{
				case 1:
					switch (xuhao)
					{
						case 1:
							return b1_have_can; break;
						case 2:
							return b1_position; break;
						case 3:
							return b1_have_iron; break;
						case 4:
							return b1curent_mession; break;
						case 5:
							return b1wait_state; break;
						case 6:
							return b1_position_num; break;
						case 7:
							return b1zengzai_shoutie; break;
						case 8:
							return b1bzd_stop; break;
						case 9:
							return b1bzd_busy; break;
						case 10:
							return erro_b1; break;
						case 11:
							return jerro_b1; break;
						case 12:
							return b1_luck ; break;
					}
					break;
				case 2:
					switch (xuhao)
					{
						case 1:
							return b2_have_can; break;
						case 2:
							return b2_position; break;
						case 3:
							return b2_have_iron; break;
						case 4:
							return b2curent_mession; break;
						case 5:
							return b2wait_state; break;
						case 6:
							return b2_position_num; break;
						case 7:
							return b2zengzai_shoutie; break;
						case 8:
							return b2bzd_stop; break;
						case 9:
							return b2bzd_busy; break;
						case 10:
							return erro_b2; break;
						case 11:
							return jerro_b2; break;
						case 12:
							return b2_luck; break;
					}
					break;
				case 3:
					switch (xuhao)
					{
						case 1:
							return b3_have_can; break;
						case 2:
							return b3_position; break;
						case 3:
							return b3_have_iron; break;
						case 4:
							return b3curent_mession; break;
						case 5:
							return b3wait_state; break;
						case 6:
							return b3_position_num; break;
						case 7:
							return b3zengzai_shoutie; break;
						case 8:
							return b3bzd_stop; break;
						case 9:
							return b3bzd_busy; break;
						case 10:
							return erro_b3; break;
						case 11:
							return jerro_b3; break;
						case 12:
							return b3_luck; break;
					}
					break;
				case 4:
					switch (xuhao)
					{
						case 1:
							return b4_have_can; break;
						case 2:
							return b4_position; break;
						case 3:
							return b4_have_iron; break;
						case 4:
							return b4curent_mession; break;
						case 5:
							return b4wait_state; break;
						case 6:
							return b4_position_num; break;
						case 7:
							return b4zengzai_shoutie; break;
						case 8:
							return b4bzd_stop; break;
						case 9:
							return b4bzd_busy; break;
						case 10:
							return erro_b4; break;
						case 11:
							return jerro_b4; break;
						case 12:
							return b4_luck; break;
					}
					break;
			}
			return -1;
		}
	}

}


