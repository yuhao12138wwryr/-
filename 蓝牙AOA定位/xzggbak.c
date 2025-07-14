/*
 * File: xzggbak.c
 *
 * MATLAB Coder version            : 3.4
 * C/C++ source code generated on  : 18-Jun-2023 15:57:58
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "testangle.h"
#include "xzggbak.h"

/* Function Definitions */

/*
 * Arguments    : creal_T V[121]
 *                int ilo
 *                int ihi
 *                const int rscale[11]
 * Return Type  : void
 */
void xzggbak(creal_T V[121], int ilo, int ihi, const int rscale[11])
{
  int i;
  int k;
  int j;
  double tmp_re;
  double tmp_im;
  if (ilo > 1) {
    for (i = ilo - 2; i + 1 >= 1; i--) {
      k = rscale[i] - 1;
      if (rscale[i] != i + 1) {
        for (j = 0; j < 11; j++) {
          tmp_re = V[i + 11 * j].re;
          tmp_im = V[i + 11 * j].im;
          V[i + 11 * j] = V[k + 11 * j];
          V[k + 11 * j].re = tmp_re;
          V[k + 11 * j].im = tmp_im;
        }
      }
    }
  }

  if (ihi < 11) {
    for (i = ihi; i + 1 < 12; i++) {
      k = rscale[i] - 1;
      if (rscale[i] != i + 1) {
        for (j = 0; j < 11; j++) {
          tmp_re = V[i + 11 * j].re;
          tmp_im = V[i + 11 * j].im;
          V[i + 11 * j] = V[k + 11 * j];
          V[k + 11 * j].re = tmp_re;
          V[k + 11 * j].im = tmp_im;
        }
      }
    }
  }
}

/*
 * File trailer for xzggbak.c
 *
 * [EOF]
 */
