/*********************
 *   Float Class
 *********************/

#include "defs.h"

#ifndef FPLLL_NR_FP_H
#define FPLLL_NR_FP_H

FPLLL_BEGIN_NAMESPACE


/* declaration Z_NR */
template<class F> class Z_NR;


/**
 * FP_NR stores floating-point numbers. This template provides a uniform
 * interface for doing floating-point computations with several underlying
 * types (double, dpe_t and mpfr_t). For all functions, the rounding 
 * mode rnd is ignored unless F=mpfr_t. 
 */
template<class F> 
class FP_NR 
{

  F data;

public:

  /**
   * Constructors.
   */
  inline FP_NR<F>();
  inline FP_NR<F>(const FP_NR<F>& f);
  inline ~FP_NR<F>();

  /**
   * Returns the current precision for new FP_NR&lt;F&gt; objects.
   */
  static inline unsigned int getprec();

  /**
   * Sets the precision of new FP_NR&lt;F&gt; objects. Returns the 
   # previous value. This has no effect is F != mpfr_t.
   */
  static inline unsigned int setprec(unsigned int prec);

  /** get data */

  /**
   * Returns the internal representation of the data. 
   */
  inline F& getData()             {return data;}

  /**
   * Returns the internal representation of the data.
   */
  inline const F& getData() const {return data;}

  /**
   * Converts this object to a double. If it does not fit in a double,
   * the result is undefined.
   */
  inline double get_d(mp_rnd_t rnd = GMP_RNDN) const;

  /**
   * Convert this object to a mpfr_t r.
   */
  inline void get_mpfr(mpfr_t r, mp_rnd_t rnd = GMP_RNDN) const;

  /**
   * Converts this object to a long. The rounding direction is undefined.
   * If it does not fit in a long, the result is undefined.
   */
  inline long get_si() const;

  /**
   * Returns expo such value 2^(expo-1) <= value < 2^expo
   *  (expo = floor(abs(log2(abs(value)))) + 1).
   * The return value is undefined if *this == 0. 
   */
  inline long exponent() const;

  /**
   * Returns x and defines expo such that 
   *  trunc(value * 2^expoAdd) ~= x * 2^expo
   * The '~=' is an equality if trunc(value * 2^expoAdd) <= LONG_MAX.
   * expo is the minimum non-negative value such that x <= LONG_MAX.
   * expoAdd must be 0 if T=dpe_t or T=mpfr_t. 
   */
  inline long get_si_exp_we(long& expo, long expoAdd) const;

  /**
   * Returns x and defines expo such that trunc(value) ~= x * 2^expo.
   * The '~=' is an equality if trunc(value) <= LONG_MAX.
   * expo is the minimum non-negative value such that |x| <= LONG_MAX.
   * (x is the largest among all possible |x| <= LONG_MAX).
   */
  inline long get_si_exp(long& expo) const;

  /**
   * Computes a and expo such that trunc(value) ~= a * 2^expo.
   *  The '~=' is an equality if Z=mpz_t. expo is always non-negative.
   *  Note that expo might be very close to LONG_MAX when value = 0.
   *  (in nr_FP_misc.h)
   */
  template<class Z> inline void get_z_exp(Z_NR<Z>& a, long& expo) const;

  /**
   * Computes a and expo such that trunc(value) * 2^expoAdd ~= a * 2^expo.
   * The '~=' is an equality if Z=mpz_t. expo is always non-negative.
   * expoAdd must be 0 if T=dpe_t or T=mpfr_t.
   *  (in nr_FP_misc.h)
   */
  template<class Z> inline void get_z_exp_we(Z_NR<Z>& a, long& expo, long expoAdd) const;

  /** set data */

  /**
   * Sets the value to z. 
   * (in nr_FP_misc.h)
   */
  template<class Z> inline void set_z(const Z_NR<Z>& z, mp_rnd_t rnd = GMP_RNDN);

  /** comparison */

  /**
   * 3-way comparison. Returns a positive number if *this > b,
   * a negative number if *this < b or zero is *this == b. 
   */
  inline int cmp(const FP_NR<F>& b) const;

  /**
   * 3-way comparison. Returns a positive number if *this > d, 
   * a negative number if *this < d or zero is *this == d.
   */
  inline int cmp(double d) const;

  /**
   * Sign. Returns a positive number, a negative number or zero if the 
   * value of this object is respectively positive, negative or null. 
   */
  inline int sgn() const;

  /**
   * Operator
   */
  inline void operator=(const FP_NR<F>& a);
  inline void operator=(double a);
  inline void operator=(mpfr_t& a);
  inline bool operator<(const FP_NR<F>& a) const;
  inline bool operator<(double a) const;
  inline bool operator>(const FP_NR<F>& a) const;
  inline bool operator>(double a) const;
  inline bool operator<=(const FP_NR<F>& a) const;
  inline bool operator<=(double a) const;
  inline bool operator>=(const FP_NR<F>& a) const;
  inline bool operator>=(double a) const;

  /**
   * max between a and b
   */
  inline FP_NR& maxF(FP_NR<F>& b) {
    if ((*this)<=b)
      return b;
    else
      return (*this);
  }

  /**
   * Returns non-zero if the current value is zero, 0 otherwise.
   */
  inline bool is_zero() const;
  inline int zero_p() const {return is_zero();}

  /**
   * Returns non-zero if the current value is NaN, 0 otherwise.
   */
  inline int is_nan() const;

  /**
   * Returns non-zero if !isnan(value) and !isinf(value), 0 otherwise.
   */
  inline int is_finite() const;

  /** arithmetic */

