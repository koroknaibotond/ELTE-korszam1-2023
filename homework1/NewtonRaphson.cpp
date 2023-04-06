#include <iostream>
#include <math.h>

template <typename F, typename D, typename T> // creating the template of the Newton-Raphson iteration
T Newton(F f, D df, T x0)
{
    int iter_num = 10; // number of repeats which i though would be more than enough to give a good result for the square root.
    for (int i = 0; i < iter_num; ++i)
    {
        T x1 = x0 - f(x0) / df(x0);
        x0 = x1;
    }
    return x0;
}

int main()
{
    double result = Newton([](double x)
                           { return x * x - 612.0; }, // Test function
                           [](double x)
                           { return 2.0 * x; },
                           10.0);
    std::cout << "The square root of the function is: " << result << std::endl; // The result
    return 0;
}
