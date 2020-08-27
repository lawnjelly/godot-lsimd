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
#include "core/math/transform.h"
#include "simd_cpu.h"

#ifndef float32_t
#define float32_t float
#endif


// Mostly we will rely on auto-vectorization.
// However some instructions (e.g. reciprocal sqrt) cannot be autovectorized
// Note that you seem to need -O3 for autovectorization, and x86_64 has minimum SSE2 support...
// for x86 you need to explicitly enable it in the compiler with -msse etc.


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





}
