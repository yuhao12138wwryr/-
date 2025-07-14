/*
 * File: xzhseqr.c
 *
 * MATLAB Coder version            : 3.4
 * C/C++ source code generated on  : 18-Jun-2023 15:57:58
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "testangle.h"
#include "xzhseqr.h"
#include "Angle2.h"
#include "xzlarfg.h"
#include "sqrt.h"
#include "xscal.h"
#include "testangle_rtwutil.h"

/* Function Definitions */

/*
 * Arguments    : creal_T h[121]
 *                creal_T z[121]
 * Return Type  : int
 */
int eml_zlahqr(creal_T h[121], creal_T z[121])
{
  int info;
  int j;
  int i;
  boolean_T exitg1;
  double tst;
  double htmp1;
  double ba;
  int L;
  boolean_T goto140;
  creal_T sc;
  int its;
  boolean_T exitg2;
  int k;
  boolean_T exitg3;
  creal_T x2;
  int u1;
  double ab;
  boolean_T goto70;
  int m;
  double u_re;
  double u_im;
  double aa;
  double s;
  int b_k;
  double d0;
  creal_T v[2];
  int c;
  double b_u_re;
  info = 0;
  for (j = 0; j < 8; j++) {
    h[(j + 11 * j) + 2].re = 0.0;
    h[(j + 11 * j) + 2].im = 0.0;
    h[(j + 11 * j) + 3].re = 0.0;
    h[(j + 11 * j) + 3].im = 0.0;
  }

  h[98].re = 0.0;
  h[98].im = 0.0;
  for (i = 0; i < 10; i++) {
    if (h[(i + 11 * i) + 1].im != 0.0) {
      tst = h[(i + 11 * i) + 1].re;
      htmp1 = h[(i + 11 * i) + 1].im;
      ba = fabs(h[(i + 11 * i) + 1].re) + fabs(h[(i + 11 * i) + 1].im);
      if (htmp1 == 0.0) {
        sc.re = tst / ba;
        sc.im = 0.0;
      } else if (tst == 0.0) {
        sc.re = 0.0;
        sc.im = htmp1 / ba;
      } else {
        sc.re = tst / ba;
        sc.im = htmp1 / ba;
      }

      ba = rt_hypotd_snf(sc.re, sc.im);
      if (-sc.im == 0.0) {
        sc.re /= ba;
        sc.im = 0.0;
      } else if (sc.re == 0.0) {
        sc.re = 0.0;
        sc.im = -sc.im / ba;
      } else {
        sc.re /= ba;
        sc.im = -sc.im / ba;
      }

      h[(i + 11 * i) + 1].re = rt_hypotd_snf(h[(i + 11 * i) + 1].re, h[(i + 11 *
        i) + 1].im);
      h[(i + 11 * i) + 1].im = 0.0;
      b_xscal(10 - i, sc, h, (i + (i + 1) * 11) + 2);
      x2.re = sc.re;
      x2.im = -sc.im;
      u1 = i + 3;
      if (11 < u1) {
        u1 = 11;
      }

      xscal(u1, x2, h, 1 + (i + 1) * 11);
      x2.re = sc.re;
      x2.im = -sc.im;
      c_xscal(x2, z, 1 + (i + 1) * 11);
    }
  }

  i = 10;
  exitg1 = false;
  while ((!exitg1) && (i + 1 >= 1)) {
    L = -1;
    goto140 = false;
    its = 0;
    exitg2 = false;
    while ((!exitg2) && (its < 331)) {
      k = i;
      exitg3 = false;
      while ((!exitg3) && ((k + 1 > L + 2) && (!(fabs(h[k + 11 * (k - 1)].re) +
                fabs(h[k + 11 * (k - 1)].im) <= 1.102292598004935E-291)))) {
        tst = (fabs(h[(k + 11 * (k - 1)) - 1].re) + fabs(h[(k + 11 * (k - 1)) -
                1].im)) + (fabs(h[k + 11 * k].re) + fabs(h[k + 11 * k].im));
        if (tst == 0.0) {
          if (k - 1 >= 1) {
            tst = fabs(h[(k + 11 * (k - 2)) - 1].re);
          }

          if (k + 2 <= 11) {
            tst += fabs(h[(k + 11 * k) + 1].re);
          }
        }

        if (fabs(h[k + 11 * (k - 1)].re) <= 2.2204460492503131E-16 * tst) {
          htmp1 = fabs(h[k + 11 * (k - 1)].re) + fabs(h[k + 11 * (k - 1)].im);
          tst = fabs(h[(k + 11 * k) - 1].re) + fabs(h[(k + 11 * k) - 1].im);
          if (htmp1 > tst) {
            ab = htmp1;
            ba = tst;
          } else {
            ab = tst;
            ba = htmp1;
          }

          htmp1 = fabs(h[k + 11 * k].re) + fabs(h[k + 11 * k].im);
          tst = fabs(h[(k + 11 * (k - 1)) - 1].re - h[k + 11 * k].re) + fabs(h
            [(k + 11 * (k - 1)) - 1].im - h[k + 11 * k].im);
          if (htmp1 > tst) {
            aa = htmp1;
            htmp1 = tst;
          } else {
            aa = tst;
          }

          s = aa + ab;
          tst = 2.2204460492503131E-16 * (htmp1 * (aa / s));
          if ((1.102292598004935E-291 > tst) || rtIsNaN(tst)) {
            d0 = 1.102292598004935E-291;
          } else {
            d0 = tst;
          }

          if (ba * (ab / s) <= d0) {
            exitg3 = true;
          } else {
            k--;
          }
        } else {
          k--;
        }
      }

      L = k - 1;
      if (k + 1 > 1) {
        h[k + 11 * (k - 1)].re = 0.0;
        h[k + 11 * (k - 1)].im = 0.0;
      }

      if (k + 1 >= i + 1) {
        goto140 = true;
        exitg2 = true;
      } else {
        if (its == 10) {
          ba = 0.75 * fabs(h[(k + 11 * k) + 1].re) + h[k + 11 * k].re;
          ab = h[k + 11 * k].im;
        } else if (its == 20) {
          ba = 0.75 * fabs(h[i + 11 * (i - 1)].re) + h[i + 11 * i].re;
          ab = h[i + 11 * i].im;
        } else {
          ba = h[i + 11 * i].re;
          ab = h[i + 11 * i].im;
          x2 = h[(i + 11 * i) - 1];
          c_sqrt(&x2);
          sc = h[i + 11 * (i - 1)];
          c_sqrt(&sc);
          u_re = x2.re * sc.re - x2.im * sc.im;
          u_im = x2.re * sc.im + x2.im * sc.re;
          s = fabs(u_re) + fabs(u_im);
          if (s != 0.0) {
            ba = 0.5 * (h[(i + 11 * (i - 1)) - 1].re - h[i + 11 * i].re);
            ab = 0.5 * (h[(i + 11 * (i - 1)) - 1].im - h[i + 11 * i].im);
            aa = fabs(ba) + fabs(ab);
            tst = fabs(ba) + fabs(ab);
            if (!((s > tst) || rtIsNaN(tst))) {
              s = tst;
            }

            if (ab == 0.0) {
              x2.re = ba / s;
              x2.im = 0.0;
            } else if (ba == 0.0) {
              x2.re = 0.0;
              x2.im = ab / s;
            } else {
              x2.re = ba / s;
              x2.im = ab / s;
            }

            tst = x2.re;
            htmp1 = x2.re;
            x2.re = x2.re * x2.re - x2.im * x2.im;
            x2.im = tst * x2.im + x2.im * htmp1;
            if (u_im == 0.0) {
              sc.re = u_re / s;
              sc.im = 0.0;
            } else if (u_re == 0.0) {
              sc.re = 0.0;
              sc.im = u_im / s;
            } else {
              sc.re = u_re / s;
              sc.im = u_im / s;
            }

            x2.re += sc.re * sc.re - sc.im * sc.im;
            x2.im += sc.re * sc.im + sc.im * sc.re;
            c_sqrt(&x2);
            sc.re = s * x2.re;
            sc.im = s * x2.im;
            if (aa > 0.0) {
              if (ab == 0.0) {
                x2.re = ba / aa;
                x2.im = 0.0;
              } else if (ba == 0.0) {
                x2.re = 0.0;
                x2.im = ab / aa;
              } else {
                x2.re = ba / aa;
                x2.im = ab / aa;
              }

              if (x2.re * sc.re + x2.im * sc.im < 0.0) {
                sc.re = -sc.re;
                sc.im = -sc.im;
              }
            }

            ba += sc.re;
            aa = ab + sc.im;
            if (aa == 0.0) {
              if (u_im == 0.0) {
                b_u_re = u_re / ba;
                tst = 0.0;
              } else if (u_re == 0.0) {
                b_u_re = 0.0;
                tst = u_im / ba;
              } else {
                b_u_re = u_re / ba;
                tst = u_im / ba;
              }
            } else if (ba == 0.0) {
              if (u_re == 0.0) {
                b_u_re = u_im / aa;
                tst = 0.0;
              } else if (u_im == 0.0) {
                b_u_re = 0.0;
                tst = -(u_re / aa);
              } else {
                b_u_re = u_im / aa;
                tst = -(u_re / aa);
              }
            } else {
              ab = fabs(ba);
              tst = fabs(aa);
              if (ab > tst) {
                s = aa / ba;
                tst = ba + s * aa;
                b_u_re = (u_re + s * u_im) / tst;
                tst = (u_im - s * u_re) / tst;
              } else if (tst == ab) {
                if (ba > 0.0) {
                  htmp1 = 0.5;
                } else {
                  htmp1 = -0.5;
                }

                if (aa > 0.0) {
                  tst = 0.5;
                } else {
                  tst = -0.5;
                }

                b_u_re = (u_re * htmp1 + u_im * tst) / ab;
                tst = (u_im * htmp1 - u_re * tst) / ab;
              } else {
                s = ba / aa;
                tst = aa + s * ba;
                b_u_re = (s * u_re + u_im) / tst;
                tst = (s * u_im - u_re) / tst;
              }
            }

            ba = h[i + 11 * i].re - (u_re * b_u_re - u_im * tst);
            ab = h[i + 11 * i].im - (u_re * tst + u_im * b_u_re);
          }
        }

        goto70 = false;
        m = i;
        exitg3 = false;
        while ((!exitg3) && (m > k + 1)) {
          sc.re = h[(m + 11 * (m - 1)) - 1].re - ba;
          sc.im = h[(m + 11 * (m - 1)) - 1].im - ab;
          tst = h[m + 11 * (m - 1)].re;
          s = (fabs(sc.re) + fabs(sc.im)) + fabs(tst);
          if (sc.im == 0.0) {
            sc.re /= s;
            sc.im = 0.0;
          } else if (sc.re == 0.0) {
            sc.re = 0.0;
            sc.im /= s;
          } else {
            sc.re /= s;
            sc.im /= s;
          }

          tst /= s;
          v[0] = sc;
          v[1].re = tst;
          v[1].im = 0.0;
          if (fabs(h[(m + 11 * (m - 2)) - 1].re) * fabs(tst) <=
              2.2204460492503131E-16 * ((fabs(sc.re) + fabs(sc.im)) * ((fabs(h
                  [(m + 11 * (m - 1)) - 1].re) + fabs(h[(m + 11 * (m - 1)) - 1].
                  im)) + (fabs(h[m + 11 * m].re) + fabs(h[m + 11 * m].im))))) {
            goto70 = true;
            exitg3 = true;
          } else {
            m--;
          }
        }

        if (!goto70) {
          sc.re = h[k + 11 * k].re - ba;
          sc.im = h[k + 11 * k].im - ab;
          tst = h[(k + 11 * k) + 1].re;
          s = (fabs(sc.re) + fabs(sc.im)) + fabs(tst);
          if (sc.im == 0.0) {
            sc.re /= s;
            sc.im = 0.0;
          } else if (sc.re == 0.0) {
            sc.re = 0.0;
            sc.im /= s;
          } else {
            sc.re /= s;
            sc.im /= s;
          }

          tst /= s;
          v[0] = sc;
          v[1].re = tst;
          v[1].im = 0.0;
        }

        for (b_k = m; b_k <= i; b_k++) {
          if (b_k > m) {
            v[0] = h[(b_k + 11 * (b_k - 2)) - 1];
            v[1] = h[b_k + 11 * (b_k - 2)];
          }

          sc = b_xzlarfg(&v[0], &v[1]);
          if (b_k > m) {
            h[(b_k + 11 * (b_k - 2)) - 1] = v[0];
            h[b_k + 11 * (b_k - 2)].re = 0.0;
            h[b_k + 11 * (b_k - 2)].im = 0.0;
          }

          ba = v[1].re;
          ab = v[1].im;
          tst = sc.re * v[1].re - sc.im * v[1].im;
          for (j = b_k - 1; j + 1 < 12; j++) {
            x2.re = (sc.re * h[(b_k + 11 * j) - 1].re - -sc.im * h[(b_k + 11 * j)
                     - 1].im) + tst * h[b_k + 11 * j].re;
            x2.im = (sc.re * h[(b_k + 11 * j) - 1].im + -sc.im * h[(b_k + 11 * j)
                     - 1].re) + tst * h[b_k + 11 * j].im;
            h[(b_k + 11 * j) - 1].re -= x2.re;
            h[(b_k + 11 * j) - 1].im -= x2.im;
            h[b_k + 11 * j].re -= x2.re * ba - x2.im * ab;
            h[b_k + 11 * j].im -= x2.re * ab + x2.im * ba;
          }

          if (b_k + 2 < i + 1) {
            u1 = b_k;
          } else {
            u1 = i - 1;
          }

          for (j = 0; j + 1 <= u1 + 2; j++) {
            x2.re = (sc.re * h[j + 11 * (b_k - 1)].re - sc.im * h[j + 11 * (b_k
                      - 1)].im) + tst * h[j + 11 * b_k].re;
            x2.im = (sc.re * h[j + 11 * (b_k - 1)].im + sc.im * h[j + 11 * (b_k
                      - 1)].re) + tst * h[j + 11 * b_k].im;
            h[j + 11 * (b_k - 1)].re -= x2.re;
            h[j + 11 * (b_k - 1)].im -= x2.im;
            h[j + 11 * b_k].re -= x2.re * ba - x2.im * -ab;
            h[j + 11 * b_k].im -= x2.re * -ab + x2.im * ba;
          }

          for (j = 0; j < 11; j++) {
            x2.re = (sc.re * z[j + 11 * (b_k - 1)].re - sc.im * z[j + 11 * (b_k
                      - 1)].im) + tst * z[j + 11 * b_k].re;
            x2.im = (sc.re * z[j + 11 * (b_k - 1)].im + sc.im * z[j + 11 * (b_k
                      - 1)].re) + tst * z[j + 11 * b_k].im;
            z[j + 11 * (b_k - 1)].re -= x2.re;
            z[j + 11 * (b_k - 1)].im -= x2.im;
            z[j + 11 * b_k].re -= x2.re * ba - x2.im * -ab;
            z[j + 11 * b_k].im -= x2.re * -ab + x2.im * ba;
          }

          if ((b_k == m) && (m > k + 1)) {
            sc.re = 1.0 - sc.re;
            sc.im = 0.0 - sc.im;
            ba = rt_hypotd_snf(sc.re, sc.im);
            if (sc.im == 0.0) {
              sc.re /= ba;
              sc.im = 0.0;
            } else if (sc.re == 0.0) {
              sc.re = 0.0;
              sc.im /= ba;
            } else {
              sc.re /= ba;
              sc.im /= ba;
            }

            tst = h[m + 11 * (m - 1)].re;
            htmp1 = h[m + 11 * (m - 1)].im;
            h[m + 11 * (m - 1)].re = tst * sc.re - htmp1 * -sc.im;
            h[m + 11 * (m - 1)].im = tst * -sc.im + htmp1 * sc.re;
            if (m + 2 <= i + 1) {
              tst = h[(m + 11 * m) + 1].re;
              htmp1 = h[(m + 11 * m) + 1].im;
              h[(m + 11 * m) + 1].re = tst * sc.re - htmp1 * sc.im;
              h[(m + 11 * m) + 1].im = tst * sc.im + htmp1 * sc.re;
            }

            for (j = m; j <= i + 1; j++) {
              if (j != m + 1) {
                if (11 > j) {
                  c = j + j * 11;
                  u1 = c + 11 * (10 - j);
                  while (c <= u1) {
                    tst = h[c - 1].re;
                    htmp1 = h[c - 1].im;
                    h[c - 1].re = sc.re * tst - sc.im * htmp1;
                    h[c - 1].im = sc.re * htmp1 + sc.im * tst;
                    c += 11;
                  }
                }

                c = (j - 1) * 11;
                ba = sc.re;
                ab = -sc.im;
                u1 = (c + j) - 1;
                while (c + 1 <= u1) {
                  tst = h[c].re;
                  htmp1 = h[c].im;
                  h[c].re = ba * tst - ab * htmp1;
                  h[c].im = ba * htmp1 + ab * tst;
                  c++;
                }

                c = (j - 1) * 11;
                ba = sc.re;
                ab = -sc.im;
                for (u1 = c; u1 + 1 <= c + 11; u1++) {
                  tst = z[u1].re;
                  htmp1 = z[u1].im;
                  z[u1].re = ba * tst - ab * htmp1;
                  z[u1].im = ba * htmp1 + ab * tst;
                }
              }
            }
          }
        }

        sc = h[i + 11 * (i - 1)];
        if (h[i + 11 * (i - 1)].im != 0.0) {
          tst = rt_hypotd_snf(h[i + 11 * (i - 1)].re, h[i + 11 * (i - 1)].im);
          h[i + 11 * (i - 1)].re = tst;
          h[i + 11 * (i - 1)].im = 0.0;
          if (sc.im == 0.0) {
            sc.re /= tst;
            sc.im = 0.0;
          } else if (sc.re == 0.0) {
            sc.re = 0.0;
            sc.im /= tst;
          } else {
            sc.re /= tst;
            sc.im /= tst;
          }

          if (11 > i + 1) {
            c = i + (i + 1) * 11;
            ba = sc.re;
            ab = -sc.im;
            u1 = (c + 11 * (9 - i)) + 1;
            while (c + 1 <= u1) {
              tst = h[c].re;
              htmp1 = h[c].im;
              h[c].re = ba * tst - ab * htmp1;
              h[c].im = ba * htmp1 + ab * tst;
              c += 11;
            }
          }

          c = i * 11;
          u1 = c + i;
          while (c + 1 <= u1) {
            tst = h[c].re;
            htmp1 = h[c].im;
            h[c].re = sc.re * tst - sc.im * htmp1;
            h[c].im = sc.re * htmp1 + sc.im * tst;
            c++;
          }

          c = i * 11;
          for (k = c; k + 1 <= c + 11; k++) {
            tst = z[k].re;
            htmp1 = z[k].im;
            z[k].re = sc.re * tst - sc.im * htmp1;
            z[k].im = sc.re * htmp1 + sc.im * tst;
          }
        }

        its++;
      }
    }

    if (!goto140) {
      info = i + 1;
      exitg1 = true;
    } else {
      i = L;
    }
  }

  return info;
}

/*
 * File trailer for xzhseqr.c
 *
 * [EOF]
 */
