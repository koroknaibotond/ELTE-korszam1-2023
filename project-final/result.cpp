#include <iostream>
#include "montecarlo.hpp"
#include <cmath>

int main()
{
    MonteCarlo params(
        [](double x, double y, double z)
        { return std::exp(-x * x - y * y - z * z); },
        [](double x, double y, double z) -> bool
        { return x * x + y * y + z * z < 16.0; },
        -4.0, 4.0, -4.0, 4.0, -4.0, 4.0);

    double result = params.getResult();
    std::cout << "\n";

    std::cout << "Az integrálás eredménye: " << result << std::endl;
    std::cout << "\n";

    double control = params.getControl();
    std::cout << "Az ellenőrzés eredménye: " << control << std::endl;
    std::cout << "\n";

    double diff = pow(control - result, 2);
    std::cout << "A két integrálás négyzetes eltérése:" << diff << std ::endl;

    double percent = 100 * std::abs((result - control) / control);
    std::cout << "A két integrálás százalákos eltérése:" << percent << std ::endl;
    return 0;
}