#pragma once

#include "simd_types.h"
#include "simd_vector.h"
#include "core/reference.h"
#include "core/math/vector3.h"
#include "core/pool_vector.h"

//#include "scene/3d/spatial.h"
//#include "scene/resources/mesh.h"


class FastArray_4f32: public Reference
{
    GDCLASS(FastArray_4f32, Reference);
public:
	FastArray_4f32();

	// sizing
	void reserve(int size)
	{
		m_Vec.resize(size);
		zero();
	}

	void resize(int size)
	{
		m_Vec.resize(size);
	}

	void copy(Object * pArr2);

	void copyfrom_poolvector3array(const PoolVector<Vector3> &arr);
	PoolVector<Vector3> get_poolvector3array() const;

	// element access
	Quat read(int i) const
	{
		Quat q;
		m_Vec[i].to_quat(q);
		return q;
	}

	void set(int i, const Quat &q)
	{
		m_Vec[i].from_quat(q);
	}

	void fill(const Quat &val);
	void zero();

	int size() const {return m_Vec.size();}

	// SIMD
	void add(const Quat &val, int from, int to);
	void subtract(const Quat &val, int from, int to);
	void multiply(const Quat &val, int from, int to);
	void divide(const Quat &val, int from, int to);

	void add_array(Object * pArr2, int from, int to);
	void subtract_array(Object * pArr2, int from, int to);
	void multiply_array(Object * pArr2, int from, int to);
	void divide_array(Object * pArr2, int from, int to);

	void sqrt(int from, int to);
	void inv_sqrt(int from, int to);
	void reciprocal(int from, int to);

protected:
	static void _bind_methods();
	
private:
	bool check_range(int from, int to) const;

	GSimd::SVector<GSimd::f32_4> m_Vec;

//	PoolVector<Vector3> test;

};
