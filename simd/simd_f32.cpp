#include "simd_f32.h"
#include "core/variant.h"
#include <string.h>


#ifdef GSIMD_SSE
#include <xmmintrin.h>
#endif

using namespace GSimd;

// Note that most of these routines will be auto-vectorized if -O3 is used and the architecture is set

FastArray_4f32::FastArray_4f32()
{

}

bool FastArray_4f32::check_range(int from, int to) const
{
	int size = m_Vec.size();
	// check for below zero at same time
	if ((unsigned int) from >= size) return false;
	if ((unsigned int) to >= size) return false;
	return true;
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
//	PoolVector3Array * pArr = array;
//	if (!pArr)
//		return;

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


void FastArray_4f32::add_array(Object * pArr2, int from, int to)
{
	FastArray_4f32 * p2 = Object::cast_to<FastArray_4f32>(pArr2);
	if (!p2)
		return; // not the right type

	for (int n=from; n<to; n++)
		m_Vec[n].add(p2->m_Vec[n]);
}

void FastArray_4f32::subtract_array(Object * pArr2, int from, int to)
{
	FastArray_4f32 * p2 = Object::cast_to<FastArray_4f32>(pArr2);
	if (!p2)
		return; // not the right type

	for (int n=from; n<to; n++)
		m_Vec[n].subtract(p2->m_Vec[n]);
}

void FastArray_4f32::multiply_array(Object * pArr2, int from, int to)
{
	FastArray_4f32 * p2 = Object::cast_to<FastArray_4f32>(pArr2);
	if (!p2)
		return; // not the right type

	for (int n=from; n<to; n++)
		m_Vec[n].multiply(p2->m_Vec[n]);
}

void FastArray_4f32::divide_array(Object * pArr2, int from, int to)
{
	FastArray_4f32 * p2 = Object::cast_to<FastArray_4f32>(pArr2);
	if (!p2)
		return; // not the right type

	for (int n=from; n<to; n++)
		m_Vec[n].divide(p2->m_Vec[n]);
}

void FastArray_4f32::add(const Quat &val, int from, int to)
{
	f32_4 u;
	u.from_quat(val);

	for (int n=from; n<to; n++)
		m_Vec[n].add(u);
}

void FastArray_4f32::subtract(const Quat &val, int from, int to)
{
	f32_4 u;
	u.from_quat(val);
	for (int n=from; n<to; n++)
		m_Vec[n].subtract(u);
}

void FastArray_4f32::multiply(const Quat &val, int from, int to)
{
	f32_4 u;
	u.from_quat(val);
	for (int n=from; n<to; n++)
		m_Vec[n].multiply(u);
}

void FastArray_4f32::divide(const Quat &val, int from, int to)
{
	f32_4 u;
	u.from_quat(val);
	for (int n=from; n<to; n++)
		m_Vec[n].divide(u);
}

void FastArray_4f32::sqrt(int from, int to)
{
	for (int n=from; n<to; n++)
		m_Vec[n].sqrt();
}

void FastArray_4f32::reciprocal(int from, int to)
{
	for (int n=from; n<to; n++)
		m_Vec[n].reciprocal();
}

void FastArray_4f32::inv_sqrt(int from, int to)
{
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

	ClassDB::bind_method(D_METHOD("read", "element"), &FastArray_4f32::read);
	ClassDB::bind_method(D_METHOD("write", "element", "value"), &FastArray_4f32::set);
	ClassDB::bind_method(D_METHOD("size"), &FastArray_4f32::size);

	ClassDB::bind_method(D_METHOD("add_array", "array2", "from", "to"), &FastArray_4f32::add_array);
	ClassDB::bind_method(D_METHOD("subtract_array", "array2", "from", "to"), &FastArray_4f32::add_array);
	ClassDB::bind_method(D_METHOD("multiply_array", "array2", "from", "to"), &FastArray_4f32::add_array);
	ClassDB::bind_method(D_METHOD("divide_array", "array2", "from", "to"), &FastArray_4f32::add_array);

	ClassDB::bind_method(D_METHOD("add", "value", "from", "to"), &FastArray_4f32::add);
	ClassDB::bind_method(D_METHOD("subtract", "value", "from", "to"), &FastArray_4f32::subtract);
	ClassDB::bind_method(D_METHOD("multiply", "value", "from", "to"), &FastArray_4f32::multiply);
	ClassDB::bind_method(D_METHOD("divide", "value", "from", "to"), &FastArray_4f32::divide);

	ClassDB::bind_method(D_METHOD("sqrt", "from", "to"), &FastArray_4f32::sqrt);
	ClassDB::bind_method(D_METHOD("inv_sqrt", "from", "to"), &FastArray_4f32::inv_sqrt);
	ClassDB::bind_method(D_METHOD("reciprocal", "from", "to"), &FastArray_4f32::reciprocal);
}
