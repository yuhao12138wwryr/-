using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Threading;
using System.Windows.Forms;
using shoutie;
using System.Timers;
using SetButtonAppearance;

namespace banzidong
{

	public class CustomMessageBox3 : Form
	{
        System.Windows.Forms.Timer UpdateValueTimer = new System.Windows.Forms.Timer();

        System.Timers.Timer timer2;//定时器
        shoutie.global_var global_var2 = new shoutie.global_var();
		public CustomMessageBox3(object gv)
		{
			global_var2 = (shoutie.global_var)gv;//引用
            timer2 = new System.Timers.Timer();
            timer2.Interval = 1000;
            timer2.Elapsed += dingshiqi;
            timer2.Enabled = true;
            InitializeComponent();

            UpdateValueTimer.Interval = 500;
            UpdateValueTimer.Tick += new EventHandler((object sender, EventArgs e) => {
                if ((int)global_var2.zhuangtai_du(1, 9) == 1 || (int)global_var2.zhuangtai_du(2, 9) == 1)
                {
                    button6.Enabled = false;
                    button5.Enabled = false;
                    button13.Enabled = false;
                    button2.Enabled = false;
                    button1.Enabled = false;
                    button9.Enabled = false;
                    button10.Enabled = false;
                    button12.Enabled = false;
                    button8.Enabled = false;
                }
                if ((int)global_var2.zhuangtai_du(1, 9) == 0 &&(int)global_var2.zhuangtai_du(2, 9) == 0)
                {
                    button6.Enabled = true;
                    button5.Enabled = true;
                    button13.Enabled = true;
                    button2.Enabled = true;
                    button1.Enabled = true;
                    button9.Enabled = true;
                    button10.Enabled = true;
                    button12.Enabled = true;
                    button8.Enabled = true;
                }
                if ((int)global_var2.zhuangtai_du(3, 9) == 1 || (int)global_var2.zhuangtai_du(4, 9) == 1)
                {
                    button15.Enabled = false;
                    button18.Enabled = false;
                    button19.Enabled = false;
                    button14.Enabled = false;
                    button20.Enabled = false;
                    button21.Enabled = false;
                    button22.Enabled = false;
                    button24.Enabled = false;
                    button25.Enabled = false;
                }
                if ((int)global_var2.zhuangtai_du(3, 9) == 0 && (int)global_var2.zhuangtai_du(4, 9) == 0)
                {
                    button15.Enabled = true;
                    button18.Enabled = true;
                    button19.Enabled = true;
                    button14.Enabled = true;
                    button20.Enabled = true;
                    button21.Enabled = true;
                    button22.Enabled = true;
                    button24.Enabled = true;
                    button25.Enabled = true;
                }
            });
            UpdateValueTimer.Enabled = true;

        }

        private Button button1;
		private Button button2;
		private Button button5;
		private Button button6;
		private Button button7;
		private Button button8;
		private Button button9;
		private Button button10;
		private Button button12;
		private Button button13;
		private Button button14;
		private Button button15;
		private Button button18;
		private Button button19;
		private Button button20;
		private Button button21;
		private Button button22;
		private Button button24;
		private Button button25;
		private Label label1;
		private Label label2;
		private Label label3;
		private Button button26;
		private Button button27;
		private Button button28;
		private Button button29;
        private Button button3;
        private Button button11;
        private Button button17;
        private Button button23;
        private Button button30;
        private Label label4;

