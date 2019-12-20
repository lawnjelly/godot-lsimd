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


#include "simd_f32.h"
#include "core/variant.h"
#include <string.h>
#include "simd_f32_sse.h"
#include "simd_f32_sse3.h"
#include "simd_f32_sse4_1.h"


//#ifdef GSIMD_USE_SSE
//#include <xmmintrin.h>
//#endif
//#ifdef GSIMD_USE_SSE2
//#include <emmintrin.h>
//#endif
//#ifdef GSIMD_USE_SSE3
//#include <pmmintrin.h>
//#endif
//#ifdef GSIMD_USE_SSSE3
//#include <tmmintrin.h>
//#endif
//#ifdef GSIMD_USE_SSE4_1
//#include <smmintrin.h>
//#endif
//#ifdef GSIMD_USE_SSE4_2
//#include <nmmintrin.h>
//#endif
//#if defined GSIMD_USE_AVX || defined GSIMD_USE_AVX512
//#include <immintrin.h>
//#endif


using namespace GSimd;


#define GSIMD_CHECK_RANGE if (!check_range(from, num, size())) {return;}
#define GSIMD_CHECK_BOTH_RANGE if (!check_range(from, num, size())) {return;} \
if (!check_range(from2, num, arr2.size())) {return;}

// Note that most of these routines will be auto-vectorized if -O3 is used and the architecture is set

Simd_4f32::Simd_4f32()
{

}



Vector3 Simd_4f32::vec3_read(int i) const
{
	const GSimd::f32_4 &u = m_Vec[i];
	return Vector3(u.v[0], u.v[1], u.v[2]);
}

void Simd_4f32::vec3_write(int i, const Vector3 &v)
{
	GSimd::f32_4 &u = m_Vec[i];
	u.v[0] = v.x;
	u.v[1] = v.y;
	u.v[2] = v.z;
	u.v[3] = 0.0;
}


Quat Simd_4f32::read(int i) const
{
	Quat q;
	m_Vec[i].to_quat(q);
	return q;
}

void Simd_4f32::write(int i, const Quat &q)
{
	m_Vec[i].from_quat(q);
}




bool Simd_4f32::check_range(int from, int num, int size) const
{
	int to = from + num;

	// check for below zero at same time
	if ((unsigned int) from > (unsigned int) size) goto failed;
	if ((unsigned int) to > (unsigned int) size) goto failed;
	return true;

failed:
	ERR_FAIL_INDEX_V(from, size, false);
	ERR_FAIL_INDEX_V(to, size, false);
	return false;
}

void Simd_4f32::fill(const Quat &val)
{
	f32_4 u;
	u.from_quat(val);
	int s = size();
	for (int n=0; n<s; n++)
		m_Vec[n] = u;
}

void Simd_4f32::zero()
{
	int s = size();
	if (!s) return;
	memset(&m_Vec[0], 0, sizeof (GSimd::f32_4) * s);
}

PoolRealArray Simd_4f32::get_poolrealarray_result() const
{
	int s = size();

	PoolRealArray arr;
	arr.resize(s);
	for (int n=0; n<s; n++)
	{
		arr.set(n, m_Vec[n].v[3]);
	}

	return arr;
}


PoolVector<Vector3> Simd_4f32::get_poolvector3array() const
{
	int s = size();

	PoolVector3Array arr;
	arr.resize(s);


	for (int n=0; n<s; n++)
	{
		Vector3 v;
		m_Vec[n].to_vector3(v);
		arr.set(n, v);
	}

	return arr;
}


void Simd_4f32::copy_from_poolvector3array(const PoolVector<Vector3> &arr)
{
	int size = arr.size();

	if (size == 0)
	{
		m_Vec.clear(true);
		return;
	}

	reserve(size);

	for (int n=0; n<size; n++)
	{
		Vector3 v = arr[n];
		m_Vec[n].from_vector3(v);
	}
}

