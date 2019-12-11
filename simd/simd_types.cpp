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

#include "simd_types.h"

namespace GSimd
{

void f32_transform::from_transform_inv(const Transform &tr)
{
	basis[0] = tr.basis.elements[0][0];
	basis[1] = tr.basis.elements[1][0];
	basis[2] = tr.basis.elements[2][0];
	basis[3] = 0.0f; // pad
	basis[4] = tr.basis.elements[0][1];
	basis[5] = tr.basis.elements[1][1];
	basis[6] = tr.basis.elements[2][1];
	basis[7] = 0.0f; // pad
	basis[8] = tr.basis.elements[0][2];
	basis[9] = tr.basis.elements[1][2];
	basis[10] = tr.basis.elements[2][2];
	basis[11] = 0.0f; // pad

	origin[0] = tr.origin.x;
	origin[1] = tr.origin.y;
	origin[2] = tr.origin.z;
	origin[3] = 0.0f; // pad
}


void f32_transform::from_transform(const Transform &tr)
{
	basis[0] = tr.basis[0].x;
	basis[1] = tr.basis[0].y;
	basis[2] = tr.basis[0].z;
	basis[3] = 0.0f; // pad
	basis[4] = tr.basis[1].x;
	basis[5] = tr.basis[1].y;
	basis[6] = tr.basis[1].z;
	basis[7] = 0.0f; // pad
	basis[8] = tr.basis[2].x;
	basis[9] = tr.basis[2].y;
	basis[10] = tr.basis[2].z;
	basis[11] = 0.0f; // pad

	origin[0] = tr.origin.x;
	origin[1] = tr.origin.y;
	origin[2] = tr.origin.z;
	origin[3] = 0.0f; // pad
}



}  // namespace
