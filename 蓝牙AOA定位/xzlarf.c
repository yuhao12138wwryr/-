/*
 * File: xzlarf.c
 *
 * MATLAB Coder version            : 3.4
 * C/C++ source code generated on  : 18-Jun-2023 15:57:58
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "testangle.h"
#include "xzlarf.h"
#include "xgerc.h"
#include "xgemv.h"

/* Function Definitions */

/*
 * Arguments    : int m
 *                int n
 *                int iv0
 *                const creal_T tau
 *                creal_T C[121]
 *                int ic0
 *                creal_T work[11]
 * Return Type  : void
 */
void b_xzlarf(int m, int n, int iv0, const creal_T tau, creal_T C[121], int ic0,
              creal_T work[11])
{
  int lastv;
  int lastc;
  creal_T b_tau;
  boolean_T exitg2;
  int coltop;
  int ia;
  int exitg1;
  if ((tau.re != 0.0) || (tau.im != 0.0)) {
    lastv = m;
    lastc = iv0 + m;
    while ((lastv > 0) && ((C[lastc - 2].re == 0.0) && (C[lastc - 2].im == 0.0)))
    {
      lastv--;
      lastc--;
    }

    lastc = n;
    exitg2 = false;
    while ((!exitg2) && (lastc > 0)) {
      coltop = ic0 + (lastc - 1) * 11;
      ia = coltop;
      do {
        exitg1 = 0;
        if (ia <= (coltop + lastv) - 1) {
          if ((C[ia - 1].re != 0.0) || (C[ia - 1].im != 0.0)) {
            exitg1 = 1;
          } else {
            ia++;
          }
        } else {
          lastc--;
          exitg1 = 2;
        }
      } while (exitg1 == 0);

      if (exitg1 == 1) {
        exitg2 = true;
      }
    }
  } else {
    lastv = 0;
    lastc = 0;
  }

  if (lastv > 0) {
    xgemv(lastv, lastc, C, ic0, C, iv0, work);
    b_tau.re = -tau.re;
    b_tau.im = -tau.im;
    xgerc(lastv, lastc, b_tau, iv0, work, C, ic0);
  }
}

/*
 * Arguments    : int n
 *                int iv0
 *                const creal_T tau
 *                creal_T C[121]
 *                int ic0
 *                creal_T work[11]
 * Return Type  : void
 */
void xzlarf(int n, int iv0, const creal_T tau, creal_T C[121], int ic0, creal_T
            work[11])
{
  int lastv;
  int lastc;
  int i;
  boolean_T exitg2;
  double c_re;
  double c_im;
  int ix;
  int i3;
  int ia;
  int jy;
  int j;
  int exitg1;
  double temp_re;
  double temp_im;
  if ((tau.re != 0.0) || (tau.im != 0.0)) {
    lastv = n;
    i = iv0 + n;
    while ((lastv > 0) && ((C[i - 2].re == 0.0) && (C[i - 2].im == 0.0))) {
      lastv--;
      i--;
    }

    lastc = 11;
    exitg2 = false;
    while ((!exitg2) && (lastc > 0)) {
      i = (ic0 + lastc) - 1;
      ia = i;
      do {
        exitg1 = 0;
        if (ia <= i + (lastv - 1) * 11) {
          if ((C[ia - 1].re != 0.0) || (C[ia - 1].im != 0.0)) {
            exitg1 = 1;
          } else {
            ia += 11;
          }
        } else {
          lastc--;
          exitg1 = 2;
        }
      } while (exitg1 == 0);

      if (exitg1 == 1) {
        exitg2 = true;
      }
    }
  } else {
    lastv = 0;
    lastc = 0;
  }

  if (lastv > 0) {
    if (lastc != 0) {
      for (i = 1; i <= lastc; i++) {
        work[i - 1].re = 0.0;
        work[i - 1].im = 0.0;
      }

      ix = iv0;
      i3 = ic0 + 11 * (lastv - 1);
      for (jy = ic0; jy <= i3; jy += 11) {
        c_re = C[ix - 1].re - 0.0 * C[ix - 1].im;
        c_im = C[ix - 1].im + 0.0 * C[ix - 1].re;
        i = 0;
        j = (jy + lastc) - 1;
        for (ia = jy; ia <= j; ia++) {
          work[i].re += C[ia - 1].re * c_re - C[ia - 1].im * c_im;
          work[i].im += C[ia - 1].re * c_im + C[ia - 1].im * c_re;
          i++;
        }

        ix++;
      }
    }

    c_re = -tau.re;
    c_im = -tau.im;
    if (!((-tau.re == 0.0) && (-tau.im == 0.0))) {
      i = ic0 - 1;
      jy = iv0 - 1;
      for (j = 1; j <= lastv; j++) {
        if ((C[jy].re != 0.0) || (C[jy].im != 0.0)) {
          temp_re = C[jy].re * c_re + C[jy].im * c_im;
          temp_im = C[jy].re * c_im - C[jy].im * c_re;
          ix = 0;
          i3 = lastc + i;
          for (ia = i; ia + 1 <= i3; ia++) {
            C[ia].re += work[ix].re * temp_re - work[ix].im * temp_im;
            C[ia].im += work[ix].re * temp_im + work[ix].im * temp_re;
            ix++;
          }
        }

        jy++;
        i += 11;
      }
    }
  }
}

/*
 * File trailer for xzlarf.c
 *
 * [EOF]
 */
