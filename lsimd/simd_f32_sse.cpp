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

#include "simd_f32_sse.h"
#include "simd_f32.h"
#include "simd_cpu.h"
#include "simd_macros.h"

#ifdef GSIMD_USE_SSE
#include <xmmintrin.h>
#endif


#ifdef GSIMD_USE_SSE
namespace GSimd
{
GSIMD_IMPL_DUAL(Simd_4f32_SSE, add, _mm_add_ps);
GSIMD_IMPL_DUAL(Simd_4f32_SSE, subtract, _mm_sub_ps);
GSIMD_IMPL_DUAL(Simd_4f32_SSE, multiply, _mm_mul_ps);
GSIMD_IMPL_DUAL(Simd_4f32_SSE, divide, _mm_div_ps);

GSIMD_IMPL_VAL(Simd_4f32_SSE, value_add, _mm_add_ps);
GSIMD_IMPL_VAL(Simd_4f32_SSE, value_subtract, _mm_sub_ps);
GSIMD_IMPL_VAL(Simd_4f32_SSE, value_multiply, _mm_mul_ps);
GSIMD_IMPL_VAL(Simd_4f32_SSE, value_divide, _mm_div_ps);

GSIMD_IMPL_SIMPLE(Simd_4f32_SSE, reciprocal, _mm_rcp_ps);
GSIMD_IMPL_SIMPLE(Simd_4f32_SSE, sqrt, _mm_sqrt_ps);
GSIMD_IMPL_SIMPLE(Simd_4f32_SSE, inv_sqrt, _mm_rsqrt_ps);

} // namespace
#endif // GSIMD_USE_SSE

#include "simd_macros_undef.h"
