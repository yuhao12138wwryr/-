/*
 * File: xscal.h
 *
 * MATLAB Coder version            : 3.4
 * C/C++ source code generated on  : 18-Jun-2023 15:57:58
 */

#ifndef XSCAL_H
#define XSCAL_H

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
extern void b_xscal(int n, const creal_T a, creal_T x[121], int ix0);
extern void c_xscal(const creal_T a, creal_T x[121], int ix0);
extern void xscal(int n, const creal_T a, creal_T x[121], int ix0);

#endif

/*
 * File trailer for xscal.h
 *
 * [EOF]
 */
