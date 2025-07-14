/*
 * File: triu.c
 *
 * MATLAB Coder version            : 3.4
 * C/C++ source code generated on  : 18-Jun-2023 15:57:58
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "testangle.h"
#include "triu.h"

/* Function Definitions */

/*
 * Arguments    : creal_T x[121]
 * Return Type  : void
 */
void triu(creal_T x[121])
{
  int istart;
  int j;
  int i;
  istart = 2;
  for (j = 0; j < 10; j++) {
    for (i = istart; i < 12; i++) {
      x[(i + 11 * j) - 1].re = 0.0;
      x[(i + 11 * j) - 1].im = 0.0;
    }

    istart++;
  }
}

/*
 * File trailer for triu.c
 *
 * [EOF]
 */
