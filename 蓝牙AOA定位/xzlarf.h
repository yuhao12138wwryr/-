/*
 * File: xzlarf.h
 *
 * MATLAB Coder version            : 3.4
 * C/C++ source code generated on  : 18-Jun-2023 15:57:58
 */

#ifndef XZLARF_H
#define XZLARF_H

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
extern void b_xzlarf(int m, int n, int iv0, const creal_T tau, creal_T C[121],
                     int ic0, creal_T work[11]);
extern void xzlarf(int n, int iv0, const creal_T tau, creal_T C[121], int ic0,
                   creal_T work[11]);

#endif

/*
 * File trailer for xzlarf.h
 *
 * [EOF]
 */
