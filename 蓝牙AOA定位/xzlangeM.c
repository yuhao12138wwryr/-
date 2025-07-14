/*
 * File: xzlangeM.c
 *
 * MATLAB Coder version            : 3.4
 * C/C++ source code generated on  : 18-Jun-2023 15:57:58
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "testangle.h"
#include "xzlangeM.h"
#include "Angle2.h"
#include "testangle_rtwutil.h"

/* Function Definitions */

/*
 * Arguments    : const creal_T x[121]
 * Return Type  : double
 */
double xzlangeM(const creal_T x[121])
{
  double y;
  int k;
  boolean_T exitg1;
  double absxk;
  y = 0.0;
  k = 0;
  exitg1 = false;
  while ((!exitg1) && (k < 121)) {
    absxk = rt_hypotd_snf(x[k].re, x[k].im);
    if (rtIsNaN(absxk)) {
      y = rtNaN;
      exitg1 = true;
    } else {
      if (absxk > y) {
        y = absxk;
      }

      k++;
    }
  }

  return y;
}

/*
 * File trailer for xzlangeM.c
 *
 * [EOF]
 */
