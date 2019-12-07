#pragma once

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

	void sqrt()
	{
		for (int i=0; i<4; i++)
			v[i] = ::sqrt(v[i]);
	}

	void inv_sqrt()
	{
		for (int i=0; i<4; i++)
			v[i] = 1.0f / ::sqrt(v[i]);
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
