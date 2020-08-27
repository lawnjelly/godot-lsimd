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

#include "fastarray_4i32.h"

using namespace GSimd;

Ref<Vec4_i32> FastArray_4i32::read(int i) const
{
	i32_4 val = m_Array.read(i);
	Ref<Vec4_i32> res(memnew(Vec4_i32(val)));
	return res;
}


void FastArray_4i32::write(int i, const Ref<Vec4_i32> &val)
{
	m_Array.write(i, val.ptr()->d);
}



void FastArray_4i32::_bind_methods()
{
	ClassDB::bind_method(D_METHOD("reserve", "size"), &FastArray_4i32::reserve);
	ClassDB::bind_method(D_METHOD("resize", "size"), &FastArray_4i32::resize);
	ClassDB::bind_method(D_METHOD("fill", "value"), &FastArray_4i32::fill);
	ClassDB::bind_method(D_METHOD("zero"), &FastArray_4i32::zero);
	ClassDB::bind_method(D_METHOD("size"), &FastArray_4i32::size);

	ClassDB::bind_method(D_METHOD("read", "element"), &FastArray_4i32::read);
	ClassDB::bind_method(D_METHOD("write", "element", "Vec4_i32"), &FastArray_4i32::write);


	ClassDB::bind_method(D_METHOD("value_add", "value", "from", "num"), &FastArray_4i32::value_add);
	ClassDB::bind_method(D_METHOD("value_subtract", "value", "from", "num"), &FastArray_4i32::value_subtract);
	ClassDB::bind_method(D_METHOD("value_multiply", "value", "from", "num"), &FastArray_4i32::value_multiply);
	ClassDB::bind_method(D_METHOD("value_divide", "value", "from", "num"), &FastArray_4i32::value_divide);

	ClassDB::bind_method(D_METHOD("add", "array2", "from", "from2", "num"), &FastArray_4i32::add);
	ClassDB::bind_method(D_METHOD("subtract", "array2", "from", "from2", "num"), &FastArray_4i32::subtract);
	ClassDB::bind_method(D_METHOD("multiply", "array2", "from", "from2", "num"), &FastArray_4i32::multiply);
	ClassDB::bind_method(D_METHOD("divide", "array2", "from", "from2", "num"), &FastArray_4i32::divide);


	ClassDB::bind_method(D_METHOD("vec3_length", "from", "num"), &FastArray_4i32::vec3_length);

}

