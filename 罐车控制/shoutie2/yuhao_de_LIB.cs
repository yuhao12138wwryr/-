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
using System.Data;

namespace shoutie
{
	public static class receve_iron//受铁
	{

		public static void liucao_baidong(int chehao, int guidao1, int guidao2)//溜槽摆动
		{
			if (chehao == 1 || chehao == 2)
			{
                Constant.CommWithPLC.ChuteSwingAny(3, 15);
            }
			if (chehao == 3 || chehao == 4)
			{
                Constant.CommWithPLC.ChuteSwingAny(3, -15);
            }
		}



		public static int du_liucao_baidong_wancheng(int chehao, int guidao1, int guidao2)//溜槽摆动完成，两个方向只要到了位置就算1，也算检测摆动方向与命令方向是否一致
		{
            if (chehao == 1 || chehao == 2)
            {
                if(Constant.CommWithPLC.plc2data.Chute_3_SwingAngle>15)
                { return 1; }
            }
            if (chehao == 3 || chehao == 4)
            {
                if (Constant.CommWithPLC.plc2data.Chute_3_SwingAngle <- 15)
                { return 1; }
            }
            return 0;
		}


		public static int xintiao(int guidao1, int guidao2)//读受铁心跳
		{

            if (Constant.CommWithPLC.plc2hmi1.beat)
            { return 1; }
            else { return 0; }
		}
		public static int zhengzai_shoutie(int chehao, int guidao1, int guidao2)//读受铁状态，1正在受铁
		{
			CustomMessageBox4 customMessageBox = new CustomMessageBox4();
			customMessageBox.Text = $"{chehao}读受铁状态，1正在受铁";
			DialogResult result4 = customMessageBox.ShowDialog();
			return ((int)customMessageBox.i);
		}

	}
	public static class xiaoche_b1//轨道1
	{


		public static int xintiao(int bianhao, int guidao1, int guidao2)//心跳
		{
			if (bianhao == 1)
			{
                if (Constant.CommWithPLC.xiaochezaixian(guidao1, 1))
                { return 1; }
                else { return 0; }
			}
			if (bianhao == 2)
			{
                if (Constant.CommWithPLC.xiaochezaixian(guidao1, 2))
                { return 1; }
                else { return 0; }
            }
			if (bianhao == 3)
			{
                if (Constant.CommWithPLC.xiaochezaixian(guidao2, 1))
                { return 1; }
                else { return 0; }
            }
			if (bianhao == 4)
			{
                if (Constant.CommWithPLC.xiaochezaixian(guidao2, 2))
                { return 1; }
                else { return 0; }
            }
			return 0;

		}


