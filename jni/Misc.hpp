#ifndef MISC_HPP
#define MISC_HPP

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
