#include <iostream>
#include <random>
#include <cmath>
#include <functional>

class MonteCarlo
{
private:
    std::random_device rd;
    std::mt19937 gen;
    std::uniform_real_distribution<double> distributionx;
    std::uniform_real_distribution<double> distributiony;
    std::uniform_real_distribution<double> distributionz;
    double result;
    double controlvalue;

public:
    template <typename Func, typename Dom>
    MonteCarlo(Func integrand, Dom domain, double xmin, double xmax, double ymin, double ymax, double zmin, double zmax, int samples = 1e6)
        : gen(rd()), distributionx(xmin, xmax), distributiony(ymin, ymax), distributionz(zmin, zmax)
    {
        result = integrate(integrand, domain, samples);
        controlvalue = control(integrand);
    }

    double getResult() const
    {
        return result;
    }

    double getControl() const
    {
        return controlvalue;
    }

private:
    template <typename Func, typename Dom>
    double integrate(Func integrand, Dom domain, int samples)
    {
        int indomain = 0;
        double sum = 0.0;
        for (int i = 0; i < samples; ++i)
        {
            double x = distributionx(gen);
            double y = distributiony(gen);
            double z = distributionz(gen);

            if (domain(x, y, z))
            {
                double value = integrand(x, y, z);
                sum += value;
                indomain++;
            }
        }

        double volume = (distributionx.max() - distributionx.min()) * (distributiony.max() - distributiony.min()) * (distributionz.max() - distributionz.min());
        /*double integral = static_cast<double>(indomain) / static_cast<double>(samples) * volume;*/
        std::cout << "Montecarlo sum:" << sum << std::endl; // tesztelés

        double integral = sum / samples / 1000 * indomain * (1e6 / samples); // 1000-es szorzó miért?
        return integral;
    }
    template <typename Func>
    double control(Func integrand)
    {
        double a = distributionx.min();
        double b = distributionx.max();
        double c = distributiony.min();
        double d = distributiony.max();
        double e = distributionz.min();
        double f = distributionz.max();

        int n = 100;            // Osztások száma
        double h = (b - a) / n; // Hossz
        double k = (d - c) / n;
        double m = (f - e) / n;

        double sum = 0.0;
        for (int i = 0; i <= n; ++i)
        {
            double x = a + i * h;
            for (int j = 0; j <= n; ++j)
            {
                double y = c + j * k;
                for (int l = 0; l <= n; ++l)
                {
                    double z = e + l * m;
                    if (x * x + y * y + z * z < 16.0)
                    {
                        double value = integrand(x, y, z);
                        sum += value;
                    }
                }
            }
        }

        double volume = (b - a) * (d - c) * (f - e);
        double integral = sum * (h * k * m);
        std::cout << "Hagyományos sum:" << sum << std::endl; // tesztelés
        return integral;
    }
};