		public static void suoche(int bianhao, int guidao1, int guidao2)//锁车
		{
			if (bianhao == 1)
			{
			}
			if (bianhao == 2)
			{ }
			if (bianhao == 3)
			{ }
			if (bianhao == 4)
			{ }
		}
		public static void jiesuo(int bianhao, int guidao1, int guidao2)//解锁
		{
			if (bianhao == 1)
			{ }
			if (bianhao == 2)
			{ }
			if (bianhao == 3)
			{ }
			if (bianhao == 4)
			{ }
		}
		public static void xianche_houtui(int bianhao, int priority, int key, int guidao1, int guidao2,shoutie .global_var global_var1)//小车前进，，
		{
			if (priority == 1 || priority == 3)//轨道1和轨道2上的B1车
			{
				if (bianhao == 1)
				{
					if (key != 1 && key != 3)//锁定轨道1的B1车控制权，低位为1锁定
					{

						if ((int)global_var1.zhuangtai_du(bianhao,12) == 0)
						{
                            Constant.CommWithPLC.MoveForward(guidao1, 1); }
					}
				}//轨道1，B1车前进
				if (bianhao == 2)
				{
					if ((int)global_var1.zhuangtai_du(bianhao, 12) == 0)
					{ Constant.CommWithPLC.MoveForward(guidao1, 2); }
				}//轨道1，B2车前进
				if (bianhao == 3)
				{
					if (key != 3 && key != 2)//锁定轨道2的B1车控制权，高位为1锁定
					{
						if ((int)global_var1.zhuangtai_du(bianhao, 12) == 0)
						{ Constant.CommWithPLC.MoveForward(guidao2, 1); }
					}
				}//轨道2，B1车前进
				if (bianhao == 4)
				{
					if ((int)global_var1.zhuangtai_du(bianhao, 12) == 0)
					{ Constant.CommWithPLC.MoveForward(guidao2, 2); }
				}//轨道2，B1车前进
			}
			if (priority == 2 || priority == 4)
			{
				if (bianhao == 1)
				{
					if ((int)global_var1.zhuangtai_du(bianhao, 12) == 0)
					{ Constant.CommWithPLC.MoveForward(guidao1, 1); }
				}//轨道1，B1车前进
				if (bianhao == 2)
				{
					if ((int)global_var1.zhuangtai_du(bianhao, 12) == 0)
					{ Constant.CommWithPLC.MoveForward(guidao1, 2); }
				}//轨道1，B2车前进
				if (bianhao == 3)
				{
					if ((int)global_var1.zhuangtai_du(bianhao, 12) == 0)
					{ Constant.CommWithPLC.MoveForward(guidao2, 1); }
				}//轨道2，B1车前进
				if (bianhao == 4)
				{
					if ((int)global_var1.zhuangtai_du(bianhao, 12) == 0)
					{ Constant.CommWithPLC.MoveForward(guidao2, 2); }
				}//轨道2，B1车前进 
			}

		}
		public static void xianche_qianjing(int bianhao, int priority, int key, int guidao1, int guidao2, shoutie.global_var global_var1)//小车后退
		{
			if (priority == 1 || priority == 3)//轨道1和轨道2上的B1车
			{
				if (bianhao == 1)
				{
					if (key != 1 && key != 3)//锁定轨道1的B1车控制权，低位为1锁定
					{
						if ((int)global_var1.zhuangtai_du(bianhao, 12) == 0)
						{ Constant.CommWithPLC.MoveBackward(guidao1, 1); }
					}
				}//轨道1，B1车前进
				if (bianhao == 2)
				{
					if ((int)global_var1.zhuangtai_du(bianhao, 12) == 0)
					{ Constant.CommWithPLC.MoveBackward(guidao1, 2); }
				}//轨道1，B2车前进
				if (bianhao == 3)
				{
					if (key != 3 && key != 2)//锁定轨道2的B1车控制权，高位为1锁定
					{
						if ((int)global_var1.zhuangtai_du(bianhao, 12) == 0)
						{ Constant.CommWithPLC.MoveBackward(guidao2, 1); }
					}
				}//轨道2，B1车前进
				if (bianhao == 4)
				{
					if ((int)global_var1.zhuangtai_du(bianhao, 12) == 0)
					{ Constant.CommWithPLC.MoveBackward(guidao2, 2); }
				}//轨道2，B1车前进
			}
			if (priority == 2 || priority == 4)
			{
				if (bianhao == 1)
				{
					if ((int)global_var1.zhuangtai_du(bianhao, 12) == 0)
					{ Constant.CommWithPLC.MoveBackward(guidao1, 1); }
				}//轨道1，B1车前进
				if (bianhao == 2)
				{
					if ((int)global_var1.zhuangtai_du(bianhao, 12) == 0)
					{ Constant.CommWithPLC.MoveBackward(guidao1, 2); }
				}//轨道1，B2车前进
				if (bianhao == 3)
				{
					if ((int)global_var1.zhuangtai_du(bianhao, 12) == 0)
					{ Constant.CommWithPLC.MoveBackward(guidao2, 1); }
				}//轨道2，B1车前进
				if (bianhao == 4)
				{
					if ((int)global_var1.zhuangtai_du(bianhao, 12) == 0)
					{ Constant.CommWithPLC.MoveBackward(guidao2, 2); }
				}//轨道2，B1车前进 
			}

		}
		public static void xianche_tingzhi(int bianhao, int guidao1, int guidao2)//小车停止，，
		{
			if (bianhao == 1)
			{
				Constant.CommWithPLC.StopMoving(guidao1, 1);
			}//轨道1，B1车停止
			if (bianhao == 2)
			{
				Constant.CommWithPLC.StopMoving(guidao1, 2);
			}//轨道1，B2车停止
			if (bianhao == 3)
			{
				Constant.CommWithPLC.StopMoving(guidao2, 1);
			}//轨道2，B1车停止
			if (bianhao == 4)
			{
				Constant.CommWithPLC.StopMoving(guidao2, 2);
			}//轨道2，B1车停止
		}

