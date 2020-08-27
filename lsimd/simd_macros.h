#pragma once

//	Copyright (c) 2019 Lawnjelly

//	Permission is hereby granted, free of charge, to any person obtaining a copy
//	of this software and associated documentation files (the "Software"), to deal
//	in the Software without restriction, including without limitation the rights
//	to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//	copies of the Software, and to permit persons to whom the Software is
//	furnished to do so, subject to the following conditions:

//	The above copyright notice and this permission notice shall be included in all
//	copies or substantial portions of the Software.

//	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
//	SOFTWARE.


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
