/*
 * File: xgemv.c
 *
 * MATLAB Coder version            : 3.4
 * C/C++ source code generated on  : 18-Jun-2023 15:57:58
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "testangle.h"
#include "xgemv.h"

/* Function Definitions */

/*
 * Arguments    : int m
 *                int n
 *                const creal_T A[121]
 *                int ia0
 *                const creal_T x[121]
 *                int ix0
 *                creal_T y[11]
 * Return Type  : void
 */
void xgemv(int m, int n, const creal_T A[121], int ia0, const creal_T x[121],
           int ix0, creal_T y[11])
{
  int iy;
  int i4;
  int iac;
  int ix;
  double c_re;
  double c_im;
  int i5;
  int ia;
  if (n != 0) {
    for (iy = 1; iy <= n; iy++) {
      y[iy - 1].re = 0.0;
      y[iy - 1].im = 0.0;
    }

    iy = 0;
    i4 = ia0 + 11 * (n - 1);
    for (iac = ia0; iac <= i4; iac += 11) {
      ix = ix0 - 1;
      c_re = 0.0;
      c_im = 0.0;
      i5 = (iac + m) - 1;
      for (ia = iac - 1; ia + 1 <= i5; ia++) {
        c_re += A[ia].re * x[ix].re + A[ia].im * x[ix].im;
        c_im += A[ia].re * x[ix].im - A[ia].im * x[ix].re;
        ix++;
      }

      y[iy].re += c_re - 0.0 * c_im;
      y[iy].im += c_im + 0.0 * c_re;
      iy++;
    }
  }
}

/*
 * File trailer for xgemv.c
 *
 * [EOF]
 */
