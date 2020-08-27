#pragma once

#include "simd_types.h"
#include "simd_vector.h"
#include "core/reference.h"
#include "simd_f32.h"

class FastArray_2f32: public Reference
{
	GDCLASS(FastArray_2f32, Reference);

	enum eRangeFlags
	{
		RF_BEFORE = 1 << 0,
		RF_AFTER = 1 << 1,
	};

public:
	FastArray_2f32();

	// sizing
	void reserve(int size)
	{
		m_iSize = size;
		m_Array.resize(_calc_quad_size(size));
		m_Result.resize(m_Array.size() * 2);
		m_Result.zero();
		zero();
	}

	void resize(int size)
	{
		m_iSize = size;
		m_Array.resize(_calc_quad_size(size));
		m_Result.resize(m_Array.size() * 2);
		m_Result.zero();
	}

	int size() const {return m_iSize;}

	void fill(const Vector2 &v);
	void zero() {m_Array.zero();}

	void copy_from(const Ref<FastArray_2f32> &arr2);

	Vector2 read(int i) const;
	void write(int i, const Vector2 &v);

	float read_result(int i) const;

	void value_add(const Vector2 &val, int from, int num);
	void value_subtract(const Vector2 &val, int from, int num);
	void value_multiply(const Vector2 &val, int from, int num);
	void value_divide(const Vector2 &val, int from, int num);

	void sqrt(int from, int num);
	void inv_sqrt(int from, int num);
	void reciprocal(int from, int num);

	void add(const Ref<FastArray_2f32> &arr2, int from, int from2, int num);
	void subtract(const Ref<FastArray_2f32> &arr2, int from, int from2, int num);
	void multiply(const Ref<FastArray_2f32> &arr2, int from, int from2, int num);
	void divide(const Ref<FastArray_2f32> &arr2, int from, int from2, int num);

	void dot(const Ref<FastArray_2f32> &arr2, int from, int from2, int num);
	void cross(const Ref<FastArray_2f32> &arr2, int from, int from2, int num);

	void normalize(int from, int num);
	void length(int from, int num);
	void length_squared(int from, int num);

protected:
	static void _bind_methods();

private:
	int _calc_quad_size(int size) const;
	unsigned int _find_quad_range(int from, int num, int &q_from, int &num_quads) const;

	Simd_4f32 m_Array;

	// store the results of operations like dot product in an array of equal length to the number of elements
	GSimd::SVector<float> m_Result;

	int m_iSize; // in vector 2 units
};
