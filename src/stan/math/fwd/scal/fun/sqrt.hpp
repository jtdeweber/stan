#ifndef STAN_MATH_FWD_SCAL_FUN_SQRT_HPP
#define STAN_MATH_FWD_SCAL_FUN_SQRT_HPP

#include <stan/math/fwd/core.hpp>

#include <stan/math/prim/scal/fun/inv_sqrt.hpp>

namespace stan {

  namespace agrad {

    template <typename T>
    inline
    fvar<T>
    sqrt(const fvar<T>& x) {
      using std::sqrt;
      using stan::math::inv_sqrt;
      return fvar<T>(sqrt(x.val_), 0.5 * x.d_ * inv_sqrt(x.val_));
    }
  }
}
#endif
