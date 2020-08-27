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

/**
	@author lawnjelly <lawnjelly@gmail.com>
*/


#include "type_f32_4.h"
#include "simd_vector.h"
#include "core/math/vector3.h"
#include "core/math/vector2.h"
#include "core/pool_vector.h"
#include "core/variant.h"

class Simd_4f32
{
public:
	Simd_4f32();

	// sizing
	void reserve(int size)
	{
		m_Vec.resize(size);
		zero();
	}

	void resize(int size)
	{
		m_Vec.resize(size);
	}

	void copy_from(const Simd_4f32 &o);

	void copy_from_poolvector3array(const PoolVector<Vector3> &arr);
	PoolVector<Vector3> get_poolvector3array() const;

	// get the results of operation like length, which are returned as element 3
	PoolRealArray get_poolrealarray_result() const;

	// element access
	Quat read(int i) const;
	void write(int i, const Quat &q);

	Vector3 vec3_read(int i) const;
	void vec3_write(int i, const Vector3 &v);

	void fill(const Quat &val);
	void zero();

	int size() const {return m_Vec.size();}

	// SIMD
	void value_add(const Quat &val, int from, int num);
	void value_subtract(const Quat &val, int from, int num);
	void value_multiply(const Quat &val, int from, int num);
	void value_divide(const Quat &val, int from, int num);

	void add(const Simd_4f32 &arr2, int from, int from2, int num);
	void subtract(const Simd_4f32 &arr2, int from, int from2, int num);
	void multiply(const Simd_4f32 &arr2, int from, int from2, int num);
	void divide(const Simd_4f32 &arr2, int from, int from2, int num);

	// geometry
	// vec3
	void vec3_dot(const Simd_4f32 &arr2, int from, int from2, int num);
	void vec3_cross(const Simd_4f32 &arr2, int from, int from2, int num);
	void vec3_unit_cross(const Simd_4f32 &arr2, int from, int from2, int num);

	void vec3_normalize(int from, int num);
	void vec3_length(int from, int num);
	void vec3_length_squared(int from, int num);

	void vec3_xform(const Transform &tr, int from, int num);
	void vec3_inv_xform(const Transform &tr, int from, int num);

	// vec2
	void vec2_dot(const Simd_4f32 &arr2, int from, int from2, int num, float * pfResult);
	void vec2_cross(const Simd_4f32 &arr2, int from, int from2, int num, float * pfResult);

	void vec2_length(int from, int num, float * pfResult);
	void vec2_length_squared(int from, int num, float * pfResult);

	void vec2_normalize(int from, int num);



	void sqrt(int from, int num);
	void inv_sqrt(int from, int num);
	void reciprocal(int from, int num);

	void test(int from, int num);

	String get_cpu_name();
	String get_cpu_caps(String spacer);

private:
	bool check_range(int from, int num, int size) const;

public:
	GSimd::SVector<GSimd::f32_4> m_Vec;

};
