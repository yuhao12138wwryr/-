/*
 * File: xzggev.c
 *
 * MATLAB Coder version            : 3.4
 * C/C++ source code generated on  : 18-Jun-2023 15:57:58
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "testangle.h"
#include "xzggev.h"
#include "xzlascl.h"
#include "xzggbak.h"
#include "xztgevc.h"
#include "xzhgeqz.h"
#include "xzgghrd.h"
#include "xzggbal.h"
#include "isfinite.h"
#include "xzlangeM.h"
#include "sqrt.h"

/* Function Definitions */

/*
 * Arguments    : creal_T A[121]
 *                int *info
 *                creal_T alpha1[11]
 *                creal_T beta1[11]
 *                creal_T V[121]
 * Return Type  : void
 */
void xzggev(creal_T A[121], int *info, creal_T alpha1[11], creal_T beta1[11],
            creal_T V[121])
{
  double BIGNUM;
  double SMLNUM;
  double anrm;
  boolean_T ilascl;
  int i;
  double anrmto;
  int ihi;
  int rscale[11];
  double y;
  *info = 0;
  BIGNUM = 2.2250738585072014E-308;
  b_sqrt(&BIGNUM);
  SMLNUM = BIGNUM / 2.2204460492503131E-16;
  BIGNUM = 1.0 / SMLNUM;
  anrm = xzlangeM(A);
  if (!b_isfinite(anrm)) {
    for (i = 0; i < 11; i++) {
      alpha1[i].re = rtNaN;
      alpha1[i].im = 0.0;
      beta1[i].re = rtNaN;
      beta1[i].im = 0.0;
    }

    for (i = 0; i < 121; i++) {
      V[i].re = rtNaN;
      V[i].im = 0.0;
    }
  } else {
    ilascl = false;
    anrmto = anrm;
    if ((anrm > 0.0) && (anrm < SMLNUM)) {
      anrmto = SMLNUM;
      ilascl = true;
    } else {
      if (anrm > BIGNUM) {
        anrmto = BIGNUM;
        ilascl = true;
      }
    }

    if (ilascl) {
      xzlascl(anrm, anrmto, A);
    }

    xzggbal(A, &i, &ihi, rscale);
    xzgghrd(i, ihi, A, V);
    xzhgeqz(A, i, ihi, V, info, alpha1, beta1);
    if (*info == 0) {
      xztgevc(A, V);
      xzggbak(V, i, ihi, rscale);
      for (i = 0; i < 11; i++) {
        BIGNUM = fabs(V[11 * i].re) + fabs(V[11 * i].im);
        for (ihi = 0; ihi < 10; ihi++) {
          y = fabs(V[(ihi + 11 * i) + 1].re) + fabs(V[(ihi + 11 * i) + 1].im);
          if (y > BIGNUM) {
            BIGNUM = y;
          }
        }

        if (BIGNUM >= SMLNUM) {
          BIGNUM = 1.0 / BIGNUM;
          for (ihi = 0; ihi < 11; ihi++) {
            V[ihi + 11 * i].re *= BIGNUM;
            V[ihi + 11 * i].im *= BIGNUM;
          }
        }
      }

      if (ilascl) {
        b_xzlascl(anrmto, anrm, alpha1);
      }
    }
  }
}

/*
 * File trailer for xzggev.c
 *
 * [EOF]
 */
