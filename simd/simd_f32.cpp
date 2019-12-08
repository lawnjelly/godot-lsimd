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


#ifdef GSIMD_SSE
#include <xmmintrin.h>
#endif

using namespace GSimd;


#define GSIMD_CHECK_RANGE if (!check_range(from, to)) {return;}


// Note that most of these routines will be auto-vectorized if -O3 is used and the architecture is set

FastArray_4f32::FastArray_4f32()
{

}

Quat FastArray_4f32::read(int i) const
{
	Quat q;
	m_Vec[i].to_quat(q);
	return q;
}

void FastArray_4f32::write(int i, const Quat &q)
{
	m_Vec[i].from_quat(q);
}


bool FastArray_4f32::check_range(int from, int to) const
{
	int size = m_Vec.size();
	// check for below zero at same time
	if ((unsigned int) from > size) goto failed;
	if ((unsigned int) to > size) goto failed;
	return true;

failed:
	ERR_FAIL_INDEX_V(from, size, false);
	ERR_FAIL_INDEX_V(to, size, false);
	return false;
}

void FastArray_4f32::fill(const Quat &val)
{
	f32_4 u;
	u.from_quat(val);
	int s = size();
	for (int n=0; n<s; n++)
		m_Vec[n] = u;
}

void FastArray_4f32::zero()
{
	int s = size();
	if (!s) return;
	memset(&m_Vec[0], 0, sizeof (GSimd::f32_4) * s);
}

PoolRealArray FastArray_4f32::get_poolrealarray_result() const
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


PoolVector<Vector3> FastArray_4f32::get_poolvector3array() const
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


void FastArray_4f32::copyfrom_poolvector3array(const PoolVector<Vector3> &arr)
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

void FastArray_4f32::copy(Object * pArr2)
{
	FastArray_4f32 * p2 = Object::cast_to<FastArray_4f32>(pArr2);
	if (!p2)
		return; // not the right type

	int size = p2->size();
	if (size == 0)
	{
		m_Vec.clear(true);
		return;
	}

	reserve(size);

	memcpy(&m_Vec[0], &p2->m_Vec[0], sizeof (GSimd::f32_4) * size);
}


void FastArray_4f32::add(Object * pArr2, int from, int to)
{
	GSIMD_CHECK_RANGE
	FastArray_4f32 * p2 = Object::cast_to<FastArray_4f32>(pArr2);
	if (!p2)
		return; // not the right type

	for (int n=from; n<to; n++)
		m_Vec[n].add(p2->m_Vec[n]);
}

void FastArray_4f32::subtract(Object * pArr2, int from, int to)
{
	GSIMD_CHECK_RANGE
	FastArray_4f32 * p2 = Object::cast_to<FastArray_4f32>(pArr2);
	if (!p2)
		return; // not the right type

	for (int n=from; n<to; n++)
		m_Vec[n].subtract(p2->m_Vec[n]);
}

void FastArray_4f32::multiply(Object * pArr2, int from, int to)
{
	GSIMD_CHECK_RANGE
	FastArray_4f32 * p2 = Object::cast_to<FastArray_4f32>(pArr2);
	if (!p2)
		return; // not the right type

	for (int n=from; n<to; n++)
		m_Vec[n].multiply(p2->m_Vec[n]);
}

void FastArray_4f32::divide(Object * pArr2, int from, int to)
{
	GSIMD_CHECK_RANGE
	FastArray_4f32 * p2 = Object::cast_to<FastArray_4f32>(pArr2);
	if (!p2)
		return; // not the right type

	for (int n=from; n<to; n++)
		m_Vec[n].divide(p2->m_Vec[n]);
}

void FastArray_4f32::dot(Object * pArr2, int from, int to)
{
	GSIMD_CHECK_RANGE

	FastArray_4f32 * p2 = Object::cast_to<FastArray_4f32>(pArr2);
	if (!p2)
		return; // not the right type

	for (int n=from; n<to; n++)
		m_Vec[n].dot(p2->m_Vec[n]);
}


void FastArray_4f32::unit_cross(Object * pArr2, int from, int to)
{
	GSIMD_CHECK_RANGE
	FastArray_4f32 * p2 = Object::cast_to<FastArray_4f32>(pArr2);
	if (!p2)
		return; // not the right type

	for (int n=from; n<to; n++)
	{
		m_Vec[n].cross(p2->m_Vec[n]);
		m_Vec[n].normalize();
	}

}

void FastArray_4f32::cross(Object * pArr2, int from, int to)
{
	GSIMD_CHECK_RANGE
	FastArray_4f32 * p2 = Object::cast_to<FastArray_4f32>(pArr2);
	if (!p2)
		return; // not the right type

	for (int n=from; n<to; n++)
		m_Vec[n].cross(p2->m_Vec[n]);
}



void FastArray_4f32::value_add(const Quat &val, int from, int to)
{
	GSIMD_CHECK_RANGE
	f32_4 u;
	u.from_quat(val);

	for (int n=from; n<to; n++)
		m_Vec[n].add(u);
}

void FastArray_4f32::value_subtract(const Quat &val, int from, int to)
{
	GSIMD_CHECK_RANGE
	f32_4 u;
	u.from_quat(val);
	for (int n=from; n<to; n++)
		m_Vec[n].subtract(u);
}

void FastArray_4f32::value_multiply(const Quat &val, int from, int to)
{
	GSIMD_CHECK_RANGE
	f32_4 u;
	u.from_quat(val);
	for (int n=from; n<to; n++)
		m_Vec[n].multiply(u);
}

