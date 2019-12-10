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
GSIMD_IMPL_DUAL(FastArray_4f32_SSE, add, _mm_add_ps);
GSIMD_IMPL_DUAL(FastArray_4f32_SSE, subtract, _mm_sub_ps);
GSIMD_IMPL_DUAL(FastArray_4f32_SSE, multiply, _mm_mul_ps);
GSIMD_IMPL_DUAL(FastArray_4f32_SSE, divide, _mm_div_ps);

GSIMD_IMPL_VAL(FastArray_4f32_SSE, value_add, _mm_add_ps);
GSIMD_IMPL_VAL(FastArray_4f32_SSE, value_subtract, _mm_sub_ps);
GSIMD_IMPL_VAL(FastArray_4f32_SSE, value_multiply, _mm_mul_ps);
GSIMD_IMPL_VAL(FastArray_4f32_SSE, value_divide, _mm_div_ps);

GSIMD_IMPL_SIMPLE(FastArray_4f32_SSE, reciprocal, _mm_rcp_ps);
GSIMD_IMPL_SIMPLE(FastArray_4f32_SSE, sqrt, _mm_sqrt_ps);
GSIMD_IMPL_SIMPLE(FastArray_4f32_SSE, inv_sqrt, _mm_rsqrt_ps);

} // namespace
#endif // GSIMD_USE_SSE

#include "simd_macros_undef.h"
