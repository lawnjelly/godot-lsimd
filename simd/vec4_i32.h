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

	Vector3 get_vec3() const {return Vector3(d.x, d.y, d.z);}
	void set_vec3_round(const Vector3 &pt) {d.x = Math::round(pt.x); d.y = Math::round(pt.y); d.z = Math::round(pt.z); d.w = 0;}


	static Vec4_i32 * safe_cast(Object * pObj);
	static const Vec4_i32 * safe_cast(const Object * pObj);

protected:
	static void _bind_methods();
};
