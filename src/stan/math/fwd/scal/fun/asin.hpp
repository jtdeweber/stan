#ifndef STAN_MATH_FWD_SCAL_FUN_ASIN_HPP
#define STAN_MATH_FWD_SCAL_FUN_ASIN_HPP

#include <stan/math/fwd/core.hpp>

#include <stan/math/prim/scal/fun/square.hpp>
#include <math.h>

namespace stan {

  namespace agrad {

    template <typename T>
    inline
    fvar<T>
    asin(const fvar<T>& x) {
      using ::asin;
      using std::sqrt;
      using stan::math::square;
      return fvar<T>(asin(x.val_), x.d_ / sqrt(1 - square(x.val_)));
    }
  }
}
#endif
