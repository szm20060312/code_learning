#include "a.h"
#include <cmath>
namespace A
{
	const double G = 6.67430e-11;
	double Gravitational_Acceleration(double r, double m)
	{
		return G * m / r;
	}
	double Escape_Velocity(double r,double m)
	{
		return sqrt(2 * G * m / r);
	}
}
