/*
 * File: abs.c
 *
 * MATLAB Coder version            : 3.4
 * C/C++ source code generated on  : 18-Jun-2023 15:57:58
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "testangle.h"
#include "abs.h"

/* Function Definitions */

/*
 * Arguments    : const double x[1000000]
 *                double y[1000000]
 * Return Type  : void
 */
void b_abs(const double x[1000000], double y[1000000])
{
  int k;
  for (k = 0; k < 1000000; k++) {
    y[k] = fabs(x[k]);
  }
}

/*
 * File trailer for abs.c
 *
 * [EOF]
 */
