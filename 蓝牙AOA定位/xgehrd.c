/*
 * File: xgehrd.c
 *
 * MATLAB Coder version            : 3.4
 * C/C++ source code generated on  : 18-Jun-2023 15:57:58
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "testangle.h"
#include "xgehrd.h"
#include "xzlarf.h"
#include "xzlarfg.h"

/* Function Definitions */

/*
 * Arguments    : creal_T a[121]
 *                creal_T tau[10]
 * Return Type  : void
 */
void xgehrd(creal_T a[121], creal_T tau[10])
{
  int i;
  creal_T work[11];
  int im1n;
  int in;
  creal_T alpha1;
  int u0;
  creal_T b_tau;
  for (i = 0; i < 11; i++) {
    work[i].re = 0.0;
    work[i].im = 0.0;
  }

  for (i = 0; i < 10; i++) {
    im1n = i * 11 + 2;
    in = (i + 1) * 11;
    alpha1 = a[(i + 11 * i) + 1];
    u0 = i + 3;
    if (!(u0 < 11)) {
      u0 = 11;
    }

    tau[i] = xzlarfg(10 - i, &alpha1, a, u0 + i * 11);
    a[(i + 11 * i) + 1].re = 1.0;
    a[(i + 11 * i) + 1].im = 0.0;
    xzlarf(10 - i, i + im1n, tau[i], a, in + 1, work);
    b_tau.re = tau[i].re;
    b_tau.im = -tau[i].im;
    b_xzlarf(10 - i, 10 - i, i + im1n, b_tau, a, (i + in) + 2, work);
    a[(i + 11 * i) + 1] = alpha1;
  }
}

/*
 * File trailer for xgehrd.c
 *
 * [EOF]
 */
