#ifndef __TriangleMesh_h
#define __TriangleMesh_h

//[]------------------------------------------------------------------------[]
//|                                                                          |
//|                          GVSG Graphics Classes                           |
//|                               Version 1.0                                |
//|                                                                          |
//|              CopyrightŪ 2010-2014, Paulo Aristarco Pagliosa              |
//|              All Rights Reserved.                                        |
//|                                                                          |
//[]------------------------------------------------------------------------[]
//
//  OVERVIEW: TriangleMesh.h
//  ========
//  Class definition for simple triangle mesh.

#include "Geometry/Bounds3.h"
#include "Graphics/Color.h"
#include "Object.h"

using namespace Ds;
using namespace Geometry;

namespace Graphics
{ // begin namespace Graphics

using namespace System;

//
// Auxiliary functions
//
__host__ __device__ inline vec3
triangleNormal(const vec3& v0, const vec3& v1, const vec3& v2)
{
  return ((v1 - v0).cross(v2 - v0)).versor();
}

__host__ __device__ inline vec3
triangleNormal(vec3* v)
{
  return triangleNormal(v[0], v[1], v[2]);
}

__host__ __device__ inline vec3
triangleNormal(vec3* v, int i, int j, int k)
{
  return triangleNormal(v[i], v[j], v[k]);
}

__host__ __device__ inline vec3
triangleNormal(vec3* v, int i[3])
{
  return triangleNormal(v[i[0]], v[i[1]], v[i[2]]);
}

__host__ __device__ inline vec3
triangleCenter(const vec3& v0, const vec3& v1, const vec3& v2)
{
  return (v0 + v1 + v2) * Math::inverse<REAL>(3);
}

__host__ __device__ inline vec3
triangleCenter(vec3* v)
{
  return triangleCenter(v[0], v[1], v[2]);
}

__host__ __device__ inline vec3
triangleCenter(vec3* v, int i, int j, int k)
{
  return triangleCenter(v[i], v[j], v[k]);
}

__host__ __device__ inline vec3
triangleCenter(vec3* v, int i[3])
{
  return triangleCenter(v[i[0]], v[i[1]], v[i[2]]);
}


//////////////////////////////////////////////////////////
//
// Triangle: simple triangle mesh class
// ========
struct Triangle
{
  vec3 v0, v1, v2;
  vec3 N;

  // Constructors
  __host__ __device__
  Triangle()
  {
    // do nothing
  }

  __host__ __device__
  Triangle(const vec3& p0, const vec3& p1, const vec3& p2)
  {
    v0 = p0;
    v1 = p1;
    v2 = p2;
    computeNormal();
  }

  __host__ __device__
  Triangle(vec3* p)
  {
    v0 = p[0];
    v1 = p[1];
    v2 = p[2];
    computeNormal();
  }

  __host__ __device__
  Triangle(vec3* p, int i[3])
  {
    v0 = p[i[0]];
    v1 = p[i[1]];
    v2 = p[i[2]];
    computeNormal();
  }

  __host__ __device__
  vec3 center() const
  {
    return triangleCenter(v0, v1, v2);
  }

  template <typename T>
  __host__ __device__
  static T interpolate(const vec3& p, const T& v0, const T& v1, const T& v2)
  {
    return v0 * p.x + v1 * p.y + v2 * p.z;
  }

  template <typename T>
  __host__ __device__
  static T interpolate(const vec3& p, T v[3])
  {
    return interpolate<T>(p, v[0], v[1], v[2]);
  }

private:
  __host__ __device__
  void computeNormal()
  {
    N = triangleNormal(v0, v1, v2);
  }

}; // Triangle


//////////////////////////////////////////////////////////
//
// TriangleMesh: simple triangle mesh class
// ============
class TriangleMesh: public Object
{
public:
  struct Triangle
  {
    int v[3];

    void setVertices(int v0, int v1, int v2)
    {
      v[0] = v0;
      v[1] = v1;
      v[2] = v2;
    }

  }; // Triangle

  struct Data
  {
    vec3* vertices;
    vec3* normals;
    Triangle* triangles;
    Color* colors;

    __host__ __device__
    vec3 normalAt(Triangle* t, const vec3& p) const
    {
      if (normals == 0)
        return triangleNormal(vertices, t->v);

      vec3 N0 = normals[t->v[0]];
      vec3 N1 = normals[t->v[1]];
      vec3 N2 = normals[t->v[2]];

      return Graphics::Triangle::interpolate<vec3>(p, N0, N1, N2);
    }

  }; // Data

  struct Arrays: public Data
  {
    int numberOfVertices;
    int numberOfNormals;
    int numberOfTriangles;
    int numberOfColors;

    // Constructor
    Arrays():
      numberOfVertices(0),
      numberOfNormals(0),
      numberOfTriangles(0),
      numberOfColors(0)
    {
      vertices = 0;
      normals = 0;
      triangles = 0;
      colors = 0;
    }

    Arrays copy() const;
    void print(FILE*) const;

  }; // Arrays

  ObjectPtr<Object> userData;

  // Constructor
  TriangleMesh(const Arrays& aData):
    data(aData)
  {
    // do nothing
  }

  // Destructor
  ~TriangleMesh()
  {
    delete data.vertices;
    delete data.normals;
    delete data.triangles;
    delete data.colors;
  }

  Object* clone() const;
  Bounds3 boundingBox() const;

  void computeNormals();

  void setColors(Color* colors, int n)
  {
    delete data.colors;
    data.colors = colors;
    data.numberOfColors = n;
  }

  const Arrays& getData() const
  {
    return data;
  }

protected:
  Arrays data;

}; // TriangleMesh

} // end namespace Graphics

#endif // __TriangleMesh_h
