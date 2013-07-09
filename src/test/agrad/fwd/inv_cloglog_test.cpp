#include <gtest/gtest.h>
#include <stan/agrad/fvar.hpp>
#include <stan/math/functions/inv_cloglog.hpp>
#include <stan/agrad/var.hpp>
#include <test/agrad/util.hpp>

TEST(AgradFwdInvCLogLog,Fvar) {
  using stan::agrad::fvar;
  using stan::math::inv_cloglog;

  fvar<double> x(0.5,1.0);

  fvar<double> a = inv_cloglog(x);
  EXPECT_FLOAT_EQ(inv_cloglog(0.5), a.val_);
  EXPECT_FLOAT_EQ(exp(0.5 -exp(0.5)), a.d_);

  fvar<double> y(-1.2,1.0);

  fvar<double> b = inv_cloglog(y);
  EXPECT_FLOAT_EQ(inv_cloglog(-1.2), b.val_);
  EXPECT_FLOAT_EQ(exp(-1.2 -exp(-1.2)), b.d_);

  fvar<double> z(1.5,2.0);

  fvar<double> c = inv_cloglog(z);
  EXPECT_FLOAT_EQ(inv_cloglog(1.5), c.val_);
  EXPECT_FLOAT_EQ(2.0 * exp(1.5 -exp(1.5)), c.d_);
}

TEST(AgradFwdInvCLogLog,FvarVar_1stDeriv) {
  using stan::agrad::fvar;
  using stan::agrad::var;
  using stan::math::inv_cloglog;
  using std::exp;

  fvar<var> x(0.5,1.3);
  fvar<var> a = inv_cloglog(x);

  EXPECT_FLOAT_EQ(inv_cloglog(0.5), a.val_.val());
  EXPECT_FLOAT_EQ(1.3 * exp(0.5 - exp(0.5)), a.d_.val());

  AVEC y = createAVEC(x.val_);
  VEC g;
  a.val_.grad(y,g);
  EXPECT_FLOAT_EQ(exp(0.5 - exp(0.5)), g[0]);
}
TEST(AgradFwdInvCLogLog,FvarVar_2ndDeriv) {
  using stan::agrad::fvar;
  using stan::agrad::var;
  using stan::math::inv_cloglog;
  using std::exp;

  fvar<var> x(0.5,1.3);
  fvar<var> a = inv_cloglog(x);

  AVEC y = createAVEC(x.val_);
  VEC g;
  a.d_.grad(y,g);
  EXPECT_FLOAT_EQ(-exp(0.5 - exp(0.5)) * (exp(0.5) - 1.0) * 1.3, g[0]);
}
TEST(AgradFwdInvCLogLog,FvarFvarDouble) {
  using stan::agrad::fvar;
  using stan::math::inv_cloglog;
  using std::exp;

  fvar<fvar<double> > x;
  x.val_.val_ = 0.5;
  x.val_.d_ = 1.0;

  fvar<fvar<double> > a = inv_cloglog(x);

  EXPECT_FLOAT_EQ(inv_cloglog(0.5), a.val_.val_);
  EXPECT_FLOAT_EQ(exp(0.5 - exp(0.5)), a.val_.d_);
  EXPECT_FLOAT_EQ(0, a.d_.val_);
  EXPECT_FLOAT_EQ(0, a.d_.d_);

  fvar<fvar<double> > y;
  y.val_.val_ = 0.5;
  y.d_.val_ = 1.0;

  a = inv_cloglog(y);
  EXPECT_FLOAT_EQ(inv_cloglog(0.5), a.val_.val_);
  EXPECT_FLOAT_EQ(0, a.val_.d_);
  EXPECT_FLOAT_EQ(exp(0.5 - exp(0.5)), a.d_.val_);
  EXPECT_FLOAT_EQ(0, a.d_.d_);
}
TEST(AgradFwdInvCLogLog,FvarFvarVar_1stDeriv) {
  using stan::agrad::fvar;
  using stan::agrad::var;
  using stan::math::inv_cloglog;
  using std::exp;

  fvar<fvar<var> > x;
  x.val_.val_ = 0.5;
  x.val_.d_ = 1.0;

  fvar<fvar<var> > a = inv_cloglog(x);

  EXPECT_FLOAT_EQ(inv_cloglog(0.5), a.val_.val_.val());
  EXPECT_FLOAT_EQ(exp(0.5 - exp(0.5)), a.val_.d_.val());
  EXPECT_FLOAT_EQ(0, a.d_.val_.val());
  EXPECT_FLOAT_EQ(0, a.d_.d_.val());

  AVEC p = createAVEC(x.val_.val_);
  VEC g;
  a.val_.val_.grad(p,g);
  EXPECT_FLOAT_EQ(exp(0.5 - exp(0.5)), g[0]);

  fvar<fvar<var> > y;
  y.val_.val_ = 0.5;
  y.d_.val_ = 1.0;

  fvar<fvar<var> > b = inv_cloglog(y);
  EXPECT_FLOAT_EQ(inv_cloglog(0.5), b.val_.val_.val());
  EXPECT_FLOAT_EQ(0, b.val_.d_.val());
  EXPECT_FLOAT_EQ(exp(0.5 - exp(0.5)), b.d_.val_.val());
  EXPECT_FLOAT_EQ(0, b.d_.d_.val());

  AVEC q = createAVEC(y.val_.val_);
  VEC r;
  b.val_.val_.grad(q,r);
  EXPECT_FLOAT_EQ(exp(0.5 - exp(0.5)), r[0]);
}
TEST(AgradFwdInvCLogLog,FvarFvarVar_2ndDeriv) {
  using stan::agrad::fvar;
  using stan::agrad::var;
  using stan::math::inv_cloglog;
  using std::exp;

  fvar<fvar<var> > x;
  x.val_.val_ = 0.5;
  x.val_.d_ = 1.0;

  fvar<fvar<var> > a = inv_cloglog(x);

  EXPECT_FLOAT_EQ(inv_cloglog(0.5), a.val_.val_.val());
  EXPECT_FLOAT_EQ(exp(0.5 - exp(0.5)), a.val_.d_.val());
  EXPECT_FLOAT_EQ(0, a.d_.val_.val());
  EXPECT_FLOAT_EQ(0, a.d_.d_.val());

  AVEC p = createAVEC(x.val_.val_);
  VEC g;
  a.val_.d_.grad(p,g);
  EXPECT_FLOAT_EQ(exp(0.5 - exp(0.5)) * (1.0 - exp(0.5)), g[0]);

  fvar<fvar<var> > y;
  y.val_.val_ = 0.5;
  y.d_.val_ = 1.0;

  fvar<fvar<var> > b = inv_cloglog(y);
  EXPECT_FLOAT_EQ(inv_cloglog(0.5), b.val_.val_.val());
  EXPECT_FLOAT_EQ(0, b.val_.d_.val());
  EXPECT_FLOAT_EQ(exp(0.5 - exp(0.5)), b.d_.val_.val());
  EXPECT_FLOAT_EQ(0, b.d_.d_.val());

  AVEC q = createAVEC(y.val_.val_);
  VEC r;
  b.d_.val_.grad(q,r);
  EXPECT_FLOAT_EQ(exp(0.5 - exp(0.5)) * (1.0 - exp(0.5)), r[0]);
}


