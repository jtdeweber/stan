#ifndef __STAN__AGRAD__FWD__ATAN2__HPP__
#define __STAN__AGRAD__FWD__ATAN2__HPP__

#include <stan/agrad/fwd/fvar.hpp>
#include <stan/meta/traits.hpp>
#include <stan/math/functions/square.hpp>

namespace stan {

  namespace agrad {

    template <typename T>
    inline
    fvar<T>
    atan2(const fvar<T>& x1, const fvar<T>& x2) {
      using std::atan2;
      using stan::math::square;
      return fvar<T>(atan2(x1.val_, x2.val_), 
                     (x1.d_ * x2.val_ - x1.val_ * x2.d_) / 
                     (square(x2.val_) + square(x1.val_)));
    }

    template <typename T>
    inline
    fvar<typename stan::return_type<T,double>::type>
    atan2(double x1, const fvar<T>& x2) {
      using std::atan2;
      using stan::math::square;
      return fvar<typename 
                  stan::return_type<T,double>::type>(atan2(x1, x2.val_), 
                   (-x1 * x2.d_) / (square(x1) + square(x2.val_)));
    }

    template <typename T>
    inline
    fvar<typename stan::return_type<T,double>::type>
    atan2(const fvar<T>& x1, double x2) {
      using std::atan2;
      using stan::math::square;
      return fvar<typename 
                  stan::return_type<T,double>::type>(atan2(x1.val_, x2), 
                    (x1.d_ * x2) / (square(x2) + square(x1.val_)));
    }
  }
}
#endif
