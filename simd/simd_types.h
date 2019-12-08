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


#include "core/math/quat.h"

#ifndef float32_t
#define float32_t float
#endif

// Mostly we will rely on auto-vectorization.
// However some instructions (e.g. reciprocal sqrt) cannot be autovectorized
// Note that you seem to need -O3 for autovectorization, and x86_64 has minimum SSE2 support...
// for x86 you need to explicitly enable it in the compiler with -msse etc.
#define GSIMD_NONE
#if defined(__x86_64) || defined(__x86_64__) || defined(__amd64__)
//#define GSIMD_SSE
#endif
#if (defined(__i386) || defined(__i386__))
//#define GSIMD_SSE
#endif
#if defined(__arm__)
//#define GSIMD_NEON
#endif

// TODO:
// Alignment

namespace GSimd
{

struct f32_transform
{
	float32_t basis[12];
	float32_t origin[4];

	void from_transform(const Transform &tr);

	// pre-prepare inversed transform for fast inv_xform (basis and origin is different, see Transform source)
	void from_transform_inv(const Transform &tr);
};


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



}
