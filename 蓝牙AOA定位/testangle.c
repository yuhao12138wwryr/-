/*
 * File: testangle.c
 *
 * MATLAB Coder version            : 3.4
 * C/C++ source code generated on  : 18-Jun-2023 15:57:58
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "testangle.h"
#include "Angle2.h"

/* Function Declarations */
static void TWO(double sta1, double fa1, double sta2, double fa2, double x1,
                double b_y1, double z1, double x2, double y2, double z2, double
                TWOD[3]);

/* Function Definitions */

/*
 * Arguments    : double sta1
 *                double fa1
 *                double sta2
 *                double fa2
 *                double x1
 *                double b_y1
 *                double z1
 *                double x2
 *                double y2
 *                double z2
 *                double TWOD[3]
 * Return Type  : void
 */
static void TWO(double sta1, double fa1, double sta2, double fa2, double x1,
                double b_y1, double z1, double x2, double y2, double z2, double
                TWOD[3])
{
  double arf1;
  double beta1;
  double lamd1;
  double arf2;
  double beta2;
  double lamd2;
  double A[12];
  double B[4];
  int p1;
  double x[9];
  double XX[9];
  int p2;
  int p3;
  int itmp;
  double b_A[3];

  /*  角度->弧度 */
  /* sta2=-180;fa2=34;%标签到第一个基站的航向角 */
  /* sta1=0;fa1=73.6;%标签到第二个基站的航向角 */
  /* AAA=pi/2; */
  /* E1=tan(62*derad); */
  arf1 = cos(sta1 * 0.017453292519943295) * cos(fa1 * 0.017453292519943295);
  beta1 = sin(sta1 * 0.017453292519943295) * cos(fa1 * 0.017453292519943295);
  lamd1 = sin(fa1 * 0.017453292519943295);

  /* 转换为系数 */
  arf2 = cos(sta2 * 0.017453292519943295) * cos(fa2 * 0.017453292519943295);
  beta2 = sin(sta2 * 0.017453292519943295) * cos(fa2 * 0.017453292519943295);
  lamd2 = sin(fa2 * 0.017453292519943295);

  /*  */
  /* x1=0;y1=0;z1=0;%第一个基站的坐标 */
  /* x2=4;y2=0;z2=0;%第二个基站的坐标 */
  /* 设置A矩阵 */
  A[0] = beta1;
  A[4] = -arf1;
  A[8] = 0.0;
  A[1] = lamd1;
  A[5] = 0.0;
  A[9] = -arf1;
  A[2] = beta2;
  A[6] = -arf2;
  A[10] = 0.0;
  A[3] = lamd2;
  A[7] = 0.0;
  A[11] = -arf2;
  B[0] = beta1 * x1 - arf1 * b_y1;
  B[1] = lamd1 * x1 - arf1 * z1;
  B[2] = beta2 * x2 - arf2 * y2;
  B[3] = lamd2 * x2 - arf2 * z2;

  /* 设置B矩阵 */
  for (p1 = 0; p1 < 3; p1++) {
    for (p2 = 0; p2 < 3; p2++) {
      XX[p1 + 3 * p2] = 0.0;
      for (p3 = 0; p3 < 4; p3++) {
        XX[p1 + 3 * p2] += A[p3 + (p1 << 2)] * A[p3 + (p2 << 2)];
      }
    }
  }

  memcpy(&x[0], &XX[0], 9U * sizeof(double));
  p1 = 0;
  p2 = 3;
  p3 = 6;
  arf1 = fabs(XX[0]);
  beta1 = fabs(XX[1]);
  lamd1 = fabs(XX[2]);
  if ((beta1 > arf1) && (beta1 > lamd1)) {
    p1 = 3;
    p2 = 0;
    x[0] = XX[1];
    x[1] = XX[0];
    x[3] = XX[4];
    x[4] = XX[3];
    x[6] = XX[7];
    x[7] = XX[6];
  } else {
    if (lamd1 > arf1) {
      p1 = 6;
      p3 = 0;
      x[0] = XX[2];
      x[2] = XX[0];
      x[3] = XX[5];
      x[5] = XX[3];
      x[6] = XX[8];
      x[8] = XX[6];
    }
  }

  arf1 = x[1] / x[0];
  x[1] /= x[0];
  beta1 = x[2] / x[0];
  x[2] /= x[0];
  x[4] -= arf1 * x[3];
  x[5] -= beta1 * x[3];
  x[7] -= arf1 * x[6];
  x[8] -= beta1 * x[6];
  if (fabs(x[5]) > fabs(x[4])) {
    itmp = p2;
    p2 = p3;
    p3 = itmp;
    x[1] = beta1;
    x[2] = arf1;
    arf1 = x[4];
    x[4] = x[5];
    x[5] = arf1;
    arf1 = x[7];
    x[7] = x[8];
    x[8] = arf1;
  }

  arf1 = x[5] / x[4];
  x[5] /= x[4];
  x[8] -= arf1 * x[7];
  arf1 = (x[5] * x[1] - x[2]) / x[8];
  beta1 = -(x[1] + x[7] * arf1) / x[4];
  XX[p1] = ((1.0 - x[3] * beta1) - x[6] * arf1) / x[0];
  XX[p1 + 1] = beta1;
  XX[p1 + 2] = arf1;
  arf1 = -x[5] / x[8];
  beta1 = (1.0 - x[7] * arf1) / x[4];
  XX[p2] = -(x[3] * beta1 + x[6] * arf1) / x[0];
  XX[p2 + 1] = beta1;
  XX[p2 + 2] = arf1;
  arf1 = 1.0 / x[8];
  beta1 = -x[7] * arf1 / x[4];
  XX[p3] = -(x[3] * beta1 + x[6] * arf1) / x[0];
  XX[p3 + 1] = beta1;
  XX[p3 + 2] = arf1;
  for (p1 = 0; p1 < 3; p1++) {
    b_A[p1] = 0.0;
    for (p2 = 0; p2 < 4; p2++) {
      b_A[p1] += A[p2 + (p1 << 2)] * B[p2];
    }
  }

  for (p1 = 0; p1 < 3; p1++) {
    TWOD[p1] = 0.0;
    for (p2 = 0; p2 < 3; p2++) {
      TWOD[p1] += XX[p1 + 3 * p2] * b_A[p2];
    }
  }

  /* 求X矩阵 */
  /* fprintf(b2,"%.2f,",ca);  */
  /* fprintf(b2,"%.2f\n",cb); */
}

/*
 * Arguments    : const double d1[91]
 *                const double d2[91]
 *                double ax1
 *                double ay1
 *                double az1
 *                double ax2
 *                double ay2
 *                double az2
 *                double anss[3]
 * Return Type  : void
 */
void testangle(const double d1[91], const double d2[91], double ax1, double ay1,
               double az1, double ax2, double ay2, double az2, double anss[7])
{
  double aqq1[2];
  double aqq2[2];
  Angle2(d1, aqq1);
  Angle2(d2, aqq2);
  anss[3]=aqq1[0];
   anss[4]=aqq1[1];
     anss[5]=aqq2[0];
	   anss[6]=aqq2[1];  
  TWO(aqq1[0], aqq1[1], aqq2[0], aqq2[1], ax1, ay1, az1, ax2, ay2, az2, anss);
}

/*
 * File trailer for testangle.c
 *
 * [EOF]
 */
