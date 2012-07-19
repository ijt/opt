#ifndef OPT_H
#define OPT_H

#include <vector>

// Classes for function optimization

namespace Opt {

class Vector
{
public:
    Vector();
    explicit Vector(double x);
    Vector(double x, double y);

    // Squared Euclidean length
    double length2() const;

    // Euclidean length
    double length() const;

    std::vector<double> v;
};

class Function
{
public:
    // Value of the function at a point x
    virtual double val(Vector p) const = 0;

    // Gradient of the function at a point x
    virtual Vector grad(Vector p) const = 0;
};

class GradientDescentMinimizer {
public: 
    GradientDescentMinimizer(const Function* f, Vector init);

    // Take a single step in the opposite direction of the
    // gradient.
    void step(double size);

    // Return the current location.
    Vector point() const;
private:
    Vector p;
    const Function* f;
};

}

#endif

