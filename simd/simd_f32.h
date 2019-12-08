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


#include "simd_types.h"
#include "simd_vector.h"
#include "core/reference.h"
#include "core/math/vector3.h"
#include "core/pool_vector.h"

class FastArray_4f32: public Reference
{
    GDCLASS(FastArray_4f32, Reference);
public:
	FastArray_4f32();

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

	void copy(Object * pArr2);

	void copyfrom_poolvector3array(const PoolVector<Vector3> &arr);
	PoolVector<Vector3> get_poolvector3array() const;

	// get the results of operation like length, which are returned as element 3
	PoolRealArray get_poolrealarray_result() const;

	// element access
	Quat read(int i) const;
	void write(int i, const Quat &q);

	void fill(const Quat &val);
	void zero();

	int size() const {return m_Vec.size();}

	// SIMD
	void value_add(const Quat &val, int from, int to);
	void value_subtract(const Quat &val, int from, int to);
	void value_multiply(const Quat &val, int from, int to);
	void value_divide(const Quat &val, int from, int to);

	void add(Object * pArr2, int from, int to);
	void subtract(Object * pArr2, int from, int to);
	void multiply(Object * pArr2, int from, int to);
	void divide(Object * pArr2, int from, int to);

	// geometry
	void dot(Object * pArr2, int from, int to);
	void cross(Object * pArr2, int from, int to);
	void unit_cross(Object * pArr2, int from, int to);
	void normalize(int from, int to);

	void length(int from, int to);
	void length_squared(int from, int to);

	void sqrt(int from, int to);
	void inv_sqrt(int from, int to);
	void reciprocal(int from, int to);

protected:
	static void _bind_methods();
	
private:
	bool check_range(int from, int to) const;

	GSimd::SVector<GSimd::f32_4> m_Vec;

};
