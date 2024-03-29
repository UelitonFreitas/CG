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
//  OVERVIEW: TriangleMeshShape.cpp
//  ========
//  Source file for triangle mesh shape.

#include "TriangleMeshShape.h"

using namespace Graphics;


//////////////////////////////////////////////////////////
//
// TriangleMeshShape implementation
// =================
Object*
TriangleMeshShape::clone() const
//[]---------------------------------------------------[]
//|  Make copy                                          |
//[]---------------------------------------------------[]
{
  return new TriangleMeshShape((TriangleMesh*)mesh->clone());
}

const TriangleMesh*
TriangleMeshShape::triangleMesh() const
//[]---------------------------------------------------[]
//|  Triangle mesh                                      |
//[]---------------------------------------------------[]
{
  return mesh;
}

Bounds3
TriangleMeshShape::boundingBox() const
//[]---------------------------------------------------[]
//|  Bounding box                                       |
//[]---------------------------------------------------[]
{
  Bounds3 b = bounds;

  b.transform(this->matrix);
  return b;
}