		public static int duqu_weizhi(int bianhao, shoutie.global_var global_var1)//读取当前位置,返回状态标志，记得区分车号
		{
            return (int)global_var1.zhuangtai_du(bianhao, 6);
            if (bianhao == 1)
			{
				CustomMessageBox4 customMessageBox = new CustomMessageBox4();
				customMessageBox.Text = "获取轨道1小车1位置，公共函数，参考备注";
				customMessageBox.label1.Text = "备用车2停车位1\r\n受铁位、常用车停车位、称台2\r\n备用车2接近等待位3\r\n常用车1接近等待位4\r\n备用车2等待位5\r\n常用车1等待位6\r\n备用车2接近吊罐位7\r\n常用车1接近吊罐位8\r\n吊罐位9\r\n备用车2跨吊位10\r\n常用车1跨吊位11";

				DialogResult result4 = customMessageBox.ShowDialog();
				return ((int)customMessageBox.i);
			}//读B1车的位置
			else if (bianhao == 2)
			{
				CustomMessageBox4 customMessageBox = new CustomMessageBox4();
				customMessageBox.Text = "获取轨道1小车2位置，公共函数，参考备注";
				customMessageBox.label1.Text = "备用车2停车位1\r\n受铁位、常用车停车位、称台2\r\n备用车2接近等待位3\r\n常用车1接近等待位4\r\n备用车2等待位5\r\n常用车1等待位6\r\n备用车2接近吊罐位7\r\n常用车1接近吊罐位8\r\n吊罐位9\r\n备用车2跨吊位10\r\n常用车1跨吊位11";

				DialogResult result4 = customMessageBox.ShowDialog();
				return ((int)customMessageBox.i);
			}//读B2车的位置
			if (bianhao == 3)
			{
				CustomMessageBox4 customMessageBox = new CustomMessageBox4();
				customMessageBox.Text = "获取轨道2小车1位置，公共函数，参考备注";
				customMessageBox.label1.Text = "备用车2停车位1\r\n受铁位、常用车停车位、称台2\r\n备用车2接近等待位3\r\n常用车1接近等待位4\r\n备用车2等待位5\r\n常用车1等待位6\r\n备用车2接近吊罐位7\r\n常用车1接近吊罐位8\r\n吊罐位9\r\n备用车2跨吊位10\r\n常用车1跨吊位11";
				DialogResult result4 = customMessageBox.ShowDialog();
				return ((int)customMessageBox.i);
			}//读B1车的位置
			else if (bianhao == 4)
			{
				CustomMessageBox4 customMessageBox = new CustomMessageBox4();
				customMessageBox.Text = "获取轨道2小车2位置，公共函数，参考备注";
				customMessageBox.label1.Text = "备用车2停车位1\r\n受铁位、常用车停车位、称台2\r\n备用车2接近等待位3\r\n常用车1接近等待位4\r\n备用车2等待位5\r\n常用车1等待位6\r\n备用车2接近吊罐位7\r\n常用车1接近吊罐位8\r\n吊罐位9\r\n备用车2跨吊位10\r\n常用车1跨吊位11";

				DialogResult result4 = customMessageBox.ShowDialog();
				return ((int)customMessageBox.i);
			}//读B2车的位置
			return 0;
		}

	}

	public class CustomMessageBox4 : Form
	{
		private TextBox textBox1;
		private Button button1;
		public Label label1;

		public float i;
		public CustomMessageBox4()
		{
			i = 0;
			InitializeComponent();
		}

