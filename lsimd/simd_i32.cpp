#include "simd_i32.h"

#define GSIMD_CHECK_RANGE if (!check_range(from, num, size())) {return;}
#define GSIMD_CHECK_BOTH_RANGE if (!check_range(from, num, size())) {return;} \
if (!check_range(from2, num, arr2.size())) {return;}


namespace GSimd
{

bool Simd_4i32::check_range(int from, int num, int size) const
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


void Simd_4i32::fill(const GSimd::i32_4 &v)
{
	for (int n=0; n<m_Vec.size(); n++)
		m_Vec[n] = v;
}


void Simd_4i32::value_add(const GSimd::i32_4 &val, int from, int num)
{
	int to = from + num;
	GSIMD_CHECK_RANGE
	for (int n=from; n<to; n++)
		m_Vec[n].add(val);
}

void Simd_4i32::value_subtract(const GSimd::i32_4 &val, int from, int num)
{
	int to = from + num;
	GSIMD_CHECK_RANGE
	for (int n=from; n<to; n++)
		m_Vec[n].subtract(val);
}

void Simd_4i32::value_multiply(const GSimd::i32_4 &val, int from, int num)
{
	int to = from + num;
	GSIMD_CHECK_RANGE
	for (int n=from; n<to; n++)
		m_Vec[n].multiply(val);
}

void Simd_4i32::value_divide(const GSimd::i32_4 &val, int from, int num)
{
	int to = from + num;
	GSIMD_CHECK_RANGE
	for (int n=from; n<to; n++)
		m_Vec[n].divide(val);
}

void Simd_4i32::add(const Simd_4i32 &arr2, int from, int from2, int num)
{
	int to = from + num;
	GSIMD_CHECK_BOTH_RANGE
	for (int n=from; n<to; n++)
		m_Vec[n].add(arr2.m_Vec[from2++]);
}

void Simd_4i32::subtract(const Simd_4i32 &arr2, int from, int from2, int num)
{
	int to = from + num;
	GSIMD_CHECK_BOTH_RANGE
	for (int n=from; n<to; n++)
		m_Vec[n].subtract(arr2.m_Vec[from2++]);
}

void Simd_4i32::multiply(const Simd_4i32 &arr2, int from, int from2, int num)
{
	int to = from + num;
	GSIMD_CHECK_BOTH_RANGE
	for (int n=from; n<to; n++)
		m_Vec[n].multiply(arr2.m_Vec[from2++]);
}

void Simd_4i32::divide(const Simd_4i32 &arr2, int from, int from2, int num)
{
	int to = from + num;
	GSIMD_CHECK_BOTH_RANGE
	for (int n=from; n<to; n++)
		m_Vec[n].divide(arr2.m_Vec[from2++]);
}


void Simd_4i32::vec3_length(int from, int num)
{
	int to = from + num;
	GSIMD_CHECK_RANGE
	for (int n=from; n<to; n++)
		m_Vec[n].vec3_length();
}


} // namespace

#undef GSIMD_CHECK_RANGE
#undef GSIMD_CHECK_BOTH_RANGE
