#include <iostream>
#include "montecarlo.hpp"

int main()
{
    MonteCarlo params(
        [](double x, double y, double z)
        { return std::exp(-x * x - y * y - z * z); },
        [](double x, double y, double z) -> bool
        { return x * x + y * y + z * z < 16.0; },
        -4.0, 4.0, -4.0, 4.0, -4.0, 4.0, 2e6); // Megadjuk a változókat,amikkel a MonteCarlo integrálást végezzük.

    double result = params.getResult(); // ezzel a segédfüggvénnyel előhívjuk a class, private részéből az inegrálás eredményét.
    std::cout << "\n";

    std::cout << "Az integrálás eredménye: " << result << std::endl; // Kiiratjuk
    std::cout << "\n";

    return 0;
}