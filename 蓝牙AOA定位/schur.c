/*
 * File: schur.c
 *
 * MATLAB Coder version            : 3.4
 * C/C++ source code generated on  : 18-Jun-2023 15:57:58
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "testangle.h"
#include "schur.h"
#include "triu.h"
#include "xhseqr.h"
#include "xungorghr.h"
#include "xgehrd.h"
#include "anyNonFinite.h"

/* Function Definitions */

/*
 * Arguments    : const creal_T A[121]
 *                creal_T V[121]
 *                creal_T T[121]
 * Return Type  : void
 */
void schur(const creal_T A[121], creal_T V[121], creal_T T[121])
{
  int i0;
  creal_T tau[10];
  if (anyNonFinite(A)) {
    for (i0 = 0; i0 < 121; i0++) {
      V[i0].re = rtNaN;
      V[i0].im = 0.0;
    }

    triu(V);
    for (i0 = 0; i0 < 121; i0++) {
      T[i0].re = rtNaN;
      T[i0].im = 0.0;
    }
  } else {
    memcpy(&T[0], &A[0], 121U * sizeof(creal_T));
    xgehrd(T, tau);
    memcpy(&V[0], &T[0], 121U * sizeof(creal_T));
    xungorghr(V, tau);
    xhseqr(T, V);
  }
}

/*
 * File trailer for schur.c
 *
 * [EOF]
 */
