/*
 * File: exp.c
 *
 * MATLAB Coder version            : 3.4
 * C/C++ source code generated on  : 18-Jun-2023 15:57:58
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "testangle.h"
#include "exp.h"

/* Function Definitions */

/*
 * Arguments    : creal_T x[33]
 * Return Type  : void
 */
void b_exp(creal_T x[33])
{
  int k;
  double x_re;
  double r;
  for (k = 0; k < 33; k++) {
    if (x[k].im == 0.0) {
      x_re = exp(x[k].re);
      r = 0.0;
    } else if (rtIsInf(x[k].im) && rtIsInf(x[k].re) && (x[k].re < 0.0)) {
      x_re = 0.0;
      r = 0.0;
    } else {
      r = exp(x[k].re / 2.0);
      x_re = r * (r * cos(x[k].im));
      r *= r * sin(x[k].im);
    }

    x[k].re = x_re;
    x[k].im = r;
  }
}

/*
 * Arguments    : creal_T x[4]
 * Return Type  : void
 */
void c_exp(creal_T x[4])
{
  int k;
  double x_re;
  double r;
  for (k = 0; k < 4; k++) {
    if (x[k].im == 0.0) {
      x_re = exp(x[k].re);
      r = 0.0;
    } else if (rtIsInf(x[k].im) && rtIsInf(x[k].re) && (x[k].re < 0.0)) {
      x_re = 0.0;
      r = 0.0;
    } else {
      r = exp(x[k].re / 2.0);
      x_re = r * (r * cos(x[k].im));
      r *= r * sin(x[k].im);
    }

    x[k].re = x_re;
    x[k].im = r;
  }
}

/*
 * File trailer for exp.c
 *
 * [EOF]
 */
