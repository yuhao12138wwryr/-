/*
 * File: xungorghr.c
 *
 * MATLAB Coder version            : 3.4
 * C/C++ source code generated on  : 18-Jun-2023 15:57:58
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "testangle.h"
#include "xungorghr.h"
#include "xzlarf.h"

/* Function Definitions */

/*
 * Arguments    : creal_T A[121]
 *                const creal_T tau[10]
 * Return Type  : void
 */
void xungorghr(creal_T A[121], const creal_T tau[10])
{
  int j;
  int i;
  int c;
  int itau;
  creal_T work[11];
  int iaii;
  double a_re;
  double a_im;
  double A_re;
  double A_im;
  for (j = 9; j >= 0; j--) {
    c = (j + 1) * 11 - 1;
    for (i = 1; i <= j + 1; i++) {
      A[c + i].re = 0.0;
      A[c + i].im = 0.0;
    }

    for (i = j + 3; i < 12; i++) {
      A[c + i] = A[(c + i) - 11];
    }
  }

  for (i = 0; i < 11; i++) {
    A[i].re = 0.0;
    A[i].im = 0.0;
    work[i].re = 0.0;
    work[i].im = 0.0;
  }

  A[0].re = 1.0;
  A[0].im = 0.0;
  itau = 9;
  for (i = 9; i >= 0; i--) {
    iaii = (i + i * 11) + 12;
    if (i + 1 < 10) {
      A[iaii].re = 1.0;
      A[iaii].im = 0.0;
      b_xzlarf(10 - i, 9 - i, iaii + 1, tau[itau], A, iaii + 12, work);
      a_re = -tau[itau].re;
      a_im = -tau[itau].im;
      c = iaii - i;
      for (j = iaii + 1; j + 1 <= c + 10; j++) {
        A_re = A[j].re;
        A_im = A[j].im;
        A[j].re = a_re * A_re - a_im * A_im;
        A[j].im = a_re * A_im + a_im * A_re;
      }
    }

    A[iaii].re = 1.0 - tau[itau].re;
    A[iaii].im = 0.0 - tau[itau].im;
    for (j = 1; j <= i; j++) {
      A[iaii - j].re = 0.0;
      A[iaii - j].im = 0.0;
    }

    itau--;
  }
}

/*
 * File trailer for xungorghr.c
 *
 * [EOF]
 */