		private void InitializeComponent()
		{
			this.button1 = new System.Windows.Forms.Button();
			this.button2 = new System.Windows.Forms.Button();
			this.button5 = new System.Windows.Forms.Button();
			this.button6 = new System.Windows.Forms.Button();
			this.button7 = new System.Windows.Forms.Button();
			this.button8 = new System.Windows.Forms.Button();
			this.button9 = new System.Windows.Forms.Button();
			this.button10 = new System.Windows.Forms.Button();
			this.button12 = new System.Windows.Forms.Button();
			this.button13 = new System.Windows.Forms.Button();
			this.button14 = new System.Windows.Forms.Button();
			this.button15 = new System.Windows.Forms.Button();
			this.button18 = new System.Windows.Forms.Button();
			this.button19 = new System.Windows.Forms.Button();
			this.button20 = new System.Windows.Forms.Button();
			this.button21 = new System.Windows.Forms.Button();
			this.button22 = new System.Windows.Forms.Button();
			this.button24 = new System.Windows.Forms.Button();
			this.button25 = new System.Windows.Forms.Button();
			this.label1 = new System.Windows.Forms.Label();
			this.label2 = new System.Windows.Forms.Label();
			this.label3 = new System.Windows.Forms.Label();
			this.label4 = new System.Windows.Forms.Label();
			this.button26 = new System.Windows.Forms.Button();
			this.button27 = new System.Windows.Forms.Button();
			this.button28 = new System.Windows.Forms.Button();
			this.button29 = new System.Windows.Forms.Button();
			this.button3 = new System.Windows.Forms.Button();
			this.button11 = new System.Windows.Forms.Button();
			this.button17 = new System.Windows.Forms.Button();
			this.button23 = new System.Windows.Forms.Button();
			this.button30 = new System.Windows.Forms.Button();
			this.SuspendLayout();
			// 
			// button1
			// 
			this.button1.Location = new System.Drawing.Point(162, 91);
			this.button1.Name = "button1";
			this.button1.Size = new System.Drawing.Size(115, 38);
			this.button1.TabIndex = 0;
			this.button1.Text = "前往受铁位";
			this.button1.UseVisualStyleBackColor = true;
			this.button1.Click += new System.EventHandler(this.button1_Click);
			// 
			// button2
			// 
			this.button2.Location = new System.Drawing.Point(315, 91);
			this.button2.Name = "button2";
			this.button2.Size = new System.Drawing.Size(115, 38);
			this.button2.TabIndex = 1;
			this.button2.Text = "前往吊罐位";
			this.button2.UseVisualStyleBackColor = true;
			this.button2.Click += new System.EventHandler(this.button2_Click);
			// 
			// button5
			// 
			this.button5.Location = new System.Drawing.Point(618, 91);
			this.button5.Name = "button5";
			this.button5.Size = new System.Drawing.Size(106, 38);
			this.button5.TabIndex = 4;
			this.button5.Text = "前往等待位";
			this.button5.UseVisualStyleBackColor = true;
			this.button5.Click += new System.EventHandler(this.button5_Click);
			// 
			// button6
			// 
			this.button6.Location = new System.Drawing.Point(755, 91);
			this.button6.Name = "button6";
			this.button6.Size = new System.Drawing.Size(119, 38);
			this.button6.TabIndex = 5;
			this.button6.Text = "前往跨吊位";
			this.button6.UseVisualStyleBackColor = true;
			this.button6.Click += new System.EventHandler(this.button6_Click);
			// 
			// button7
			// 
			this.button7.Location = new System.Drawing.Point(894, 334);
			this.button7.Name = "button7";
			this.button7.Size = new System.Drawing.Size(93, 38);
			this.button7.TabIndex = 6;
			this.button7.Text = "停止所有";
			this.button7.UseVisualStyleBackColor = true;
			this.button7.Click += new System.EventHandler(this.button7_Click);
			// 
			// button8
			// 
			this.button8.Location = new System.Drawing.Point(755, 152);
			this.button8.Name = "button8";
			this.button8.Size = new System.Drawing.Size(119, 38);
			this.button8.TabIndex = 12;
			this.button8.Text = "测试";
			this.button8.UseVisualStyleBackColor = true;
			this.button8.Click += new System.EventHandler(this.button8_Click);
			// 
			// button9
			// 
			this.button9.Location = new System.Drawing.Point(618, 152);
			this.button9.Name = "button9";
			this.button9.Size = new System.Drawing.Size(106, 38);
			this.button9.TabIndex = 11;
			this.button9.Text = "前往等待位";
			this.button9.UseVisualStyleBackColor = true;
			this.button9.Click += new System.EventHandler(this.button9_Click);
			// 
			// button10
			// 
			this.button10.Location = new System.Drawing.Point(474, 152);
			this.button10.Name = "button10";
			this.button10.Size = new System.Drawing.Size(109, 38);
			this.button10.TabIndex = 10;
			this.button10.Text = "返回停车位";
			this.button10.UseVisualStyleBackColor = true;
			this.button10.Click += new System.EventHandler(this.button10_Click);
			// 
			// button12
			// 
			this.button12.Location = new System.Drawing.Point(315, 152);
			this.button12.Name = "button12";
			this.button12.Size = new System.Drawing.Size(115, 38);
			this.button12.TabIndex = 8;
			this.button12.Text = "前往吊罐位";
			this.button12.UseVisualStyleBackColor = true;
			this.button12.Click += new System.EventHandler(this.button12_Click);
			// 
			// button13
			// 
			this.button13.Location = new System.Drawing.Point(162, 152);
			this.button13.Name = "button13";
			this.button13.Size = new System.Drawing.Size(115, 38);
			this.button13.TabIndex = 7;
			this.button13.Text = "前往受铁位";
			this.button13.UseVisualStyleBackColor = true;
			this.button13.Click += new System.EventHandler(this.button13_Click);
			// 
			// button14
			// 
			this.button14.Location = new System.Drawing.Point(755, 212);
			this.button14.Name = "button14";
			this.button14.Size = new System.Drawing.Size(119, 38);
			this.button14.TabIndex = 18;
			this.button14.Text = "前往跨吊位";
			this.button14.UseVisualStyleBackColor = true;
			this.button14.Click += new System.EventHandler(this.button14_Click);
			// 
			// button15
			// 
			this.button15.Location = new System.Drawing.Point(618, 212);
			this.button15.Name = "button15";
			this.button15.Size = new System.Drawing.Size(106, 38);
			this.button15.TabIndex = 17;
			this.button15.Text = "前往等待位";
			this.button15.UseVisualStyleBackColor = true;
			this.button15.Click += new System.EventHandler(this.button15_Click);
			// 
			// button18
			// 
			this.button18.Location = new System.Drawing.Point(315, 212);
			this.button18.Name = "button18";
			this.button18.Size = new System.Drawing.Size(115, 38);
			this.button18.TabIndex = 14;
			this.button18.Text = "前往吊罐位";
			this.button18.UseVisualStyleBackColor = true;
			this.button18.Click += new System.EventHandler(this.button18_Click);
			// 
			// button19
			// 
			this.button19.Location = new System.Drawing.Point(162, 212);
			this.button19.Name = "button19";
			this.button19.Size = new System.Drawing.Size(115, 38);
			this.button19.TabIndex = 13;
			this.button19.Text = "前往受铁位";
			this.button19.UseVisualStyleBackColor = true;
			this.button19.Click += new System.EventHandler(this.button19_Click);
			// 
			// button20
			// 
			this.button20.Location = new System.Drawing.Point(755, 272);
			this.button20.Name = "button20";
			this.button20.Size = new System.Drawing.Size(119, 38);
			this.button20.TabIndex = 24;
			this.button20.Text = "测试";
			this.button20.UseVisualStyleBackColor = true;
			this.button20.Click += new System.EventHandler(this.button20_Click);
			// 
			// button21
			// 
			this.button21.Location = new System.Drawing.Point(618, 272);
			this.button21.Name = "button21";
			this.button21.Size = new System.Drawing.Size(106, 38);
			this.button21.TabIndex = 23;
			this.button21.Text = "前往等待位";
			this.button21.UseVisualStyleBackColor = true;
			this.button21.Click += new System.EventHandler(this.button21_Click);
			// 
			// button22
			// 
			this.button22.Location = new System.Drawing.Point(474, 272);
			this.button22.Name = "button22";
			this.button22.Size = new System.Drawing.Size(109, 38);
			this.button22.TabIndex = 22;
			this.button22.Text = "返回停车位";
			this.button22.UseVisualStyleBackColor = true;
			this.button22.Click += new System.EventHandler(this.button22_Click);
			// 
			// button24
			// 
			this.button24.Location = new System.Drawing.Point(315, 272);
			this.button24.Name = "button24";
			this.button24.Size = new System.Drawing.Size(115, 38);
			this.button24.TabIndex = 20;
			this.button24.Text = "前往吊罐位";
			this.button24.UseVisualStyleBackColor = true;
			this.button24.Click += new System.EventHandler(this.button24_Click);
			// 
			// button25
			// 
			this.button25.Location = new System.Drawing.Point(162, 272);
			this.button25.Name = "button25";
			this.button25.Size = new System.Drawing.Size(115, 38);
			this.button25.TabIndex = 19;
			this.button25.Text = "前往受铁位";
			this.button25.UseVisualStyleBackColor = true;
			this.button25.Click += new System.EventHandler(this.button25_Click);
			// 
			// label1
			// 
			this.label1.AutoSize = true;
			this.label1.Font = new System.Drawing.Font("宋体", 11F);
			this.label1.Location = new System.Drawing.Point(34, 97);
			this.label1.Name = "label1";
			this.label1.Size = new System.Drawing.Size(142, 22);
			this.label1.TabIndex = 25;
			this.label1.Text = "16号线常用车";
			// 
			// label2
			// 
			this.label2.AutoSize = true;
			this.label2.Font = new System.Drawing.Font("宋体", 11F);
			this.label2.Location = new System.Drawing.Point(34, 152);
			this.label2.Name = "label2";
			this.label2.Size = new System.Drawing.Size(142, 22);
			this.label2.TabIndex = 26;
			this.label2.Text = "16号线备用车";
			// 
			// label3
			// 
			this.label3.AutoSize = true;
			this.label3.Font = new System.Drawing.Font("宋体", 11F);
			this.label3.Location = new System.Drawing.Point(34, 218);
			this.label3.Name = "label3";
			this.label3.Size = new System.Drawing.Size(142, 22);
			this.label3.TabIndex = 27;
			this.label3.Text = "17号线常用车";
			// 
			// label4
			// 
			this.label4.AutoSize = true;
			this.label4.Font = new System.Drawing.Font("宋体", 11F);
			this.label4.Location = new System.Drawing.Point(34, 278);
			this.label4.Name = "label4";
			this.label4.Size = new System.Drawing.Size(142, 22);
			this.label4.TabIndex = 28;
			this.label4.Text = "17号线备用车";
			// 
			// button26
			// 
			this.button26.Location = new System.Drawing.Point(894, 272);
			this.button26.Name = "button26";
			this.button26.Size = new System.Drawing.Size(93, 38);
			this.button26.TabIndex = 32;
			this.button26.Text = "停止";
			this.button26.UseVisualStyleBackColor = true;
			this.button26.Click += new System.EventHandler(this.button26_Click);
			// 
			// button27
			// 
			this.button27.Location = new System.Drawing.Point(894, 212);
			this.button27.Name = "button27";
			this.button27.Size = new System.Drawing.Size(93, 38);
			this.button27.TabIndex = 31;
			this.button27.Text = "停止";
			this.button27.UseVisualStyleBackColor = true;
			this.button27.Click += new System.EventHandler(this.button27_Click);
			// 
			// button28
			// 
			this.button28.Location = new System.Drawing.Point(894, 152);
			this.button28.Name = "button28";
			this.button28.Size = new System.Drawing.Size(93, 38);
			this.button28.TabIndex = 30;
			this.button28.Text = "停止";
			this.button28.UseVisualStyleBackColor = true;
			this.button28.Click += new System.EventHandler(this.button28_Click);
			// 
			// button29
			// 
			this.button29.Location = new System.Drawing.Point(894, 91);
			this.button29.Name = "button29";
			this.button29.Size = new System.Drawing.Size(93, 38);
			this.button29.TabIndex = 29;
			this.button29.Text = "停止";
			this.button29.UseVisualStyleBackColor = true;
			this.button29.Click += new System.EventHandler(this.button29_Click);
			// 
			// button3
			// 
			this.button3.Location = new System.Drawing.Point(162, 316);
			this.button3.Name = "button3";
			this.button3.Size = new System.Drawing.Size(115, 28);
			this.button3.TabIndex = 33;
			this.button3.Text = "0";
			this.button3.UseVisualStyleBackColor = true;
			this.button3.Click += new System.EventHandler(this.button3_Click);
			// 
			// button11
			// 
			this.button11.Location = new System.Drawing.Point(315, 316);
			this.button11.Name = "button11";
			this.button11.Size = new System.Drawing.Size(115, 28);
			this.button11.TabIndex = 34;
			this.button11.Text = "-15";
			this.button11.UseVisualStyleBackColor = true;
			this.button11.Click += new System.EventHandler(this.button11_Click);
			// 
			// button17
			// 
			this.button17.Location = new System.Drawing.Point(474, 319);
			this.button17.Name = "button17";
			this.button17.Size = new System.Drawing.Size(109, 25);
			this.button17.TabIndex = 35;
			this.button17.Text = "15";
			this.button17.UseVisualStyleBackColor = true;
			this.button17.Click += new System.EventHandler(this.button17_Click);
			// 
			// button23
			// 
			this.button23.Location = new System.Drawing.Point(618, 321);
			this.button23.Name = "button23";
			this.button23.Size = new System.Drawing.Size(106, 23);
			this.button23.TabIndex = 36;
			this.button23.Text = "34";
			this.button23.UseVisualStyleBackColor = true;
			this.button23.Click += new System.EventHandler(this.button23_Click);
			// 
			// button30
			// 
			this.button30.Location = new System.Drawing.Point(755, 321);
			this.button30.Name = "button30";
			this.button30.Size = new System.Drawing.Size(119, 23);
			this.button30.TabIndex = 37;
			this.button30.Text = "急停";
			this.button30.UseVisualStyleBackColor = true;
			this.button30.Click += new System.EventHandler(this.button30_Click);
			// 
			// CustomMessageBox3
			// 
			this.ClientSize = new System.Drawing.Size(1099, 459);
			this.Controls.Add(this.button30);
			this.Controls.Add(this.button23);
			this.Controls.Add(this.button17);
			this.Controls.Add(this.button11);
			this.Controls.Add(this.button3);
			this.Controls.Add(this.button26);
			this.Controls.Add(this.button27);
			this.Controls.Add(this.button28);
			this.Controls.Add(this.button29);
			this.Controls.Add(this.label4);
			this.Controls.Add(this.label3);
			this.Controls.Add(this.label2);
			this.Controls.Add(this.label1);
			this.Controls.Add(this.button20);
			this.Controls.Add(this.button21);
			this.Controls.Add(this.button22);
			this.Controls.Add(this.button24);
			this.Controls.Add(this.button25);
			this.Controls.Add(this.button14);
			this.Controls.Add(this.button15);
			this.Controls.Add(this.button18);
			this.Controls.Add(this.button19);
			this.Controls.Add(this.button8);
			this.Controls.Add(this.button9);
			this.Controls.Add(this.button10);
			this.Controls.Add(this.button12);
			this.Controls.Add(this.button13);
			this.Controls.Add(this.button7);
			this.Controls.Add(this.button6);
			this.Controls.Add(this.button5);
			this.Controls.Add(this.button2);
			this.Controls.Add(this.button1);
			this.Name = "CustomMessageBox3";
			this.Load += new System.EventHandler(this.CustomMessageBox3_Load);
			this.ResumeLayout(false);
			this.PerformLayout();

		}
		banzidong banzidong = new banzidong();



