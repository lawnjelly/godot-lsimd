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

#include "vec4_i32.h"

Vec4_i32::Vec4_i32()
{
	print_line ("Vec4_i32 create");
}

Vec4_i32::~Vec4_i32()
{
	print_line ("Vec4_i32 destroy");
}

Vec4_i32::Vec4_i32(GSimd::i32_4 val)
{
	print_line ("Vec4_i32 create");
	d = val;
}

Vec4_i32 * Vec4_i32::safe_cast(Object * pObj)
{
	if (pObj->get_class_ptr_static() == 	get_class_ptr_static())
		return (Vec4_i32 *) pObj;
	return 0;
}

const Vec4_i32 * Vec4_i32::safe_cast(const Object * pObj)
{
	if (pObj->get_class_ptr_static() == 	get_class_ptr_static())
		return (const Vec4_i32 *) pObj;
	return 0;
}


void Vec4_i32::_bind_methods()
{
	ClassDB::bind_method(D_METHOD("x"), &Vec4_i32::x);
	ClassDB::bind_method(D_METHOD("y"), &Vec4_i32::y);
	ClassDB::bind_method(D_METHOD("z"), &Vec4_i32::z);
	ClassDB::bind_method(D_METHOD("w"), &Vec4_i32::w);
	ClassDB::bind_method(D_METHOD("get_tuple", "tuple"), &Vec4_i32::get_tuple);

	ClassDB::bind_method(D_METHOD("set_x", "value"), &Vec4_i32::set_x);
	ClassDB::bind_method(D_METHOD("set_y", "value"), &Vec4_i32::set_y);
	ClassDB::bind_method(D_METHOD("set_z", "value"), &Vec4_i32::set_z);
	ClassDB::bind_method(D_METHOD("set_w", "value"), &Vec4_i32::set_w);

	ClassDB::bind_method(D_METHOD("set_xyz", "x", "y", "z"), &Vec4_i32::set_xyz);
	ClassDB::bind_method(D_METHOD("set_xyzw", "x", "y", "z", "w"), &Vec4_i32::set_xyzw);
	ClassDB::bind_method(D_METHOD("set_tuple", "tuple", "value"), &Vec4_i32::set_tuple);

	ClassDB::bind_method(D_METHOD("copy_from", "value"), &Vec4_i32::copy_from);

	ClassDB::bind_method(D_METHOD("get_vec3"), &Vec4_i32::get_vec3);
	ClassDB::bind_method(D_METHOD("set_vec3_round", "xyz"), &Vec4_i32::set_vec3_round);

	ClassDB::bind_method(D_METHOD("equals", "value"), &Vec4_i32::equals);
	ClassDB::bind_method(D_METHOD("vec3_equals", "value"), &Vec4_i32::vec3_equals);

	ClassDB::bind_method(D_METHOD("add", "value"), &Vec4_i32::add);
	ClassDB::bind_method(D_METHOD("subtract", "value"), &Vec4_i32::subtract);
	ClassDB::bind_method(D_METHOD("multiply", "value"), &Vec4_i32::multiply);
	ClassDB::bind_method(D_METHOD("divide", "value"), &Vec4_i32::divide);

	ClassDB::bind_method(D_METHOD("dot", "value"), &Vec4_i32::dot);
	ClassDB::bind_method(D_METHOD("vec3_dot", "value"), &Vec4_i32::vec3_dot);
	ClassDB::bind_method(D_METHOD("vec3_cross", "value"), &Vec4_i32::vec3_cross);

	ClassDB::bind_method(D_METHOD("vec3_length_squared"), &Vec4_i32::vec3_length_squared);
	ClassDB::bind_method(D_METHOD("vec3_length"), &Vec4_i32::vec3_length);

	ClassDB::bind_method(D_METHOD("vec3_normalize_to_scale", "scale"), &Vec4_i32::vec3_normalize_to_scale);

}
