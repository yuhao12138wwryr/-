/*
 * File: sum.c
 *
 * MATLAB Coder version            : 3.4
 * C/C++ source code generated on  : 18-Jun-2023 15:57:58
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "testangle.h"
#include "sum.h"

/* Function Definitions */

/*
 * Arguments    : const double x[1000]
 * Return Type  : double
 */
double sum(const double x[1000])
{
  double y;
  int k;
  y = x[0];
  for (k = 0; k < 999; k++) {
    y += x[k + 1];
  }

  return y;
}

/*
 * File trailer for sum.c
 *
 * [EOF]
 */
