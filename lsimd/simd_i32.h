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


#include "type_i32_4.h"
#include "simd_vector.h"
#include "core/math/vector3.h"
#include "core/math/vector2.h"
#include "core/pool_vector.h"
#include "core/variant.h"

namespace GSimd
{


class Simd_4i32
{
public:
	//Simd_4i32();

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

	// element access
	GSimd::i32_4 read(int i) const {return m_Vec[i];}
	void write(int i, const GSimd::i32_4 &v) {m_Vec[i] = v;}

	void fill(const GSimd::i32_4 &v);
	void zero() {m_Vec.zero();}

	int size() const {return m_Vec.size();}

	// SIMD
	void value_add(const GSimd::i32_4 &val, int from, int num);
	void value_subtract(const GSimd::i32_4 &val, int from, int num);
	void value_multiply(const GSimd::i32_4 &val, int from, int num);
	void value_divide(const GSimd::i32_4 &val, int from, int num);

	void add(const Simd_4i32 &arr2, int from, int from2, int num);
	void subtract(const Simd_4i32 &arr2, int from, int from2, int num);
	void multiply(const Simd_4i32 &arr2, int from, int from2, int num);
	void divide(const Simd_4i32 &arr2, int from, int from2, int num);

//	// geometry
//	// vec3
//	void vec3_dot(Simd_4f32 &arr2, int from, int from2, int num);
//	void vec3_cross(Simd_4f32 &arr2, int from, int from2, int num);
//	void vec3_unit_cross(Simd_4f32 &arr2, int from, int from2, int num);

//	void vec3_normalize(int from, int num);
	void vec3_length(int from, int num);
//	void vec3_length_squared(int from, int num);

//	void vec3_xform(const Transform &tr, int from, int num);
//	void vec3_inv_xform(const Transform &tr, int from, int num);

//	// vec2
//	void vec2_dot(Simd_4f32 &arr2, int from, int from2, int num, float * pfResult);
//	void vec2_cross(Simd_4f32 &arr2, int from, int from2, int num, float * pfResult);

//	void vec2_length(int from, int num, float * pfResult);
//	void vec2_length_squared(int from, int num, float * pfResult);

//	void vec2_normalize(int from, int num);



//	void sqrt(int from, int num);
//	void inv_sqrt(int from, int num);
//	void reciprocal(int from, int num);

private:
	bool check_range(int from, int num, int size) const;

public:
	GSimd::SVector<GSimd::i32_4> m_Vec;

};

} // namespace
