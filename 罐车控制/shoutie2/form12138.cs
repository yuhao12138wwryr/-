using System;
using System.Drawing;
using System.Windows.Forms;

namespace shoutie_chuangti
{
	public class CustomMessageBox3 : Form
	{
		private Button button1;
		private Button button2;
		private Button button3;
		public int i;

		public CustomMessageBox3()
		{
			InitializeComponent();
			i = 0;
		}

		private void InitializeComponent()
		{
			this.button1 = new System.Windows.Forms.Button();
			this.button2 = new Button();
			this.button3 = new Button();
			this.SuspendLayout();

			// 
			// button1
			// 
			this.button1.Location = new System.Drawing.Point(110, 200);
			this.button1.Name = "button1";
			this.button1.Size = new System.Drawing.Size(200, 100);
			this.button1.Text = "线路1";
			this.button1.Click += new System.EventHandler(this.Button1_Click);

			// 
			// button2
			// 
			this.button2.Location = new System.Drawing.Point(110, 30);
			this.button2.Name = "button2";
			this.button2.Size = new System.Drawing.Size(200, 100);
			this.button2.Text = "线路2";
			this.button2.Click += new System.EventHandler(this.Button2_Click);

			// 
			// button3
			// 
			this.button3.Location = new System.Drawing.Point(190, 30);
			this.button3.Name = "button3";
			this.button3.Size = new System.Drawing.Size(200, 100);
			this.button3.Text = "3";
			this.button3.Click += new System.EventHandler(this.Button3_Click);

			// 
			// CustomMessageBox3
			// 
			this.ClientSize = new System.Drawing.Size(505, 385);
			this.Controls.Add(this.button1);
			this.Controls.Add(this.button2);
			//this.Controls.Add(this.button3);
			this.Name = "CustomMessageBox3wer";
			this.ResumeLayout(false);
			this.Text = "选择线路";



		}

		private void Button1_Click(object sender, EventArgs e)
		{
			i = 1;
			this.Close();
		}

		private void Button2_Click(object sender, EventArgs e)
		{
			i = 2;
			this.Close();
		}

		private void Button3_Click(object sender, EventArgs e)
		{
			i = 3;
			this.Close();
		}
	}
	public class CustomMessageBox : Form
	{

		private Button button1;
		public int i;
		public CustomMessageBox()
		{
			i = 0;
			InitializeComponent();
		}

		private void InitializeComponent()
		{
			this.button1 = new System.Windows.Forms.Button();
			this.SuspendLayout();

			// 设置窗体属性
			this.ClientSize = new System.Drawing.Size(705, 385);
			this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
			this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
			this.Text = "方向是否正确，确认后注入铁水";





			// 设置按钮属性
			this.button1.Location = new System.Drawing.Point(110, 200);
			this.button1.Name = "button11";
			this.button1.Size = new System.Drawing.Size(200, 100);
			this.button1.Text = "确认";
			this.button1.Click += new System.EventHandler(this.button1_Click);

			// 添加按钮到窗体
			this.ClientSize = new System.Drawing.Size(505, 385);
			this.Controls.Add(this.button1);
			this.ResumeLayout(false);
			this.PerformLayout();
		}

		private void button1_Click(object sender, EventArgs e)
		{
			i = 1;
			this.Close();
		}
	}
}
