/* 
 * lazy.cc
 *
 * Copyright Johan Astborg 2014
 * https://github.com/joastbg
 *
 * A short demo program of how to use lazy generators, in particular
 * generators for random numbers and brownian motion. Use gen.sh to
 * plot result using gnuplot.
 *
 * Usage: make run
 */

#include <iostream>
#include <vector>
#include <ctime> 
#include <cmath>

#include <boost/random/mersenne_twister.hpp>
#include <boost/random/normal_distribution.hpp>
#include <boost/random/variate_generator.hpp>
#include <boost/generator_iterator.hpp>
//include <boost/date_time/posix_time/posix_time.hpp>
//include <boost/thread.hpp>

/* Definitions for random number generation */
typedef boost::mt19937                                      T_base_prng;
typedef boost::normal_distribution<>                        T_norm_dist;
typedef boost::variate_generator<T_base_prng&, T_norm_dist> T_norm_varg;

/* Sample generator for fibonacci numbers */
class fib_generator
{
public:
	typedef int result_type;
	fib_generator() : one(0), two(1), i(0) { }
	int operator()() { 

		if (++i < 2) return i;

		int res = one + two;

		one = two;
		two = res;

		return res;
	}
private:
	int one, two, i;
};

/* Random number generator, taking a seed as input */
class lazy_random_generator
{
public:
	typedef double result_type;
	lazy_random_generator(double mean, double stdev, int seed) : base_prng(seed), norm_dist(mean, stdev), norm_varg(base_prng, norm_dist) { }
	double operator()() {
		return norm_varg();
	}
private:
	T_base_prng  base_prng;
	T_norm_dist  norm_dist;
	T_norm_varg  norm_varg;
};

/* Brownian motion generator */
class lazy_brownian_motion
{
public:
	typedef double result_type;
	
	lazy_brownian_motion(double mean, double stdev, int seed) : base_prng(seed), norm_dist(mean, stdev), norm_varg(base_prng, norm_dist) { }
	
	double operator()() {
		memo+= norm_varg();
		return memo;
	}
private:
	double       memo;
	T_base_prng  base_prng;
	T_norm_dist  norm_dist;
	T_norm_varg  norm_varg;
};

class asset_path
{
public:
	typedef double result_type;

	asset_path(double mean, double stdev, int seed) : memo(1), base_prng(seed), norm_dist(mean, stdev), norm_varg(base_prng, norm_dist) { }

	double operator()() {
		/* TODO: Take as parameters, as well as generator (norm_varg()) */
		double S0 = 50.0;
		double mu = 0.04;
		double sig = 0.1;
		double dt = 1/356.0;
		memo *= exp((mu-sig*sig/2)*dt+sig*sqrt(dt)*norm_varg());
		return  S0*memo;
	}

	void reset() { memo = 1; }

private:
	double       memo;
	T_base_prng  base_prng;
	T_norm_dist  norm_dist;
	T_norm_varg  norm_varg;
};

int main()
{
	// Lazy generators

	// fib_generator gen;
	// boost::generator_iterator_generator<fib_generator>::type it = boost::make_generator_iterator(gen);
	// for (int i = 0; i < 15; ++i, ++it) {
	// 	std::cout << *it << std::endl;
	// }

	// lazy_random_generator zgen(0,1,static_cast<unsigned int>(std::time(0)));
	// boost::generator_iterator_generator<lazy_random_generator>::type it2 = boost::make_generator_iterator(zgen);
	// for (int i = 0; i < 15; ++i, ++it2) {
	// 	std::cout << *it2 << std::endl;
	// }

    // lazy_brownian_motion bgen(0,1,static_cast<unsigned int>(std::time(0)));
	// boost::generator_iterator_generator<lazy_brownian_motion>::type it3 = boost::make_generator_iterator(bgen);
	// for (int i = 0; i < 1500; ++i, ++it3) {
	// 	std::cout << *it3 << std::endl;
	// }

	asset_path bgen(0,1,static_cast<unsigned int>(std::time(0)));
	boost::generator_iterator_generator<asset_path>::type it4 = boost::make_generator_iterator(bgen);

	for (int r = 0; r < 20; r++) {
		std::cout << "# " << r << std::endl;
		for (int i = 0; i < 365*2; i++, it4++) {
			std::cout << i << "   " << *it4 << std::endl;
		}
		std::cout << std::endl;
		// reset generator
		bgen.reset();
	}
  
	return 0;
}
