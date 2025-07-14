/*
 * File: anyNonFinite.c
 *
 * MATLAB Coder version            : 3.4
 * C/C++ source code generated on  : 18-Jun-2023 15:57:58
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "testangle.h"
#include "anyNonFinite.h"

/* Function Definitions */

/*
 * Arguments    : const creal_T x[121]
 * Return Type  : boolean_T
 */
boolean_T anyNonFinite(const creal_T x[121])
{
  boolean_T p;
  int k;
  p = true;
  for (k = 0; k < 121; k++) {
    if (p && ((!(rtIsInf(x[k].re) || rtIsInf(x[k].im))) && (!(rtIsNaN(x[k].re) ||
           rtIsNaN(x[k].im))))) {
      p = true;
    } else {
      p = false;
    }
  }

  return !p;
}

/*
 * File trailer for anyNonFinite.c
 *
 * [EOF]
 */
