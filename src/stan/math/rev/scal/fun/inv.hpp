#ifndef STAN_MATH_REV_SCAL_FUN_INV_HPP
#define STAN_MATH_REV_SCAL_FUN_INV_HPP

#include <stan/math/rev/core.hpp>
#include <stan/math/prim/scal/fun/inv.hpp>
#include <valarray>

namespace stan {
  namespace agrad {

    namespace {
      class inv_vari : public op_v_vari {
      public:
        explicit inv_vari(vari* avi) :
          op_v_vari(stan::math::inv(avi->val_), avi) {
        }
        void chain() {
          avi_->adj_ -= adj_ / (avi_->val_ * avi_->val_);
        }
      };
    }

    /**
     *
       \f[
       \mbox{inv}(x) =
       \begin{cases}
         \frac{1}{x} & \mbox{if } -\infty\leq x \leq \infty \\[6pt]
         \textrm{NaN} & \mbox{if } x = \textrm{NaN}
       \end{cases}
       \f]

       \f[
       \frac{\partial\, \mbox{inv}(x)}{\partial x} =
       \begin{cases}
         -\frac{1}{x^2} & \mbox{if } -\infty\leq x\leq \infty \\[6pt]
         \textrm{NaN} & \mbox{if } x = \textrm{NaN}
       \end{cases}
       \f]
     *
     */
    inline var inv(const var& a) {
      return var(new inv_vari(a.vi_));
    }

  }
}
#endif
