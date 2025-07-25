/*
 * File: xgemv.h
 *
 * MATLAB Coder version            : 3.4
 * C/C++ source code generated on  : 18-Jun-2023 15:57:58
 */

#ifndef XGEMV_H
#define XGEMV_H

/* Include Files */
#include <math.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "rtGetNaN.h"
#include "rt_defines.h"
#include "rt_nonfinite.h"
#include "rtwtypes.h"
#include "testangle_types.h"

/* Function Declarations */
extern void xgemv(int m, int n, const creal_T A[121], int ia0, const creal_T x
                  [121], int ix0, creal_T y[11]);

#endif

/*
 * File trailer for xgemv.h
 *
 * [EOF]
 */