		private void InitializeComponent()
		{
			this.button1 = new Button();
			this.label1 = new Label();
			this.SuspendLayout();

			// 设置窗体属性
			this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
			this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
			this.Text = "方向是否正确，确认后注入铁水";

			// 设置按钮属性
			this.button1.Location = new Point(110, 200);
			this.button1.Name = "button11";
			this.button1.Size = new Size(200, 100);
			this.button1.Text = "确认";
			this.button1.Click += new System.EventHandler(this.button1_Click);

			textBox1 = new TextBox();
			textBox1.Location = new Point(110, 100);
			textBox1.Name = "textBox1";
			textBox1.Size = new Size(122, 30);
			textBox1.TabIndex = 4;

			label1.Dock = DockStyle.Right;
			label1.Location = new Point(660, 0);
			label1.AutoSize = true;
			label1.Name = "label1";
			label1.Size = new Size(63, 24);
			label1.TabIndex = 3;
			label1.Text = "label1";


			// 添加按钮到窗体
			this.ClientSize = new Size(705, 385);
			this.Controls.Add(this.button1);
			this.Controls.Add(textBox1);
			this.Controls.Add(label1);
			this.ResumeLayout(false);
			this.PerformLayout();
		}


		private void button1_Click(object sender, EventArgs e)
		{
			i = float.Parse(textBox1.Text);
			this.Close();
		}

	}

}

namespace guanchedida//抵达吊包位
{
	public static class shijue
	{
		public static int shijue_kuadiaowei(int chehao, object global_var)//为0，则跨吊位占用
		{
			return 1;
		}
		public static int shijue_diaoguanwei(int chehao, object global_var)//为0，则吊罐位占用
		{
			CustomMessageBox4 customMessageBox = new CustomMessageBox4();
			customMessageBox.Text = $"{chehao}为0，则吊罐位占用，1空闲";
			DialogResult result4 = customMessageBox.ShowDialog();
			return ((int)customMessageBox.i);
		}
	}
}

namespace diaoguan_yidong
{
	public class yemian//液面
	{

		private float yemianji_leida = 0;//雷达液面数据，上次的
		private float yemianji_bianhualv_leida = 0;//雷达变化率
		private float yemianji_xiangji = 0;//相机液面数据，上次的
		private float yemianji_bianhualv_xiangji = 0;//相机变化率
		private float yemianji_zhongliangji = 0;//重量计液面数据，上次的
		private float yemianji_bianhualv_zhongliangji = 0;//重量计变化率
		private float yemian_shuzhi = 0;//输出的液面数据
		private float yemian_shuzhi_biahualv = 0;//输出的液面数据变化率
		public float Yemian_shuzhi_biahualv
		{
			get { return yemian_shuzhi_biahualv; }
			set { yemian_shuzhi_biahualv = value; }
		}
		public float Yemian_shuzhi
		{
			get { return yemian_shuzhi; }
			set { yemian_shuzhi = value; }
		}
		public void yemian_shuchu(int guidao)
		{
			float leida, zhongliangji, xiangji;//当前值
			leida = yemian.duqu_leida(guidao);
			zhongliangji = yemian.duqu_zhongliangji(guidao);
			xiangji = yemian.duqu_xiangji(guidao);
			yemianji_bianhualv_leida = leida - yemianji_leida;
			yemianji_bianhualv_zhongliangji = zhongliangji - yemianji_zhongliangji;
			yemianji_bianhualv_xiangji = xiangji - yemianji_xiangji;
			yemianji_leida = leida;
			yemianji_zhongliangji = zhongliangji;
			yemianji_xiangji = xiangji;
			if (zhongliangji != -1)//重量计无故障
			{
				yemian_shuzhi = zhongliangji;
				yemian_shuzhi_biahualv = yemianji_bianhualv_zhongliangji;
			}//相信重量计
			else if (zhongliangji == -1 && leida != -1)//重量计故障
			{

				yemian_shuzhi = leida;//相信雷达
				yemian_shuzhi_biahualv = yemianji_bianhualv_leida;
			}
			if (yemianji_bianhualv_leida > 10 || yemianji_bianhualv_zhongliangji > 10)
			{
				yemian.baojing_bianhualv();//变化过快，报警，也可能是初值没清0导致的
			}
			else
			{
				yemian.zhengchangtishi();//变化正常，正常播报
			}
		}

		public static float duqu_leida(int guidao)//读取雷达,没有心跳返回-1
		{
			CustomMessageBox4 customMessageBox = new CustomMessageBox4();
			customMessageBox.Text = $"{guidao}雷达计输入值，-1故障";
			DialogResult result4 = customMessageBox.ShowDialog();
			return ((int)customMessageBox.i);
			//return -1;
		}
		public static float duqu_xiangji(int guidao)//读取相机
		{
			return -1;
		}


