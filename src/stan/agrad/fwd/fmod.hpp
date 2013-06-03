#ifndef __STAN__AGRAD__FWD__FMOD__HPP__
#define __STAN__AGRAD__FWD__FMOD__HPP__

#include <stan/agrad/fwd/fvar.hpp>
#include <stan/meta/traits.hpp>

namespace stan {

  namespace agrad {

    template <typename T>
    inline
    fvar<T>
    fmod(const fvar<T>& x1, const fvar<T>& x2) {
      using std::fmod;
      using std::floor;
      return fvar<T>(fmod(x1.val_, x2.val_), 
                     x1.d_ - x2.d_ * floor(x1.val_ / x2.val_));
    }

    template <typename T>
    inline
    fvar<typename stan::return_type<T,double>::type>
    fmod(const fvar<T>& x1, double x2) {
      using std::fmod;
      return fvar<typename stan::return_type<T,double>::type>(
        fmod(x1.val_, x2), x1.d_ / x2);
    }

    template <typename T>
    inline
    fvar<typename stan::return_type<T,double>::type>
    fmod(double x1, const fvar<T>& x2) {
      using std::fmod;
      using std::floor;
      return fvar<typename stan::return_type<T,double>::type>(
        fmod(x1, x2.val_), -x2.d_ * floor(x1 / x2.val_));
    }
  }
}
#endif
