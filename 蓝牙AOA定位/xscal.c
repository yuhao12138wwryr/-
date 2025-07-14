/*
 * File: xscal.c
 *
 * MATLAB Coder version            : 3.4
 * C/C++ source code generated on  : 18-Jun-2023 15:57:58
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "testangle.h"
#include "xscal.h"

/* Function Definitions */

/*
 * Arguments    : int n
 *                const creal_T a
 *                creal_T x[121]
 *                int ix0
 * Return Type  : void
 */
void b_xscal(int n, const creal_T a, creal_T x[121], int ix0)
{
  int i7;
  int k;
  double x_re;
  double x_im;
  i7 = ix0 + 11 * (n - 1);
  for (k = ix0; k <= i7; k += 11) {
    x_re = x[k - 1].re;
    x_im = x[k - 1].im;
    x[k - 1].re = a.re * x_re - a.im * x_im;
    x[k - 1].im = a.re * x_im + a.im * x_re;
  }
}

/*
 * Arguments    : const creal_T a
 *                creal_T x[121]
 *                int ix0
 * Return Type  : void
 */
void c_xscal(const creal_T a, creal_T x[121], int ix0)
{
  int k;
  double x_re;
  double x_im;
  for (k = ix0; k <= ix0 + 10; k++) {
    x_re = x[k - 1].re;
    x_im = x[k - 1].im;
    x[k - 1].re = a.re * x_re - a.im * x_im;
    x[k - 1].im = a.re * x_im + a.im * x_re;
  }
}

/*
 * Arguments    : int n
 *                const creal_T a
 *                creal_T x[121]
 *                int ix0
 * Return Type  : void
 */
void xscal(int n, const creal_T a, creal_T x[121], int ix0)
{
  int i2;
  int k;
  double x_re;
  double x_im;
  i2 = (ix0 + n) - 1;
  for (k = ix0; k <= i2; k++) {
    x_re = x[k - 1].re;
    x_im = x[k - 1].im;
    x[k - 1].re = a.re * x_re - a.im * x_im;
    x[k - 1].im = a.re * x_im + a.im * x_re;
  }
}

/*
 * File trailer for xscal.c
 *
 * [EOF]
 */
