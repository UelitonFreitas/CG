//[]---------------------------------------------------------------[]
//|                                                                 |
//| Copyright (C) 2014 Orthrus Group.                               |
//|                                                                 |
//| This software is provided 'as-is', without any express or       |
//| implied warranty. In no event will the authors be held liable   |
//| for any damages arising from the use of this software.          |
//|                                                                 |
//| Permission is granted to anyone to use this software for any    |
//| purpose, including commercial applications, and to alter it and |
//| redistribute it freely, subject to the following restrictions:  |
//|                                                                 |
//| 1. The origin of this software must not be misrepresented; you  |
//| must not claim that you wrote the original software. If you use |
//| this software in a product, an acknowledgment in the product    |
//| documentation would be appreciated but is not required.         |
//|                                                                 |
//| 2. Altered source versions must be plainly marked as such, and  |
//| must not be misrepresented as being the original software.      |
//|                                                                 |
//| 3. This notice may not be removed or altered from any source    |
//| distribution.                                                   |
//|                                                                 |
//[]---------------------------------------------------------------[]
//
// OVERVIEW: Flags.h
// ========
// Class definition for flags.
//
// Author: Paulo Pagliosa
// Last revision: 08/09/2014

#ifndef __Flags_h
#define __Flags_h

#include "Core/Global.h"

DS_BEGIN_NAMESPACE


/////////////////////////////////////////////////////////////////////
//
// Flags: flags class
// =====
class Flags
{
public:
  /// Contructs a Flags object with no bits set.
  Flags()
  {
    bits = 0;
  }

  /// Constructs a Flags object initialized with mask.
  Flags(int mask)
  {
    bits = mask;
  }

  /// \brief Assigns mask to the bits of this object and returns a
  /// reference to this object.
  Flags& operator =(int mask)
  {
    bits = mask;
    return *this;
  }

  /// Sets the bits of this object, given by mask, to 1.
  void set(int mask)
  {
    bits |= mask;
  }

  /// Sets the bits of this object, given by mask, to 0.
  void reset(int mask)
  {
    bits &= ~mask;
  }

  /// Sets all bits of this object to 0.
  void clear()
  {
    bits = 0;
  }

  /// Sets the bits of this object, given by mask, to state.
  void enable(int mask, bool state)
  {
    state ? set(mask) : reset(mask);
  }

  /// Converts this object to int.
  operator int() const
  {
    return bits;
  }

  /// Returns true if all bits of this object, given by mask, are set.
  bool isSet(int mask) const
  {
    return (bits & mask) == mask;
  }

  /// Returns true if any bits of this object, given by mask, are set.
  bool test(int mask) const
  {
    return (bits & mask) != 0;
  }

private:
  int bits;

}; // Flags

DS_END_NAMESPACE

#endif // __Flags_h
