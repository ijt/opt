#include <stdlib.h>
#include <gtest/gtest.h>

#include "opt.h"

// 1D parabola
class Parabola: public Opt::Function {
public:
    Parabola(double a_in, double b_in, double c_in) {
        a = a_in;
        b = b_in;
        c = c_in;
    }

    // Value of the parabola at a point x
    double f(Opt::Vector p) {
        double x = p.v[0];
        return a*x*x + b*x + c;
    }

    // Gradient of the parabola at a point x.
    // This is just a 1D vector
    Opt::Vector grad(Opt::Vector p) {
        double x = p.v[0];
        return Opt::Vector(2.0*a*x + b);        
    }

private:
    double a;
    double b;
    double c;
};

TEST(GradientDescentTestSuite, zeroParabolaTestCase)
{
    double step_size=1e-3;
    Parabola p(1.0, 0.0, 0.0);
    Opt::Vector init(10.0 * drand48());
    Opt::GradientDescentMinimizer o(&p, init);
    while (p.grad(o.point()).length2() > 1e-6*1e-6) {
        o.step(drand48() * step_size);
    }
    ASSERT_TRUE(o.point().length() <= 0.5e-6);
}

int main(int argc, char **argv){
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
