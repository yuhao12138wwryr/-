/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2020,��ɿƼ�
 * All rights reserved.
 * ��������QQȺ����Ⱥ��824575535
 *
 * �����������ݰ�Ȩ������ɿƼ����У�δ��������������ҵ��;��
 * ��ӭ��λʹ�ò������������޸�����ʱ���뱣����ɿƼ��İ�Ȩ������
 *
 * @file       		main
 * @company	   		�ɶ���ɿƼ����޹�˾
 * @author     		��ɿƼ�(QQ3184284598)
 * @version    		�鿴doc��version�ļ� �汾˵��
 * @Software 		ADS v1.2.2
 * @Target core		TC264D
 * @Taobao   		https://seekfree.taobao.com/
 * @date       		2020-3-23
 ********************************************************************************************************************/
//com38������

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
int shuru_x=30,shuru_y=255;//�ֱ��������300�ͺ������С250
int shengyuanzuobiao=150;//��Դ����
int shengyuanzuobiao_shu=17;//��Դ����
char caiyici_biaozhi;
int time_huancun1,time_huancun2,time_huancun3;
int i,j,k,m,n;//ѭ��������
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
	get_clk();//��ȡʱ��Ƶ��  ��ر���
    ips114_init();     //��ʼ��TFT��Ļ
    //�û��ڴ˴����ø��ֳ�ʼ��������
	//ʹ��CCU6_0ģ���ͨ��0 ����һ�� 100ms�������ж�
	pit_interrupt_us(CCU6_0, PIT_CH0, 1);
	pit_interrupt_ms(CCU6_0, PIT_CH1, 100);
    gpio_init(P20_11, GPO, 1, PUSHPULL);  //����
    gpio_init(P20_4, GPO, 1, PUSHPULL);  //����P21_2Ϊ���� PULLUP����������
    gpio_init(P20_12, GPO, 1, PUSHPULL);  //����P21_2Ϊ���� PULLUP����������
    gpio_init(P20_13, GPO, 1, PUSHPULL);  //����P21_2Ϊ���� PULLUP����������

    gpio_init(P22_0, GPI, 0, PULLUP);//����s2������
    gpio_init(P22_1, GPI, 0, PULLUP);//����s1,�ƶ�
    gpio_init(P22_2, GPI, 0, PULLUP);//����s1,�ƶ�

    gpio_init(P33_7, GPO, 1, PUSHPULL);  //����P21_2Ϊ���� PULLUP����������
    gpio_init(P33_6, GPO, 1, PUSHPULL);  //����P21_2Ϊ���� PULLUP����������
    gpio_init(P00_9, GPO, 1, PUSHPULL);  //����P21_2Ϊ���� PULLUP����������
    gpio_init(P02_8, GPO, 1, PUSHPULL);  //����P21_2Ϊ���� PULLUP����������
    gpio_set(P02_8, 0);
    gtm_pwm_init(ATOM1_CH2_P21_4, 50,    600);//�������
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
    pwm_duty(ATOM1_CH2_P21_4,387);//Խda��Խ����//275
    pwm_duty(ATOM1_CH1_P33_9,750);//ԽС��Խ���ң���264���򿴣����棩610
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
	//�жϺ�����isr.c�� ��������Ϊcc60_pit_ch0_isr
	//�ж���ص����ò�����isr_config.h��
	//�����ò����� CCU6_0_CH0_INT_SERVICE �� CCU6_0_CH0_ISR_PRIORITY
	//CCU6_0_CH0_INT_SERVICE �жϷ�����
	//CCU6_0_CH0_ISR_PRIORITY �ж����ȼ� ���ȼ���Χ1-255 Խ�����ȼ�Խ�� ��ƽʱʹ�õĵ�Ƭ����һ��

	//��Ҫ�ر�ע�����  �����������ȼ���ͬ���жϺ��� ÿ���жϵ����ȼ��������ǲ�һ����
    enableInterrupts();
