using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Threading;
using shoutie;
using System.Timers;

namespace shoutie
{
    public partial class Form1 : Form
    {
        shoutie.global_var global_var = new shoutie.global_var();
        public Form1()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            shoutie.AffectedIron yuhao = new shoutie.AffectedIron();
            yuhao.chushihuao(global_var, 1);
        }

        private void button2_Click(object sender, EventArgs e)
        {
            global_var.over_proj = 1;
            global_var.zhuangtai_xie(1,12,0);//解锁
			global_var.zhuangtai_xie(2, 12,0);
			global_var.zhuangtai_xie(3, 12, 0);
			global_var.zhuangtai_xie(4, 12, 0);
		}

        private void button3_Click(object sender, EventArgs e)
        {
            guanchedida.diaoguan yuhao = new guanchedida.diaoguan();
            yuhao.chushihuao(global_var, 1);
        }

        private void button4_Click(object sender, EventArgs e)
        {
            diaoli.diaoli yuhao = new diaoli.diaoli();
            yuhao.chushihuao(global_var, 1);
        }

        private void button5_Click(object sender, EventArgs e)
        {
            fanhui.fanhui yuhao = new fanhui.fanhui();
            yuhao.chushihuao(global_var, 1);
        }

        private void button6_Click(object sender, EventArgs e)
        {
            weizhi.weizhi yuhao = new weizhi.weizhi();
            yuhao.chushihuao(global_var);
        }

        private void button7_Click(object sender, EventArgs e)
        {
            banzidong.banzidong customMessageBox3 = new banzidong.banzidong();
            customMessageBox3.qidong_chuangti(global_var);
        }

        private void Form1_Load(object sender, EventArgs e)
        {

        }

        private void label1_Click(object sender, EventArgs e)
        {

        }



	}
}
