/*
 * File: kron.c
 *
 * MATLAB Coder version            : 3.4
 * C/C++ source code generated on  : 18-Jun-2023 15:57:58
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "testangle.h"
#include "kron.h"

/* Function Definitions */

/*
 * Arguments    : const creal_T A[4]
 *                const creal_T B[4]
 *                creal_T K[16]
 * Return Type  : void
 */
void kron(const creal_T A[4], const creal_T B[4], creal_T K[16])
{
  int kidx;
  int i1;
  int i2;
  kidx = -1;
  for (i1 = 0; i1 < 4; i1++) {
    for (i2 = 0; i2 < 4; i2++) {
      kidx++;
      K[kidx].re = A[i1].re * B[i2].re - A[i1].im * B[i2].im;
      K[kidx].im = A[i1].re * B[i2].im + A[i1].im * B[i2].re;
    }
  }
}

/*
 * File trailer for kron.c
 *
 * [EOF]
 */
