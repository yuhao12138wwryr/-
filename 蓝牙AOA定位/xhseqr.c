/*
 * File: xhseqr.c
 *
 * MATLAB Coder version            : 3.4
 * C/C++ source code generated on  : 18-Jun-2023 15:57:58
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "testangle.h"
#include "xhseqr.h"
#include "xzhseqr.h"

/* Function Definitions */

/*
 * Arguments    : creal_T h[121]
 *                creal_T z[121]
 * Return Type  : int
 */
int xhseqr(creal_T h[121], creal_T z[121])
{
  int info;
  int istart;
  int j;
  int i;
  info = eml_zlahqr(h, z);
  istart = 4;
  for (j = 0; j < 8; j++) {
    for (i = istart; i < 12; i++) {
      h[(i + 11 * j) - 1].re = 0.0;
      h[(i + 11 * j) - 1].im = 0.0;
    }

    istart++;
  }

  return info;
}

/*
 * File trailer for xhseqr.c
 *
 * [EOF]
 */
