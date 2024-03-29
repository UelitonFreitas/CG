//[]------------------------------------------------------------------------[]
//|                                                                          |
//|                          GVSG Graphics Library                           |
//|                               Version 1.0                                |
//|                                                                          |
//|              CopyrightŪ 2007-2014, Paulo Aristarco Pagliosa              |
//|              All Rights Reserved.                                        |
//|                                                                          |
//[]------------------------------------------------------------------------[]
//
// OVERVIEW: Material.cpp
// ========
// Source file for material.

#ifndef __Material_h
#include "Material.h"
#endif

using namespace Graphics;


//////////////////////////////////////////////////////////
//
// Material implementation
// ========
Material::Material(const string& name, const Color& color):
  NameableObject(name)
//[]---------------------------------------------------[]
//|  Constructor                                        |
//[]---------------------------------------------------[]
{
  setSurface(color, Finish());
}

void
Material::setSurface(const Color& color, const Finish& finish)
//[]---------------------------------------------------[]
//|  Set surface                                        |
//[]---------------------------------------------------[]
{
  surface.ambient = color * finish.ambient;
  surface.diffuse = color * finish.diffuse;
  surface.shine = finish.shine;
  surface.spot = color * finish.spot;
  surface.specular = Color::black;
  surface.transparency = Color::black;
  surface.IOR = 1;
}

//////////////////////////////////////////////////////////
//
// MaterialFactory implementation
// ===============
MaterialFactory::Materials MaterialFactory::materials;

Material*
MaterialFactory::New(const Color& color)
//[]---------------------------------------------------[]
//|  Create material                                    |
//[]---------------------------------------------------[]
{
  uint id = materials.size();
  char name[16];

  sprintf(name, "mat%d", id);

  Material* material = new Material(name, color);

  add(material);
  return material;
}

Material*
MaterialFactory::New(const string& name, const Color& color)
//[]---------------------------------------------------[]
//|  Create material                                    |
//[]---------------------------------------------------[]
{
  Material* material = get(name);
  
  if (material == 0)
    add(material = new Material(name, color));
  return material;
}

Material*
MaterialFactory::get(const string& name)
//[]---------------------------------------------------[]
//|  Get material                                       |
//[]---------------------------------------------------[]
{
  for (MaterialIterator mit(materials); mit; ++mit)
    if (name == mit.current()->getName())
      return mit.current();
  return 0;
}