		public static float duqu_zhongliangji(int guidao)//读取重量计,没有心跳返回-1
		{
			CustomMessageBox4 customMessageBox = new CustomMessageBox4();
			customMessageBox.Text = $"{guidao}重量计输入值，为-1故障";
			DialogResult result4 = customMessageBox.ShowDialog();
			return ((int)customMessageBox.i);
			//return -1;
		}


		public static void baojing_zhongliangji()//报警，重量计故障
		{

		}
		public static void baojing_bianhualv()//报警，变化率过快
		{

		}
		public static void zhengchangtishi()//正常提示
		{

		}

	}
}

namespace diaoli
{
	public static class shijue
	{
		public static void tongzhi_xingche_diaoguan(int chehao, int guidao1, int guidao2)//通知行车调离重罐
		{
			if (chehao == 1 || chehao == 2)//轨道1
			{ }
			if (chehao == 3 || chehao == 4)//轨道2
			{ }
		}
		public static void tongzhi_xingche_luoguan(int chehao, int guidao1, int guidao2)//通知行车落罐
		{
			if (chehao == 1 || chehao == 2)//轨道1
			{ }
			if (chehao == 3 || chehao == 4)//轨道2
			{ }
		}
		public static int zhongggun_diaoli(int chehao, object global_var)//视觉判断重罐调离完成
		{
			if (chehao == 1 || chehao == 2)//轨道1
			{
				CustomMessageBox4 customMessageBox = new CustomMessageBox4();
				customMessageBox.Text = $"{chehao}为1，则轨道1重罐掉离成功";
				customMessageBox.ShowDialog();
				return ((int)customMessageBox.i);
			}
			if (chehao == 3 || chehao == 4)//轨道2
			{
				CustomMessageBox4 customMessageBox = new CustomMessageBox4();
				customMessageBox.Text = $"{chehao}为1，则轨道2重罐掉离成功";
				customMessageBox.ShowDialog();
				return ((int)customMessageBox.i);
			}
			return 0;
		}
		public static int qingguan_luogun(int chehao, object global_var)//视觉判断行车落罐
		{
			if (chehao == 1 || chehao == 2)//轨道1
			{
				CustomMessageBox4 customMessageBox = new CustomMessageBox4();
				customMessageBox.Text = $"{chehao}为1，则轨道1行车落罐成功";
				customMessageBox.ShowDialog();
				return ((int)customMessageBox.i);
			}
			if (chehao == 3 || chehao == 4)//轨道2
			{
				CustomMessageBox4 customMessageBox = new CustomMessageBox4();
				customMessageBox.Text = $"{chehao}为1，则轨道2行车落罐成功";
				customMessageBox.ShowDialog();
				return ((int)customMessageBox.i);
			}
			return 0;
		}
		public static int tuogou(int chehao, object global_var)//视觉判断脱钩完成
		{
			if (chehao == 1 || chehao == 2)//轨道1
			{
				CustomMessageBox4 customMessageBox = new CustomMessageBox4();
				customMessageBox.Text = $"{chehao}为1，则轨道1脱钩完成";
				customMessageBox.ShowDialog();
				return ((int)customMessageBox.i);
			}
			if (chehao == 3 || chehao == 4)//轨道2
			{
				CustomMessageBox4 customMessageBox = new CustomMessageBox4();
				customMessageBox.Text = $"{chehao}为1，则轨道2脱钩完成";
				customMessageBox.ShowDialog();
				return ((int)customMessageBox.i);
			}
			return 0;
		}
		public static int gunhao(int chehao, object global_var)//视觉判断重罐调离完成
		{
			if (chehao == 1 || chehao == 2)//轨道1
			{
				CustomMessageBox4 customMessageBox = new CustomMessageBox4();
				customMessageBox.Text = "轨道1当前罐号";
				customMessageBox.ShowDialog();
				return ((int)customMessageBox.i);
			}
			if (chehao == 3 || chehao == 4)//轨道2
			{
				CustomMessageBox4 customMessageBox = new CustomMessageBox4();
				customMessageBox.Text = "轨道2当前罐号";
				customMessageBox.ShowDialog();
				return ((int)customMessageBox.i);
			}
			return 0;
		}
	}
}