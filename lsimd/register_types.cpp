/* register_types.cpp */

#include "register_types.h"

#include "core/class_db.h"
#include "fastarray_4f32.h"
#include "fastarray_2f32.h"
#include "fastarray_4i32.h"
#include "vec4_i32.h"


void register_lsimd_types() {
	ClassDB::register_class<FastArray_4f32>();
	ClassDB::register_class<FastArray_2f32>();
	ClassDB::register_class<FastArray_4i32>();
	ClassDB::register_class<Vec4_i32>();
}

void unregister_lsimd_types() {
	//nothing to do here
}
