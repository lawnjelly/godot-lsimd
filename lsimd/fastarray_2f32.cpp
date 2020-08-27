#include "fastarray_2f32.h"

using namespace GSimd;

#define IMPL_PREPARE {\
if (!num) return;\
int q_from, num_quads;\
unsigned int flags = _find_quad_range(from , num, q_from, num_quads);\
int q_last = q_from + num_quads - 1;\
f32_4 temp_before = m_Array.m_Vec[q_from];\
f32_4 temp_after = m_Array.m_Vec[q_last];


#define IMPL_RESTORE if (flags & RF_BEFORE)\
{\
f32_4 &u = m_Array.m_Vec[q_from];\
u.v[0] = temp_before.v[0];\
u.v[1] = temp_before.v[1];\
}\
if (flags & RF_AFTER)\
{\
f32_4 &u = m_Array.m_Vec[q_last];\
u.v[2] = temp_after.v[2];\
u.v[3] = temp_after.v[3];\
}\
}


#define IMPL_VALUE(A) void FastArray_2f32::A(const Vector2 &val, int from, int num)\
IMPL_PREPARE \
m_Array.A(Quat(val.x, val.y, val.x, val.y), q_from, num_quads);\
IMPL_RESTORE

#define IMPL_SIMPLE(A, B) void FastArray_2f32::A(int from, int num)\
IMPL_PREPARE \
m_Array.B(q_from, num_quads);\
IMPL_RESTORE


IMPL_VALUE(value_add);
IMPL_VALUE(value_subtract);
IMPL_VALUE(value_multiply);
IMPL_VALUE(value_divide);

IMPL_SIMPLE(sqrt, sqrt);
IMPL_SIMPLE(inv_sqrt, inv_sqrt);
IMPL_SIMPLE(reciprocal, reciprocal);
IMPL_SIMPLE(normalize, vec2_normalize);

#define IMPL_DUAL(A) void FastArray_2f32::A(const Ref<FastArray_2f32> &arr2, int from, int from2, int num)\
IMPL_PREPARE \
int q_from2;\
unsigned int flags2 = arr2->_find_quad_range(from2, num, q_from2, num_quads);\
/* they must be in sync or else */ \
if (flags != flags2)\
{\
WARN_PRINT_ONCE("FastArray_2f32 from and from2 must be both odd, or both even");\
return;\
}\
m_Array.A(arr2->m_Array, q_from, q_from2, num_quads);\
IMPL_RESTORE


IMPL_DUAL(add);
IMPL_DUAL(subtract);
IMPL_DUAL(multiply);
IMPL_DUAL(divide);


#define IMPL_RESULT(A, B) void FastArray_2f32::A(const Ref<FastArray_2f32> &arr2, int from, int from2, int num) \
{\
if (!num) return;\
int q_from, q_from2, num_quads;\
unsigned int flags = _find_quad_range(from , num, q_from, num_quads);\
unsigned int flags2 = arr2->_find_quad_range(from2, num, q_from2, num_quads);\
/* they must be in sync or else */ \
if (flags != flags2)\
{\
WARN_PRINT_ONCE("FastArray_2f32 from and from2 must be both odd, or both even");\
return;\
}\
float fTempBefore = 0.0f; float fTempAfter = 0.0f;\
int res_before = from-1;\
int res_after = from + num;\
if (flags & RF_BEFORE) {fTempBefore = m_Result[res_before];}\
if (flags & RF_AFTER) {fTempAfter = m_Result[res_after];}\
\
m_Array.B(arr2->m_Array, q_from, q_from2, num_quads, &m_Result[q_from * 2]);\
\
if (flags & RF_BEFORE)\
{m_Result[res_before] = fTempBefore;}\
if (flags & RF_AFTER)\
{m_Result[res_after] = fTempAfter;}\
}

IMPL_RESULT(dot, vec2_dot);
IMPL_RESULT(cross, vec2_cross);


#define IMPL_SIMPLE_RESULT(A, B) void FastArray_2f32::A(int from, int num) \
{\
if (!num) return;\
int q_from, num_quads;\
unsigned int flags = _find_quad_range(from , num, q_from, num_quads);\
/* they must be in sync or else */ \
float fTempBefore = 0.0f; float fTempAfter = 0.0f;\
int res_before = from-1;\
int res_after = from + num;\
if (flags & RF_BEFORE) {fTempBefore = m_Result[res_before];}\
if (flags & RF_AFTER) {fTempAfter = m_Result[res_after];}\
\
m_Array.B(q_from, num_quads, &m_Result[q_from * 2]);\
\
if (flags & RF_BEFORE)\
{m_Result[res_before] = fTempBefore;}\
if (flags & RF_AFTER)\
{m_Result[res_after] = fTempAfter;}\
}


IMPL_SIMPLE_RESULT(length, vec2_length);
IMPL_SIMPLE_RESULT(length_squared, vec2_length_squared);


FastArray_2f32::FastArray_2f32()
{
	m_iSize = 0;
}

