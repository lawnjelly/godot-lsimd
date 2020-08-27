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


#include "simd_f32.h"
//#include "simd_types.h"
//#include "simd_vector.h"
#include "core/reference.h"
//#include "core/math/vector3.h"
#include "core/pool_vector.h"

class FastArray_4f32: public Reference
{
	GDCLASS(FastArray_4f32, Reference);

public:

	// sizing
	void reserve(int size) {m_Array.reserve(size);}
	void resize(int size) {	m_Array.resize(size);}
	void copy_from(const Ref<FastArray_4f32> &arr2);
	void copy_from_poolvector3array(const PoolVector<Vector3> &arr) {m_Array.copy_from_poolvector3array(arr);}
	PoolVector<Vector3> get_poolvector3array() const {return m_Array.get_poolvector3array();}

	// get the results of operation like length, which are returned as element 3
	PoolRealArray get_poolrealarray_result() const {return m_Array.get_poolrealarray_result();}

	// element access
	Quat read(int i) const {return m_Array.read(i);}
	void write(int i, const Quat &q) {m_Array.write(i, q);}

	Vector3 vec3_read(int i) const {return m_Array.vec3_read(i);}
	void vec3_write(int i, const Vector3 &v) {m_Array.vec3_write(i, v);}

	void fill(const Quat &val) {m_Array.fill(val);}
	void zero() {m_Array.zero();}

	int size() const {return m_Array.size();}

	// SIMD
	void value_add(const Quat &val, int from, int num) {m_Array.value_add(val, from, num);}
	void value_subtract(const Quat &val, int from, int num) {m_Array.value_subtract(val, from, num);}
	void value_multiply(const Quat &val, int from, int num) {m_Array.value_multiply(val, from, num);}
	void value_divide(const Quat &val, int from, int num) {m_Array.value_divide(val, from, num);}

	void add(const Ref<FastArray_4f32> &arr2, int from, int from2, int num);
	void subtract(const Ref<FastArray_4f32> &arr2, int from, int from2, int num);
	void multiply(const Ref<FastArray_4f32> &arr2, int from, int from2, int num);
	void divide(const Ref<FastArray_4f32> &arr2, int from, int from2, int num);

	// geometry
	// vec3
	void vec3_dot(const Ref<FastArray_4f32> &arr2, int from, int from2, int num);
	void vec3_cross(const Ref<FastArray_4f32> &arr2, int from, int from2, int num);
	void vec3_unit_cross(const Ref<FastArray_4f32> &arr2, int from, int from2, int num);

	void vec3_normalize(int from, int num) {m_Array.vec3_normalize(from, num);}
	void vec3_length(int from, int num) {m_Array.vec3_length(from, num);}
	void vec3_length_squared(int from, int num) {m_Array.vec3_length_squared(from, num);}

	void vec3_xform(const Transform &tr, int from, int num) {m_Array.vec3_xform(tr, from, num);}
	void vec3_inv_xform(const Transform &tr, int from, int num) {m_Array.vec3_inv_xform(tr, from, num);}

	void sqrt(int from, int num) {m_Array.sqrt(from, num);}
	void inv_sqrt(int from, int num) {m_Array.inv_sqrt(from, num);}
	void reciprocal(int from, int num) {m_Array.reciprocal(from, num);}

	void test(int from, int num) {m_Array.test(from, num);}

	String get_cpu_name() {return m_Array.get_cpu_name();}
	String get_cpu_caps(String spacer) {return m_Array.get_cpu_caps(spacer);}

protected:
	static void _bind_methods();
	
private:
	Simd_4f32 m_Array;
};