void Simd_4f32::copy_from(const Simd_4f32 &o)
{
	int size = o.size();
	if (size == 0)
	{
		m_Vec.clear(true);
		return;
	}

	reserve(size);

	memcpy(&m_Vec[0], &o.m_Vec[0], sizeof (GSimd::f32_4) * size);
}


void Simd_4f32::add(const Simd_4f32 &arr2, int from, int from2, int num)
{
	int to = from + num;
	GSIMD_CHECK_BOTH_RANGE
#ifdef GSIMD_USE_SSE
	if (g_GodotCPU.HasFlag(Godot_CPU::F_SSE))
	{
		Simd_4f32_SSE::add((float *) &m_Vec[from], (float *) &arr2.m_Vec[from2], num);
		return;
	}
#endif
	for (int n=from; n<to; n++)
		m_Vec[n].add(arr2.m_Vec[from2++]);
}

void Simd_4f32::subtract(const Simd_4f32 &arr2, int from, int from2, int num)
{
	int to = from + num;
	GSIMD_CHECK_BOTH_RANGE
#ifdef GSIMD_USE_SSE
	if (g_GodotCPU.HasFlag(Godot_CPU::F_SSE))
	{
		Simd_4f32_SSE::subtract((float *) &m_Vec[from], (float *) &arr2.m_Vec[from], num);
		return;
	}
#endif
	for (int n=from; n<to; n++)
		m_Vec[n].subtract(arr2.m_Vec[from2++]);
}

void Simd_4f32::multiply(const Simd_4f32 &arr2, int from, int from2, int num)
{
	int to = from + num;
	GSIMD_CHECK_BOTH_RANGE
#ifdef GSIMD_USE_SSE
	if (g_GodotCPU.HasFlag(Godot_CPU::F_SSE))
	{
		Simd_4f32_SSE::multiply((float *) &m_Vec[from], (float *) &arr2.m_Vec[from], num);
		return;
	}
#endif
	for (int n=from; n<to; n++)
		m_Vec[n].multiply(arr2.m_Vec[from2++]);
}

void Simd_4f32::divide(const Simd_4f32 &arr2, int from, int from2, int num)
{
	int to = from + num;
	GSIMD_CHECK_BOTH_RANGE
#ifdef GSIMD_USE_SSE
	if (g_GodotCPU.HasFlag(Godot_CPU::F_SSE))
	{
		Simd_4f32_SSE::divide((float *) &m_Vec[from], (float *) &arr2.m_Vec[from], num);
		return;
	}
#endif
	for (int n=from; n<to; n++)
		m_Vec[n].divide(arr2.m_Vec[from2++]);
}

void Simd_4f32::vec2_dot(const Simd_4f32 &arr2, int from, int from2, int num, float * pfResult)
{
	int to = from + num;
	GSIMD_CHECK_BOTH_RANGE

	for (int n=from; n<to; n++)
	{
		m_Vec[n].vec2_dot(arr2.m_Vec[from2++], pfResult);
		pfResult += 2;
	}
}

void Simd_4f32::vec2_cross(const Simd_4f32 &arr2, int from, int from2, int num, float * pfResult)
{
	int to = from + num;
	GSIMD_CHECK_BOTH_RANGE

	for (int n=from; n<to; n++)
	{
		m_Vec[n].vec2_cross(arr2.m_Vec[from2++], pfResult);
		pfResult += 2;
	}
}

void Simd_4f32::vec2_length(int from, int num, float * pfResult)
{
	int to = from + num;
	GSIMD_CHECK_RANGE
	for (int n=from; n<to; n++)
	{
		m_Vec[n].vec2_length(pfResult);
		pfResult += 2;
	}
}

void Simd_4f32::vec2_length_squared(int from, int num, float * pfResult)
{
	int to = from + num;
	GSIMD_CHECK_RANGE
	for (int n=from; n<to; n++)
	{
		m_Vec[n].vec2_length_squared(pfResult);
		pfResult += 2;
	}
}


