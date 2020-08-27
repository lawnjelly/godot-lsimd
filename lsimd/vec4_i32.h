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
#include "core/reference.h"

class Vec4_i32 : public Reference
{
	GDCLASS(Vec4_i32, Reference);
public:
	Vec4_i32();
	Vec4_i32(GSimd::i32_4 val);
	~Vec4_i32();

	GSimd::i32_4 d;

	int x() const {return d.x;}
	int y() const {return d.y;}
	int z() const {return d.z;}
	int w() const {return d.w;}
	int get_tuple(int t) const {return d.v[t];}

	void set_x(int x) {d.x = x;}
	void set_y(int y) {d.y = y;}
	void set_z(int z) {d.z = z;}
	void set_w(int w) {d.w = w;}

	void set_xyz(int x, int y, int z) {d.x = x; d.y = y; d.z = z; d.w = 0;}
	void set_xyzw(int x, int y, int z, int w) {d.x = x; d.y = y; d.z = z; d.w = w;}
	void set_tuple(int n, int val) {d.v[n] = val;}

	void copy_from(const Ref<Vec4_i32> &val) {for (int n=0; n<4; n++) {d.v[n] = val->d.v[n];}}

	Vector3 get_vec3() const {return Vector3(d.x, d.y, d.z);}
	void set_vec3_round(const Vector3 &pt) {d.x = Math::round(pt.x); d.y = Math::round(pt.y); d.z = Math::round(pt.z); d.w = 0;}

	bool vec3_equals(const Ref<Vec4_i32> &val) const {return (d.x == val->d.x) && (d.y == val->d.y) && (d.z == val->d.z);}
	bool equals(const Ref<Vec4_i32> &val) const {return (d.x == val->d.x) && (d.y == val->d.y) && (d.z == val->d.z) && (d.w == val->d.w);}

	// simple maths
	void add(const Ref<Vec4_i32> &val) {d.add(val->d);}
	void subtract(const Ref<Vec4_i32> &val) {d.add(val->d);}
	void multiply(const Ref<Vec4_i32> &val) {d.add(val->d);}
	void divide(const Ref<Vec4_i32> &val) {d.add(val->d);}


	uint64_t vec3_length_squared() const {return d.vec3_length_squared();}
	real_t vec3_length() const {return Math::sqrt((real_t) vec3_length_squared());}

	// returns length
	real_t vec3_normalize_to_scale(real_t scale)
	{
		uint64_t sl = vec3_length_squared();
		if (!sl)
			return 0.0;

		real_t l = Math::sqrt((real_t) sl);
		real_t mult = scale / l;
		d.x = Math::round(d.x * mult);
		d.y = Math::round(d.y * mult);
		d.z = Math::round(d.z * mult);

		return l;
	}


	int64_t vec3_dot(const Ref<Vec4_i32> &val) const {return d.vec3_dot(val->d);}
	int64_t dot(const Ref<Vec4_i32> &val) const {return d.dot(val->d);}
	void vec3_cross(const Ref<Vec4_i32> &val) {d.vec3_cross(val->d);}

	// casting
	static Vec4_i32 * safe_cast(Object * pObj);
	static const Vec4_i32 * safe_cast(const Object * pObj);

protected:
	static void _bind_methods();
};
