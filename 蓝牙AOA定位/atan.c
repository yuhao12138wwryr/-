/*
 * File: atan.c
 *
 * MATLAB Coder version            : 3.4
 * C/C++ source code generated on  : 18-Jun-2023 15:57:58
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "testangle.h"
#include "atan.h"

/* Function Definitions */

/*
 * Arguments    : double x[8]
 * Return Type  : void
 */
void b_atan(double x[8])
{
  int k;
  for (k = 0; k < 8; k++) {
    x[k] = atan(x[k]);
  }
}

/*
 * File trailer for atan.c
 *
 * [EOF]
 */