void Simd_4f32::vec3_dot(const Simd_4f32 &arr2, int from, int from2, int num)
{
	int to = from + num;
	GSIMD_CHECK_BOTH_RANGE
#ifdef GSIMD_USE_SSE4_1
	if (g_GodotCPU.HasFlag(Godot_CPU::F_SSE4_1))
	{
		Simd_4f32_SSE4_1::vec3_dot((float *) &m_Vec[from], (float *) &arr2.m_Vec[from], num);
		return;
	}
#endif

	for (int n=from; n<to; n++)
		m_Vec[n].vec3_dot(arr2.m_Vec[from2++]);
}

void Simd_4f32::vec3_unit_cross(const Simd_4f32 &arr2, int from, int from2, int num)
{
	int to = from + num;
	GSIMD_CHECK_BOTH_RANGE

	for (int n=from; n<to; n++)
	{
		m_Vec[n].vec3_cross(arr2.m_Vec[from2++]);
		m_Vec[n].vec3_normalize();
	}

}

void Simd_4f32::vec3_cross(const Simd_4f32 &arr2, int from, int from2, int num)
{
	int to = from + num;
	GSIMD_CHECK_BOTH_RANGE

	for (int n=from; n<to; n++)
		m_Vec[n].vec3_cross(arr2.m_Vec[from2++]);
}


void Simd_4f32::vec3_inv_xform(const Transform &tr, int from, int num)
{
	int to = from + num;
	GSIMD_CHECK_RANGE

	f32_transform trans;
	trans.from_transform_inv(tr);

	for (int n=from; n<to; n++)
		m_Vec[n].vec3_inv_xform(trans);

}


void Simd_4f32::vec3_xform(const Transform &tr, int from, int num)
{
	int to = from + num;
	GSIMD_CHECK_RANGE

	f32_transform trans;
	trans.from_transform(tr);

	for (int n=from; n<to; n++)
		m_Vec[n].vec3_xform(trans);
}





void Simd_4f32::value_add(const Quat &val, int from, int num)
{
	int to = from + num;
	GSIMD_CHECK_RANGE
	f32_4 u;
	u.from_quat(val);
#ifdef GSIMD_USE_SSE
	if (g_GodotCPU.HasFlag(Godot_CPU::F_SSE))
	{
		Simd_4f32_SSE::value_add((float *) &m_Vec[from], (float *) &u, num);
		return;
	}
#endif
	for (int n=from; n<to; n++)
		m_Vec[n].add(u);
}

void Simd_4f32::value_subtract(const Quat &val, int from, int num)
{
	int to = from + num;
	GSIMD_CHECK_RANGE
	f32_4 u;
	u.from_quat(val);
#ifdef GSIMD_USE_SSE
	if (g_GodotCPU.HasFlag(Godot_CPU::F_SSE))
	{
		Simd_4f32_SSE::value_subtract((float *) &m_Vec[from], (float *) &u, num);
		return;
	}
#endif
	for (int n=from; n<to; n++)
		m_Vec[n].subtract(u);
}

void Simd_4f32::value_multiply(const Quat &val, int from, int num)
{
	int to = from + num;
	GSIMD_CHECK_RANGE
	f32_4 u;
	u.from_quat(val);
#ifdef GSIMD_USE_SSE
	if (g_GodotCPU.HasFlag(Godot_CPU::F_SSE))
	{
		Simd_4f32_SSE::value_multiply((float *) &m_Vec[from], (float *) &u, num);
		return;
	}
#endif
	for (int n=from; n<to; n++)
		m_Vec[n].multiply(u);
}

void Simd_4f32::value_divide(const Quat &val, int from, int num)
{
	int to = from + num;
	GSIMD_CHECK_RANGE
	f32_4 u;
	u.from_quat(val);
#ifdef GSIMD_USE_SSE
	if (g_GodotCPU.HasFlag(Godot_CPU::F_SSE))
	{
		Simd_4f32_SSE::value_divide((float *) &m_Vec[from], (float *) &u, num);
		return;
	}
#endif
	for (int n=from; n<to; n++)
		m_Vec[n].divide(u);
}