		private void button1_Click(object sender, EventArgs e)
		{
            ButtonGlowManager.ApplyButtonGlow(button1, Controls);

            banzidong.chushihuao(global_var2, 1, 1);         
        }

		private void button13_Click(object sender, EventArgs e)
		{
            ButtonGlowManager.ApplyButtonGlow(button13, Controls);

            banzidong.chushihuao(global_var2, 2, 1);
		}

		private void button19_Click(object sender, EventArgs e)
		{
            ButtonGlowManager.ApplyButtonGlow(button19, Controls);

            banzidong.chushihuao(global_var2, 3, 1);
		}

		private void button25_Click(object sender, EventArgs e)
		{
            ButtonGlowManager.ApplyButtonGlow(button25, Controls);

            banzidong.chushihuao(global_var2, 4, 1);
		}

		private void button2_Click(object sender, EventArgs e)
		{
            ButtonGlowManager.ApplyButtonGlow(button2, Controls);

            banzidong.chushihuao(global_var2, 1, 2);
		}

		private void button12_Click(object sender, EventArgs e)
		{
            ButtonGlowManager.ApplyButtonGlow(button12, Controls);

            banzidong.chushihuao(global_var2, 2, 2);
		}

		private void button18_Click(object sender, EventArgs e)
		{
            ButtonGlowManager.ApplyButtonGlow(button18, Controls);

            banzidong.chushihuao(global_var2, 3, 2);
		}

