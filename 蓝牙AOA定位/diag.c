/*
 * File: diag.c
 *
 * MATLAB Coder version            : 3.4
 * C/C++ source code generated on  : 18-Jun-2023 15:57:58
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "testangle.h"
#include "diag.h"

/* Function Definitions */

/*
 * Arguments    : const creal_T v[121]
 *                creal_T d[11]
 * Return Type  : void
 */
void b_diag(const creal_T v[121], creal_T d[11])
{
  int j;
  for (j = 0; j < 11; j++) {
    d[j] = v[j * 12];
  }
}

/*
 * Arguments    : const creal_T v[1089]
 *                creal_T d[33]
 * Return Type  : void
 */
void diag(const creal_T v[1089], creal_T d[33])
{
  int j;
  for (j = 0; j < 33; j++) {
    d[j] = v[j * 34];
  }
}

/*
 * File trailer for diag.c
 *
 * [EOF]
 */