void FastArray_4f32::value_divide(const Quat &val, int from, int to)
{
	GSIMD_CHECK_RANGE
	f32_4 u;
	u.from_quat(val);
	for (int n=from; n<to; n++)
		m_Vec[n].divide(u);
}

void FastArray_4f32::length(int from, int to)
{
	GSIMD_CHECK_RANGE
	for (int n=from; n<to; n++)
		m_Vec[n].length();
}

void FastArray_4f32::length_squared(int from, int to)
{
	GSIMD_CHECK_RANGE
	for (int n=from; n<to; n++)
		m_Vec[n].length_squared();
}


void FastArray_4f32::normalize(int from, int to)
{
	GSIMD_CHECK_RANGE
	for (int n=from; n<to; n++)
		m_Vec[n].normalize();
}

void FastArray_4f32::sqrt(int from, int to)
{
	GSIMD_CHECK_RANGE
	for (int n=from; n<to; n++)
		m_Vec[n].sqrt();
}

void FastArray_4f32::reciprocal(int from, int to)
{
	GSIMD_CHECK_RANGE
	for (int n=from; n<to; n++)
		m_Vec[n].reciprocal();
}

void FastArray_4f32::inv_sqrt(int from, int to)
{
	GSIMD_CHECK_RANGE
	// cannot be auto-vectorized! must be done manually
	for (int n=from; n<to; n++)
		m_Vec[n].inv_sqrt();

#ifdef GSIMD_NONE
#endif

#ifdef GSIMD_SSE
//	__m128 add_val = _mm_set_ps(val.x, val.y, val.z, val.w);

//	float * pf = (float *) &m_Vec[from];

//	for (int n=from; n<to; n++)
//	{
//		__m128 m = _mm_load_ps(pf);
//		__m128 res = _mm_add_ps(m, add_val);
//		_mm_store_ps(pf, res);
//		pf += 4;
//	}
#endif

#ifdef GSIMD_NEON
//	float * pf = (float *) &m_Vec[from];
//	for (int n=from; n<to; n++)
//	{
//		float32x4_t m;
//		float32x4_t  res = vaddq_f32(m, add_val);
//		pf += 4;
//	}
#endif

}



void FastArray_4f32::_bind_methods()
{
	ClassDB::bind_method(D_METHOD("reserve", "size"), &FastArray_4f32::reserve);
	ClassDB::bind_method(D_METHOD("resize", "size"), &FastArray_4f32::resize);
	ClassDB::bind_method(D_METHOD("fill", "value"), &FastArray_4f32::fill);
	ClassDB::bind_method(D_METHOD("zero"), &FastArray_4f32::zero);


	ClassDB::bind_method(D_METHOD("copy", "Second FastArray_4f32"), &FastArray_4f32::copy);
	ClassDB::bind_method(D_METHOD("copyfrom_poolvector3array", "array"), &FastArray_4f32::copyfrom_poolvector3array);
	ClassDB::bind_method(D_METHOD("get_poolvector3array"), &FastArray_4f32::get_poolvector3array);
	ClassDB::bind_method(D_METHOD("get_poolrealarray_result"), &FastArray_4f32::get_poolrealarray_result);

	ClassDB::bind_method(D_METHOD("read", "element"), &FastArray_4f32::read);
	ClassDB::bind_method(D_METHOD("write", "element", "value"), &FastArray_4f32::write);
	ClassDB::bind_method(D_METHOD("size"), &FastArray_4f32::size);

	ClassDB::bind_method(D_METHOD("add", "array2", "from", "to"), &FastArray_4f32::add);
	ClassDB::bind_method(D_METHOD("subtract", "array2", "from", "to"), &FastArray_4f32::subtract);
	ClassDB::bind_method(D_METHOD("multiply", "array2", "from", "to"), &FastArray_4f32::multiply);
	ClassDB::bind_method(D_METHOD("divide", "array2", "from", "to"), &FastArray_4f32::divide);

	ClassDB::bind_method(D_METHOD("dot", "array2", "from", "to"), &FastArray_4f32::dot);
	ClassDB::bind_method(D_METHOD("cross", "array2", "from", "to"), &FastArray_4f32::cross);
	ClassDB::bind_method(D_METHOD("unit_cross", "array2", "from", "to"), &FastArray_4f32::unit_cross);

	ClassDB::bind_method(D_METHOD("value_add", "value", "from", "to"), &FastArray_4f32::value_add);
	ClassDB::bind_method(D_METHOD("value_subtract", "value", "from", "to"), &FastArray_4f32::value_subtract);
	ClassDB::bind_method(D_METHOD("value_multiply", "value", "from", "to"), &FastArray_4f32::value_multiply);
	ClassDB::bind_method(D_METHOD("value_divide", "value", "from", "to"), &FastArray_4f32::value_divide);

	ClassDB::bind_method(D_METHOD("length", "from", "to"), &FastArray_4f32::length);
	ClassDB::bind_method(D_METHOD("length_squared", "from", "to"), &FastArray_4f32::length_squared);

	ClassDB::bind_method(D_METHOD("normalize", "from", "to"), &FastArray_4f32::normalize);
	ClassDB::bind_method(D_METHOD("sqrt", "from", "to"), &FastArray_4f32::sqrt);
	ClassDB::bind_method(D_METHOD("inv_sqrt", "from", "to"), &FastArray_4f32::inv_sqrt);
	ClassDB::bind_method(D_METHOD("reciprocal", "from", "to"), &FastArray_4f32::reciprocal);
}
