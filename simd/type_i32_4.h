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

#include <cstdint>
#include "core/math/math_funcs.h"

namespace GSimd
{
	struct i32_4
	{
		union {
			struct {int32_t x, y, z, w;};
			int32_t v[4];
		};

		void add(const i32_4 &o)
		{
			for (int n=0; n<4; n++)
				v[n] += o.v[n];
		}

		void subtract(const i32_4 &o)
		{
			for (int n=0; n<4; n++)
				v[n] -= o.v[n];
		}

		void multiply(const i32_4 &o)
		{
			for (int n=0; n<4; n++)
				v[n] *= o.v[n];
		}

		void divide(const i32_4 &o)
		{
			for (int n=0; n<4; n++)
				v[n] /= o.v[n];
		}

		uint64_t vec3_length_squared() const
		{
			return ((int64_t) v[0] * v[0]) + ((int64_t) v[1] * v[1]) + ((int64_t) v[2] * v[2]);
		}

		// calculate length, store result in w
		void vec3_length()
		{
			uint64_t sl = vec3_length_squared();
			v[3] = (0.5 + Math::sqrt((double) sl)); // include some rounding
		}

		int64_t vec3_dot(const i32_4 &o) const
		{
			int64_t r = 0;
			for (int n=0; n<3; n++)
				r += v[n] * o.v[n];
			return r;
		}

		int64_t dot(const i32_4 &o) const
		{
			int64_t r = 0;
			for (int n=0; n<4; n++)
				r += v[n] * o.v[n];
			return r;
		}

		void vec3_cross(const i32_4 &o)
		{
			i32_4 r;
			r.x = (y * o.z) - (z * o.y);
			r.y = (z * o.x) - (x * o.z);
			r.z = (x * o.y) - (y * o.x);
			r.w = 0;
			*this = r;
		}

	};
	
} // namspace
