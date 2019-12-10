#pragma once

// Instead of writing all the SIMD code out longhand, we will use macros where possible.
// This makes it more concise, and easier to make changes to all at the same time.


#define GSIMD_IMPL_VAL(MYCLASS, F_NAME, INSTR) void MYCLASS::F_NAME(float * pfUnits, const float * pfVal, int nUnits)\
{\
float * pf = pfUnits;\
__m128 arg = _mm_loadu_ps(pfVal);\
for (int n=0; n<nUnits; n++)\
{\
__m128 m = _mm_loadu_ps(pf);\
__m128 res = INSTR(m, arg);\
_mm_storeu_ps(pf, res);\
pf += 4;\
}\
}


#define GSIMD_IMPL_SIMPLE(MYCLASS, F_NAME, INSTR) void MYCLASS::F_NAME(float * pfUnits, int nUnits)\
{\
float * pf = pfUnits;\
for (int n=0; n<nUnits; n++)\
{\
__m128 m = _mm_loadu_ps(pf);\
__m128 res = INSTR(m);\
_mm_storeu_ps(pf, res);\
pf += 4;\
}\
}

#define GSIMD_IMPL_DUAL(MYCLASS, F_NAME, INSTR) void MYCLASS::F_NAME(float * pfUnits, const float * pfUnits2, int nUnits)\
{\
for (int n=0; n<nUnits; n++)\
{\
__m128 m = _mm_loadu_ps(pfUnits);\
__m128 m2 = _mm_loadu_ps(pfUnits2);\
__m128 res = INSTR(m, m2);\
_mm_storeu_ps(pfUnits, res);\
pfUnits += 4;\
pfUnits2 += 4;\
}\
}