		private void button24_Click(object sender, EventArgs e)
		{
            ButtonGlowManager.ApplyButtonGlow(button24, Controls);

            banzidong.chushihuao(global_var2, 4, 2);
		}



		private void button10_Click(object sender, EventArgs e)
		{
            ButtonGlowManager.ApplyButtonGlow(button10, Controls);

            banzidong.chushihuao(global_var2, 2, 4);
		}



		private void button22_Click(object sender, EventArgs e)
		{
            ButtonGlowManager.ApplyButtonGlow(button22, Controls);

            banzidong.chushihuao(global_var2, 4, 4);
		}

		private void button5_Click(object sender, EventArgs e)
		{
            ButtonGlowManager.ApplyButtonGlow(button5, Controls);

            banzidong.chushihuao(global_var2, 1, 6);
		}

		private void button9_Click(object sender, EventArgs e)
		{
            ButtonGlowManager.ApplyButtonGlow(button9, Controls);

            banzidong.chushihuao(global_var2, 2, 6);
		}

		private void button15_Click(object sender, EventArgs e)
		{
            ButtonGlowManager.ApplyButtonGlow(button15, Controls);

            banzidong.chushihuao(global_var2, 3, 6);
		}

		private void button21_Click(object sender, EventArgs e)
		{
            ButtonGlowManager.ApplyButtonGlow(button21, Controls);

            banzidong.chushihuao(global_var2, 4, 6);
		}

		private void button6_Click(object sender, EventArgs e)
		{
            ButtonGlowManager.ApplyButtonGlow(button6, Controls);

            banzidong.chushihuao(global_var2, 1, 5);
		}

		private void button8_Click(object sender, EventArgs e)
		{
            ButtonGlowManager.ApplyButtonGlow(button8, Controls);

            banzidong.chushihuao(global_var2, 2, 5);
		}

		private void button14_Click(object sender, EventArgs e)
		{
            ButtonGlowManager.ApplyButtonGlow(button14, Controls);

            banzidong.chushihuao(global_var2, 3, 5);
		}

		private void button20_Click(object sender, EventArgs e)
		{
            ButtonGlowManager.ApplyButtonGlow(button20, Controls);

            banzidong.chushihuao(global_var2, 4, 5);
		}

		private void button29_Click(object sender, EventArgs e)
		{
            ButtonGlowManager.ApplyButtonGlow(button29, Controls);

            global_var2.zhuangtai_xie(1, 8, 1);//停止状态写1
		}

		private void button28_Click(object sender, EventArgs e)
		{
            ButtonGlowManager.ApplyButtonGlow(button28, Controls);

            global_var2.zhuangtai_xie(2, 8, 1);//停止状态写1
		}

		private void button27_Click(object sender, EventArgs e)
		{
            ButtonGlowManager.ApplyButtonGlow(button27, Controls);

            global_var2.zhuangtai_xie(3, 8, 1);//停止状态写1
		}

		private void button26_Click(object sender, EventArgs e)
		{
            ButtonGlowManager.ApplyButtonGlow(button26, Controls);

            global_var2.zhuangtai_xie(4, 8, 1);//停止状态写1
		}

		private void button7_Click(object sender, EventArgs e)
		{
            ButtonGlowManager.ApplyButtonGlow(button7, Controls);

            global_var2.zhuangtai_xie(1, 8, 1);//停止状态写1
			global_var2.zhuangtai_xie(2, 8, 1);//停止状态写1
			global_var2.zhuangtai_xie(3, 8, 1);//停止状态写1
			global_var2.zhuangtai_xie(4, 8, 1);//停止状态写1
		}

