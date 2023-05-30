#include "montecarlo.h"
#include <iostream>

int main()
{
    double result = MonteCarlo(
        [](double x, double y, double z)
        { return std::exp(-x * x - y * y - z * z); },
        [](double x, double y, double z) -> bool
        { return x * x + y * y + z * z < 16.0; },
        -4.0, 4.0, -4.0, 4.0, -4.0, 4.0);

    std::cout << "Az integrálás eredménye: " << result << std::endl;

    return 0;
}
