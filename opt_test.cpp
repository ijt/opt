#include <math.h>
#include <stdio.h>
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
    double val(Opt::Vector p) const {
        double x = p.v[0];
        return a*x*x + b*x + c;
    }

    // Gradient of the parabola at a point x.
    // This is just a 1D vector
    Opt::Vector grad(Opt::Vector p) const {
        double x = p.v[0];
        return Opt::Vector(2.0*a*x + b);        
    }

private:
    double a;
    double b;
    double c;
};

TEST(GradientDescentTestSuite, parabolaTestCase)
{
    double step_size = 1e-3;
    for (int i = 0; i < 10; i++)
    {
        // Set up a parabola with random coefficients in [0, 1]
        double a, b, c;
        // Choose a random value of a that is not too small.
        do {
            a = drand48();
        } while(fabs(a) < 1e-3);
        b = drand48();
        c = drand48();
        Parabola p(a, b, c);

        // Set up a minimizer with initial point between 0 and 10.
        Opt::Vector init(10.0 * drand48());
        Opt::GradientDescentMinimizer o(&p, init);
        while (true) {
            double grad_len2 = p.grad(o.point()).length2();
            if (grad_len2 < 1e-6*1e-6) {
                break;
            }
            o.step(drand48() * step_size);
        }

        // Check against the known minimum formula for parabolas.
        double x = o.point().v[0];
        ASSERT_TRUE(fabs(x - (- b / (2.0 * a))) <= 1e-3);
    }
}

int main(int argc, char **argv){
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

