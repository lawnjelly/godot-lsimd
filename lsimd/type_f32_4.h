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

namespace GSimd
{

struct f32_4
{
	float32_t v[4];

	void add(const f32_4 &o)
	{
		for (int i=0; i<4; i++)
			v[i] += o.v[i];
	}

	void subtract(const f32_4 &o)
	{
		for (int i=0; i<4; i++)
			v[i] -= o.v[i];
	}

	void multiply(const f32_4 &o)
	{
		for (int i=0; i<4; i++)
			v[i] *= o.v[i];
	}

	void divide(const f32_4 &o)
	{
		for (int i=0; i<4; i++)
			v[i] /= o.v[i];
	}

	void vec3_inv_xform(const f32_transform &tr)
	{
		f32_4 o;
		o.v[0] = v[0] - tr.origin[0];
		o.v[1] = v[1] - tr.origin[1];
		o.v[2] = v[2] - tr.origin[2];

		f32_4 t;
		t.v[0] = (tr.basis[0] * o.v[0]) + (tr.basis[1] * o.v[1]) + (tr.basis[2] * o.v[2]);
		t.v[1] = (tr.basis[4] * o.v[0]) + (tr.basis[5] * o.v[1]) + (tr.basis[6] * o.v[2]);
		t.v[2] = (tr.basis[8] * o.v[0]) + (tr.basis[9] * o.v[1]) + (tr.basis[10] * o.v[2]);
		t.v[3] = 0.0f;

		*this = t;
	}

	void vec3_xform(const f32_transform &tr)
	{
		f32_4 t;
		t.v[0] = (tr.basis[0] * v[0]) + (tr.basis[1] * v[1]) + (tr.basis[2] * v[2]) + tr.origin[0];
		t.v[1] = (tr.basis[4] * v[0]) + (tr.basis[5] * v[1]) + (tr.basis[6] * v[2]) + tr.origin[1];
		t.v[2] = (tr.basis[8] * v[0]) + (tr.basis[9] * v[1]) + (tr.basis[10] * v[2]) + tr.origin[2];
		t.v[3] = 0.0f;

		*this = t;
	}

	void vec2_dot(const f32_4 &o, float * pfRes)
	{
		pfRes[0] = (v[0] * o.v[0]) + (v[1] * o.v[1]);
		pfRes[1] = (v[2] * o.v[2]) + (v[3] * o.v[3]);
	}

	void vec2_cross(const f32_4 &o, float * pfRes)
	{
		pfRes[0] = (v[0] * o.v[1]) - (v[1] * o.v[0]);
		pfRes[1] = (v[2] * o.v[3]) - (v[3] * o.v[2]);
	}

	void vec2_length_squared(float * pfRes)
	{
		pfRes[0] = (v[0] * v[0]) + (v[1] * v[1]);
		pfRes[1] = (v[2] * v[2]) + (v[3] * v[3]);
	}

	void vec2_length(float * pfRes)
	{
		vec2_length_squared(pfRes);
		pfRes[0] = Math::sqrt(pfRes[0]);
		pfRes[1] = Math::sqrt(pfRes[1]);
	}

	void vec2_normalize()
	{
		float sl[2];
		vec2_length_squared(sl);

		for (int n=0; n<2; n++)
		{
			int base = n * 2;

			if (sl[n] == 0.0f)
			{
				v[base] = 0.0f; v[base+1] = 0.0f;
			}
			else
			{
				float l = Math::sqrt(sl[n]);

				v[base] /= l;
				v[base+1] /= l;
			}
		}
	}

	void vec3_dot(const f32_4 &o)
	{
		v[3] = (v[0] * o.v[0]) + (v[1] * o.v[1]) + (v[2] * o.v[2]);
	}

	void vec3_cross(const f32_4 &o)
	{
		f32_4 t;
		t.v[0] = (v[1] * o.v[2]);
		t.v[1] = (v[2] * o.v[0]);
		t.v[2] = (v[0] * o.v[1]);

		t.v[0] -= (v[2] * o.v[1]);
		t.v[1] -= (v[0] * o.v[2]);
		t.v[2] -= (v[1] * o.v[0]);

		t.v[3] = 0.0f;
		*this = t;
	}

	void vec3_normalize()
	{
		float l_squared = (v[0] * v[0]) + (v[1] * v[1]) + (v[2] * v[2]);
		if (l_squared == 0.0f)
		{
			v[0] = v[1] = v[2] = v[3] = 0.0f;
		}
		else
		{
			float l = Math::sqrt(l_squared);

			v[0] /= l;
			v[1] /= l;
			v[2] /= l;

			// store the length in the free tuple, it can be useful
			v[3] = l;
		}
	}

	void vec3_length_squared()
	{
		v[3] = (v[0] * v[0]) + (v[1] * v[1]) + (v[2] * v[2]);
	}

	void vec3_length()
	{
		float sl = (v[0] * v[0]) + (v[1] * v[1]) + (v[2] * v[2]);
		v[3] = Math::sqrt(sl);
	}

	void sqrt()
	{
		for (int i=0; i<4; i++)
			v[i] = Math::sqrt(v[i]);
	}

	void inv_sqrt()
	{
		for (int i=0; i<4; i++)
			v[i] = 1.0f / Math::sqrt(v[i]);
	}

	void reciprocal()
	{
		for (int i=0; i<4; i++)
			v[i] = 1.0f / v[i];
	}

	void from_vector3(const Vector3 &o)
	{
		v[0] = o.x; v[1] = o.y; v[2] = o.z; v[3] = 0.0;
	}

	void to_vector3(Vector3 &o) const
	{
		o.x = v[0]; o.y = v[1]; o.z = v[2];
	}

	void from_quat(const Quat &q)
	{
		v[0] = q.x;
		v[1] = q.y;
		v[2] = q.z;
		v[3] = q.w;
	}

	void to_quat(Quat &q) const
	{
		q.x = v[0];
		q.y = v[1];
		q.z = v[2];
		q.w = v[3];
	}
};




} // namespace
