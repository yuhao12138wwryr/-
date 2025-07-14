
//using shoutie;
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

	namespace guanchedida//抵达吊包位

	{

		public class diaoguan
		{
			//定时器变量定义处	

			//线程变量定义处
			private Thread zhuchengxu;//主程序线程
											//窗体变量定义处
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
			int xiaoche_bianhao = CarNum;
            if (global_var.over_proj == 1) { return; }
            Thread.Sleep(100);
            int weizhi = 0;
            global_var.zhuangtai_xie(xiaoche_bianhao, 5, $"{xiaoche_bianhao}等待到达等待位前面");
            while ( weizhi != 4)//当前的车到达等待位前面，B1或B2
			{              
                weizhi = shoutie.xiaoche_b1.duqu_weizhi(xiaoche_bianhao, global_var);//获取位置，这里不区分常用车还是备用车
                shoutie.xiaoche_b1.xianche_qianjing(xiaoche_bianhao, xiaoche_bianhao, global_var.priority_key, global_var.LineID1, global_var.LineID2, global_var);
                if (global_var.over_proj == 1) { return; }
					Thread.Sleep(1000);
			}
            global_var.zhuangtai_xie(xiaoche_bianhao, 5, $"{xiaoche_bianhao}已经到达等待位前面");
            shoutie.xiaoche_b1.xianche_tingzhi(xiaoche_bianhao, global_var.LineID1, global_var.LineID2);//刹车
			if (xiaoche_bianhao == 1|| xiaoche_bianhao == 3)//当前车为常用车
				{
					if (shijue.shijue_diaoguanwei(xiaoche_bianhao, global_var) == 0)//吊罐位不空闲
					{
						customMessageBox1.i = 0;
						while (customMessageBox1.i == 0)//操作员确认吊罐位被占
						{
							customMessageBox1.Text = $"{xiaoche_bianhao}确认吊罐位占用？";
							try { customMessageBox1.ShowDialog(); } catch { }
							if (global_var.over_proj == 1) { return; }
							Thread.Sleep(100);
						}

                    global_var.zhuangtai_xie(xiaoche_bianhao, 5, $"{xiaoche_bianhao}等待到达等待位");
                    while (shoutie.xiaoche_b1.duqu_weizhi(xiaoche_bianhao, global_var) != 6)//等待小车1到达等待位
					{
                        
                        shoutie.xiaoche_b1.xianche_qianjing(xiaoche_bianhao, xiaoche_bianhao, global_var.priority_key, global_var.LineID1, global_var.LineID2, global_var);
						if (global_var.over_proj == 1) { return; }
							Thread.Sleep(1000);
						}
					shoutie.xiaoche_b1.xianche_tingzhi(xiaoche_bianhao, global_var.LineID1, global_var.LineID2);//刹车
						while (shijue.shijue_diaoguanwei(xiaoche_bianhao, global_var) == 0)//视觉检测，等待吊罐位空闲
						{
							if (global_var.over_proj == 1) { return; }
							Thread.Sleep(1000);
						}
					}
					customMessageBox1.i = 0;
					while (customMessageBox1.i == 0)//操作员确认吊罐位空闲
					{
						customMessageBox1.Text = $"{xiaoche_bianhao}确认吊罐位空闲？";
						try { customMessageBox1.ShowDialog(); } catch { }
						if (global_var.over_proj == 1) { return; }
						Thread.Sleep(100);
					}

                global_var.zhuangtai_xie(xiaoche_bianhao, 5, $"{xiaoche_bianhao}等待到达吊罐位");
                while (shoutie.xiaoche_b1.duqu_weizhi(xiaoche_bianhao, global_var) != 9)//等待小车到达吊罐位
					{
                 
                    shoutie.xiaoche_b1.xianche_qianjing(xiaoche_bianhao, xiaoche_bianhao, global_var.priority_key, global_var.LineID1, global_var.LineID2, global_var);
					if (global_var.over_proj == 1) { return; }
						Thread.Sleep(1000);
					}
				shoutie.xiaoche_b1.xianche_tingzhi(xiaoche_bianhao, global_var.LineID1, global_var.LineID2);//刹车，已到达


				}
				if (xiaoche_bianhao == 2|| xiaoche_bianhao == 4)//当前车为备用车
			{
                global_var.zhuangtai_xie(xiaoche_bianhao, 5, $"{xiaoche_bianhao}备用车等待常用车到达等待位");
                while (shoutie.xiaoche_b1.duqu_weizhi(xiaoche_bianhao - 1, global_var) != 6)//等待常用车到达等待位，这里不控制前进，是常用车线程控制的
                {           
                    if (global_var.over_proj == 1) { return; }
                    Thread.Sleep(1000);
                }
                global_var.zhuangtai_xie(xiaoche_bianhao, 5, $"{xiaoche_bianhao}备用车确认了常用车已经到达等待位");
                global_var.zhuangtai_xie(xiaoche_bianhao, 5, $"{xiaoche_bianhao}备用车等待常用车到达吊罐位前面");
                while (shoutie.xiaoche_b1.duqu_weizhi(xiaoche_bianhao-1, global_var) != 8)//等待常用车到达吊罐位之前的一个地方
				{                    
                    shoutie.xiaoche_b1.xianche_qianjing(xiaoche_bianhao-1, xiaoche_bianhao, global_var.priority_key, global_var.LineID1, global_var.LineID2, global_var);
					if (global_var.over_proj == 1) { return; }
						Thread.Sleep(1000);
				}
                global_var.zhuangtai_xie(xiaoche_bianhao, 5, $"{xiaoche_bianhao}备用车确认了常用车已经到达吊罐位前面");

                shoutie.xiaoche_b1.xianche_tingzhi(xiaoche_bianhao - 1, global_var.LineID1, global_var.LineID2);//刹车，已到达
				if (shijue.shijue_diaoguanwei(xiaoche_bianhao, global_var) == 0)//视觉检测吊罐位，0占用
				    {
					shoutie.xiaoche_b1.xianche_tingzhi(xiaoche_bianhao-1, global_var.LineID1, global_var.LineID2);//1刹车
						customMessageBox1.i = 0;
                    global_var.zhuangtai_xie(xiaoche_bianhao, 5, $"{xiaoche_bianhao}等待操作员确认吊罐位不空闲");
                    while (customMessageBox1.i == 0)//操作员确认吊罐位不空闲
						{
							customMessageBox1.Text = $"{xiaoche_bianhao}确认吊罐位占用？";
							try { customMessageBox1.ShowDialog(); } catch { }
							if (global_var.over_proj == 1) { return; }
							Thread.Sleep(100);
						}
                    global_var.zhuangtai_xie(xiaoche_bianhao, 5, $"{xiaoche_bianhao}操作员确认吊罐位不空闲");
                    global_var.zhuangtai_xie(xiaoche_bianhao, 5, $"{xiaoche_bianhao}等待视觉检测吊罐位不空闲");
                    while (shijue.shijue_diaoguanwei(xiaoche_bianhao, global_var) == 0)//视觉检测，等待吊罐位空闲
						{
							if (global_var.over_proj == 1) { return; }
							Thread.Sleep(1000);
						}
                    global_var.zhuangtai_xie(xiaoche_bianhao, 5, $"{xiaoche_bianhao}视觉检测确认吊罐位不空闲");
                }
					customMessageBox1.i = 0;
                global_var.zhuangtai_xie(xiaoche_bianhao, 5, $"{xiaoche_bianhao}等待操作员确认吊罐位空闲");
                while (customMessageBox1.i == 0)//操作员确认吊罐位空闲
					{
						customMessageBox1.Text = $"{xiaoche_bianhao}确认吊罐位空闲？";
						try { customMessageBox1.ShowDialog(); } catch { }
						if (global_var.over_proj == 1) { return; }
						Thread.Sleep(100);
					}
                global_var.zhuangtai_xie(xiaoche_bianhao, 5, $"{xiaoche_bianhao}操作员确认吊罐位空闲");
                global_var.zhuangtai_xie(xiaoche_bianhao, 5, $"{xiaoche_bianhao}备用车等待常用车到达吊罐位");
                while (shoutie.xiaoche_b1.duqu_weizhi(xiaoche_bianhao-1, global_var) != 9)//等待小车到达吊罐位
					{
					shoutie.xiaoche_b1.xianche_qianjing(xiaoche_bianhao-1, xiaoche_bianhao, global_var.priority_key, global_var.LineID1, global_var.LineID2, global_var);
					if (global_var.over_proj == 1) { return; }
						Thread.Sleep(1000);
					}
                global_var.zhuangtai_xie(xiaoche_bianhao, 5, $"{xiaoche_bianhao}备用车确认常用车已经到达吊罐位");
                shoutie.xiaoche_b1.xianche_tingzhi(xiaoche_bianhao-1, global_var.LineID1, global_var.LineID2);//1已经到达吊罐位
                global_var.zhuangtai_xie(xiaoche_bianhao, 5, $"{xiaoche_bianhao}等待到达吊罐位前面");
                while (shoutie.xiaoche_b1.duqu_weizhi(xiaoche_bianhao, global_var) != 8)//等待小车2到达吊罐位之前的一个地方
				{
					shoutie.xiaoche_b1.xianche_qianjing(xiaoche_bianhao, xiaoche_bianhao, global_var.priority_key, global_var.LineID1, global_var.LineID2, global_var);//2前进
					if (global_var.over_proj == 1) { return; }
						Thread.Sleep(1000);
				}
                global_var.zhuangtai_xie(xiaoche_bianhao, 5, $"{xiaoche_bianhao}已经到达吊罐位前面");
                shoutie.xiaoche_b1.xianche_tingzhi(xiaoche_bianhao, global_var.LineID1, global_var.LineID2);//小车2已经到达吊罐位之前的一个地方
					if (shijue.shijue_kuadiaowei(xiaoche_bianhao,  global_var) == 0)//视觉检测，等待跨吊位占用
					{
						customMessageBox1.i = 0;
                    global_var.zhuangtai_xie(xiaoche_bianhao, 5, $"{xiaoche_bianhao}等待操作员确认跨吊位占用");
                    while (customMessageBox1.i == 0)//操作员确认跨吊位占用
						{
							customMessageBox1.Text = $"{xiaoche_bianhao}确认跨吊罐位占用？";
							try { customMessageBox1.ShowDialog(); } catch { }
							if (global_var.over_proj == 1) { return; }
							Thread.Sleep(100);
						}
						while (shijue.shijue_kuadiaowei(xiaoche_bianhao,  global_var) != 0)//视觉检测，等待跨吊位空闲
						{
							if (global_var.over_proj == 1) { return; }
							Thread.Sleep(1000);
						}
					}
					customMessageBox1.i = 0;
                global_var.zhuangtai_xie(xiaoche_bianhao, 5, $"{xiaoche_bianhao}等待操作员确认跨吊位空闲");
                while (customMessageBox1.i == 0)//操作员确认跨吊位空闲
					{
						customMessageBox1.Text = $"{xiaoche_bianhao}确认跨吊罐位空闲？";
						try { customMessageBox1.ShowDialog(); } catch { }
						if (global_var.over_proj == 1) { return; }
						Thread.Sleep(100);
					}
				customMessageBox1.Text = $"{xiaoche_bianhao-1}将向跨吊位前进";
				try { customMessageBox1.ShowDialog(); } catch { }
                global_var.zhuangtai_xie(xiaoche_bianhao, 5, $"{xiaoche_bianhao}备用车等待常用车到达跨吊位");
                while (shoutie.xiaoche_b1.duqu_weizhi(xiaoche_bianhao-1, global_var) != 10)//等待常用车到达跨吊位
					{
					shoutie.xiaoche_b1.xianche_qianjing(xiaoche_bianhao-1, xiaoche_bianhao, global_var.priority_key, global_var.LineID1, global_var.LineID2, global_var);//1前进
					if (global_var.over_proj == 1) { return; }
						Thread.Sleep(1000);
					}
                global_var.zhuangtai_xie(xiaoche_bianhao, 5, $"{xiaoche_bianhao}备用车确认常用车到达跨吊位");
                shoutie.xiaoche_b1.xianche_tingzhi(xiaoche_bianhao-1, global_var.LineID1, global_var.LineID2);//小车1已经到达跨吊位

				customMessageBox1.Text = $"{xiaoche_bianhao}将向吊罐位前进";
				try { customMessageBox1.ShowDialog(); } catch { }
                global_var.zhuangtai_xie(xiaoche_bianhao, 5, $"{xiaoche_bianhao}等待到达吊罐位");
                while (shoutie.xiaoche_b1.duqu_weizhi(xiaoche_bianhao, global_var) != 9)//等待小车2到达吊罐位
				{
					shoutie.xiaoche_b1.xianche_qianjing(xiaoche_bianhao, xiaoche_bianhao, global_var.priority_key, global_var.LineID1, global_var.LineID2, global_var);//2前进
					if (global_var.over_proj == 1) { return; }
						Thread.Sleep(1000);
				}
                global_var.zhuangtai_xie(xiaoche_bianhao, 5, $"{xiaoche_bianhao}已经到达吊罐位");

                shoutie.xiaoche_b1.xianche_tingzhi(xiaoche_bianhao, global_var.LineID1, global_var.LineID2);//小车2已经到达吊罐位
				}
			diaoli.diaoli diaoli1 = new diaoli.diaoli();
			diaoli1.MyThreadMethod(global_var1, xiaoche_bianhao);
		}

		}


	}
