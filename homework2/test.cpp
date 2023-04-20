#include "vector2.h"
#include <iostream>
int main()
{
    // Az összeadás tesztelése belső,külső függvényekkel:
    std::cout << "A teszteléshez használt két vektor:" << std::endl;
    std::cout << "u = (1,1), és v = (2,2)" << std::endl;
    std::cout << "\n";
    std::cout << "Az összeadás tesztelése - új vektorral : w = u + v " << std::endl;
    Vector2<int> u(1, 1);
    Vector2<int> v(2, 2);
    Vector2<int> w = u + v;
    std::cout << "w = (" << w.x << ", " << w.y << ")" << std::endl;
    std::cout << "Az összeadás tesztelése - módosítással : w += u " << std::endl;
    w += u;
    std::cout << "w = (" << w.x << ", " << w.y << ")" << std::endl;

    // A kivonás tesztelése belső,külső függvényekkel:
    std::cout << "\n";
    std::cout << "A kivonás tesztelése - új vektorral: w2 = u - v " << std::endl;
    Vector2<int> w2 = u - v;
    std::cout << "w2 = (" << w2.x << ", " << w2.y << ")" << std::endl;
    std::cout << "A kivonás tesztelése - módosítással : w -= u " << std::endl;
    w2 -= u;
    std::cout << "w2 = (" << w2.x << ", " << w2.y << ")" << std::endl;

    // Hossz számítás tesztelése:
    std::cout << "\n";
    std::cout << "A hossz számítás tesztelésére a v = (2,2)-vektort használtam," << std::endl;
    std::cout << "melynek hossza így:  |v| = " << length(v) << std::endl;

    // A hossz négyzetének tesztszámolása:
    std::cout << "\n";
    std::cout << "A hossz négyzeténeks tesztelésére  a v = (2,2)-vektort használtam," << std::endl;
    std::cout << "melynek hossza így:  |v|^2 = " << sqlength(v) << std::endl;

    // Normalizálás tesztelése:
    std::cout << "\n";
    std::cout << "A normalizálás tesztelésére szintén v = (2,2)-vektort használtam." << std::endl;
    Vector2<double> normalized_v = normalized(v);
    std::cout << "A normalizált vektor így: vnorm = (" << normalized_v.x << ',' << normalized_v.y << ")" << std::endl;
    std::cout << "\n";

    // Skalárral szorzás - külső/belső függvények:
    Vector2<int> v_scalar_int(2, 2);
    Vector2<double> v_scalar_double(1.5, 1.5);
    std::cout << "A skalárral szórzás tesztelése  a v_scalar_int = (2,2), valamint a v_scalar_double = (1.5,1.5) vektorokat hívtam segítségül." << std::endl;
    // Jobbról szorzás:
    std::cout << "\n";
    std::cout << "Jobbról szorzás:" << std::endl;
    std::cout << "Az elsőt 2-vel, míg a másodikat 2.5-el szoroztam:" << std::endl;
    Vector2<int> v_right_int = v_scalar_int * 2;
    Vector2<double> v_right_double = v_scalar_double * 2.5;
    std::cout << "v_right_int= (" << v_right_int.x << ',' << v_right_int.y << ")" << std::endl;
    std::cout << "v_right_double= (" << v_right_double.x << ',' << v_right_double.y << ")" << std::endl;
    std::cout << "\n";
    // Balról szórzás:
    std::cout << "Balról szorzás:" << std::endl;
    std::cout << "Az elsőt 3-al, míg a másodikat 3.5-el szoroztam:" << std::endl;
    Vector2<int> v_left_int = v_scalar_int * 3;
    Vector2<double> v_left_double = v_scalar_double * 3.5;
    std::cout << "v_left_int= (" << v_left_int.x << ',' << v_left_int.y << ")" << std::endl;
    std::cout << "v_right_double= (" << v_left_double.x << ',' << v_left_double.y << ")" << std::endl;
    // Belső - skalárral szorzás - vektor módosítással:
    std::cout << "\n";
    std::cout << "Skalárral szorzás - vektor módosítással:" << std ::endl;
    std::cout << "Az elsőt 4-el, míg a másodikat 4.5-el szoroztam:" << std::endl;
    v_scalar_int *= 4;
    v_scalar_double *= 4.5;
    std::cout << "v_scalar_int= (" << v_scalar_int.x << ',' << v_scalar_int.y << ")" << std::endl;
    std::cout << "v_scalar_double= (" << v_scalar_double.x << ',' << v_scalar_double.y << ")" << std::endl;

    // Skalárral osztás - külső függvény
    std::cout << "\n";
    Vector2<int> v_divide_int(4, 4);
    Vector2<double> v_divide_double(6.5, 6.5);
    std::cout << "A skalárral osztás teszteléséhez  a v_divide_int = (4,4), valamint a v_divide_double = (6.5,6.5) definiáltam." << std::endl;
    std::cout << "Az elsőt 2-vel, míg a másodikat 2.5-el osztottam:" << std::endl;
    Vector2<int> v_final_int = v_divide_int / 2;
    Vector2<double> v_final_double = v_divide_double / 2.5;
    std::cout << "v_final_int= (" << v_final_int.x << ',' << v_final_int.y << ")" << std::endl;
    std::cout << "v_final_double= (" << v_final_double.x << ',' << v_final_double.y << ")" << std::endl;
    // Belső skalárral osztás - vektor módosítással:
    std::cout << "\n";
    std::cout << "Skalárral osztás - vektor módosítással:" << std ::endl;
    std::cout << "Az elsőt 4-el, míg a másodikat 4.5-el osztottam:" << std::endl;
    v_divide_int /= 4;
    v_divide_double /= 4.5;
    std::cout << "v_divide_int= (" << v_divide_int.x << ',' << v_divide_int.y << ")" << std::endl;
    std::cout << "v_divide_double= (" << v_divide_double.x << ',' << v_divide_double.y << ")" << std::endl;

    // Skalárszorzás:
    std::cout << "\n";
    std::cout << "A skalár szorzás teszteléséhez használt vektorok: test_v1 = (5,5), test_v2 = (10,10)" << std::endl;
    Vector2<int> test_1(5, 5);
    Vector2<int> test_2(10, 10);
    int test_result = dot(test_1, test_2);
    std::cout << "A skalárszorzat erdménye: " << test_result << std::endl;
}
