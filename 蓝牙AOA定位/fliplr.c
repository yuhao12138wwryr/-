/*
 * File: fliplr.c
 *
 * MATLAB Coder version            : 3.4
 * C/C++ source code generated on  : 18-Jun-2023 15:57:58
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "testangle.h"
#include "fliplr.h"

/* Function Definitions */

/*
 * Arguments    : creal_T x[121]
 * Return Type  : void
 */
void fliplr(creal_T x[121])
{
  int b_j1;
  int i;
  double xtmp_re;
  double xtmp_im;
  for (b_j1 = 0; b_j1 < 5; b_j1++) {
    for (i = 0; i < 11; i++) {
      xtmp_re = x[i + 11 * b_j1].re;
      xtmp_im = x[i + 11 * b_j1].im;
      x[i + 11 * b_j1] = x[i + 11 * (10 - b_j1)];
      x[i + 11 * (10 - b_j1)].re = xtmp_re;
      x[i + 11 * (10 - b_j1)].im = xtmp_im;
    }
  }
}

/*
 * File trailer for fliplr.c
 *
 * [EOF]
 */
