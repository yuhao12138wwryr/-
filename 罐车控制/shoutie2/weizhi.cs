using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Timers;
using System.Threading;
using shoutie;
using System.Windows.Forms;
using Microsoft.Win32;
using System.Data;

namespace weizhi
{

	public class weizhi//更新车的位置
	{
		System.Timers.Timer timer2;//定时器
		weizhi_huoqu weizhi_huoqu = new weizhi_huoqu();
		shoutie.global_var global_var2 = new global_var();
		private Thread jianshi;//定时器监视线程
		public void chushihuao(object global_var1)//初始化程序
		{
			global_var2 = (shoutie.global_var)global_var1;
			weizhi_huoqu.guidao1 = global_var2.LineID1;
			weizhi_huoqu.guidao2 = global_var2.LineID2;

			//定时器2,位置获取,轨道1，b1
			timer2 = new System.Timers.Timer();
			timer2.Interval = 1000;
			timer2.Elapsed += weizhi_dingshiqi;
			timer2.Enabled = true;
			//定时器2,位置获取,轨道1，b1


			jianshi = new Thread(TimerCallback);//启动控制线程
			jianshi.Start(global_var1);//启动控制线程	

		}

		private void TimerCallback(object global_var1)
		{
			shoutie.global_var global_var = (shoutie.global_var)global_var1;


			if (global_var.over_proj == 1)
			{
				timer2.Close();
				return;
			}
			if (weizhi_huoqu.weizhi_g1_b1 == -1)
			{
				shoutie_chuangti.CustomMessageBox customMessageBox1 = new shoutie_chuangti.CustomMessageBox();//单按钮窗体
				try
				{
					customMessageBox1.ClientSize = new System.Drawing.Size(705, 385);
					customMessageBox1.Text = "小车轨道1常用车位置获取异常，请确认传感器状况";
					customMessageBox1.ShowDialog();
				}
				catch { }
			}
			if (weizhi_huoqu.weizhi_g1_b2 == -1)
			{
				shoutie_chuangti.CustomMessageBox customMessageBox1 = new shoutie_chuangti.CustomMessageBox();//单按钮窗体
				try
				{
					customMessageBox1.ClientSize = new System.Drawing.Size(705, 385);
					customMessageBox1.Text = "小车轨道1备用车位置获取异常，请确认传感器状况";
					customMessageBox1.ShowDialog();
				}
				catch { }
			}
			if (weizhi_huoqu.weizhi_g2_b1 == -1)
			{
				shoutie_chuangti.CustomMessageBox customMessageBox1 = new shoutie_chuangti.CustomMessageBox();//单按钮窗体
				try
				{
					customMessageBox1.ClientSize = new System.Drawing.Size(705, 385);
					customMessageBox1.Text = "小车轨道2常用车位置获取异常，请确认传感器状况";
					customMessageBox1.ShowDialog();
				}
				catch { }
			}
			if (weizhi_huoqu.weizhi_g2_b2 == -1)
			{
				shoutie_chuangti.CustomMessageBox customMessageBox1 = new shoutie_chuangti.CustomMessageBox();//单按钮窗体
				try
				{
					customMessageBox1.ClientSize = new System.Drawing.Size(705, 385);
					customMessageBox1.Text = "小车轨道2备用车位置获取异常，请确认传感器状况";
					customMessageBox1.ShowDialog();
				}
				catch { }
			}

		}
		private void weizhi_dingshiqi(object sender, ElapsedEventArgs e)
		{
			weizhi_huoqu.weizhi_g1_b1 = weizhi_huoqu.whizhu_huoqu_fun(weizhi_huoqu.jiguangceju(weizhi_huoqu.guidao1, 1), weizhi_huoqu.bianmaqi(weizhi_huoqu.guidao1, 1), weizhi_huoqu.dingweiqi(1, weizhi_huoqu.guidao1, weizhi_huoqu.guidao2), global_var2, 1);
			weizhi_huoqu.weizhi_g1_b2 = weizhi_huoqu.whizhu_huoqu_fun(weizhi_huoqu.jiguangceju(weizhi_huoqu.guidao1, 2), weizhi_huoqu.bianmaqi(weizhi_huoqu.guidao1, 2), weizhi_huoqu.dingweiqi(2, weizhi_huoqu.guidao1, weizhi_huoqu.guidao2), global_var2, 2);
			weizhi_huoqu.weizhi_g2_b1 = weizhi_huoqu.whizhu_huoqu_fun(weizhi_huoqu.jiguangceju(weizhi_huoqu.guidao2, 1), weizhi_huoqu.bianmaqi(weizhi_huoqu.guidao2, 1), weizhi_huoqu.dingweiqi(3, weizhi_huoqu.guidao1, weizhi_huoqu.guidao2), global_var2, 3);
			weizhi_huoqu.weizhi_g2_b2 = weizhi_huoqu.whizhu_huoqu_fun(weizhi_huoqu.jiguangceju(weizhi_huoqu.guidao2, 2), weizhi_huoqu.bianmaqi(weizhi_huoqu.guidao2, 2), weizhi_huoqu.dingweiqi(4, weizhi_huoqu.guidao1, weizhi_huoqu.guidao2), global_var2, 4);
			global_var2.b1_position = weizhi_huoqu.weizhi_g1_b1;
			global_var2.b2_position = weizhi_huoqu.weizhi_g1_b2;
			global_var2.b3_position = weizhi_huoqu.weizhi_g2_b1;
			global_var2.b4_position = weizhi_huoqu.weizhi_g2_b2;
			if (global_var2.b1_qianjing_zhuangtai == 1)//根据是前进还是后退，选择车对应的距离差值
			{
				global_var2.b1_position_num = weizhi_xuhao(global_var2.b1_position, global_var2.position_differ_qianjing,1);
			}
			else
			{
				global_var2.b1_position_num = weizhi_xuhao(global_var2.b1_position, global_var2.position_differ_houtui,1);
			}
			if (global_var2.b2_qianjing_zhuangtai == 1)
			{
				global_var2.b2_position_num = weizhi_xuhao(global_var2.b2_position, global_var2.position_differ_qianjing,2);
			}
			else
			{
				global_var2.b2_position_num = weizhi_xuhao(global_var2.b2_position, global_var2.position_differ_houtui,2);
			}

			if (global_var2.b3_qianjing_zhuangtai == 1)
			{
				global_var2.b3_position_num = weizhi_xuhao(global_var2.b3_position, global_var2.position_differ_qianjing,3);

			}
			else
			{
				global_var2.b3_position_num = weizhi_xuhao(global_var2.b3_position, global_var2.position_differ_houtui,3);
			}
			if (global_var2.b4_qianjing_zhuangtai == 1)
			{
				global_var2.b4_position_num = weizhi_xuhao(global_var2.b4_position, global_var2.position_differ_qianjing,4);

			}
			else
			{
				global_var2.b4_position_num = weizhi_xuhao(global_var2.b4_position, global_var2.position_differ_houtui,4);
			}

		}
		int i11,i12,i13,i14,   i21,i22,i23,i24,    i41,i42,i43,i44,   i61,i62,i63,i64,   i81,i82,i83,i84,    i91,i92,i93,i94,    i101,i102,i103,i104;//对各个状态计算，超过2次才判断进入状态