        private void button3_Click(object sender, EventArgs e)//自动转到0度
        {
            ButtonGlowManager.ApplyButtonGlow(button3, Controls);

            //Constant.CommWithPLC.ChuteSwingAny(3, 0);
            //Constant.CommWithPLC.ChuteSwingAnyNoAngel(3, 0);
            Constant.CommWithPLC.ChuteSwingAnyWithStep(3, 0);
        }

        private void button11_Click(object sender, EventArgs e)//自动转到-15度
        {
            ButtonGlowManager.ApplyButtonGlow(button11, Controls);

            // Constant.CommWithPLC.ChuteSwingAny(3, -15);
            //Constant.CommWithPLC.ChuteSwingAnyNoAngel(3, -15);
            Constant.CommWithPLC.ChuteSwingAnyWithStep(3, -15);
        }

        private void button17_Click(object sender, EventArgs e)//自动转到15度
        {
            ButtonGlowManager.ApplyButtonGlow(button17, Controls);

            // Constant.CommWithPLC.ChuteSwingAny(3, 15);
            //Constant.CommWithPLC.ChuteSwingAnyNoAngel(3,15);
            Constant.CommWithPLC.ChuteSwingAnyWithStep(3, 15);
        }

        private void button23_Click(object sender, EventArgs e)  //自动转到34度
        {
            ButtonGlowManager.ApplyButtonGlow(button23, Controls);

            // Constant.CommWithPLC.ChuteSwingAny(3, 34);
           // Constant.CommWithPLC.ChuteSwingAnyNoAngel(3, 34);
            Constant.CommWithPLC.ChuteSwingAnyWithStep(3, 34);
        }

        private void button30_Click(object sender, EventArgs e)
        {
            ButtonGlowManager.ApplyButtonGlow(button30, Controls);

            Constant.CommWithPLC.Stop_Chute_Auto_flag = false;
        }

        private void CustomMessageBox3_Load(object sender, EventArgs e)
        {

        }
        private void dingshiqi(object sender, ElapsedEventArgs e)
        {
           
        }


        }
    public class banzidong
	{
		//窗体变量定义处
		public shoutie_chuangti.CustomMessageBox3 customMessageBox = new shoutie_chuangti.CustomMessageBox3();//双按钮窗体
		public shoutie_chuangti.CustomMessageBox customMessageBox1 = new shoutie_chuangti.CustomMessageBox();//单按钮窗体

		public void qidong_chuangti(object global_var)//初始化窗体的程序，单独线程
		{
			shoutie.global_var global_var1 = (shoutie.global_var)global_var;

			Thread zhuchengxu = new Thread(() => chuangti(global_var));
			zhuchengxu.Start();//启动主线程	
		}

		public void chushihuao(object global_var, int CarNum, int gongneng)//初始化程序
		{
			shoutie.global_var global_var1 = (shoutie.global_var)global_var;

			Thread zhuchengxu = new Thread(() => MyThreadMethod(global_var, CarNum, gongneng));
			zhuchengxu.Start();//启动主线程	

		}

		private void chuangti(object global_var)//窗体的程序，单独线程
		{
			CustomMessageBox3 customMessageBox3 = new CustomMessageBox3(global_var);
			customMessageBox3.ShowDialog();
		}

		private void MyThreadMethod(object global_var1, int CarNum, int gongneng)//主程序
		{
			switch (gongneng)
			{
				case 1:
					shoutie_bzd(CarNum, (shoutie.global_var)global_var1); break;
				case 2:
					xiang_diaoguanwei_yidong(CarNum, (shoutie.global_var)global_var1); break;
				case 3:
					diaoli_bzd(CarNum, (shoutie.global_var)global_var1); break;
				case 4:
					fanhui_bzd(CarNum, (shoutie.global_var)global_var1); break;
				case 5:
					kuadiaowei_bzd(CarNum, (shoutie.global_var)global_var1); break;
				case 6:
					dengdai_bzd(CarNum, (shoutie.global_var)global_var1); break;
			}

		}
		public static int tingchewei_zuobiao = 1;
		public static int shoutiewei_zuobiao = 2;
		public static int dengdaiwei_zuobiao = 3;
		public static int diaoguanwei_zuobiao = 4;
		public static int kuadiaowei_zuobiao = 5;
		void shoutie_bzd(int xiaoche_bianhao, shoutie.global_var global_var1)
		{
			global_var1.zhuangtai_xie(xiaoche_bianhao, 8, 0);//停止状态写0
			if ((int)global_var1.zhuangtai_du(xiaoche_bianhao, 9) == 1)//忙
			{
				customMessageBox1.Text = $"车{xiaoche_bianhao}正在进行其他操作";
				try { customMessageBox1.ShowDialog(); } catch { }
				return;
			}


			global_var1.zhuangtai_xie(xiaoche_bianhao, 9, 1);//忙状态写1
            float  a = global_var1.zuobiao_huoqu(xiaoche_bianhao, shoutiewei_zuobiao);
            float b = (float)global_var1.zhuangtai_du(xiaoche_bianhao, 2);
            if ((float)global_var1.zhuangtai_du(xiaoche_bianhao, 2) < global_var1.zuobiao_huoqu(xiaoche_bianhao, shoutiewei_zuobiao))//车没到受铁位,前进
			{				

				while ((int)global_var1.zhuangtai_du(xiaoche_bianhao, 6) != 2)//开往受铁位
				{
					shoutie.xiaoche_b1.xianche_qianjing(xiaoche_bianhao, xiaoche_bianhao, global_var1.priority_key, global_var1.LineID1, global_var1.LineID2, global_var1);
					global_var1.b1_qianjing_zhuangtai = 1;//设置车处于前进状态，用来更改停车差值用的
					if ((int)global_var1.zhuangtai_du(xiaoche_bianhao, 8) == 1)//判断是否停车
					{
						shoutie.xiaoche_b1.xianche_tingzhi(xiaoche_bianhao, global_var1.LineID1, global_var1.LineID2);
						global_var1.zhuangtai_xie(xiaoche_bianhao, 9, 0);//忙状态写0
						return;
					}
					Thread.Sleep(100);
				}
			}
			else //车没到受铁位,后进
			{
				while ((int)global_var1.zhuangtai_du(xiaoche_bianhao, 6) != 2)//开往受铁位
				{
					shoutie.xiaoche_b1.xianche_houtui(xiaoche_bianhao, xiaoche_bianhao, global_var1.priority_key, global_var1.LineID1, global_var1.LineID2, global_var1);
					global_var1.b1_qianjing_zhuangtai = 0;//设置车处于后退状态，用来更改停车差值用的
					if ((int)global_var1.zhuangtai_du(xiaoche_bianhao, 8) == 1)//判断是否停车
					{
						shoutie.xiaoche_b1.xianche_tingzhi(xiaoche_bianhao, global_var1.LineID1, global_var1.LineID2);
						global_var1.zhuangtai_xie(xiaoche_bianhao, 9, 0);//忙状态写0
						return;
					}
					Thread.Sleep(100);
				}
			}
			shoutie.xiaoche_b1.xianche_tingzhi(xiaoche_bianhao, global_var1.LineID1, global_var1.LineID2);



			if ((int)global_var1.zhuangtai_du(xiaoche_bianhao, 8) == 1)//判断是否停车
			{
				shoutie.xiaoche_b1.xianche_tingzhi(xiaoche_bianhao, global_var1.LineID1, global_var1.LineID2);
				global_var1.zhuangtai_xie(xiaoche_bianhao, 9, 0);//忙状态写0
				return;
			}
			global_var1.zhuangtai_xie(xiaoche_bianhao, 9, 0);//忙状态写0


		}

