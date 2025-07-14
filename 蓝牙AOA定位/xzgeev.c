/*
 * File: xzgeev.c
 *
 * MATLAB Coder version            : 3.4
 * C/C++ source code generated on  : 18-Jun-2023 15:57:58
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "testangle.h"
#include "xzgeev.h"
#include "xnrm2.h"
#include "xzggev.h"

/* Function Definitions */

/*
 * Arguments    : const creal_T A[121]
 *                int *info
 *                creal_T alpha1[11]
 *                creal_T beta1[11]
 *                creal_T V[121]
 * Return Type  : void
 */
void xzgeev(const creal_T A[121], int *info, creal_T alpha1[11], creal_T beta1
            [11], creal_T V[121])
{
  creal_T At[121];
  int coltop;
  double colnorm;
  int j;
  memcpy(&At[0], &A[0], 121U * sizeof(creal_T));
  xzggev(At, info, alpha1, beta1, V);
  for (coltop = 0; coltop <= 111; coltop += 11) {
    colnorm = b_xnrm2(V, coltop + 1);
    for (j = coltop; j + 1 <= coltop + 11; j++) {
      if (V[j].im == 0.0) {
        V[j].re /= colnorm;
        V[j].im = 0.0;
      } else if (V[j].re == 0.0) {
        V[j].re = 0.0;
        V[j].im /= colnorm;
      } else {
        V[j].re /= colnorm;
        V[j].im /= colnorm;
      }
    }
  }
}

/*
 * File trailer for xzgeev.c
 *
 * [EOF]
 */
