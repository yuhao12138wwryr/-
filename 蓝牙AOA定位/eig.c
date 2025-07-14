/*
 * File: eig.c
 *
 * MATLAB Coder version            : 3.4
 * C/C++ source code generated on  : 18-Jun-2023 15:57:58
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "testangle.h"
#include "eig.h"
#include "schur.h"
#include "xzgeev.h"
#include "ishermitian.h"
#include "anyNonFinite.h"

/* Function Declarations */
static void diagDiagUpperHessNoImag(creal_T D[121]);
static void makeD(const creal_T alpha1[11], const creal_T beta1[11], creal_T D
                  [121]);
static void setDiag(creal_T D[121], const creal_T val);

/* Function Definitions */

/*
 * Arguments    : creal_T D[121]
 * Return Type  : void
 */
static void diagDiagUpperHessNoImag(creal_T D[121])
{
  int j;
  int i;
  D[0].im = 0.0;
  for (j = 0; j < 10; j++) {
    D[(j + 11 * (j + 1)) + 1].im = 0.0;
    D[(j + 11 * j) + 1].re = 0.0;
    D[(j + 11 * j) + 1].im = 0.0;
    for (i = 1; i <= j + 1; i++) {
      D[(i + 11 * (j + 1)) - 1].re = 0.0;
      D[(i + 11 * (j + 1)) - 1].im = 0.0;
    }
  }
}

/*
 * Arguments    : const creal_T alpha1[11]
 *                const creal_T beta1[11]
 *                creal_T D[121]
 * Return Type  : void
 */
static void makeD(const creal_T alpha1[11], const creal_T beta1[11], creal_T D
                  [121])
{
  int k;
  double brm;
  double bim;
  double d;
  for (k = 0; k < 121; k++) {
    D[k].re = 0.0;
    D[k].im = 0.0;
  }

  for (k = 0; k < 11; k++) {
    if (beta1[k].im == 0.0) {
      if (alpha1[k].im == 0.0) {
        D[k + 11 * k].re = alpha1[k].re / beta1[k].re;
        D[k + 11 * k].im = 0.0;
      } else if (alpha1[k].re == 0.0) {
        D[k + 11 * k].re = 0.0;
        D[k + 11 * k].im = alpha1[k].im / beta1[k].re;
      } else {
        D[k + 11 * k].re = alpha1[k].re / beta1[k].re;
        D[k + 11 * k].im = alpha1[k].im / beta1[k].re;
      }
    } else if (beta1[k].re == 0.0) {
      if (alpha1[k].re == 0.0) {
        D[k + 11 * k].re = alpha1[k].im / beta1[k].im;
        D[k + 11 * k].im = 0.0;
      } else if (alpha1[k].im == 0.0) {
        D[k + 11 * k].re = 0.0;
        D[k + 11 * k].im = -(alpha1[k].re / beta1[k].im);
      } else {
        D[k + 11 * k].re = alpha1[k].im / beta1[k].im;
        D[k + 11 * k].im = -(alpha1[k].re / beta1[k].im);
      }
    } else {
      brm = fabs(beta1[k].re);
      bim = fabs(beta1[k].im);
      if (brm > bim) {
        bim = beta1[k].im / beta1[k].re;
        d = beta1[k].re + bim * beta1[k].im;
        D[k + 11 * k].re = (alpha1[k].re + bim * alpha1[k].im) / d;
        D[k + 11 * k].im = (alpha1[k].im - bim * alpha1[k].re) / d;
      } else if (bim == brm) {
        if (beta1[k].re > 0.0) {
          bim = 0.5;
        } else {
          bim = -0.5;
        }

        if (beta1[k].im > 0.0) {
          d = 0.5;
        } else {
          d = -0.5;
        }

        D[k + 11 * k].re = (alpha1[k].re * bim + alpha1[k].im * d) / brm;
        D[k + 11 * k].im = (alpha1[k].im * bim - alpha1[k].re * d) / brm;
      } else {
        bim = beta1[k].re / beta1[k].im;
        d = beta1[k].im + bim * beta1[k].re;
        D[k + 11 * k].re = (bim * alpha1[k].re + alpha1[k].im) / d;
        D[k + 11 * k].im = (bim * alpha1[k].im - alpha1[k].re) / d;
      }
    }
  }
}

/*
 * Arguments    : creal_T D[121]
 *                const creal_T val
 * Return Type  : void
 */
static void setDiag(creal_T D[121], const creal_T val)
{
  int k;
  for (k = 0; k < 11; k++) {
    D[k + 11 * k] = val;
  }
}

/*
 * Arguments    : const creal_T A[121]
 *                creal_T V[121]
 *                creal_T D[121]
 * Return Type  : void
 */
void eig(const creal_T A[121], creal_T V[121], creal_T D[121])
{
  static creal_T dc0 = { 0.0,          /* re */
    0.0                                /* im */
  };

  int info;
  creal_T alpha1[11];
  creal_T beta1[11];
  dc0.re = rtGetNaN();
  if (anyNonFinite(A)) {
    for (info = 0; info < 121; info++) {
      V[info].re = rtNaN;
      V[info].im = 0.0;
      D[info].re = 0.0;
      D[info].im = 0.0;
    }

    setDiag(D, dc0);
  } else if (ishermitian(A)) {
    schur(A, V, D);
    diagDiagUpperHessNoImag(D);
  } else {
    xzgeev(A, &info, alpha1, beta1, V);
    makeD(alpha1, beta1, D);
  }
}

/*
 * File trailer for eig.c
 *
 * [EOF]
 */
