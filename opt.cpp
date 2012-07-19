#include <math.h>
#include "opt.h"

namespace Opt {

Vector::Vector()
{
}

Vector::Vector(double x)
{
    v.push_back(x);
}

Vector::Vector(double x, double y)
{
    v.push_back(x);
    v.push_back(y);
}

double Vector::length2() const
{
    double len2 = 0.0;
    int I = v.size();
    for (int i = 0; i < I; i++)
    {
        len2 += v[i] * v[i];
    }
    return len2;
}

double Vector::length() const
{
    return sqrt(length2());
}

GradientDescentMinimizer::GradientDescentMinimizer(
        const Function* f_in,
        Vector init)
{
    f = f_in;
    p = init;
}

void GradientDescentMinimizer::step(double step_size)
{
    // p = p - step_size * g;
    Vector g = f->grad(p);
    int I = p.v.size();
    for (int i = 0; i < I; i++)
    {
        p.v[i] = p.v[i] - step_size * g.v[i]; 
    }
}

Vector GradientDescentMinimizer::point() const
{
    return p;
}

}

