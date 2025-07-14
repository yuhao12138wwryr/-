/*
 * File: xzgghrd.c
 *
 * MATLAB Coder version            : 3.4
 * C/C++ source code generated on  : 18-Jun-2023 15:57:58
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "testangle.h"
#include "xzgghrd.h"
#include "xzlartg.h"

/* Function Definitions */

/*
 * Arguments    : int ilo
 *                int ihi
 *                creal_T A[121]
 *                creal_T Z[121]
 * Return Type  : void
 */
void xzgghrd(int ilo, int ihi, creal_T A[121], creal_T Z[121])
{
  signed char I[121];
  int k;
  int jcol;
  int jrow;
  double c;
  creal_T s;
  double stemp_re;
  double stemp_im;
  double Z_re;
  double A_re;
  memset(&I[0], 0, 121U * sizeof(signed char));
  for (k = 0; k < 11; k++) {
    I[k + 11 * k] = 1;
  }

  for (k = 0; k < 121; k++) {
    Z[k].re = I[k];
    Z[k].im = 0.0;
  }

  if (!(ihi < ilo + 2)) {
    for (jcol = ilo - 1; jcol + 1 < ihi - 1; jcol++) {
      for (jrow = ihi - 1; jrow + 1 > jcol + 2; jrow--) {
        xzlartg(A[(jrow + 11 * jcol) - 1], A[jrow + 11 * jcol], &c, &s, &A[(jrow
                 + 11 * jcol) - 1]);
        A[jrow + 11 * jcol].re = 0.0;
        A[jrow + 11 * jcol].im = 0.0;
        for (k = jcol + 1; k + 1 < 12; k++) {
          stemp_re = c * A[(jrow + 11 * k) - 1].re + (s.re * A[jrow + 11 * k].re
            - s.im * A[jrow + 11 * k].im);
          stemp_im = c * A[(jrow + 11 * k) - 1].im + (s.re * A[jrow + 11 * k].im
            + s.im * A[jrow + 11 * k].re);
          Z_re = A[(jrow + 11 * k) - 1].im;
          A_re = A[(jrow + 11 * k) - 1].re;
          A[jrow + 11 * k].re = c * A[jrow + 11 * k].re - (s.re * A[(jrow + 11 *
            k) - 1].re + s.im * A[(jrow + 11 * k) - 1].im);
          A[jrow + 11 * k].im = c * A[jrow + 11 * k].im - (s.re * Z_re - s.im *
            A_re);
          A[(jrow + 11 * k) - 1].re = stemp_re;
          A[(jrow + 11 * k) - 1].im = stemp_im;
        }

        s.re = -s.re;
        s.im = -s.im;
        for (k = 0; k + 1 <= ihi; k++) {
          stemp_re = c * A[k + 11 * jrow].re + (s.re * A[k + 11 * (jrow - 1)].re
            - s.im * A[k + 11 * (jrow - 1)].im);
          stemp_im = c * A[k + 11 * jrow].im + (s.re * A[k + 11 * (jrow - 1)].im
            + s.im * A[k + 11 * (jrow - 1)].re);
          Z_re = A[k + 11 * jrow].im;
          A_re = A[k + 11 * jrow].re;
          A[k + 11 * (jrow - 1)].re = c * A[k + 11 * (jrow - 1)].re - (s.re *
            A[k + 11 * jrow].re + s.im * A[k + 11 * jrow].im);
          A[k + 11 * (jrow - 1)].im = c * A[k + 11 * (jrow - 1)].im - (s.re *
            Z_re - s.im * A_re);
          A[k + 11 * jrow].re = stemp_re;
          A[k + 11 * jrow].im = stemp_im;
        }

        for (k = 0; k < 11; k++) {
          stemp_re = c * Z[k + 11 * jrow].re + (s.re * Z[k + 11 * (jrow - 1)].re
            - s.im * Z[k + 11 * (jrow - 1)].im);
          stemp_im = c * Z[k + 11 * jrow].im + (s.re * Z[k + 11 * (jrow - 1)].im
            + s.im * Z[k + 11 * (jrow - 1)].re);
          Z_re = Z[k + 11 * jrow].re;
          Z[k + 11 * (jrow - 1)].re = c * Z[k + 11 * (jrow - 1)].re - (s.re *
            Z[k + 11 * jrow].re + s.im * Z[k + 11 * jrow].im);
          Z[k + 11 * (jrow - 1)].im = c * Z[k + 11 * (jrow - 1)].im - (s.re *
            Z[k + 11 * jrow].im - s.im * Z_re);
          Z[k + 11 * jrow].re = stemp_re;
          Z[k + 11 * jrow].im = stemp_im;
        }
      }
    }
  }
}

/*
 * File trailer for xzgghrd.c
 *
 * [EOF]
 */
