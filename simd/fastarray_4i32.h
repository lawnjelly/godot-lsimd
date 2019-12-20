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


#include "simd_i32.h"
#include "vec4_i32.h"
#include "core/reference.h"
#include "core/pool_vector.h"

class FastArray_4i32: public Reference
{
	GDCLASS(FastArray_4i32, Reference);

public:

	// sizing
	void reserve(int size) {m_Array.reserve(size);}
	void resize(int size) {	m_Array.resize(size);}

	// element access
	Ref<Vec4_i32> read(int i) const;
	void write(int i, const Ref<Vec4_i32> &val);

	void fill(const Ref<Vec4_i32> &val) {m_Array.fill(val->d);}
	void zero() {m_Array.zero();}

	int size() const {return m_Array.size();}

	void value_add(const Ref<Vec4_i32> &val, int from, int num) {m_Array.value_add(val.ptr()->d, from, num);}
	void value_subtract(const Ref<Vec4_i32> &val, int from, int num) {m_Array.value_subtract(val.ptr()->d, from, num);}
	void value_multiply(const Ref<Vec4_i32> &val, int from, int num) {m_Array.value_multiply(val.ptr()->d, from, num);}
	void value_divide(const Ref<Vec4_i32> &val, int from, int num) {m_Array.value_divide(val.ptr()->d, from, num);}

	void add(const Ref<FastArray_4i32> &arr2, int from, int from2, int num) {m_Array.add(arr2->m_Array, from, from2, num);}
	void subtract(const Ref<FastArray_4i32> &arr2, int from, int from2, int num) {m_Array.subtract(arr2->m_Array, from, from2, num);}
	void multiply(const Ref<FastArray_4i32> &arr2, int from, int from2, int num) {m_Array.multiply(arr2->m_Array, from, from2, num);}
	void divide(const Ref<FastArray_4i32> &arr2, int from, int from2, int num) {m_Array.divide(arr2->m_Array, from, from2, num);}

	// geometry
	void vec3_length(int from, int num) {m_Array.vec3_length(from, num);}

protected:
	static void _bind_methods();

private:
	GSimd::Simd_4i32 m_Array;
};
