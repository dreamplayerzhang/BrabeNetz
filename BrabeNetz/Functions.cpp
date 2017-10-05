#include "stdafx.h"
#include "Functions.h"
#include <cmath>
#include <vector>
using namespace std;

// The Euler's constant (e) calculated with exp(1)
const DECIMAL euler_constant = exp(1.0);
// Minimum value that's possible as a Squash(..) input parameter
const DECIMAL min_value = 0;
// Maximum value that's possible as a Squash(..) input parameter
const DECIMAL max_value = 1;

DECIMAL squash(const DECIMAL value)
{
	return 1 / (1 + exp(-value));
}

DECIMAL expand(const DECIMAL squashed)
{
	return log(squashed / (1 - squashed));
}

DECIMAL squash_derivative(const DECIMAL value)
{
	// TODO: Decide between those 2
	return value / (1 - value);
	return exp(-value) / pow(1 + exp(-value), 2);
}

DECIMAL transfer_derivative(const DECIMAL value)
{
	return value * (1 - value);
}

DECIMAL rectify(const DECIMAL value)
{
	return fmax(value, 0);
}

DECIMAL euclidean_dist(DECIMAL* x, DECIMAL* y, const int length)
{
	DECIMAL result = 0.0;
	for (int i = 0; i < length; i++)
	{
		result += pow(x[i] - y[i], 2);
	}
	return sqrt(result);
}

DECIMAL cost_func(DECIMAL* expected, DECIMAL* actual, const int length)
{
	DECIMAL sum = 0.0;
	for (int i = 0; i < length; i++)
	{
		sum += 0.5 * pow(expected[i] - actual[i], 2);
	}
	return sum;
}

DECIMAL cost_derivative(DECIMAL* expected, DECIMAL* actual, const int length)
{
	// TODO: derivative of what? partial? constants should get 0
	DECIMAL sum = 0.0;
	for (int i = 0; i < length; i++)
	{
		sum += -(expected[i] - actual[i]) * squash_derivative(expand(actual[i]));
	}
	return sum;
}

DECIMAL get_error(const DECIMAL expected, const DECIMAL actual)
{
	return actual * (1 - actual) * (expected - actual);
}

DECIMAL get_error(const DECIMAL neuron_value, const DECIMAL* next_errors,
				  const DECIMAL* next_weights, const int next_layer_size)
{
	double sum = 0;
	for (int i = 0; i < next_layer_size; i++)
	{
		sum += next_errors[i] * next_weights[i];
	}
	return neuron_value * (1 - neuron_value) * sum;
}

DECIMAL sum(vector<DECIMAL>& values)
{
	DECIMAL sum = 0;
	for (int i = 0; i < values.size(); i++)
	{
		sum += values.at(i);
	}
	return sum;
}

DECIMAL sum(DECIMAL* values, const int length)
{
	DECIMAL sum = 0;
	for (int i = 0; i < length; i++)
	{
		sum += values[i];
	}
	return sum;
}


// LOGISTIC:
//   float exp = std::pow(EulerConstant, value);
//   return exp / (exp + 1);

// HYPERBOLIC TAN:
//   float expP = std::pow(EulerConstant, value);
//   float expN = std::pow(EulerConstant, -value);
//   return (expP - expN) / (expP + expN);

// SPECIFIC ALGEBRAIC
//   return (value) / std::sqrt(1 + std::pow(value, 2));

// BRAH
// ((value - min_A) / max_A - min_A) * (new_max_A - new_min_A) + new_min_A
