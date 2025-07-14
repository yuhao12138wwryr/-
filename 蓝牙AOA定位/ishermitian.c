/*
 * File: ishermitian.c
 *
 * MATLAB Coder version            : 3.4
 * C/C++ source code generated on  : 18-Jun-2023 15:57:58
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "testangle.h"
#include "ishermitian.h"

/* Function Definitions */

/*
 * Arguments    : const creal_T A[121]
 * Return Type  : boolean_T
 */
boolean_T ishermitian(const creal_T A[121])
{
  boolean_T p;
  int j;
  boolean_T exitg2;
  int i;
  int exitg1;
  p = true;
  j = 0;
  exitg2 = false;
  while ((!exitg2) && (j < 11)) {
    i = 0;
    do {
      exitg1 = 0;
      if (i <= j) {
        if (!((A[i + 11 * j].re == A[j + 11 * i].re) && (A[i + 11 * j].im ==
              -A[j + 11 * i].im))) {
          p = false;
          exitg1 = 1;
        } else {
          i++;
        }
      } else {
        j++;
        exitg1 = 2;
      }
    } while (exitg1 == 0);

    if (exitg1 == 1) {
      exitg2 = true;
    }
  }

  return p;
}

/*
 * File trailer for ishermitian.c
 *
 * [EOF]
 */
