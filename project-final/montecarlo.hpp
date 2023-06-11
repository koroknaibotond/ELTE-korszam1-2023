#include <iostream>
#include <random>
#include <cmath>

class MonteCarlo
{
private:
    std::random_device rd;
    std::mt19937 gen; // a randomszám generáláshoz egy Mersenne Twister típusú véletlenszám-generátort használtam
    std::uniform_real_distribution<double> distributionx;
    std::uniform_real_distribution<double> distributiony; // A koordinátákhoz a megadott határok között egyenletesen elosztott véleletlenszámokat generáltam
    std::uniform_real_distribution<double> distributionz;
    double result;       // Ebbe a változóban tároljuk az Montecarlo integrálás eredményét
    double controlvalue; // Ebben pedig az ellenőrzés során kiszámolt értéket

public:
    template <typename Func, typename Dom>
    MonteCarlo(Func integrand, Dom domain, double xmin, double xmax, double ymin, double ymax, double zmin, double zmax, int samples = 0.5e6)
        : gen(rd()), distributionx(xmin, xmax), distributiony(ymin, ymax), distributionz(zmin, zmax)
    { // Ebben a konstuktoban adhatjuk meg az integrandust, az integrálási tartományt, és a tartományt magába foglaló téglalap határait
      // valamint inicializáljuk randomszám generátort, és az eloszlásokat a megfelelő határokkal
        try
        {
            result = integrate(integrand, domain, samples); // Elvégezzük a Montecarlo integrálást
            controlvalue = control(integrand, domain);      // Elvégezzük téglalap módszeres integrálást
            double diff = pow(controlvalue - result, 2);    // Kiszámítjuk a négyzetes eltérést
            if (diff > 1e-04)                               // Ha az eltérés meghaladja a hibahatárt.
            {
                throw std::runtime_error("Hiba! A kiszámított érték és a Control érték négyzetes eltérése nagyobb mint : 1e-04"); // Hibát kapunk
            }
        }
        catch (const std::runtime_error &e)
        {
            std::cerr << e.what() << std::endl; // Kiiratjuk a hibát.
        }
    }

    double getResult() const
    {
        return result;
    }
    // Ez csak két segédfüggvény, ami a privateből kiolvassa a Montecalro és az ellenőrzés értékét.
    double getControl() const
    {
        return controlvalue;
    }

private: // Montecarlo módszert megvalósító függvény
    template <typename Func, typename Dom>
    double integrate(Func integrand, Dom domain, int samples) // megadjuk az integrandust, a tartományt és az ismétlés számot (nem szükséges alapértelmezetten 500 ezer)
    {
        double sum = 0.0;
        for (int i = 0; i < samples; ++i)
        {
            double x = distributionx(gen); // Generálunk random koordinátákat
            double y = distributiony(gen);
            double z = distributionz(gen);

            if (domain(x, y, z)) // ellenőrizzük, hogy a tartományba találhatóak-e?
            {
                double value = integrand(x, y, z); // Amennyiben igen, kiszámoljuk a integrandus értékét az adott ponton
                sum += value;                      // A tartományban található pontok esetén számolt értékeket összegezzük
            }
        }

        double volume = (distributionx.max() - distributionx.min()) * (distributiony.max() - distributiony.min()) * (distributionz.max() - distributionz.min());
        double integral = sum / static_cast<double>(samples) * volume; // Az integrál értékének kiszámítása
        return integral;
    }
    template <typename Func, typename Dom>
    double control(Func integrand, Dom domain) // Kontrol integrálás
    {
        double a = distributionx.min();
        double b = distributionx.max(); // Definiáljuk azt a téglatestet ahol végig kell futni az integrálásnak
        double c = distributiony.min();
        double d = distributiony.max();
        double e = distributionz.min();
        double f = distributionz.max();

        int n = 100;            // Osztások száma
        double h = (b - a) / n; // Hossz
        double k = (d - c) / n;
        double m = (f - e) / n;

        double sum = 0.0;
        for (int i = 0; i <= n; ++i) // mindegyik oldal mentén végigfutunk, a h,k,m hosszokat lépkedve
        {
            double x = a + i * h;
            for (int j = 0; j <= n; ++j)
            {
                double y = c + j * k;
                for (int l = 0; l <= n; ++l)
                {
                    double z = e + l * m;
                    if (domain(x, y, z)) // erre azért volt szükség, hogy tényleg a tartmonányon integráljunk és ne az egész téglalapon.
                    {
                        double value = integrand(x, y, z);
                        sum += value;
                    }
                }
            }
        }

        double volume = (b - a) * (d - c) * (f - e);
        double integral = sum * (h * k * m); // Az ellenőrző integrál meghatározása.
        return integral;
    }
};