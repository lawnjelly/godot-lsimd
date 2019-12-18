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

namespace GSimd
{

class Simd_4f32_SSE
{
public:
	static void add(float * pfUnits, const float * pUnits2, int nUnits);
	static void subtract(float * pfUnits, const float * pUnits2, int nUnits);
	static void multiply(float * pfUnits, const float * pUnits2, int nUnits);
	static void divide(float * pfUnits, const float * pUnits2, int nUnits);

	static void value_add(float * pfUnits, const float * pfVal, int nUnits);
	static void value_subtract(float * pfUnits, const float * pfVal, int nUnits);
	static void value_multiply(float * pfUnits, const float * pfVal, int nUnits);
	static void value_divide(float * pfUnits, const float * pfVal, int nUnits);

	static void reciprocal(float * pfUnits, int nUnits);
	static void sqrt(float * pfUnits, int nUnits);
	static void inv_sqrt(float * pfUnits, int nUnits);
};

} // namespace
