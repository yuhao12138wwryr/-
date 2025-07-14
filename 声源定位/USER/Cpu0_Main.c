/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2020,逐飞科技
 * All rights reserved.
 * 技术讨论QQ群：三群：824575535
 *
 * 以下所有内容版权均属逐飞科技所有，未经允许不得用于商业用途，
 * 欢迎各位使用并传播本程序，修改内容时必须保留逐飞科技的版权声明。
 *
 * @file       		main
 * @company	   		成都逐飞科技有限公司
 * @author     		逐飞科技(QQ3184284598)
 * @version    		查看doc内version文件 版本说明
 * @Software 		ADS v1.2.2
 * @Target core		TC264D
 * @Taobao   		https://seekfree.taobao.com/
 * @date       		2020-3-23
 ********************************************************************************************************************/
//com38是蓝牙

#include "headfile.h"
#pragma section all "cpu0_dsram"
#include "math.h"

char s2=1,s1,s1_diyici,s3;
char helm_enable;
long time_ch0,time_ch1,time_ch2,time_ch3,time_ch4;
extern long time;
float distance13,distance35,distance23,distance34;
char gpio_status1,gpio_status2,gpio_status3,gpio_status4,gpio_status5,chufabiaozhi;
int shengshu=0.034;
char cpu1_chuandi;
int helm,helm_kp,helm_kd,helm_ki;
int distance_last,distance_in;
int helm_heng=400,helm_shu=400;
int adc_valu[8];
int shuru_x=30,shuru_y=255;//分别是竖向的300和横向的最小250
int shengyuanzuobiao=150;//声源坐标
int shengyuanzuobiao_shu=17;//声源坐标
char caiyici_biaozhi;
int time_huancun1,time_huancun2,time_huancun3;
int i,j,k,m,n;//循环计数用
float x,y,x1,y1;
int jieguo31_x[3000];
int jieguo31_y[3000];
float sitaaa,sitaaa1,sitaaa_chuandi;
float juili_1,juili_2;
float disatant1,disatant2,disatant3;
float zhuixiao,zhuixiao12138,zhuixiao1,zhuixiao2=99999,zhuixiao3=99999;
float shijijili,ceshijuli,shiji_chazhi;
float real,real_helm;
float helm_velocity_zero;
int core0_main(void)
{
	disableInterrupts();
	get_clk();//获取时钟频率  务必保留
    ips114_init();     //初始化TFT屏幕
    //用户在此处调用各种初始化函数等
	//使用CCU6_0模块的通道0 产生一个 100ms的周期中断
	pit_interrupt_us(CCU6_0, PIT_CH0, 1);
	pit_interrupt_ms(CCU6_0, PIT_CH1, 100);
    gpio_init(P20_11, GPO, 1, PUSHPULL);  //激光
    gpio_init(P20_4, GPO, 1, PUSHPULL);  //设置P21_2为输入 PULLUP：上拉输入
    gpio_init(P20_12, GPO, 1, PUSHPULL);  //设置P21_2为输入 PULLUP：上拉输入
    gpio_init(P20_13, GPO, 1, PUSHPULL);  //设置P21_2为输入 PULLUP：上拉输入

    gpio_init(P22_0, GPI, 0, PULLUP);//按键s2，单次
    gpio_init(P22_1, GPI, 0, PULLUP);//按键s1,移动
    gpio_init(P22_2, GPI, 0, PULLUP);//按键s1,移动

    gpio_init(P33_7, GPO, 1, PUSHPULL);  //设置P21_2为输入 PULLUP：上拉输入
    gpio_init(P33_6, GPO, 1, PUSHPULL);  //设置P21_2为输入 PULLUP：上拉输入
    gpio_init(P00_9, GPO, 1, PUSHPULL);  //设置P21_2为输入 PULLUP：上拉输入
    gpio_init(P02_8, GPO, 1, PUSHPULL);  //设置P21_2为输入 PULLUP：上拉输入
    gpio_set(P02_8, 0);
    gtm_pwm_init(ATOM1_CH2_P21_4, 50,    600);//两个舵机
    gtm_pwm_init(ATOM1_CH1_P33_9, 50,    600);

    adc_init(ADC_0, ADC0_CH0_A0);
    adc_init(ADC_0, ADC0_CH1_A1);
    adc_init(ADC_0, ADC0_CH2_A2);
    adc_init(ADC_0, ADC0_CH3_A3);
    adc_init(ADC_0, ADC0_CH4_A4);
    adc_init(ADC_0, ADC0_CH5_A5);
    adc_init(ADC_0, ADC0_CH6_A6);
    adc_init(ADC_0, ADC0_CH7_A7);
    real_helm=atan((150.1-shengyuanzuobiao)/(257));
    pwm_duty(ATOM1_CH2_P21_4,387);//越da，越向下//275
    pwm_duty(ATOM1_CH1_P33_9,750);//越小，越向右，从264方向看（背面）610
    pwm_duty(ATOM1_CH1_P33_9,750+920/3.14*real_helm);
 //  while(1)
  // {       gpio_set(P02_8, 1);
  //     real_helm=atan((6.1-shengyuanzuobiao)/(277));
 //   pwm_duty(ATOM1_CH1_P33_9,750+935/3.14*real_helm);
//    systick_delay_ms(STM0, 2000);
 //  real_helm=atan((0.1-shengyuanzuobiao)/(277));
 //      pwm_duty(ATOM1_CH1_P33_9,750+935/3.14*real_helm);
 //     systick_delay_ms(STM0, 2000);
 //      real_helm=atan((300.1-shengyuanzuobiao)/(277));
 //      pwm_duty(ATOM1_CH1_P33_9,750+935/3.14*real_helm);
 //      systick_delay_ms(STM0, 2000);
 //   }
	//中断函数在isr.c中 函数名称为cc60_pit_ch0_isr
	//中断相关的配置参数在isr_config.h内
	//可配置参数有 CCU6_0_CH0_INT_SERVICE 和 CCU6_0_CH0_ISR_PRIORITY
	//CCU6_0_CH0_INT_SERVICE 中断服务者
	//CCU6_0_CH0_ISR_PRIORITY 中断优先级 优先级范围1-255 越大优先级越高 与平时使用的单片机不一样

	//需要特备注意的是  不可以有优先级相同的中断函数 每个中断的优先级都必须是不一样的
    enableInterrupts();
//printf("aa");
systick_delay_ms(STM0,600);
ips114_showstr(0,0,"juli"); //显示字符串
ips114_showstr(0,2,"jiaodu"); //显示字符串
ips114_showstr(0,4,"x"); //显示字符串
ips114_showstr(0,6,"y"); //显示字符串
while (1)
    {helm_enable=0;
    if(gpio_get(P22_0)==0)
    {s2=1;}
    if(gpio_get(P22_1)==0)
        {s1=1;}
    if(gpio_get(P22_2)==0)
       {s3=1;}
 //   adc_mean_filter(ADC_0, ADC0_CH1_A1, ADC_12BIT, 10);
 //    adc_valu[1] =  adc_mean_filter1(ADC_0,ADC0_CH0_A0,ADC_12BIT,3);
 //    adc_valu[2] =  adc_mean_filter1(ADC_0,ADC0_CH5_A5,ADC_12BIT,3);//ADC0_CH2_A2本来是，发现坏了
//     adc_valu[3] =  adc_mean_filter1(ADC_0,ADC0_CH3_A3,ADC_12BIT,3);
 //    adc_valu[4] =  adc_mean_filter1(ADC_0,ADC0_CH4_A4,ADC_12BIT,3);
//     adc_valu[5] =  adc_mean_filter1(ADC_0,ADC0_CH1_A1,ADC_12BIT,3);
//    printf("%d,%d,%d\r\n",adc_valu[1],adc_valu[3],adc_valu[5]);
     adc_valu[1] =  adc_convert(ADC_0,ADC0_CH3_A3,ADC_12BIT);
 //    adc_valu[1] =  adc_mean_filter1(ADC_0,ADC0_CH0_A0,ADC_12BIT,3);
if(adc_valu[1]>1700||adc_valu[1]<1300)
{ if(gpio_status1==0)
{  if(chufabiaozhi==0)
    {chufabiaozhi=1;
      time_ch0=0;
      time=0;
    }
if(chufabiaozhi==1)
{time_ch0=time;}
gpio_status1=1;
}
}

adc_valu[5] =  adc_convert(ADC_0,ADC0_CH1_A1,ADC_12BIT);
//adc_valu[5] =  adc_mean_filter1(ADC_0,ADC0_CH1_A1,ADC_12BIT,3);
if(adc_valu[5]>1700||adc_valu[5]<1300)
{ if(gpio_status5==0)
{  if(chufabiaozhi==0)
    {chufabiaozhi=1;
      time_ch4=0;
      time=0; }
  if(chufabiaozhi==1)
  {time_ch4=time;}
gpio_status5=1;
}
}

adc_valu[3] =  adc_convert(ADC_0,ADC0_CH0_A0,ADC_12BIT);
//adc_valu[3] =  adc_mean_filter1(ADC_0,ADC0_CH3_A3,ADC_12BIT,3);
if(adc_valu[3]>1700||adc_valu[3]<1300)
{ if(gpio_status3==0)
{  if(chufabiaozhi==0)
    {chufabiaozhi=1;
      time_ch2=0;
      time=0; }
  if(chufabiaozhi==1)
  {time_ch2=time;}
  gpio_status3=1;
}
}
if(time_ch0>1200||time_ch1>1200||time_ch4>1200||time_ch3>1200||time_ch2>1200)
{chufabiaozhi=0;//参数错误，清除
gpio_status1=0;
gpio_status2=0;
gpio_status3=0;
gpio_status4=0;
gpio_status5=0;

adc_valu[1]=0;
 adc_valu[2]=0;
 adc_valu[3]=0;
 adc_valu[4]=0;
 adc_valu[5]=0;

 time_ch0=0;
 time_ch1=0;
 time_ch2=0;
 time_ch3=0;
 time_ch4=0;}
if(gpio_status1==1&&gpio_status5==1&&gpio_status3==1)
{helm_enable=1;
 //  printf("%d,%d,%d,%d,%d\r\n",time_ch0,time_ch1,time_ch2,time_ch3,time_ch4);
//    disatant1=(time_ch0-time_ch1)*0.034;//乘以音速
    distance13=(time_ch0-time_ch2)*0.034;
    distance35=(time_ch2-time_ch4)*0.034;
 //   distance23=(time_ch1-time_ch2)*0.034;
 //   distance34=(time_ch2-time_ch3)*0.034;
//    shiji_chazhi=sqrt((shuru_x-178)*(shuru_x-178)+shuru_y*shuru_y)-sqrt((shuru_x-122)*(shuru_x-122)+shuru_y*shuru_y);
//    shijijili=sqrt((shuru_x-shengyuanzuobiao)*(shuru_x-shengyuanzuobiao)+shuru_y*shuru_y);
//        printf("%f\r\n",disatant1);
    m=0;
    zhuixiao2=9999;
        for(i=300;i>=0;i--)
    {
        for(j=0;j<=300;j++)
        {
            zhuixiao= sqrt((j+shengyuanzuobiao_shu)*(j+shengyuanzuobiao_shu)+(i-(shengyuanzuobiao+9.5))*(i-(shengyuanzuobiao+9.5)))-sqrt((j+shengyuanzuobiao_shu)*(j+shengyuanzuobiao_shu)+(i-(shengyuanzuobiao))*(i-(shengyuanzuobiao)));
            zhuixiao1=zhuixiao-distance13;
            if(fabs(zhuixiao1)<0.1)
            {

                zhuixiao= sqrt( (j+shengyuanzuobiao_shu)* (j+shengyuanzuobiao_shu)+(i-(shengyuanzuobiao))*(i-(shengyuanzuobiao)))-sqrt((j+shengyuanzuobiao_shu)*(j+shengyuanzuobiao_shu)+(i-(shengyuanzuobiao-9.5))*(i-(shengyuanzuobiao-9.5)))-distance35;
              //printf("%d,%d,%d,%f,%d\r\n",time_ch0,time_ch2,time_ch4,zhuixiao,i);
                if(fabs(zhuixiao)<zhuixiao2)
              {zhuixiao2=fabs(zhuixiao);
            x= i;
            y=j;
              }
 //              printf("%d,%d,%d,%f,%d,%d,%d\r\n",time_ch0,time_ch2,time_ch4,zhuixiao1,j,i,m);
            }
        }
    }
for(i=0;i<=m;i++)
{
}
juili_1=sqrt((x-shengyuanzuobiao)*(x-shengyuanzuobiao)+(y+shengyuanzuobiao_shu)*(y+shengyuanzuobiao_shu));
//zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz

//zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz
sitaaa=180/3.14*atan(x/y);

//real= sqrt(j*j+(i-(shengyuanzuobiao+18.5))*(i-(shengyuanzuobiao+18.5)))-sqrt(j*j+(i-(shengyuanzuobiao))*(i-(shengyuanzuobiao)));
printf("%d,%d,%d,%f,%f,%f,%f\r\n",time_ch0,time_ch2,time_ch4,zhuixiao2,sitaaa,x-150,y);
if(time_ch0-time_ch2<0||time_ch4-time_ch2<0)
{if(s1==0&&fabs(zhuixiao3)<4)
{ pwm_duty(ATOM1_CH1_P33_9,750+935/3.14*sitaaa1);
gpio_set(P02_8, 1);
}
if(s1==1&&s1_diyici==0)
{helm_velocity_zero=750+935/3.14*sitaaa1;
s1_diyici=1;}
sitaaa_chuandi=920/3.14*sitaaa1;
ips114_showstr(0,0,"juli"); //显示字符串
ips114_showint32(0,1,juili_2,5);              //显示一个32位有符号数  并去除无效0
ips114_showstr(0,2,"jiaodu"); //显示字符串
sitaaa1=atan((x1-shengyuanzuobiao)/y1);
ips114_showint32(0,3,180/3.14*sitaaa1,5);
ips114_showstr(0,4,"x"); //显示字符串
ips114_showint32(0,5,y1,5);
ips114_showstr(0,6,"y"); //显示字符串
ips114_showint32(0,7,x1-150,5);
}
else{
    if(s1==0&&fabs(zhuixiao2)<4)
    {  pwm_duty(ATOM1_CH1_P33_9,750+935/3.14*sitaaa);
    gpio_set(P02_8, 1);}
    if(s1==1&&s1_diyici==0)
    {helm_velocity_zero=750+935/3.14*sitaaa;
    s1_diyici=1;}
    sitaaa_chuandi=935/3.14*sitaaa;
ips114_showstr(0,0,"juli"); //显示字符串
ips114_showint32(0,1,juili_1,5);              //显示一个32位有符号数  并去除无效0
ips114_showstr(0,2,"jiaodu"); //显示字符串
sitaaa=atan((x-shengyuanzuobiao)/y);
ips114_showint32(0,3,180/3.14*sitaaa,5);
ips114_showstr(0,4,"x"); //显示字符串
ips114_showint32(0,5,y,5);
ips114_showstr(0,6,"y"); //显示字符串
ips114_showint32(0,7,x-150,5);
}

//pwm_duty(ATOM1_CH1_P33_9,((600+1000/3.14*sitaaa1)+(600+1000/3.14*sitaaa))/2);
//       ceshijuli=sqrt((y-shengyuanzuobiao)*(y-shengyuanzuobiao)+x*x);

//        printf("%d,%d,%f,%f,%d,%d\r\n",time_ch0,time_ch1,shijijili,ceshijuli,y,x);
//        printf("%f,%f,%d,%d\r\n",disatant1,zhuixiao2,x,y);

    chufabiaozhi=0;//运算完成，清除
    gpio_status1=0;
    gpio_status2=0;
    gpio_status3=0;
    gpio_status4=0;
    gpio_status5=0;

    adc_valu[1]=0;
     adc_valu[2]=0;
     adc_valu[3]=0;
     adc_valu[4]=0;
     adc_valu[5]=0;

     time_ch0=0;
     time_ch1=0;
     time_ch2=0;
     time_ch3=0;
     time_ch4=0;
         adc_valu[1] =  adc_mean_filter(ADC_0,ADC0_CH0_A0,ADC_12BIT,200);
 //        adc_valu[2] =  adc_mean_filter(ADC_0,ADC0_CH5_A5,ADC_12BIT,200);//ADC0_CH2_A2本来是，发现坏了
        adc_valu[3] =  adc_mean_filter(ADC_0,ADC0_CH3_A3,ADC_12BIT,200);
 //       adc_valu[4] =  adc_mean_filter(ADC_0,ADC0_CH4_A4,ADC_12BIT,200);
         adc_valu[5] =  adc_mean_filter(ADC_0,ADC0_CH1_A1,ADC_12BIT,200);
    while(adc_valu[1]>110||adc_valu[3]>110||adc_valu[5]>110)
    { adc_valu[1] =  adc_mean_filter(ADC_0,ADC0_CH0_A0,ADC_12BIT,200);
//     adc_valu[2] =  adc_mean_filter(ADC_0,ADC0_CH5_A5,ADC_12BIT,200);//ADC0_CH2_A2本来是，发现坏了
     adc_valu[3] =  adc_mean_filter(ADC_0,ADC0_CH3_A3,ADC_12BIT,200);
 //    adc_valu[4] =  adc_mean_filter(ADC_0,ADC0_CH4_A4,ADC_12BIT,200);
     adc_valu[5] =  adc_mean_filter(ADC_0,ADC0_CH1_A1,ADC_12BIT,200);
     }
    systick_delay_ms(STM0,600);

systick_delay_ms(STM0,400);
}
    }



  }




		//程序运行之后 PIT中断每执行一次就会打印一次
        //将结果通过串口打印，可以先学习printf例程，了解如何使用printf



#pragma section all restore