  /**
   * value := a + b. 
   */
  inline void add(const FP_NR<F>& a, const FP_NR<F>& b, mp_rnd_t rnd = GMP_RNDN);

  /**
   * value := a - b. 
   */
  inline void sub(const FP_NR<F>& a, const FP_NR<F>& b, mp_rnd_t rnd = GMP_RNDN);

  /**
   * value := a * b. 
   */
  inline void mul(const FP_NR<F>& a, const FP_NR<F>& b, mp_rnd_t rnd = GMP_RNDN);

  /**
   * value := a * b where b is double. 
   */
  inline void mul_d(const FP_NR<F>& a, const double b, mp_rnd_t rnd = GMP_RNDN);

  /**
   * value := a * b where b is mpfr_t.
   */
  inline void mul_mpfr(const FP_NR<mpfr_t>& a, const mpfr_t b, mp_rnd_t rnd = GMP_RNDN);

  /**
   * value := a * 2^b. 
   */
  inline void mul_2si(const FP_NR<F>& a, long b);

  /**
   * value := a / b. 
   */
  inline void div(const FP_NR<F>& a, const FP_NR<F>& b, mp_rnd_t rnd = GMP_RNDN);

  /**
   * value := a / b. 
   */
  inline void div_d(const FP_NR<F>& a, const double b, mp_rnd_t rnd = GMP_RNDN);

  /**
   * value := value + a * b. 
   */
  inline void addmul(const FP_NR<F>& a, const FP_NR<F>& b, mp_rnd_t rnd = GMP_RNDN);

  /**
   * value := value - a * b. 
   */
  inline void submul(const FP_NR<F>& a, const FP_NR<F>& b, mp_rnd_t rnd = GMP_RNDN);

  /**
   * value := a^b. 
   */
  inline void pow_si(const FP_NR<F>& a, long b, mp_rnd_t rnd = GMP_RNDN);

  /**
   * value := e^b.
   */
  inline void exponential(const FP_NR<F>& b, mp_rnd_t rnd = GMP_RNDN);

  /**
   * value := natural logarithm of a. 
   */
  inline void log(const FP_NR<F>& a, mp_rnd_t rnd = GMP_RNDN);

  /**
   * value := square root of b. 
   */
  inline void sqrt(const FP_NR<F>& b, mp_rnd_t rnd = GMP_RNDN);

  /**
   * value := k-th root of b. 
   */
  inline void root(const FP_NR<F>& b, unsigned int k, mp_rnd_t rnd = GMP_RNDN);

  /**
   * value := -b. 
   */
  inline void neg(const FP_NR<F>& b);

  /**
   * value := absolute value of b. 
   */
  inline void abs(const FP_NR<F>& b);

  /**
   * value := rounding of b to the nearest integer. 
   */
  inline void rnd(const FP_NR<F>& b);

  /**
   * value <- (rounding of a * 2^expoAdd) / 2^expoAdd, but never overflows.
   * expoAdd must be 0 if T=dpe_t or T=mpfr_t. 
   */
  inline void rnd_we(const FP_NR<F>& b, long expoAdd);

  /**
   * value := largest integer not greater than b. 
   */
  inline void floor(const FP_NR<F>& b);

  /**
   * value := NaN. 
   */
  inline void set_nan();

  /**
   * Efficiently swaps the values of two FP_NR. 
   */
  inline void swap(FP_NR<F>& a);


#ifdef FPLLL_V3_COMPAT
  // Old interface (do not use)
  inline void print() const;
  inline void printerr() const;
  inline double get() const          {return get_d();}
  inline void set(const FP_NR<F>& s) {*this = s;}
  inline void set(double s)          {*this = s;}
  inline void set(unsigned int s);
  inline void mul_2ui(const FP_NR<F>& b, unsigned int c) {
    mul_2si(b, static_cast<long>(c));
  }
  inline void div_2ui(const FP_NR<F>& b, unsigned int c) {
    mul_2si(b, -static_cast<long>(c));
  }
  inline int exp() const          {return static_cast<int>(exponent());};
  inline F& GetData()             {return data;}
  inline const F& GetData() const {return data;}
#endif

}; // End class FP_NR


/**
 * FP_NR: some generic functions.
 */
template<class F>
inline void FP_NR<F>::addmul(const FP_NR<F>& b, const FP_NR<F>& c, mp_rnd_t rnd) {
  FP_NR<F> product;
  product.mul(b, c, rnd);
  add(*this, product, rnd);
}
template<class F>
inline void FP_NR<F>::submul(const FP_NR<F>& b, const FP_NR<F>& c, mp_rnd_t rnd) {
  FP_NR<F> product;
  product.mul(b, c, rnd);
  sub(*this, product, rnd);
}
template<class F>
inline bool FP_NR<F>::operator<(const FP_NR<F>& a) const {
  return cmp(a) < 0;
}
template<class F>
inline bool FP_NR<F>::operator>(const FP_NR<F>& a) const {
  return cmp(a) > 0;
}
template<class F>
inline bool FP_NR<F>::operator<(double a) const {
  return cmp(a) < 0;
}
template<class F>
inline bool FP_NR<F>::operator>(double a) const {
  return cmp(a) > 0;
}


/** overloading stream operators */

/**
 * Prints x on stream os. 
 */
template<class T>
ostream& operator<<(ostream& os, const FP_NR<T>& x) {
  return os << x.getData();
}

#ifdef FPLLL_WITH_DPE
template<>
ostream& operator<<(ostream& os, const FP_NR<dpe_t>& x);
#endif

template<>
ostream& operator<<(ostream& os, const FP_NR<mpfr_t>& x);


FPLLL_END_NAMESPACE

#endif