//printf("aa");
systick_delay_ms(STM0,600);
ips114_showstr(0,0,"juli"); //��ʾ�ַ���
ips114_showstr(0,2,"jiaodu"); //��ʾ�ַ���
ips114_showstr(0,4,"x"); //��ʾ�ַ���
ips114_showstr(0,6,"y"); //��ʾ�ַ���
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
 //    adc_valu[2] =  adc_mean_filter1(ADC_0,ADC0_CH5_A5,ADC_12BIT,3);//ADC0_CH2_A2�����ǣ����ֻ���
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
{chufabiaozhi=0;//�����������
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
//    disatant1=(time_ch0-time_ch1)*0.034;//��������
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
ips114_showstr(0,0,"juli"); //��ʾ�ַ���
ips114_showint32(0,1,juili_2,5);              //��ʾһ��32λ�з�����  ��ȥ����Ч0
ips114_showstr(0,2,"jiaodu"); //��ʾ�ַ���
sitaaa1=atan((x1-shengyuanzuobiao)/y1);
ips114_showint32(0,3,180/3.14*sitaaa1,5);
ips114_showstr(0,4,"x"); //��ʾ�ַ���
ips114_showint32(0,5,y1,5);
ips114_showstr(0,6,"y"); //��ʾ�ַ���
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
ips114_showstr(0,0,"juli"); //��ʾ�ַ���
ips114_showint32(0,1,juili_1,5);              //��ʾһ��32λ�з�����  ��ȥ����Ч0
ips114_showstr(0,2,"jiaodu"); //��ʾ�ַ���
sitaaa=atan((x-shengyuanzuobiao)/y);
ips114_showint32(0,3,180/3.14*sitaaa,5);
ips114_showstr(0,4,"x"); //��ʾ�ַ���
ips114_showint32(0,5,y,5);
ips114_showstr(0,6,"y"); //��ʾ�ַ���
ips114_showint32(0,7,x-150,5);
}

//pwm_duty(ATOM1_CH1_P33_9,((600+1000/3.14*sitaaa1)+(600+1000/3.14*sitaaa))/2);
//       ceshijuli=sqrt((y-shengyuanzuobiao)*(y-shengyuanzuobiao)+x*x);

//        printf("%d,%d,%f,%f,%d,%d\r\n",time_ch0,time_ch1,shijijili,ceshijuli,y,x);
//        printf("%f,%f,%d,%d\r\n",disatant1,zhuixiao2,x,y);

    chufabiaozhi=0;//������ɣ����
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
 //        adc_valu[2] =  adc_mean_filter(ADC_0,ADC0_CH5_A5,ADC_12BIT,200);//ADC0_CH2_A2�����ǣ����ֻ���
        adc_valu[3] =  adc_mean_filter(ADC_0,ADC0_CH3_A3,ADC_12BIT,200);
 //       adc_valu[4] =  adc_mean_filter(ADC_0,ADC0_CH4_A4,ADC_12BIT,200);
         adc_valu[5] =  adc_mean_filter(ADC_0,ADC0_CH1_A1,ADC_12BIT,200);
    while(adc_valu[1]>110||adc_valu[3]>110||adc_valu[5]>110)
    { adc_valu[1] =  adc_mean_filter(ADC_0,ADC0_CH0_A0,ADC_12BIT,200);
//     adc_valu[2] =  adc_mean_filter(ADC_0,ADC0_CH5_A5,ADC_12BIT,200);//ADC0_CH2_A2�����ǣ����ֻ���
     adc_valu[3] =  adc_mean_filter(ADC_0,ADC0_CH3_A3,ADC_12BIT,200);
 //    adc_valu[4] =  adc_mean_filter(ADC_0,ADC0_CH4_A4,ADC_12BIT,200);
     adc_valu[5] =  adc_mean_filter(ADC_0,ADC0_CH1_A1,ADC_12BIT,200);
     }
    systick_delay_ms(STM0,600);

systick_delay_ms(STM0,400);
}
    }



  }




		//��������֮�� PIT�ж�ÿִ��һ�ξͻ��ӡһ��
        //�����ͨ�����ڴ�ӡ��������ѧϰprintf���̣��˽����ʹ��printf



#pragma section all restore
