#ifndef __STAN__AGRAD__FWD__FMIN__HPP__
#define __STAN__AGRAD__FWD__FMIN__HPP__

#include <stan/agrad/fwd/fvar.hpp>
#include <stan/meta/traits.hpp>
#include <stan/math/constants.hpp>

namespace stan {

  namespace agrad {

    template <typename T>
    inline
    fvar<T>
    fmin(const fvar<T>& x1, const fvar<T>& x2) {
      using std::min;
      using stan::math::NOT_A_NUMBER;
      if(x1.val_ < x2.val_)
        return fvar<typename stan::return_type<T,double>::type>(
          min(x1.val_, x2.val_), x1.d_ * 1.0);
      else if(x1.val_ == x2.val_)
        return fvar<typename stan::return_type<T,double>::type>(
          min(x1.val_, x2.val_), NOT_A_NUMBER);
      else 
        return fvar<typename stan::return_type<T,double>::type>(
          min(x1.val_, x2.val_), x2.d_ * 1.0);              
    }

    template <typename T>
    inline
    fvar<typename stan::return_type<T,double>::type>
    fmin(double x1, const fvar<T>& x2) {
      using std::min;
      using stan::math::NOT_A_NUMBER;
      if(x1 < x2.val_)
        return fvar<typename stan::return_type<T,double>::type>(
          min(x1, x2.val_), 0.0);
      else if(x1 == x2.val_)
        return fvar<typename stan::return_type<T,double>::type>(
          min(x1, x2.val_), NOT_A_NUMBER);
      else 
        return fvar<typename stan::return_type<T,double>::type>(
          min(x1, x2.val_), x2.d_ * 1.0);               
    }

    template <typename T>
    inline
    fvar<typename stan::return_type<T,double>::type>
    fmin(const fvar<T>& x1, double x2) {
      using std::min;
      using stan::math::NOT_A_NUMBER;
      if(x1.val_ < x2)
        return fvar<typename stan::return_type<T,double>::type>(
          min(x1.val_, x2), x1.d_ * 1.0);
      else if(x1.val_ == x2)
        return fvar<typename stan::return_type<T,double>::type>(
          min(x1.val_, x2), NOT_A_NUMBER);
      else 
        return fvar<typename stan::return_type<T,double>::type>(
          min(x1.val_, x2), 0.0);
     }
  }
}
#endif