		void xiang_diaoguanwei_yidong(int xiaoche_bianhao, shoutie.global_var global_var1)//罐车向调罐位移动
		{
			global_var1.zhuangtai_xie(xiaoche_bianhao, 8, 0);//停止状态写0
			if ((int)global_var1.zhuangtai_du(xiaoche_bianhao, 9) == 1)//忙
			{
				customMessageBox1.Text = $"车{xiaoche_bianhao}正在进行其他操作";
				try { customMessageBox1.ShowDialog(); } catch { }
				return;
			}

			global_var1.zhuangtai_xie(xiaoche_bianhao, 9, 1);//忙状态写1
			global_var1.zhuangtai_xie(xiaoche_bianhao, 5, $"{xiaoche_bianhao}等待到达调罐位");


            if ((float)global_var1.zhuangtai_du(xiaoche_bianhao, 2) < global_var1.zuobiao_huoqu(xiaoche_bianhao, diaoguanwei_zuobiao))//车没到调罐位,前🈲
            {

                while ((int)global_var1.zhuangtai_du(xiaoche_bianhao, 6) != 9)//开往吊罐位
                {
                    shoutie.xiaoche_b1.xianche_qianjing(xiaoche_bianhao, xiaoche_bianhao, global_var1.priority_key, global_var1.LineID1, global_var1.LineID2, global_var1);        
                    if ((int)global_var1.zhuangtai_du(xiaoche_bianhao, 8) == 1)//判断是否停车
                    {
                        shoutie.xiaoche_b1.xianche_tingzhi(xiaoche_bianhao, global_var1.LineID1, global_var1.LineID2);
                        global_var1.zhuangtai_xie(xiaoche_bianhao, 9, 0);//忙状态写0
                        return;
                    }
                    Thread.Sleep(100);
                }
            }
            else //车没到吊罐位,后进
            {
                while ((int)global_var1.zhuangtai_du(xiaoche_bianhao, 6) != 9)//开往吊罐位
                {
                    shoutie.xiaoche_b1.xianche_houtui(xiaoche_bianhao, xiaoche_bianhao, global_var1.priority_key, global_var1.LineID1, global_var1.LineID2, global_var1);
                    if ((int)global_var1.zhuangtai_du(xiaoche_bianhao, 8) == 1)//判断是否停车
                    {
                        shoutie.xiaoche_b1.xianche_tingzhi(xiaoche_bianhao, global_var1.LineID1, global_var1.LineID2);
                        global_var1.zhuangtai_xie(xiaoche_bianhao, 9, 0);//忙状态写0
                        return;
                    }
                    Thread.Sleep(100);
                }
            }

			shoutie.xiaoche_b1.xianche_tingzhi(xiaoche_bianhao, global_var1.LineID1, global_var1.LineID2);
			global_var1.zhuangtai_xie(xiaoche_bianhao, 9, 0);//忙状态写0
		}

		void diaoli_bzd(int xiaoche_bianhao, shoutie.global_var global_var1)//罐车向调罐位移动
		{
			global_var1.zhuangtai_xie(xiaoche_bianhao, 8, 0);//停止状态写0
			if ((int)global_var1.zhuangtai_du(xiaoche_bianhao, 9) == 1)//忙
			{
				customMessageBox1.Text = $"车{xiaoche_bianhao}正在进行其他操作";
				try { customMessageBox1.ShowDialog(); } catch { }
				return;
			}

			global_var1.zhuangtai_xie(xiaoche_bianhao, 9, 1);//忙状态写1
			diaoli.shijue.tongzhi_xingche_diaoguan(xiaoche_bianhao, global_var1.LineID1, global_var1.LineID2);//通知调罐
			global_var1.zhuangtai_xie(xiaoche_bianhao, 5, $"{xiaoche_bianhao}等待调离完成");
			while (diaoli.shijue.zhongggun_diaoli(xiaoche_bianhao, global_var1) != 1)//等待调离完成
			{
				if ((int)global_var1.zhuangtai_du(xiaoche_bianhao, 8) == 1)//判断是否停车
				{
					shoutie.xiaoche_b1.xianche_tingzhi(xiaoche_bianhao, global_var1.LineID1, global_var1.LineID2);
					global_var1.zhuangtai_xie(xiaoche_bianhao, 9, 0);//忙状态写0
					return;
				}

				Thread.Sleep(100);

			}
			global_var1.zhuangtai_xie(xiaoche_bianhao, 1, 0);//更新状态，车上无罐
			global_var1.zhuangtai_xie(xiaoche_bianhao, 3, 0);//更新状态，车上无铁水
			diaoli.shijue.tongzhi_xingche_luoguan(xiaoche_bianhao, global_var1.LineID1, global_var1.LineID2);//通知落罐
			global_var1.zhuangtai_xie(xiaoche_bianhao, 5, $"{xiaoche_bianhao}等待落罐完成");
			while (diaoli.shijue.qingguan_luogun(xiaoche_bianhao, global_var1) != 1)//等待落罐完成
			{
				if ((int)global_var1.zhuangtai_du(xiaoche_bianhao, 8) == 1)//判断是否停车
				{
					shoutie.xiaoche_b1.xianche_tingzhi(xiaoche_bianhao, global_var1.LineID1, global_var1.LineID2);
					return;
				}

				Thread.Sleep(100);
			}
			global_var1.zhuangtai_xie(xiaoche_bianhao, 5, $"{xiaoche_bianhao}等待脱钩完成");
			while (diaoli.shijue.tuogou(xiaoche_bianhao, global_var1) != 1)//等待脱钩完成
			{
				if ((int)global_var1.zhuangtai_du(xiaoche_bianhao, 8) == 1)//判断是否停车
				{
					shoutie.xiaoche_b1.xianche_tingzhi(xiaoche_bianhao, global_var1.LineID1, global_var1.LineID2);
					return;
				}

				Thread.Sleep(100);
			}
			global_var1.zhuangtai_xie(xiaoche_bianhao, 9, 0);//忙状态写0
		}

