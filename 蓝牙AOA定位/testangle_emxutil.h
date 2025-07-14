/*
 * File: testangle_emxutil.h
 *
 * MATLAB Coder version            : 3.4
 * C/C++ source code generated on  : 18-Jun-2023 15:57:58
 */

#ifndef TESTANGLE_EMXUTIL_H
#define TESTANGLE_EMXUTIL_H

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
extern void emxEnsureCapacity_int32_T(emxArray_int32_T *emxArray, int oldNumel);
extern void emxFree_int32_T(emxArray_int32_T **pEmxArray);
extern void emxInit_int32_T(emxArray_int32_T **pEmxArray, int numDimensions);

#endif

/*
 * File trailer for testangle_emxutil.h
 *
 * [EOF]
 */
