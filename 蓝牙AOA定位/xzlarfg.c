/*
 * File: xzlarfg.c
 *
 * MATLAB Coder version            : 3.4
 * C/C++ source code generated on  : 18-Jun-2023 15:57:58
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "testangle.h"
#include "xzlarfg.h"
#include "recip.h"
#include "xdlapy3.h"
#include "Angle2.h"
#include "xnrm2.h"
#include "testangle_rtwutil.h"

/* Function Definitions */

/*
 * Arguments    : creal_T *alpha1
 *                creal_T *x
 * Return Type  : creal_T
 */
creal_T b_xzlarfg(creal_T *alpha1, creal_T *x)
{
  creal_T tau;
  double xnorm;
  double beta1;
  int knt;
  double ai;
  creal_T b_alpha1;
  double x_re;
  double x_im;
  int k;
  tau.re = 0.0;
  tau.im = 0.0;
  xnorm = rt_hypotd_snf(x->re, x->im);
  if ((xnorm != 0.0) || (alpha1->im != 0.0)) {
    beta1 = xdlapy3(alpha1->re, alpha1->im, xnorm);
    if (alpha1->re >= 0.0) {
      beta1 = -beta1;
    }

    if (fabs(beta1) < 1.0020841800044864E-292) {
      knt = 0;
      do {
        knt++;
        x->re *= 9.9792015476736E+291;
        x->im *= 9.9792015476736E+291;
        beta1 *= 9.9792015476736E+291;
        alpha1->re *= 9.9792015476736E+291;
        alpha1->im *= 9.9792015476736E+291;
      } while (!(fabs(beta1) >= 1.0020841800044864E-292));

      beta1 = xdlapy3(alpha1->re, alpha1->im, rt_hypotd_snf(x->re, x->im));
      if (alpha1->re >= 0.0) {
        beta1 = -beta1;
      }

      xnorm = beta1 - alpha1->re;
      ai = 0.0 - alpha1->im;
      if (ai == 0.0) {
        tau.re = xnorm / beta1;
        tau.im = 0.0;
      } else if (xnorm == 0.0) {
        tau.re = 0.0;
        tau.im = ai / beta1;
      } else {
        tau.re = xnorm / beta1;
        tau.im = ai / beta1;
      }

      b_alpha1.re = alpha1->re - beta1;
      b_alpha1.im = alpha1->im;
      *alpha1 = recip(b_alpha1);
      xnorm = alpha1->re;
      ai = alpha1->im;
      x_re = x->re;
      x_im = x->im;
      x->re = xnorm * x_re - ai * x_im;
      x->im = xnorm * x_im + ai * x_re;
      for (k = 1; k <= knt; k++) {
        beta1 *= 1.0020841800044864E-292;
      }

      alpha1->re = beta1;
      alpha1->im = 0.0;
    } else {
      xnorm = beta1 - alpha1->re;
      ai = 0.0 - alpha1->im;
      if (ai == 0.0) {
        tau.re = xnorm / beta1;
        tau.im = 0.0;
      } else if (xnorm == 0.0) {
        tau.re = 0.0;
        tau.im = ai / beta1;
      } else {
        tau.re = xnorm / beta1;
        tau.im = ai / beta1;
      }

      b_alpha1.re = alpha1->re - beta1;
      b_alpha1.im = alpha1->im;
      *alpha1 = recip(b_alpha1);
      xnorm = alpha1->re;
      ai = alpha1->im;
      x_re = x->re;
      x_im = x->im;
      x->re = xnorm * x_re - ai * x_im;
      x->im = xnorm * x_im + ai * x_re;
      alpha1->re = beta1;
      alpha1->im = 0.0;
    }
  }

  return tau;
}

/*
 * Arguments    : int n
 *                creal_T *alpha1
 *                creal_T x[121]
 *                int ix0
 * Return Type  : creal_T
 */
creal_T xzlarfg(int n, creal_T *alpha1, creal_T x[121], int ix0)
{
  creal_T tau;
  double xnorm;
  double beta1;
  int knt;
  double ai;
  int i1;
  int k;
  creal_T b_alpha1;
  double x_re;
  double x_im;
  tau.re = 0.0;
  tau.im = 0.0;
  if (!(n <= 0)) {
    xnorm = xnrm2(n - 1, x, ix0);
    if ((xnorm != 0.0) || (alpha1->im != 0.0)) {
      beta1 = xdlapy3(alpha1->re, alpha1->im, xnorm);
      if (alpha1->re >= 0.0) {
        beta1 = -beta1;
      }

      if (fabs(beta1) < 1.0020841800044864E-292) {
        knt = 0;
        i1 = (ix0 + n) - 2;
        do {
          knt++;
          for (k = ix0; k <= i1; k++) {
            x_re = x[k - 1].re;
            x_im = x[k - 1].im;
            x[k - 1].re = 9.9792015476736E+291 * x_re - 0.0 * x_im;
            x[k - 1].im = 9.9792015476736E+291 * x_im + 0.0 * x_re;
          }

          beta1 *= 9.9792015476736E+291;
          alpha1->re *= 9.9792015476736E+291;
          alpha1->im *= 9.9792015476736E+291;
        } while (!(fabs(beta1) >= 1.0020841800044864E-292));

        beta1 = xdlapy3(alpha1->re, alpha1->im, xnrm2(n - 1, x, ix0));
        if (alpha1->re >= 0.0) {
          beta1 = -beta1;
        }

        xnorm = beta1 - alpha1->re;
        ai = 0.0 - alpha1->im;
        if (ai == 0.0) {
          tau.re = xnorm / beta1;
          tau.im = 0.0;
        } else if (xnorm == 0.0) {
          tau.re = 0.0;
          tau.im = ai / beta1;
        } else {
          tau.re = xnorm / beta1;
          tau.im = ai / beta1;
        }

        b_alpha1.re = alpha1->re - beta1;
        b_alpha1.im = alpha1->im;
        *alpha1 = recip(b_alpha1);
        i1 = (ix0 + n) - 2;
        for (k = ix0; k <= i1; k++) {
          xnorm = alpha1->re;
          ai = alpha1->im;
          x_re = x[k - 1].re;
          x_im = x[k - 1].im;
          x[k - 1].re = xnorm * x_re - ai * x_im;
          x[k - 1].im = xnorm * x_im + ai * x_re;
        }

        for (k = 1; k <= knt; k++) {
          beta1 *= 1.0020841800044864E-292;
        }

        alpha1->re = beta1;
        alpha1->im = 0.0;
      } else {
        xnorm = beta1 - alpha1->re;
        ai = 0.0 - alpha1->im;
        if (ai == 0.0) {
          tau.re = xnorm / beta1;
          tau.im = 0.0;
        } else if (xnorm == 0.0) {
          tau.re = 0.0;
          tau.im = ai / beta1;
        } else {
          tau.re = xnorm / beta1;
          tau.im = ai / beta1;
        }

        b_alpha1.re = alpha1->re - beta1;
        b_alpha1.im = alpha1->im;
        *alpha1 = recip(b_alpha1);
        i1 = (ix0 + n) - 2;
        for (k = ix0; k <= i1; k++) {
          xnorm = alpha1->re;
          ai = alpha1->im;
          x_re = x[k - 1].re;
          x_im = x[k - 1].im;
          x[k - 1].re = xnorm * x_re - ai * x_im;
          x[k - 1].im = xnorm * x_im + ai * x_re;
        }

        alpha1->re = beta1;
        alpha1->im = 0.0;
      }
    }
  }

  return tau;
}

/*
 * File trailer for xzlarfg.c
 *
 * [EOF]
 */