void Simd_4f32::vec3_length(int from, int num)
{
	int to = from + num;
	GSIMD_CHECK_RANGE
#ifdef GSIMD_USE_SSE3
	if (g_GodotCPU.HasFlag(Godot_CPU::F_SSE3))
	{
		Simd_4f32_SSE3::vec3_length((float *) &m_Vec[from], num);
		return;
	}
#endif
	for (int n=from; n<to; n++)
		m_Vec[n].vec3_length();
}

void Simd_4f32::vec3_length_squared(int from, int num)
{
	int to = from + num;
	GSIMD_CHECK_RANGE
#ifdef GSIMD_USE_SSE3
	if (g_GodotCPU.HasFlag(Godot_CPU::F_SSE3))
	{
		Simd_4f32_SSE3::vec3_length_squared((float *) &m_Vec[from], num);
		return;
	}
#endif
	for (int n=from; n<to; n++)
		m_Vec[n].vec3_length_squared();
}


void Simd_4f32::vec3_normalize(int from, int num)
{
	int to = from + num;
	GSIMD_CHECK_RANGE
	for (int n=from; n<to; n++)
		m_Vec[n].vec3_normalize();
}


String Simd_4f32::get_cpu_name()
{
	return g_GodotCPU.get_name();
}

String Simd_4f32::get_cpu_caps(String spacer)
{
	return g_GodotCPU.get_sse_caps_string(spacer);
}


void Simd_4f32::test(int from, int num)
{
//	int to = from + num;
	GSIMD_CHECK_RANGE
//#ifdef GSIMD_USE_SSE
//	if (g_GodotCPU.HasFlag(Godot_CPU::F_SSE))
//	{
//		float * pf = (float *) &m_Vec[from];

//		for (int n=from; n<to; n++)
//		{
//			__m128 m = _mm_loadu_ps(pf);
//			__m128 res = _mm_sqrt_ps(m);
//			_mm_storeu_ps(pf, res);
//			pf += 4;
//		}
//		return;
//	}
//#endif

}


void Simd_4f32::vec2_normalize(int from, int num)
{
	int to = from + num;
	GSIMD_CHECK_RANGE
	for (int n=from; n<to; n++)
		m_Vec[n].vec2_normalize();
}

void Simd_4f32::sqrt(int from, int num)
{
	int to = from + num;
	GSIMD_CHECK_RANGE
#ifdef GSIMD_USE_SSE
	if (g_GodotCPU.HasFlag(Godot_CPU::F_SSE))
	{
		Simd_4f32_SSE::sqrt((float *) &m_Vec[from], num);
		return;
	}
#endif
	for (int n=from; n<to; n++)
		m_Vec[n].sqrt();
}

void Simd_4f32::reciprocal(int from, int num)
{
	int to = from + num;
	GSIMD_CHECK_RANGE
#ifdef GSIMD_USE_SSE
	if (g_GodotCPU.HasFlag(Godot_CPU::F_SSE))
	{
		Simd_4f32_SSE::reciprocal((float *) &m_Vec[from], num);
		return;
	}
#endif
	for (int n=from; n<to; n++)
		m_Vec[n].reciprocal();
}

void Simd_4f32::inv_sqrt(int from, int num)
{
	int to = from + num;
	GSIMD_CHECK_RANGE
#ifdef GSIMD_USE_SSE
	if (g_GodotCPU.HasFlag(Godot_CPU::F_SSE))
	{
		Simd_4f32_SSE::inv_sqrt((float *) &m_Vec[from], num);
		return;
	}
#endif
	// cannot be auto-vectorized! must be done manually
	for (int n=from; n<to; n++)
		m_Vec[n].inv_sqrt();
}




#ifdef GSIMD_NEON
//	float * pf = (float *) &m_Vec[from];
//	for (int n=from; n<to; n++)
//	{
//		float32x4_t m;
//		float32x4_t  res = vaddq_f32(m, add_val);
//		pf += 4;
//	}
#endif

#undef GSIMD_CHECK_RANGE
#undef GSIMD_CHECK_BOTH_RANGE
