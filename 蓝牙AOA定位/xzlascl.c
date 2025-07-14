/*
 * File: xzlascl.c
 *
 * MATLAB Coder version            : 3.4
 * C/C++ source code generated on  : 18-Jun-2023 15:57:58
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "testangle.h"
#include "xzlascl.h"

/* Function Definitions */

/*
 * Arguments    : double cfrom
 *                double cto
 *                creal_T A[11]
 * Return Type  : void
 */
void b_xzlascl(double cfrom, double cto, creal_T A[11])
{
  double cfromc;
  double ctoc;
  boolean_T notdone;
  double cfrom1;
  double cto1;
  double mul;
  int i9;
  cfromc = cfrom;
  ctoc = cto;
  notdone = true;
  while (notdone) {
    cfrom1 = cfromc * 2.0041683600089728E-292;
    cto1 = ctoc / 4.9896007738368E+291;
    if ((fabs(cfrom1) > fabs(ctoc)) && (ctoc != 0.0)) {
      mul = 2.0041683600089728E-292;
      cfromc = cfrom1;
    } else if (fabs(cto1) > fabs(cfromc)) {
      mul = 4.9896007738368E+291;
      ctoc = cto1;
    } else {
      mul = ctoc / cfromc;
      notdone = false;
    }

    for (i9 = 0; i9 < 11; i9++) {
      A[i9].re *= mul;
      A[i9].im *= mul;
    }
  }
}

/*
 * Arguments    : double cfrom
 *                double cto
 *                creal_T A[121]
 * Return Type  : void
 */
void xzlascl(double cfrom, double cto, creal_T A[121])
{
  double cfromc;
  double ctoc;
  boolean_T notdone;
  double cfrom1;
  double cto1;
  double mul;
  int i8;
  cfromc = cfrom;
  ctoc = cto;
  notdone = true;
  while (notdone) {
    cfrom1 = cfromc * 2.0041683600089728E-292;
    cto1 = ctoc / 4.9896007738368E+291;
    if ((fabs(cfrom1) > fabs(ctoc)) && (ctoc != 0.0)) {
      mul = 2.0041683600089728E-292;
      cfromc = cfrom1;
    } else if (fabs(cto1) > fabs(cfromc)) {
      mul = 4.9896007738368E+291;
      ctoc = cto1;
    } else {
      mul = ctoc / cfromc;
      notdone = false;
    }

    for (i8 = 0; i8 < 121; i8++) {
      A[i8].re *= mul;
      A[i8].im *= mul;
    }
  }
}

/*
 * File trailer for xzlascl.c
 *
 * [EOF]
 */