		static public float g1b1_e1 = 200,     g1b1_e2 =37.77f, g1b1_e4 = 150,   g1b1_e6 = 77.39f, g1b1_e8 = 800,  g1b1_e9 = 100f, g1b1_e10 = 650;//轨道1的坐标数据
		static public float g1b2_e1 = 12.5f,  g1b2_e2 = 29.02f, g1b2_e4 = 1500,  g1b2_e6 = 68.5f, g1b2_e8 = 2005,    g1b2_e9 = 90f, g1b2_e10 = 405;//轨道1的坐标数据
		static public float g2b1_e1 = 200,  g2b1_e2 = 37.77f,   g2b1_e4 = 1000,    g2b1_e6 = 77f,  g2b1_e8 = 205,     g2b1_e9 = 100F, g2b1_e10 = 850;//轨道2的坐标数据
		static public float g2b2_e1 = 12.5f, g2b2_e2 =29.08f,    g2b2_e4 = 1005,    g2b2_e6 = 68.5f,  g2b2_e8 = 200,   g2b2_e9 = 90F, g2b2_e10 = 400;//轨道2的坐标数据
/// /////////////////////////////停车位////////受铁位/////////等待位的等待位////////等待位/////////吊罐位的等待位//   /吊罐位     ///跨调位//////

