#pragma once

// just a light wrapper around a vector until we get the Godot vector allocation issues sorted
#include "core/vector.h"
#include <assert.h>
#include <vector>

namespace GSimd
{

template <class T> class SVector
{
public:

	// array subscript access
	// note this is not available in Godot Vector
	T& operator[](unsigned int ui)
	{
		assert (ui < m_iSize);
		return m_Vec[ui];
	}

	const T& operator[](unsigned int ui) const
	{
		assert (ui < (unsigned int) m_iSize);
		return m_Vec[ui];
	}

	void clear(bool bCompact = false)
	{
		m_iSize = 0;
		if (bCompact)
			compact();
	}

	void compact()
	{
		m_Vec.resize(m_iSize);
	}

	void reserve(int s)
	{
		m_Vec.resize(s);
	}

	void resize(int s, bool bCompact = false)
	{
		// new size
		m_iSize = s;

		// if compacting is not desired, no need to shrink vector
		if (m_iSize < m_Vec.size())
		{
			if (!bCompact)
			{
				return;
			}
		}

		m_Vec.resize(s);
	}

	void set(unsigned int ui, const T &t)
	{
		assert (ui < (unsigned int) m_iSize);
		m_Vec[ui] = t;
	}

	// efficient unsorted
	void remove_unsorted(unsigned int ui)
	{
		// just swap the end element and decrement count
		m_Vec[ui] = m_Vec[m_iSize-1];
		m_iSize--;
	}

	T * request()
	{
		m_iSize++;
		if (m_iSize >= m_Vec.size())
			grow();

		return &m_Vec[m_iSize-1];
	}

	void grow()
	{
		int new_size = m_Vec.size() * 2;
		if (!new_size) new_size = 1;

		reserve(new_size);
	}

	void push_back(const T &t)
	{
		int size_p1 = m_iSize+1;

		if (size_p1 < m_Vec.size())
		{
			int size = m_iSize;
			m_iSize = size_p1;
			set(size,  t);
		}
		else
		{
			// need more space
			grow();

			// call recursive
			push_back(t);
		}
	}

	void copy_from(const SVector<T> &o)
	{
		// make sure enough space
		if (o.size() > m_Vec.size())
		{
			reserve(o.size());
		}

		clear();
		m_iSize = o.size();

		for (int n=0; n<o.size(); n++)
		{
			set(n, o[n]);
		}
	}

	void copy_from(const Vector<T> &o)
	{
		// make sure enough space
		if (o.size() > m_Vec.size())
		{
			reserve(o.size());
		}

		clear();
		m_iSize = o.size();

		for (int n=0; n<o.size(); n++)
		{
			set(n, o[n]);
		}
	}

	void insert(int i, const T &val)
	{
		m_Vec.insert(m_Vec.begin() + i, val);
		m_iSize++;
	}

	int find(const T &val)
	{
		for (int n=0; n<size(); n++)
		{
			if (m_Vec[n] == val)
				return n;
		}

		return -1; // not found
	}

	SVector()
	{
		m_iSize = 0;
	}


	int size() const {return m_iSize;}

private:
	std::vector<T> m_Vec;

	// working size
	int m_iSize;
};


}