		void fanhui_bzd(int xiaoche_bianhao, shoutie.global_var global_var1)//罐车返回
		{
			global_var1.zhuangtai_xie(xiaoche_bianhao, 8, 0);//停止状态写0
			if ((int)global_var1.zhuangtai_du(xiaoche_bianhao, 9) == 1)//忙
			{
				customMessageBox1.Text = $"车{xiaoche_bianhao}正在进行其他操作";
				try { customMessageBox1.ShowDialog(); } catch { }
				return;
			}


			global_var1.zhuangtai_xie(xiaoche_bianhao, 9, 1);//忙状态写1
			if (xiaoche_bianhao == 3 || xiaoche_bianhao == 1)//当前是常用车
			{
				if ((float)global_var1.zhuangtai_du(xiaoche_bianhao, 2) < global_var1.zuobiao_huoqu(xiaoche_bianhao,shoutiewei_zuobiao))//车没到停车位,前进
				{
					while ((int)global_var1.zhuangtai_du(xiaoche_bianhao, 6) != 2)//开往停车位
					{
						shoutie.xiaoche_b1.xianche_qianjing(xiaoche_bianhao, xiaoche_bianhao, global_var1.priority_key, global_var1.LineID1, global_var1.LineID2, global_var1);
						global_var1.b1_qianjing_zhuangtai = 1;//设置车处于前进状态，用来更改停车差值用的
						if ((int)global_var1.zhuangtai_du(xiaoche_bianhao, 8) == 1)//判断是否停车
						{
							shoutie.xiaoche_b1.xianche_tingzhi(xiaoche_bianhao, global_var1.LineID1, global_var1.LineID2);
							global_var1.zhuangtai_xie(xiaoche_bianhao, 9, 0);//忙状态写0
							return;
						}
						Thread.Sleep(100);
					}
				}
				else//车没到停车位,后进
				{
					while ((int)global_var1.zhuangtai_du(xiaoche_bianhao, 6) != 2)//开往停车位
					{
						shoutie.xiaoche_b1.xianche_houtui(xiaoche_bianhao, xiaoche_bianhao, global_var1.priority_key, global_var1.LineID1, global_var1.LineID2, global_var1);
						global_var1.b1_qianjing_zhuangtai = 0;//设置车处于后退状态，用来更改停车差值用的
						if ((int)global_var1.zhuangtai_du(xiaoche_bianhao, 8) == 1)//判断是否停车
						{
							shoutie.xiaoche_b1.xianche_tingzhi(xiaoche_bianhao, global_var1.LineID1, global_var1.LineID2);
							global_var1.zhuangtai_xie(xiaoche_bianhao, 9, 0);//忙状态写0
							return;
						}
						Thread.Sleep(100);
					}
				}
				shoutie.xiaoche_b1.xianche_tingzhi(xiaoche_bianhao, global_var1.LineID1, global_var1.LineID2);


			}
			if (xiaoche_bianhao == 2 || xiaoche_bianhao == 4)//当前是备用车
			{

				if ((float)global_var1.zhuangtai_du(xiaoche_bianhao, 2) < global_var1.zuobiao_huoqu(xiaoche_bianhao, tingchewei_zuobiao))//车没到停车位,前进
				{
					while ((int)global_var1.zhuangtai_du(xiaoche_bianhao, 6) != 1)//开往停车位
					{
						shoutie.xiaoche_b1.xianche_qianjing(xiaoche_bianhao, xiaoche_bianhao, global_var1.priority_key, global_var1.LineID1, global_var1.LineID2, global_var1);
						global_var1.b1_qianjing_zhuangtai = 1;//设置车处于前进状态，用来更改停车差值用的
						if ((int)global_var1.zhuangtai_du(xiaoche_bianhao, 8) == 1)//判断是否停车
						{
							shoutie.xiaoche_b1.xianche_tingzhi(xiaoche_bianhao, global_var1.LineID1, global_var1.LineID2);
							global_var1.zhuangtai_xie(xiaoche_bianhao, 9, 0);//忙状态写0
							return;
						}
						Thread.Sleep(100);
					}
				}
				else //车没到停车位,后进
				{
					while ((int)global_var1.zhuangtai_du(xiaoche_bianhao, 6) != 1)//开往停车位
					{
						shoutie.xiaoche_b1.xianche_houtui(xiaoche_bianhao, xiaoche_bianhao, global_var1.priority_key, global_var1.LineID1, global_var1.LineID2, global_var1);
						global_var1.b1_qianjing_zhuangtai = 0;//设置车处于后退状态，用来更改停车差值用的
						if ((int)global_var1.zhuangtai_du(xiaoche_bianhao, 8) == 1)//判断是否停车
						{
							shoutie.xiaoche_b1.xianche_tingzhi(xiaoche_bianhao, global_var1.LineID1, global_var1.LineID2);
							global_var1.zhuangtai_xie(xiaoche_bianhao, 9, 0);//忙状态写0
							return;
						}
						Thread.Sleep(100);
					}
				}
				shoutie.xiaoche_b1.xianche_tingzhi(xiaoche_bianhao, global_var1.LineID1, global_var1.LineID2);
			}
			global_var1.zhuangtai_xie(xiaoche_bianhao, 9, 0);//忙状态写0
		}
		void kuadiaowei_bzd(int xiaoche_bianhao, shoutie.global_var global_var1)//罐车开往跨吊位
		{
			global_var1.zhuangtai_xie(xiaoche_bianhao, 8, 0);//停止状态写0
			if ((int)global_var1.zhuangtai_du(xiaoche_bianhao, 9) == 1)//忙
			{
				customMessageBox1.Text = $"车{xiaoche_bianhao}正在进行其他操作";
				try { customMessageBox1.ShowDialog(); } catch { }
				return;
			}
			global_var1.zhuangtai_xie(xiaoche_bianhao, 9, 1);//忙状态写1
			if ((float)global_var1.zhuangtai_du(xiaoche_bianhao, 2) < global_var1.zuobiao_huoqu(xiaoche_bianhao, kuadiaowei_zuobiao))//车没到跨吊位,前进
			{
				while ((int)global_var1.zhuangtai_du(xiaoche_bianhao, 6) != 10)//开往跨吊位
				{
					shoutie.xiaoche_b1.xianche_qianjing(xiaoche_bianhao, xiaoche_bianhao, global_var1.priority_key, global_var1.LineID1, global_var1.LineID2, global_var1);
					global_var1.b1_qianjing_zhuangtai = 1;//设置车处于前进状态，用来更改停车差值用的
					if ((int)global_var1.zhuangtai_du(xiaoche_bianhao, 8) == 1)//判断是否停车
					{
						shoutie.xiaoche_b1.xianche_tingzhi(xiaoche_bianhao, global_var1.LineID1, global_var1.LineID2);
						global_var1.zhuangtai_xie(xiaoche_bianhao, 9, 0);//忙状态写0
						return;
					}
					Thread.Sleep(100);
				}
			}
			else //车没到跨吊位,后进
			{
				while ((int)global_var1.zhuangtai_du(xiaoche_bianhao, 6) != 10)//开往跨吊位
				{
					shoutie.xiaoche_b1.xianche_houtui(xiaoche_bianhao, xiaoche_bianhao, global_var1.priority_key, global_var1.LineID1, global_var1.LineID2, global_var1);
					global_var1.b1_qianjing_zhuangtai = 0;//设置车处于后退状态，用来更改停车差值用的
					if ((int)global_var1.zhuangtai_du(xiaoche_bianhao, 8) == 1)//判断是否停车
					{
						shoutie.xiaoche_b1.xianche_tingzhi(xiaoche_bianhao, global_var1.LineID1, global_var1.LineID2);
						global_var1.zhuangtai_xie(xiaoche_bianhao, 9, 0);//忙状态写0
						return;
					}
					Thread.Sleep(100);
				}
			}
			shoutie.xiaoche_b1.xianche_tingzhi(xiaoche_bianhao, global_var1.LineID1, global_var1.LineID2);
			global_var1.zhuangtai_xie(xiaoche_bianhao, 9, 0);//忙状态写0
		
		}
		void dengdai_bzd(int xiaoche_bianhao, shoutie.global_var global_var1)//罐车开往等待位，不做任何检测
		{
			global_var1.zhuangtai_xie(xiaoche_bianhao, 8, 0);//停止状态写0
			if ((int)global_var1.zhuangtai_du(xiaoche_bianhao, 9) == 1)//忙
			{
				customMessageBox1.Text = $"车{xiaoche_bianhao}正在进行其他操作";
				try { customMessageBox1.ShowDialog(); } catch { }
				return;
			}
			global_var1.zhuangtai_xie(xiaoche_bianhao, 9, 1);//忙状态写1
				if ((float)global_var1.zhuangtai_du(xiaoche_bianhao, 2) < global_var1.zuobiao_huoqu(xiaoche_bianhao, dengdaiwei_zuobiao))//车没到等待位,前进
				{
					while ((int)global_var1.zhuangtai_du(xiaoche_bianhao, 6) != 6 )//常用车回等待位
					{
						shoutie.xiaoche_b1.xianche_qianjing(xiaoche_bianhao, xiaoche_bianhao, global_var1.priority_key, global_var1.LineID1, global_var1.LineID2, global_var1);//向常用车停车位返回					
						global_var1.b1_qianjing_zhuangtai = 1;//设置车处于前进状态，用来更改停车差值用的
						if ((int)global_var1.zhuangtai_du(xiaoche_bianhao, 8) == 1)//判断是否停车
						{
							shoutie.xiaoche_b1.xianche_tingzhi(xiaoche_bianhao, global_var1.LineID1, global_var1.LineID2);
							global_var1.zhuangtai_xie(xiaoche_bianhao, 9, 0);//忙状态写0
							return;
						}
						Thread.Sleep(100);
					}
				}
				else //车没到等待位,后进
				{
					while ((int)global_var1.zhuangtai_du(xiaoche_bianhao, 6) != 6)//常用车回等待位
					{
						shoutie.xiaoche_b1.xianche_houtui(xiaoche_bianhao, xiaoche_bianhao, global_var1.priority_key, global_var1.LineID1, global_var1.LineID2, global_var1);//向常用车停车位返回					
						global_var1.b1_qianjing_zhuangtai = 0;//设置车处于后退状态，用来更改停车差值用的
						if ((int)global_var1.zhuangtai_du(xiaoche_bianhao, 8) == 1)//判断是否停车
						{
							shoutie.xiaoche_b1.xianche_tingzhi(xiaoche_bianhao, global_var1.LineID1, global_var1.LineID2);
							global_var1.zhuangtai_xie(xiaoche_bianhao, 9, 0);//忙状态写0
							return;
						}
						Thread.Sleep(100);
					}
				}
				shoutie.xiaoche_b1.xianche_tingzhi(xiaoche_bianhao, global_var1.LineID1, global_var1.LineID2);	
			global_var1.zhuangtai_xie(xiaoche_bianhao, 9, 0);//忙状态写0
		}


	}
}