		private int weizhi_xuhao(float juli, float  dif, int chehao)
		{
			 float w1, w2, w4, w6, w8, w9, w10;//W代表车在各个位置的距离数据

		int xuhao = 0;
			
			if(chehao==1)
			{
				w1 = g1b1_e1;w2 = g1b1_e2;w4 = g1b1_e4;w6 = g1b1_e6;w8 = g1b1_e8;w9 = g1b1_e9;w10 = g1b1_e10;

				if (Math.Abs(juli - w1) < dif)
                {
                    i11++;
                    if (i11 >= 2)
                    {
                        xuhao = 1;
                        i21 = 0; i41 = 0; i61 = 0; i81 = 0; i91 = 0; i101 = 0;
                    }
                }
                else if (Math.Abs(juli - w2) < dif)
                {
                    i21++;
                    if (i21 >= 2)
                    {
                        xuhao = 2;
                        i11 = 0; i41 = 0; i61 = 0; i81 = 0; i91 = 0; i101 = 0;
                    }
                }

                else if (Math.Abs(juli - w4) < dif)
                {

                    i41++;
                    if (i41 >= 2)
                    {
                        xuhao = 4;
                        i11 = 0; i21 = 0; i61 = 0; i81 = 0; i91 = 0; i101 = 0;
                    }

                }
                else if (Math.Abs(juli - w6) < dif)
                {

                    i61++;
                    if (i61 >= 2)
                    {
                        xuhao = 6;
                        i11 = 0; i41 = 0; i21 = 0; i81 = 0; i91 = 0; i101 = 0;
                    }

                }

                else if (Math.Abs(juli - w8) < dif)
                {

                    i81++;
                    if (i81 >= 2)
                    {
                        xuhao = 8;
                        i11 = 0; i41 = 0; i61 = 0; i21 = 0; i91 = 0; i101 = 0;
                    }

                }
                else if (Math.Abs(juli - w9) < dif)
                {
                    i91++;
                    if (i91 >= 2)
                    {
                        xuhao = 9;
                        i11 = 0; i41 = 0; i61 = 0; i81 = 0; i21 = 0; i101 = 0;
                    }

                }
                else if (Math.Abs(juli - w10) < dif)
                {

                    i101++;
                    if (i101 >= 2)
                    {
                        xuhao = 10;
                        i11 = 0; i41 = 0; i61 = 0; i81 = 0; i91 = 0; i21 = 0;
                    }

                }
                else
                {
                    xuhao = 0;
                    i11 = 0; i41 = 0; i61 = 0; i81 = 0; i91 = 0; i21 = 0; i101 = 0;
                }

        }
			if (chehao == 2)
			{
				w1 = g1b2_e1; w2 = g1b2_e2; w4 = g1b2_e4; w6 = g1b2_e6; w8 = g1b2_e8; w9 = g1b2_e9; w10 = g1b2_e10;

				if (Math.Abs(juli - w1) < dif)
				{
					i12++;
					if (i12 >= 2)
					{
						xuhao = 1;
						i22 = 0; i42 = 0; i62 = 0; i82 = 0; i92 = 0; i102 = 0;
					}
				}
				else if (Math.Abs(juli - w2) < dif)
				{
					i22++;
					if (i22 >= 2)
					{
						xuhao = 2;
						i12 = 0; i42 = 0; i62 = 0; i82 = 0; i92 = 0; i102 = 0;
					}
				}

                else if (Math.Abs(juli - w4) < dif)
				{

					i42++;
					if (i42 >= 2)
					{
						xuhao = 4;
						i12 = 0; i22 = 0; i62 = 0; i82 = 0; i92 = 0; i102 = 0;
					}

				}

                else if (Math.Abs(juli - w6) < dif)
				{

					i62++;
					if (i62 >= 2)
					{
						xuhao = 6;
						i12 = 0; i42 = 0; i22 = 0; i82 = 0; i92 = 0; i102 = 0;
					}

				}

                else if (Math.Abs(juli - w8) < dif)
				{

					i82++;
					if (i82 >= 2)
					{
						xuhao = 8;
						i12 = 0; i42 = 0; i62 = 0; i22 = 0; i92 = 0; i102 = 0;
					}

				}
                else if (Math.Abs(juli - w9) < dif)
				{
					i92++;
					if (i92 >= 2)
					{
						xuhao = 9;
						i12 = 0; i42 = 0; i62 = 0; i82 = 0; i22 = 0; i102 = 0;
					}

				}
                else if (Math.Abs(juli - w10) < dif)
				{

					i102++;
					if (i102 >= 2)
					{
						xuhao = 10;
						i12 = 0; i42 = 0; i62 = 0; i82 = 0; i92 = 0; i22 = 0;
					}

				}
                else
                {
                    xuhao = 0;
                    i12 = 0; i42 = 0; i62 = 0; i82 = 0; i92 = 0; i22 = 0; i102 = 0;
                }
            }


            if (chehao == 3)
			{
				w1 = g2b1_e1; w2 = g2b1_e2; w4 = g2b1_e4; w6 = g2b1_e6; w8 = g2b1_e8; w9 = g2b1_e9; w10 = g2b1_e10;

				if (Math.Abs(juli - w1) < dif)
				{
					i13++;
					if (i13 >= 2)
					{
						xuhao = 1;
						i23 = 0; i43 = 0; i63 = 0; i83 = 0; i93 = 0; i103 = 0;
					}
				}
                else if (Math.Abs(juli - w2) < dif)
				{
					i23++;
					if (i23 >= 2)
					{
						xuhao = 2;
						i13 = 0; i43 = 0; i63 = 0; i83 = 0; i93 = 0; i103 = 0;
					}
				}

                else if (Math.Abs(juli - w4) < dif)
				{

					i43++;
					if (i43 >= 2)
					{
						xuhao = 4;
						i13 = 0; i23 = 0; i63 = 0; i83 = 0; i93 = 0; i103 = 0;
					}

				}

                else if (Math.Abs(juli - w6) < dif)
				{

					i63++;
					if (i63 >= 2)
					{
						xuhao = 6;
						i13 = 0; i43 = 0; i23 = 0; i83 = 0; i93 = 0; i103 = 0;
					}

				}

                else if (Math.Abs(juli - w8) < dif)
				{

					i83++;
					if (i83 >= 2)
					{
						xuhao = 8;
						i13 = 0; i43 = 0; i63 = 0; i23 = 0; i93 = 0; i103 = 0;
					}

				}
                else if (Math.Abs(juli - w9) < dif)
				{
					i93++;
					if (i93 >= 2)
					{
						xuhao = 9;
						i13 = 0; i43 = 0; i63 = 0; i83 = 0; i23 = 0; i103 = 0;
					}

				}
                else if (Math.Abs(juli - w10) < dif)
				{

					i103++;
					if (i103 >= 2)
					{
						xuhao = 10;
						i13 = 0; i43 = 0; i63 = 0; i83 = 0; i93 = 0; i23 = 0;
					}

				}
                else
                {
                    xuhao = 0;
                    i13 = 0; i43 = 0; i63 = 0; i83 = 0; i93 = 0; i23 = 0; i103 = 0;
                }
            }
			if (chehao == 4)
			{
				w1 = g2b2_e1; w2 = g2b2_e2; w4 = g2b2_e4; w6 = g2b2_e6; w8 = g2b2_e8; w9 = g2b2_e9; w10 = g2b2_e10;

				if (Math.Abs(juli - w1) < dif)
				{
					i14++;
					if (i14 >= 2)
					{
						xuhao = 1;
						i24 = 0; i44 = 0; i64 = 0; i84 = 0; i94 = 0; i104 = 0;
					}
				}
                else if (Math.Abs(juli - w2) < dif)
				{
					i24++;
					if (i24 >= 2)
					{
						xuhao = 2;
						i14 = 0; i44 = 0; i64 = 0; i84 = 0; i94 = 0; i104 = 0;
					}
				}

                else if (Math.Abs(juli - w4) < dif)
				{

					i44++;
					if (i44 >= 2)
					{
						xuhao = 4;
						i14 = 0; i24 = 0; i64 = 0; i84 = 0; i94 = 0; i104 = 0;
					}

				}

                else if (Math.Abs(juli - w6) < dif)
				{

					i64++;
					if (i64 >= 2)
					{
						xuhao = 6;
						i14 = 0; i44 = 0; i24 = 0; i84 = 0; i94 = 0; i104 = 0;
					}

				}

                else if (Math.Abs(juli - w8) < dif)
				{

					i84++;
					if (i84 >= 2)
					{
						xuhao = 8;
						i14 = 0; i44 = 0; i64 = 0; i24 = 0; i94 = 0; i104 = 0;
					}

				}
                else if (Math.Abs(juli - w9) < dif)
				{
					i94++;
					if (i94 >= 2)
					{
						xuhao = 9;
						i14 = 0; i44 = 0; i64 = 0; i84 = 0; i24 = 0; i104 = 0;
					}

				}
                else if (Math.Abs(juli - w10) < dif)
				{

					i104++;
					if (i104 >= 2)
					{
						xuhao = 10;
						i14 = 0; i44 = 0; i64 = 0; i84 = 0; i94 = 0; i24 = 0;
					}

				}
                else
                {
                    xuhao = 0;
                    i14 = 0; i44 = 0; i64 = 0; i84 = 0; i94 = 0; i24 = 0; i104 = 0;
                }
            }

			return xuhao;
		}

	}

