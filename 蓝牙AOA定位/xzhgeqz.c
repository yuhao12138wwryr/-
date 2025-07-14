/*
 * File: xzhgeqz.c
 *
 * MATLAB Coder version            : 3.4
 * C/C++ source code generated on  : 18-Jun-2023 15:57:58
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "testangle.h"
#include "xzhgeqz.h"
#include "xzlartg.h"
#include "sqrt.h"

/* Function Definitions */

/*
 * Arguments    : creal_T A[121]
 *                int ilo
 *                int ihi
 *                creal_T Z[121]
 *                int *info
 *                creal_T alpha1[11]
 *                creal_T beta1[11]
 * Return Type  : void
 */
void xzhgeqz(creal_T A[121], int ilo, int ihi, creal_T Z[121], int *info,
             creal_T alpha1[11], creal_T beta1[11])
{
  int i;
  double eshift_re;
  double eshift_im;
  creal_T ctemp;
  double anorm;
  double scale;
  double reAij;
  double sumsq;
  double b_atol;
  boolean_T firstNonZero;
  int j;
  int jp1;
  double ascale;
  boolean_T failed;
  boolean_T guard1 = false;
  double imAij;
  boolean_T guard2 = false;
  int ifirst;
  int istart;
  int ilast;
  double temp2;
  int ilastm1;
  int iiter;
  boolean_T goto60;
  boolean_T goto70;
  boolean_T goto90;
  int jiter;
  int exitg1;
  boolean_T exitg2;
  creal_T b_ascale;
  creal_T shift;
  double ad22_re;
  double ad22_im;
  double t1_im;
  *info = 0;
  for (i = 0; i < 11; i++) {
    alpha1[i].re = 0.0;
    alpha1[i].im = 0.0;
    beta1[i].re = 1.0;
    beta1[i].im = 0.0;
  }

  eshift_re = 0.0;
  eshift_im = 0.0;
  ctemp.re = 0.0;
  ctemp.im = 0.0;
  anorm = 0.0;
  if (!(ilo > ihi)) {
    scale = 0.0;
    sumsq = 0.0;
    firstNonZero = true;
    for (j = ilo; j <= ihi; j++) {
      jp1 = j + 1;
      if (ihi < j + 1) {
        jp1 = ihi;
      }

      for (i = ilo; i <= jp1; i++) {
        reAij = A[(i + 11 * (j - 1)) - 1].re;
        imAij = A[(i + 11 * (j - 1)) - 1].im;
        if (reAij != 0.0) {
          anorm = fabs(reAij);
          if (firstNonZero) {
            sumsq = 1.0;
            scale = anorm;
            firstNonZero = false;
          } else if (scale < anorm) {
            temp2 = scale / anorm;
            sumsq = 1.0 + sumsq * temp2 * temp2;
            scale = anorm;
          } else {
            temp2 = anorm / scale;
            sumsq += temp2 * temp2;
          }
        }

        if (imAij != 0.0) {
          anorm = fabs(imAij);
          if (firstNonZero) {
            sumsq = 1.0;
            scale = anorm;
            firstNonZero = false;
          } else if (scale < anorm) {
            temp2 = scale / anorm;
            sumsq = 1.0 + sumsq * temp2 * temp2;
            scale = anorm;
          } else {
            temp2 = anorm / scale;
            sumsq += temp2 * temp2;
          }
        }
      }
    }

    anorm = scale * sqrt(sumsq);
  }

  reAij = 2.2204460492503131E-16 * anorm;
  b_atol = 2.2250738585072014E-308;
  if (reAij > 2.2250738585072014E-308) {
    b_atol = reAij;
  }

  reAij = 2.2250738585072014E-308;
  if (anorm > 2.2250738585072014E-308) {
    reAij = anorm;
  }

  ascale = 1.0 / reAij;
  failed = true;
  for (j = ihi; j + 1 < 12; j++) {
    alpha1[j] = A[j + 11 * j];
  }

  guard1 = false;
  guard2 = false;
  if (ihi >= ilo) {
    ifirst = ilo;
    istart = ilo;
    ilast = ihi - 1;
    ilastm1 = ihi - 2;
    iiter = 0;
    goto60 = false;
    goto70 = false;
    goto90 = false;
    jiter = 1;
    do {
      exitg1 = 0;
      if (jiter <= 30 * ((ihi - ilo) + 1)) {
        if (ilast + 1 == ilo) {
          goto60 = true;
        } else if (fabs(A[ilast + 11 * ilastm1].re) + fabs(A[ilast + 11 *
                    ilastm1].im) <= b_atol) {
          A[ilast + 11 * ilastm1].re = 0.0;
          A[ilast + 11 * ilastm1].im = 0.0;
          goto60 = true;
        } else {
          j = ilastm1;
          exitg2 = false;
          while ((!exitg2) && (j + 1 >= ilo)) {
            if (j + 1 == ilo) {
              firstNonZero = true;
            } else if (fabs(A[j + 11 * (j - 1)].re) + fabs(A[j + 11 * (j - 1)].
                        im) <= b_atol) {
              A[j + 11 * (j - 1)].re = 0.0;
              A[j + 11 * (j - 1)].im = 0.0;
              firstNonZero = true;
            } else {
              firstNonZero = false;
            }

            if (firstNonZero) {
              ifirst = j + 1;
              goto70 = true;
              exitg2 = true;
            } else {
              j--;
            }
          }
        }

        if (goto60 || goto70) {
          firstNonZero = true;
        } else {
          firstNonZero = false;
        }

        if (!firstNonZero) {
          for (i = 0; i < 11; i++) {
            alpha1[i].re = rtNaN;
            alpha1[i].im = 0.0;
            beta1[i].re = rtNaN;
            beta1[i].im = 0.0;
          }

          for (jp1 = 0; jp1 < 121; jp1++) {
            Z[jp1].re = rtNaN;
            Z[jp1].im = 0.0;
          }

          *info = 1;
          exitg1 = 1;
        } else if (goto60) {
          goto60 = false;
          alpha1[ilast] = A[ilast + 11 * ilast];
          ilast = ilastm1;
          ilastm1--;
          if (ilast + 1 < ilo) {
            failed = false;
            guard2 = true;
            exitg1 = 1;
          } else {
            iiter = 0;
            eshift_re = 0.0;
            eshift_im = 0.0;
            jiter++;
          }
        } else {
          if (goto70) {
            goto70 = false;
            iiter++;
            if (iiter - iiter / 10 * 10 != 0) {
              anorm = ascale * A[ilastm1 + 11 * ilastm1].re;
              reAij = ascale * A[ilastm1 + 11 * ilastm1].im;
              if (reAij == 0.0) {
                shift.re = anorm / 0.30151134457776363;
                shift.im = 0.0;
              } else if (anorm == 0.0) {
                shift.re = 0.0;
                shift.im = reAij / 0.30151134457776363;
              } else {
                shift.re = anorm / 0.30151134457776363;
                shift.im = reAij / 0.30151134457776363;
              }

              anorm = ascale * A[ilast + 11 * ilast].re;
              reAij = ascale * A[ilast + 11 * ilast].im;
              if (reAij == 0.0) {
                ad22_re = anorm / 0.30151134457776363;
                ad22_im = 0.0;
              } else if (anorm == 0.0) {
                ad22_re = 0.0;
                ad22_im = reAij / 0.30151134457776363;
              } else {
                ad22_re = anorm / 0.30151134457776363;
                ad22_im = reAij / 0.30151134457776363;
              }

              temp2 = 0.5 * (shift.re + ad22_re);
              t1_im = 0.5 * (shift.im + ad22_im);
              anorm = ascale * A[ilastm1 + 11 * ilast].re;
              reAij = ascale * A[ilastm1 + 11 * ilast].im;
              if (reAij == 0.0) {
                sumsq = anorm / 0.30151134457776363;
                imAij = 0.0;
              } else if (anorm == 0.0) {
                sumsq = 0.0;
                imAij = reAij / 0.30151134457776363;
              } else {
                sumsq = anorm / 0.30151134457776363;
                imAij = reAij / 0.30151134457776363;
              }

              anorm = ascale * A[ilast + 11 * ilastm1].re;
              reAij = ascale * A[ilast + 11 * ilastm1].im;
              if (reAij == 0.0) {
                scale = anorm / 0.30151134457776363;
                anorm = 0.0;
              } else if (anorm == 0.0) {
                scale = 0.0;
                anorm = reAij / 0.30151134457776363;
              } else {
                scale = anorm / 0.30151134457776363;
                anorm = reAij / 0.30151134457776363;
              }

              reAij = shift.re * ad22_im + shift.im * ad22_re;
              shift.re = ((temp2 * temp2 - t1_im * t1_im) + (sumsq * scale -
                imAij * anorm)) - (shift.re * ad22_re - shift.im * ad22_im);
              shift.im = ((temp2 * t1_im + t1_im * temp2) + (sumsq * anorm +
                imAij * scale)) - reAij;
              c_sqrt(&shift);
              if ((temp2 - ad22_re) * shift.re + (t1_im - ad22_im) * shift.im <=
                  0.0) {
                shift.re += temp2;
                shift.im += t1_im;
              } else {
                shift.re = temp2 - shift.re;
                shift.im = t1_im - shift.im;
              }
            } else {
              anorm = ascale * A[ilast + 11 * ilastm1].re;
              reAij = ascale * A[ilast + 11 * ilastm1].im;
              if (reAij == 0.0) {
                sumsq = anorm / 0.30151134457776363;
                imAij = 0.0;
              } else if (anorm == 0.0) {
                sumsq = 0.0;
                imAij = reAij / 0.30151134457776363;
              } else {
                sumsq = anorm / 0.30151134457776363;
                imAij = reAij / 0.30151134457776363;
              }

              eshift_re += sumsq;
              eshift_im += imAij;
              shift.re = eshift_re;
              shift.im = eshift_im;
            }

            j = ilastm1;
            jp1 = ilastm1 + 1;
            exitg2 = false;
            while ((!exitg2) && (j + 1 > ifirst)) {
              istart = j + 1;
              ctemp.re = ascale * A[j + 11 * j].re - shift.re *
                0.30151134457776363;
              ctemp.im = ascale * A[j + 11 * j].im - shift.im *
                0.30151134457776363;
              anorm = fabs(ctemp.re) + fabs(ctemp.im);
              temp2 = ascale * (fabs(A[jp1 + 11 * j].re) + fabs(A[jp1 + 11 * j].
                im));
              reAij = anorm;
              if (temp2 > anorm) {
                reAij = temp2;
              }

              if ((reAij < 1.0) && (reAij != 0.0)) {
                anorm /= reAij;
                temp2 /= reAij;
              }

              if ((fabs(A[j + 11 * (j - 1)].re) + fabs(A[j + 11 * (j - 1)].im)) *
                  temp2 <= anorm * b_atol) {
                goto90 = true;
                exitg2 = true;
              } else {
                jp1 = j;
                j--;
              }
            }

            if (!goto90) {
              istart = ifirst;
              ctemp.re = ascale * A[(ifirst + 11 * (ifirst - 1)) - 1].re -
                shift.re * 0.30151134457776363;
              ctemp.im = ascale * A[(ifirst + 11 * (ifirst - 1)) - 1].im -
                shift.im * 0.30151134457776363;
              goto90 = true;
            }
          }

          if (goto90) {
            goto90 = false;
            b_ascale.re = ascale * A[istart + 11 * (istart - 1)].re;
            b_ascale.im = ascale * A[istart + 11 * (istart - 1)].im;
            b_xzlartg(ctemp, b_ascale, &scale, &shift);
            j = istart;
            jp1 = istart - 2;
            while (j < ilast + 1) {
              if (j > istart) {
                xzlartg(A[(j + 11 * jp1) - 1], A[j + 11 * jp1], &scale, &shift,
                        &A[(j + 11 * jp1) - 1]);
                A[j + 11 * jp1].re = 0.0;
                A[j + 11 * jp1].im = 0.0;
              }

              for (jp1 = j - 1; jp1 + 1 < 12; jp1++) {
                ad22_re = scale * A[(j + 11 * jp1) - 1].re + (shift.re * A[j +
                  11 * jp1].re - shift.im * A[j + 11 * jp1].im);
                ad22_im = scale * A[(j + 11 * jp1) - 1].im + (shift.re * A[j +
                  11 * jp1].im + shift.im * A[j + 11 * jp1].re);
                anorm = A[(j + 11 * jp1) - 1].im;
                reAij = A[(j + 11 * jp1) - 1].re;
                A[j + 11 * jp1].re = scale * A[j + 11 * jp1].re - (shift.re * A
                  [(j + 11 * jp1) - 1].re + shift.im * A[(j + 11 * jp1) - 1].im);
                A[j + 11 * jp1].im = scale * A[j + 11 * jp1].im - (shift.re *
                  anorm - shift.im * reAij);
                A[(j + 11 * jp1) - 1].re = ad22_re;
                A[(j + 11 * jp1) - 1].im = ad22_im;
              }

              shift.re = -shift.re;
              shift.im = -shift.im;
              jp1 = j;
              if (ilast + 1 < j + 2) {
                jp1 = ilast - 1;
              }

              for (i = 0; i + 1 <= jp1 + 2; i++) {
                ad22_re = scale * A[i + 11 * j].re + (shift.re * A[i + 11 * (j -
                  1)].re - shift.im * A[i + 11 * (j - 1)].im);
                ad22_im = scale * A[i + 11 * j].im + (shift.re * A[i + 11 * (j -
                  1)].im + shift.im * A[i + 11 * (j - 1)].re);
                anorm = A[i + 11 * j].im;
                reAij = A[i + 11 * j].re;
                A[i + 11 * (j - 1)].re = scale * A[i + 11 * (j - 1)].re -
                  (shift.re * A[i + 11 * j].re + shift.im * A[i + 11 * j].im);
                A[i + 11 * (j - 1)].im = scale * A[i + 11 * (j - 1)].im -
                  (shift.re * anorm - shift.im * reAij);
                A[i + 11 * j].re = ad22_re;
                A[i + 11 * j].im = ad22_im;
              }

              for (i = 0; i < 11; i++) {
                ad22_re = scale * Z[i + 11 * j].re + (shift.re * Z[i + 11 * (j -
                  1)].re - shift.im * Z[i + 11 * (j - 1)].im);
                ad22_im = scale * Z[i + 11 * j].im + (shift.re * Z[i + 11 * (j -
                  1)].im + shift.im * Z[i + 11 * (j - 1)].re);
                anorm = Z[i + 11 * j].im;
                reAij = Z[i + 11 * j].re;
                Z[i + 11 * (j - 1)].re = scale * Z[i + 11 * (j - 1)].re -
                  (shift.re * Z[i + 11 * j].re + shift.im * Z[i + 11 * j].im);
                Z[i + 11 * (j - 1)].im = scale * Z[i + 11 * (j - 1)].im -
                  (shift.re * anorm - shift.im * reAij);
                Z[i + 11 * j].re = ad22_re;
                Z[i + 11 * j].im = ad22_im;
              }

              jp1 = j - 1;
              j++;
            }
          }

          jiter++;
        }
      } else {
        guard2 = true;
        exitg1 = 1;
      }
    } while (exitg1 == 0);
  } else {
    guard1 = true;
  }

  if (guard2) {
    if (failed) {
      *info = ilast + 1;
      for (jp1 = 0; jp1 + 1 <= ilast + 1; jp1++) {
        alpha1[jp1].re = rtNaN;
        alpha1[jp1].im = 0.0;
        beta1[jp1].re = rtNaN;
        beta1[jp1].im = 0.0;
      }

      for (jp1 = 0; jp1 < 121; jp1++) {
        Z[jp1].re = rtNaN;
        Z[jp1].im = 0.0;
      }
    } else {
      guard1 = true;
    }
  }

  if (guard1) {
    for (j = 0; j + 1 < ilo; j++) {
      alpha1[j] = A[j + 11 * j];
    }
  }
}

/*
 * File trailer for xzhgeqz.c
 *
 * [EOF]
 */
