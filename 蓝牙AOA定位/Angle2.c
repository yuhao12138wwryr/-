/*
 * File: Angle2.c
 *
 * MATLAB Coder version            : 3.4
 * C/C++ source code generated on  : 18-Jun-2023 15:57:58
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "testangle.h"
#include "Angle2.h"
#include "testangle_emxutil.h"
#include "abs.h"
#include "kron.h"
#include "exp.h"
#include "fliplr.h"
#include "sort1.h"
#include "diag.h"
#include "eig.h"
#include "sum.h"
#include "atan.h"
#include "testangle_rtwutil.h"

/* Function Definitions */

/*
 * Arguments    : const double iq[91]
 *                double aq[2]
 * Return Type  : void
 */
void Angle2(const double iq[91], double aq[2])
{
  double xiuzheng[8];
  double B[1000];
  static double Isss[1000000];
  int i;
  double theta[8];
  double count;
  int ix;
  double dataiq[66];
  creal_T dcv0[33];
  creal_T b_dataiq[1089];
  creal_T c_dataiq[33];
  creal_T dcv1[33];
  creal_T dcv2[33];
  creal_T dcv3[121];
  creal_T EV[121];
  creal_T b_EV[121];
  creal_T dcv4[33];
  creal_T x[11];
  int iidx[11];
  double im;
  int ii;
  double re;
  double b_im;
  static double SP[1000000];
  int jj;
  boolean_T exitg1;
  creal_T dcv5[4];
  static const double dv0[4] = { 7.5398223686155044, 5.02654824574367,
    2.5132741228718345, 0.0 };

  creal_T dcv6[4];
  creal_T dcv7[16];
  static const double dv1[4] = { 0.0, 2.5132741228718345, 5.02654824574367,
    7.5398223686155044 };

  emxArray_int32_T *b_ii;
  emxArray_int32_T *b_jj;
  static const signed char iv0[11] = { 1, 2, 3, 4, 7, 8, 11, 12, 13, 14, 15 };

  boolean_T guard1 = false;

  /* 主程序 估算角度 */
  memset(&xiuzheng[0], 0, sizeof(double) << 3);

  /* xiuzheng2=zeros(1,1000);  */
  /* theta=zeros(1000,1);  */
  memset(&B[0], 0, 1000U * sizeof(double));
  memset(&Isss[0], 0, 1000000U * sizeof(double));

  /*  阵元个数    */
  /* d1=-(m-1)/2*dd:dd:(m-1)/2*dd;%步进 */
  /*  信源数 */
  /*  快拍数或者称为采样数 */
  /*  角度->弧度 */
  /*  弧度->角度 */
  for (i = 0; i < 8; i++) {
    theta[i] = iq[2 + (i << 1)] / iq[1 + (i << 1)];
  }

  b_atan(theta);
  for (i = 0; i < 8; i++) {
    theta[i] /= 0.017453292519943295;
  }

  /* 偏移角度 */
  count = 0.0;
  xiuzheng[0] = 0.0;
  for (i = 0; i < 7; i++) {
    if (theta[i + 1] > theta[i]) {
      count++;
    }

    xiuzheng[i + 1] = -(count * 180.0);

    /* 信号拟合 */
  }

  for (i = 0; i < 8; i++) {
    theta[i] += xiuzheng[i];
  }

  for (ix = 0; ix < 7; ix++) {
    B[ix] = fabs(theta[ix] - theta[ix + 1]);
  }

  count = 2.0 * sum(B) / 7.0;

  /*  角度->弧度 */
  for (i = 0; i < 66; i++) {
    dataiq[i] = iq[17 + i] / 127.0;
  }

  /*  这样就有虚部实部了 */
  for (i = 0; i < 33; i++) {
    dcv0[i].re = 0.017453292519943295 * (count * 0.0);
    dcv0[i].im = 0.017453292519943295 * (count * (double)i);
  }

  b_exp(dcv0);
  for (i = 0; i < 33; i++) {
    c_dataiq[i].re = dataiq[i << 1] + 0.0 * dataiq[1 + (i << 1)];
    c_dataiq[i].im = dataiq[1 + (i << 1)];
    for (ix = 0; ix < 33; ix++) {
      b_dataiq[i + 33 * ix].re = c_dataiq[i].re * dcv0[ix].re - c_dataiq[i].im *
        dcv0[ix].im;
      b_dataiq[i + 33 * ix].im = c_dataiq[i].re * dcv0[ix].im + c_dataiq[i].im *
        dcv0[ix].re;
    }
  }

  diag(b_dataiq, c_dataiq);
  for (i = 0; i < 33; i++) {
    dcv0[i] = c_dataiq[i];
    dcv1[i].re = 0.017453292519943295 * (count * 0.0);
    dcv1[i].im = 0.017453292519943295 * (count * (double)i);
  }

  b_exp(dcv1);
  for (i = 0; i < 33; i++) {
    c_dataiq[i].re = dataiq[i << 1] + 0.0 * dataiq[1 + (i << 1)];
    c_dataiq[i].im = dataiq[1 + (i << 1)];
    for (ix = 0; ix < 33; ix++) {
      b_dataiq[i + 33 * ix].re = c_dataiq[i].re * dcv1[ix].re - c_dataiq[i].im *
        dcv1[ix].im;
      b_dataiq[i + 33 * ix].im = c_dataiq[i].re * dcv1[ix].im + c_dataiq[i].im *
        dcv1[ix].re;
    }
  }

  diag(b_dataiq, c_dataiq);
  for (i = 0; i < 33; i++) {
    dcv1[i] = c_dataiq[i];
    dcv2[i] = dcv0[i];
    dcv4[i] = dcv1[i];
  }

  for (i = 0; i < 11; i++) {
    for (ix = 0; ix < 11; ix++) {
      count = 0.0;
      im = 0.0;
      for (ii = 0; ii < 3; ii++) {
        re = dcv4[ix + 11 * ii].re;
        b_im = -dcv4[ix + 11 * ii].im;
        count += dcv2[i + 11 * ii].re * re - dcv2[i + 11 * ii].im * b_im;
        im += dcv2[i + 11 * ii].re * b_im + dcv2[i + 11 * ii].im * re;
      }

      if (im == 0.0) {
        dcv3[i + 11 * ix].re = count / 3.0;
        dcv3[i + 11 * ix].im = 0.0;
      } else if (count == 0.0) {
        dcv3[i + 11 * ix].re = 0.0;
        dcv3[i + 11 * ix].im = im / 3.0;
      } else {
        dcv3[i + 11 * ix].re = count / 3.0;
        dcv3[i + 11 * ix].im = im / 3.0;
      }
    }
  }

  eig(dcv3, EV, b_EV);
  b_diag(b_EV, x);
  sort(x, iidx);
  for (i = 0; i < 11; i++) {
    for (ix = 0; ix < 11; ix++) {
      b_EV[ix + 11 * i] = EV[ix + 11 * (iidx[i] - 1)];
    }
  }

  fliplr(b_EV);

  /* Un = EV(:,1+1:M); */
  /*  角度->弧度 */
  /*  弧度->角度 */
  for (ii = 0; ii < 361; ii++) {
    count = (1.0 + (double)ii) / 2.0 * 0.017453292519943295;
    b_im = sin(count);
    re = sin(count);
    for (jj = 0; jj < 361; jj++) {
      /*    thet(ii) =(ii-361)/4;  */
      /*    f(jj) = (jj-361)/4; */
      count = (1.0 + (double)jj) / 2.0 * 0.017453292519943295;
      im = cos(count);
      count = sin(count);

      /*  a = [a1;a2]; */
      for (i = 0; i < 4; i++) {
        dcv5[i].re = count * (re * 0.0);
        dcv5[i].im = count * (re * dv0[i]);
      }

      c_exp(dcv5);
      for (i = 0; i < 4; i++) {
        dcv6[i].re = im * (b_im * 0.0);
        dcv6[i].im = im * (b_im * dv1[i]);
      }

      c_exp(dcv6);
      kron(dcv5, dcv6, dcv7);
      count = 0.0;
      im = 0.0;
      for (i = 0; i < 11; i++) {
        count += dcv7[iv0[i]].re * b_EV[i].re - -dcv7[iv0[i]].im * b_EV[i].im;
        im += dcv7[iv0[i]].re * b_EV[i].im + -dcv7[iv0[i]].im * b_EV[i].re;
      }

      count = rt_hypotd_snf(count, im);
      Isss[ii + 1000 * jj] = count * count;
    }
  }

  b_abs(Isss, SP);
  for (i = 0; i < 1000; i++) {
    ix = i * 1000;
    ii = i * 1000 + 1;
    count = SP[ix];
    if (rtIsNaN(SP[ix])) {
      jj = ii;
      exitg1 = false;
      while ((!exitg1) && (jj + 1 <= ix + 1000)) {
        ii = jj + 1;
        if (!rtIsNaN(SP[jj])) {
          count = SP[jj];
          exitg1 = true;
        } else {
          jj++;
        }
      }
    }

    if (ii < ix + 1000) {
      while (ii + 1 <= ix + 1000) {
        if (SP[ii] > count) {
          count = SP[ii];
        }

        ii++;
      }
    }

    B[i] = count;
  }

  ii = 1;
  count = B[0];
  if (rtIsNaN(B[0])) {
    ix = 2;
    exitg1 = false;
    while ((!exitg1) && (ix < 1001)) {
      ii = ix;
      if (!rtIsNaN(B[ix - 1])) {
        count = B[ix - 1];
        exitg1 = true;
      } else {
        ix++;
      }
    }
  }

  if (ii < 1000) {
    while (ii + 1 < 1001) {
      if (B[ii] > count) {
        count = B[ii];
      }

      ii++;
    }
  }

  for (i = 0; i < 1000000; i++) {
    SP[i] /= count;
  }

  for (i = 0; i < 1000; i++) {
    ix = i * 1000;
    ii = i * 1000 + 1;
    count = SP[ix];
    if (rtIsNaN(SP[ix])) {
      jj = ii;
      exitg1 = false;
      while ((!exitg1) && (jj + 1 <= ix + 1000)) {
        ii = jj + 1;
        if (!rtIsNaN(SP[jj])) {
          count = SP[jj];
          exitg1 = true;
        } else {
          jj++;
        }
      }
    }

    if (ii < ix + 1000) {
      while (ii + 1 <= ix + 1000) {
        if (SP[ii] > count) {
          count = SP[ii];
        }

        ii++;
      }
    }

    B[i] = count;
  }

  ii = 1;
  count = B[0];
  if (rtIsNaN(B[0])) {
    ix = 2;
    exitg1 = false;
    while ((!exitg1) && (ix < 1001)) {
      ii = ix;
      if (!rtIsNaN(B[ix - 1])) {
        count = B[ix - 1];
        exitg1 = true;
      } else {
        ix++;
      }
    }
  }

  if (ii < 1000) {
    while (ii + 1 < 1001) {
      if (B[ii] > count) {
        count = B[ii];
      }

      ii++;
    }
  }

  emxInit_int32_T(&b_ii, 1);
  emxInit_int32_T(&b_jj, 1);

  /* 鎵惧嚭Z鐨勬渶澶у?紌max */
  ix = 0;
  i = b_ii->size[0];
  b_ii->size[0] = 1000000;
  emxEnsureCapacity_int32_T(b_ii, i);
  i = b_jj->size[0];
  b_jj->size[0] = 1000000;
  emxEnsureCapacity_int32_T(b_jj, i);
  ii = 1;
  jj = 1;
  exitg1 = false;
  while ((!exitg1) && (jj <= 1000)) {
    guard1 = false;
    if (SP[(ii + 1000 * (jj - 1)) - 1] == count) {
      ix++;
      b_ii->data[ix - 1] = ii;
      b_jj->data[ix - 1] = jj;
      if (ix >= 1000000) {
        exitg1 = true;
      } else {
        guard1 = true;
      }
    } else {
      guard1 = true;
    }

    if (guard1) {
      ii++;
      if (ii > 1000) {
        ii = 1;
        jj++;
      }
    }
  }

  i = b_ii->size[0];
  if (1 > ix) {
    b_ii->size[0] = 0;
  } else {
    b_ii->size[0] = ix;
  }

  emxEnsureCapacity_int32_T(b_ii, i);
  i = b_jj->size[0];
  if (1 > ix) {
    b_jj->size[0] = 0;
  } else {
    b_jj->size[0] = ix;
  }

  emxEnsureCapacity_int32_T(b_jj, i);

  /* 鎵惧嚭Z鐨勬渶澶у?煎搴旂殑妯旱鍧愭爣xmax銆亂max */
  aq[0] = b_jj->data[0];
  aq[1] = b_ii->data[0];

  /* plot3(xmax,ymax,zmax,'k.','markersize',20)   %鏍囪涓?涓粦鑹茬殑鍦嗙偣 */
  /* text(xmax,ymax,zmax,['  x=',num2str(xmax),char(10),'  y=',num2str(ymax),char(10),'  z=',num2str(zmax)]);   %鏍囧嚭鍧愭爣 */
  emxFree_int32_T(&b_jj);
  emxFree_int32_T(&b_ii);
}

/*
 * File trailer for Angle2.c
 *
 * [EOF]
 */
