/* register_types.cpp */

#include "register_types.h"

#include "core/class_db.h"
#include "simd_f32.h"


void register_simd_types() {

        ClassDB::register_class<FastArray_4f32>();
}

void unregister_simd_types() {
   //nothing to do here
}
