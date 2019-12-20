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


#include "fastarray_4f32.h"
#include "core/variant.h"
#include <string.h>

using namespace GSimd;

#define FA_IMPL_DUAL(A) void FastArray_4f32::A(const Ref<FastArray_4f32> &arr2, int from, int from2, int num)\
{\
	m_Array.A(arr2->m_Array, from, from2, num);\
}

/*
FastArray_4f32 * p2 = Object::cast_to<FastArray_4f32>(pArr2);\
if (!p2)\
return;\
m_Array.A(p2->m_Array, from, from2, num);\
}
*/

FA_IMPL_DUAL(add);
FA_IMPL_DUAL(subtract);
FA_IMPL_DUAL(multiply);
FA_IMPL_DUAL(divide);

FA_IMPL_DUAL(vec3_dot);
FA_IMPL_DUAL(vec3_cross);
FA_IMPL_DUAL(vec3_unit_cross);


void FastArray_4f32::copy_from(const Ref<FastArray_4f32> &arr2)
{
	m_Array.copy_from(arr2->m_Array);
}

void FastArray_4f32::_bind_methods()
{
	ClassDB::bind_method(D_METHOD("reserve", "size"), &FastArray_4f32::reserve);
	ClassDB::bind_method(D_METHOD("resize", "size"), &FastArray_4f32::resize);
	ClassDB::bind_method(D_METHOD("fill", "value"), &FastArray_4f32::fill);
	ClassDB::bind_method(D_METHOD("zero"), &FastArray_4f32::zero);


	ClassDB::bind_method(D_METHOD("copy_from", "array2"), &FastArray_4f32::copy_from);
	ClassDB::bind_method(D_METHOD("copy_from_poolvector3array", "array"), &FastArray_4f32::copy_from_poolvector3array);
	ClassDB::bind_method(D_METHOD("get_poolvector3array"), &FastArray_4f32::get_poolvector3array);
	ClassDB::bind_method(D_METHOD("get_poolrealarray_result"), &FastArray_4f32::get_poolrealarray_result);

	ClassDB::bind_method(D_METHOD("size"), &FastArray_4f32::size);
	ClassDB::bind_method(D_METHOD("read", "element"), &FastArray_4f32::read);
	ClassDB::bind_method(D_METHOD("write", "element", "value"), &FastArray_4f32::write);
	ClassDB::bind_method(D_METHOD("vec3_read", "element"), &FastArray_4f32::vec3_read);
	ClassDB::bind_method(D_METHOD("vec3_write", "element", "value"), &FastArray_4f32::vec3_write);

	ClassDB::bind_method(D_METHOD("add", "array2", "from", "from2", "num"), &FastArray_4f32::add);
	ClassDB::bind_method(D_METHOD("subtract", "array2", "from", "from2", "num"), &FastArray_4f32::subtract);
	ClassDB::bind_method(D_METHOD("multiply", "array2", "from", "from2", "num"), &FastArray_4f32::multiply);
	ClassDB::bind_method(D_METHOD("divide", "array2", "from", "from2", "num"), &FastArray_4f32::divide);

	ClassDB::bind_method(D_METHOD("vec3_dot", "array2", "from", "from2", "num"), &FastArray_4f32::vec3_dot);
	ClassDB::bind_method(D_METHOD("vec3_cross", "array2", "from", "from2", "num"), &FastArray_4f32::vec3_cross);
	ClassDB::bind_method(D_METHOD("vec3_unit_cross", "array2", "from", "from2", "num"), &FastArray_4f32::vec3_unit_cross);
	ClassDB::bind_method(D_METHOD("vec3_length", "from", "num"), &FastArray_4f32::vec3_length);
	ClassDB::bind_method(D_METHOD("vec3_length_squared", "from", "num"), &FastArray_4f32::vec3_length_squared);
	ClassDB::bind_method(D_METHOD("vec3_normalize", "from", "num"), &FastArray_4f32::vec3_normalize);
	ClassDB::bind_method(D_METHOD("vec3_xform", "transform", "from", "num"), &FastArray_4f32::vec3_xform);
	ClassDB::bind_method(D_METHOD("vec3_xform_inv", "transform", "from", "num"), &FastArray_4f32::vec3_inv_xform);

	ClassDB::bind_method(D_METHOD("value_add", "value", "from", "num"), &FastArray_4f32::value_add);
	ClassDB::bind_method(D_METHOD("value_subtract", "value", "from", "num"), &FastArray_4f32::value_subtract);
	ClassDB::bind_method(D_METHOD("value_multiply", "value", "from", "num"), &FastArray_4f32::value_multiply);
	ClassDB::bind_method(D_METHOD("value_divide", "value", "from", "num"), &FastArray_4f32::value_divide);

	ClassDB::bind_method(D_METHOD("sqrt", "from", "num"), &FastArray_4f32::sqrt);
	ClassDB::bind_method(D_METHOD("sqrt_inv", "from", "num"), &FastArray_4f32::inv_sqrt);
	ClassDB::bind_method(D_METHOD("reciprocal", "from", "num"), &FastArray_4f32::reciprocal);

	ClassDB::bind_method(D_METHOD("get_cpu_name"), &FastArray_4f32::get_cpu_name);
	ClassDB::bind_method(D_METHOD("get_cpu_caps", "spacer"), &FastArray_4f32::get_cpu_caps);

	ClassDB::bind_method(D_METHOD("test", "from", "num"), &FastArray_4f32::test);
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

#undef FA_IMPL_DUAL