// returns flags
unsigned int FastArray_2f32::_find_quad_range(int from, int num, int &q_from, int &num_quads) const
{
	// special case no elements, don't set any flags
	if (!num)
	{
		q_from = 0;
		num_quads = 0;
		return 0;
	}

	unsigned int flags = 0;

	q_from = from / 2;
	if (from % 2)
	{
		// only if there is an element
		flags |= RF_BEFORE;
		//q_from++;
	}

	int to = from + num;
	int q_to = to / 2;
	if (to % 2)
	{
		q_to++;
		flags |= RF_AFTER;
	}

	num_quads = q_to - q_from;

	return flags;
}


int FastArray_2f32::_calc_quad_size(int size) const
{
	int q = size / 2;
	if (size % 2)
		q++;

	return q;
}

void FastArray_2f32::fill(const Vector2 &v)
{
	m_Array.fill(Quat(v.x, v.y, v.x, v.y));
}

void FastArray_2f32::copy_from(const Ref<FastArray_2f32> &arr2)
{
	m_Array.copy_from(arr2->m_Array);
	m_iSize = arr2->m_iSize;
	m_Result.resize(arr2->m_Result.size());
	m_Result.zero();
}


float FastArray_2f32::read_result(int i) const
{
	return m_Result[i];
}

Vector2 FastArray_2f32::read(int i) const
{
	int iu = i / 2;
	int which = i % 2;

	const GSimd::f32_4 &u = m_Array.m_Vec[iu];
	if (!which)
		return Vector2(u.v[0], u.v[1]);

	return Vector2(u.v[2], u.v[3]);
}




void FastArray_2f32::write(int i, const Vector2 &v)
{
	int iu = i / 2;
	int which = i % 2;

	GSimd::f32_4 &u = m_Array.m_Vec[iu];
	if (!which)
	{
		u.v[0] = v.x; u.v[1] = v.y;
		return;
	}
	u.v[2] = v.x; u.v[3] = v.y;
}

void FastArray_2f32::_bind_methods()
{
	ClassDB::bind_method(D_METHOD("reserve", "size"), &FastArray_2f32::reserve);
	ClassDB::bind_method(D_METHOD("resize", "size"), &FastArray_2f32::resize);
	ClassDB::bind_method(D_METHOD("fill", "value"), &FastArray_2f32::fill);
	ClassDB::bind_method(D_METHOD("zero"), &FastArray_2f32::zero);

	ClassDB::bind_method(D_METHOD("copy_from", "array2"), &FastArray_2f32::copy_from);

	ClassDB::bind_method(D_METHOD("size"), &FastArray_2f32::size);
	ClassDB::bind_method(D_METHOD("read", "element"), &FastArray_2f32::read);
	ClassDB::bind_method(D_METHOD("write", "element", "value"), &FastArray_2f32::write);
	ClassDB::bind_method(D_METHOD("read_result", "element"), &FastArray_2f32::read_result);


	ClassDB::bind_method(D_METHOD("value_add", "value", "from", "num"), &FastArray_2f32::value_add);
	ClassDB::bind_method(D_METHOD("value_subtract", "value", "from", "num"), &FastArray_2f32::value_subtract);
	ClassDB::bind_method(D_METHOD("value_multiply", "value", "from", "num"), &FastArray_2f32::value_multiply);
	ClassDB::bind_method(D_METHOD("value_divide", "value", "from", "num"), &FastArray_2f32::value_divide);

	ClassDB::bind_method(D_METHOD("add", "array2", "from", "from2", "num"), &FastArray_2f32::add);
	ClassDB::bind_method(D_METHOD("subtract", "array2", "from", "from2", "num"), &FastArray_2f32::subtract);
	ClassDB::bind_method(D_METHOD("multiply", "array2", "from", "from2", "num"), &FastArray_2f32::multiply);
	ClassDB::bind_method(D_METHOD("divide", "array2", "from", "from2", "num"), &FastArray_2f32::divide);

	ClassDB::bind_method(D_METHOD("sqrt", "from", "num"), &FastArray_2f32::sqrt);
	ClassDB::bind_method(D_METHOD("sqrt_inv", "from", "num"), &FastArray_2f32::inv_sqrt);
	ClassDB::bind_method(D_METHOD("reciprocal", "from", "num"), &FastArray_2f32::reciprocal);

	ClassDB::bind_method(D_METHOD("dot", "array2", "from", "from2", "num"), &FastArray_2f32::dot);
	ClassDB::bind_method(D_METHOD("cross", "array2", "from", "from2", "num"), &FastArray_2f32::cross);
	ClassDB::bind_method(D_METHOD("length", "from", "num"), &FastArray_2f32::length);
	ClassDB::bind_method(D_METHOD("length_squared", "from", "num"), &FastArray_2f32::length_squared);
	ClassDB::bind_method(D_METHOD("normalize", "from", "num"), &FastArray_2f32::normalize);

}



#undef IMPL_VALUE
#undef IMPL_DUAL
#undef IMPL_SIMPLE
#undef IMPL_RESULT

#undef IMPL_PREPARE
#undef IMPL_RESTORE
