// ASTEROIDS_LICENSE_BEGIN
/*

  asteroids GPL Source Code
  Copyright (C) 2013 Edward Knyshov

  This file is part of the asteroids GPL Source Code (asteroids Source Code).

  asteroids Source Code is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  asteroids Source Code is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with asteroids Source Code. If not, see <http://www.gnu.org/licenses/>.

*/
// ASTEROIDS_LICENSE_END

#ifndef MISC_HPP
#define MISC_HPP

#include <stdlib.h>

namespace test {

  template<typename T>
  inline const T &Max(const T &_a, const T &_b) {
    return _a > _b ? _a : _b;
  }

  template<typename T>
  inline const T &Min(const T &_a, const T &_b) {
    return _a < _b ? _a : _b;
  }

  template<typename T>
  inline const T &Clamp(const T &_val, const T &_min, const T &_max) {
    return Max( Min( _val, _max ), _min );
  }

  template<typename T>
  inline T Abs(const T &_val) {
    return _val < 0 ? -_val : _val;
  }

  template<typename T>
  T Rand(const T &_min, const T &_max, const T &_step) {
    return ::rand() %
	  static_cast<int>( ( _max - _min ) / _step + 1 ) *
	  _step +
	  _min;
  }

  template<typename T>
  inline int Sign(T _value) {
    return _value < 0.0 ? -1 : 1;
  }

}

#endif// MISC_HPP
