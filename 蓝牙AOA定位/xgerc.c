/*
 * File: xgerc.c
 *
 * MATLAB Coder version            : 3.4
 * C/C++ source code generated on  : 18-Jun-2023 15:57:58
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "testangle.h"
#include "xgerc.h"

/* Function Definitions */

/*
 * Arguments    : int m
 *                int n
 *                const creal_T alpha1
 *                int ix0
 *                const creal_T y[11]
 *                creal_T A[121]
 *                int ia0
 * Return Type  : void
 */
void xgerc(int m, int n, const creal_T alpha1, int ix0, const creal_T y[11],
           creal_T A[121], int ia0)
{
  int jA;
  int jy;
  int j;
  double temp_re;
  double temp_im;
  int ix;
  int i6;
  int ijA;
  double A_im;
  if (!((alpha1.re == 0.0) && (alpha1.im == 0.0))) {
    jA = ia0 - 1;
    jy = 0;
    for (j = 1; j <= n; j++) {
      if ((y[jy].re != 0.0) || (y[jy].im != 0.0)) {
        temp_re = y[jy].re * alpha1.re + y[jy].im * alpha1.im;
        temp_im = y[jy].re * alpha1.im - y[jy].im * alpha1.re;
        ix = ix0;
        i6 = m + jA;
        for (ijA = jA; ijA + 1 <= i6; ijA++) {
          A_im = A[ix - 1].re * temp_im + A[ix - 1].im * temp_re;
          A[ijA].re += A[ix - 1].re * temp_re - A[ix - 1].im * temp_im;
          A[ijA].im += A_im;
          ix++;
        }
      }

      jy++;
      jA += 11;
    }
  }
}

/*
 * File trailer for xgerc.c
 *
 * [EOF]
 */