	public class weizhi_huoqu
	{
		public float weizhi_g1_b1;
		public float weizhi_g1_b2;
		public float weizhi_g2_b1;
		public float weizhi_g2_b2;

		public int guidao1;
		public int guidao2;
		public int chehao;


		public float whizhu_huoqu_fun(float j1, float b1, float d1, shoutie.global_var global_var3, int chehao)//激光测距，编码器，定位器
		{

			return j1;
			float shoutie_zuobiao = global_var3.zuobiao_huoqu(chehao, 2);//受铁位坐标
			float degndai_zuobiao = global_var3.zuobiao_huoqu(chehao, 3);//等待位坐标
			float diaoguan_zuobiao = global_var3.zuobiao_huoqu(chehao, 4);//吊罐位坐标

			float shoutie_zuobiao_chazhi;//受铁位坐标和当前编码器的差值
			float degndai_zuobiao_chazhi;//等待位坐标和当前编码器的差值
			float diaoguan_zuobiao_chazhi;//吊罐位坐标和当前编码器的差值

			b1 = b1 - (float)global_var3.zhuangtai_du(chehao, 10);//由误差值更新当前值,编码器

			j1 = j1 - (float)global_var3.zhuangtai_du(chehao, 11);//由误差值更新当前值,编码器


			if (d1 == 1 && b1 != -1)//编码器没坏
			{
				shoutie_zuobiao_chazhi = Math.Abs(b1 - shoutie_zuobiao);
				degndai_zuobiao_chazhi = Math.Abs(b1 - degndai_zuobiao);
				diaoguan_zuobiao_chazhi = Math.Abs(b1 - diaoguan_zuobiao);

				if (shoutie_zuobiao_chazhi < degndai_zuobiao_chazhi && shoutie_zuobiao_chazhi < diaoguan_zuobiao_chazhi)
				{
					global_var3.zhuangtai_xie(chehao, 10, b1 - shoutie_zuobiao);//写误差值

					return shoutie_zuobiao;
				}
				if (degndai_zuobiao_chazhi < shoutie_zuobiao_chazhi && degndai_zuobiao_chazhi < diaoguan_zuobiao_chazhi)
				{
					global_var3.zhuangtai_xie(chehao, 10, b1 - degndai_zuobiao);//写误差值

					return degndai_zuobiao;
				}
				if (diaoguan_zuobiao_chazhi < shoutie_zuobiao_chazhi && diaoguan_zuobiao_chazhi < degndai_zuobiao_chazhi)
				{
					global_var3.zhuangtai_xie(chehao, 10, b1 - diaoguan_zuobiao);//写误差值

					return diaoguan_zuobiao;
				}
			}
			if (d1 == 1 && b1 == -1)//编码器坏了，激光测距没坏
			{
				shoutie_zuobiao_chazhi = Math.Abs(j1 - shoutie_zuobiao);
				degndai_zuobiao_chazhi = Math.Abs(j1 - degndai_zuobiao);
				diaoguan_zuobiao_chazhi = Math.Abs(j1 - diaoguan_zuobiao);

				if (shoutie_zuobiao_chazhi < degndai_zuobiao_chazhi && shoutie_zuobiao_chazhi < diaoguan_zuobiao_chazhi)
				{
					global_var3.zhuangtai_xie(chehao, 11, j1 - shoutie_zuobiao);//写误差值

					return shoutie_zuobiao;
				}
				if (degndai_zuobiao_chazhi < shoutie_zuobiao_chazhi && degndai_zuobiao_chazhi < diaoguan_zuobiao_chazhi)
				{
					global_var3.zhuangtai_xie(chehao, 11, j1 - degndai_zuobiao);//写误差值

					return degndai_zuobiao;
				}
				if (diaoguan_zuobiao_chazhi < shoutie_zuobiao_chazhi && diaoguan_zuobiao_chazhi < degndai_zuobiao_chazhi)
				{
					global_var3.zhuangtai_xie(chehao, 11, j1 - diaoguan_zuobiao);//写误差值

					return diaoguan_zuobiao;
				}
			}

			if (b1 != -1)//不在定位器上，返回编码器的值

			{ return b1; }
			else //不在定位器上，返回激光测距器的值
			{ return j1; }
		}


		public static float jiguangceju(int guidao, int chehao)
		{

			return Constant.CommWithPLC.Rangefinder(guidao, chehao);

		}

		public float bianmaqi(int guidao, int chehao)
		{
			return Constant.CommWithPLC.Encoder(guidao, chehao);

		}
		public static int dingweiqi(int chehao, int guidao1, int guidao2)
		{
			if (chehao == 1)
			{
				if (Constant.CommWithPLC.LimitSwitch(guidao1, 1))
				{ return 1; }
				else return 0;
			}
			if (chehao == 2)
			{
				if (Constant.CommWithPLC.LimitSwitch(guidao1, 2))
				{ return 1; }
				else return 0;
			}

			if (chehao == 3)
			{
				if (Constant.CommWithPLC.LimitSwitch(guidao2, 1))
				{ return 1; }
				else return 0;
			}
			if (chehao == 4)
			{
				if (Constant.CommWithPLC.LimitSwitch(guidao2, 2))
				{ return 1; }
				else return 0;
			}

			return -1;
		}


	}



}
