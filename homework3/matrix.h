#include <cmath>
#include <iostream>
#include <vector>

template <typename T>
class Matrix
{
private:
    std::vector<std::vector<T>> data; // 2D vektor az mátrix tárolására
    int rows;                         // sorok és oszlopok száma
    int cols;

public:
    Matrix(int numRows, int numCols)                                              // default konstruktor csak egyesekkel tölti fel, az adott méretet.
        : data(numRows, std::vector<T>(numCols, 1)), rows(numRows), cols(numCols) // inicializálom a sorok és oszlopok számát.
    {
    }

    Matrix(Matrix const &cpy)                            // copy konstruktor
        : data(cpy.data), rows(cpy.rows), cols(cpy.cols) // A tárolt számok, valamint sorok és oszlopok számának másolása.
    {
    }

    Matrix(Matrix &&mv)                                          // move konstruktor
        : data(std::move(mv.data)), rows(mv.rows), cols(mv.cols) // itt a másolás után az eredeti megszűnik
    {
        mv.rows = 0; // eredetei sorait és oszlopait is kinullázom
        mv.cols = 0;
    }

    Matrix<T> &operator=(Matrix<T> const &cpy) // sima verzió
    {
        if (this != &cpy) // Csak akkor van szükség az elemek másolására, ha eredetileg nem egyeik az = két oldalán szereplő mátrix.
        {
            data = cpy.data; // meg történnek az adatok átmásolásai
            rows = cpy.rows;
            cols = cpy.cols;
        }
        return *this;
    }

    Matrix<T> &operator=(Matrix<T> &&mv) // jobb érték referenciát váró verzió
    {
        if (this != &&mv)
        {
            data = std::move(mv.data);
            rows = mv.rows;
            cols = mv.cols;
        }
        return *this;
    }

    T &operator[](int i)
    {
        return data[i]; // két dimenziós vektorrol beszélünk meghívja az adott sort
    }

    const T &operator[](int i) const
    {
        return data[i];
    }

    T &operator()(int i, int j)
    {
        return data[i][j]; // a második [] már az első visszatért sor referenciáján belüli elemek indexeivel dolgozik.
    }

    const T &operator()(int i, int j) const
    {
        return data[i][j];
    }
    //+ operátor
    Matrix<T> operator+(const Matrix<T> &other) const // klasszikus verzió
    {
        if (rows != other.rows or cols != other.cols) // Ellenőrzöm, hogy egyezik-e a sorok és oszlopok száma a két mátrix esetén.
        {
            std::cout << ("Dimenzió hiba!");
        }

        Matrix<T> sum(rows, cols);

        for (int i = 0; i < rows; ++i) // két for ciklussal végig futok a mátrixon
        {
            for (int j = 0; j < cols; ++j)
            {
                sum.data[i][j] = data[i][j] + other.data[i][j]; // összeadom az értékeket
            }
        }

        return sum;
    }

    Matrix<T> operator+(Matrix<T> &&other) // jobb érték referencia
    {
        if (rows != other.rows or cols != other.cols)
        {
            std::cout << ("Dimenzió hiba!");
        }

        for (int i = 0; i < rows; ++i)
        {
            for (int j = 0; j < cols; ++j)
            {
                other.data[i][j] += data[i][j]; // A + jel jobb oldalán lévő mátrixba összegyűjtőm az összegeket és moveolom a baloldaliba.
            }
        }

        return data = std::move(other.data);
    }
    //- operátor
    Matrix<T> operator-(const Matrix<T> &other) const // klasszikus verzió
    {
        if (rows != other.rows or cols != other.cols) // dimenzió ellenőrzés
        {
            std::cout << ("Dimenzió hiba!");
        }

        Matrix<T> diff(rows, cols);

        for (int i = 0; i < rows; ++i)
        {
            for (int j = 0; j < cols; ++j)
            {
                diff.data[i][j] = data[i][j] - other.data[i][j]; // Kivonások elvégzése
            }
        }

        return diff;
    }

    Matrix<T> operator-(Matrix<T> &&other) // jobb érték referencia
    {
        if (rows != other.rows or cols != other.cols)
        {
            std::cout << ("Dimension mismatch.");
        }

        for (int i = 0; i < rows; ++i)
        {
            for (int j = 0; j < cols; ++j)
            {
                other.data[i][j] -= data[i][j]; // A +operátorhoz hasonlóan a különbségeket egyikbe mentettem, majd mozgattam.
            }
        }

        return data = std::move(other.data);
    }

    // skalárral szorzás:

    Matrix<T> operator*(const T &scalar) const
    {
        Matrix<T> result(rows, cols);

        for (int i = 0; i < rows; ++i)
        {
            for (int j = 0; j < cols; ++j)
            {
                result.data[i][j] = data[i][j] * scalar; // A mátrix összes tagját megszorztam a megadott skalárral.
            }
        }

        return result;
    }

    Matrix<T> operator*(Matrix<T> &&scalar) // jobb érték referencia
    {

        for (int i = 0; i < rows; ++i)
        {
            for (int j = 0; j < cols; ++j)
            {
                data[i][j] *= scalar;
            }
        }

        return data = std::move(data); // itt szintén, csak egy új mátrix létrehozása helyett az eredetibe mozgattam a felszorzott értékeket.
    }

    // skalárral osztás:

    Matrix<T> operator/(const T &scalar) const
    {
        Matrix<T> result(rows, cols);

        for (int i = 0; i < rows; ++i)
        {
            for (int j = 0; j < cols; ++j) // Minden tagot leosztottam a megadott skalárral
            {
                result.data[i][j] = data[i][j] / scalar;
            }
        }

        return result;
    }

    Matrix<T> operator/(Matrix<T> &&scalar) // jobb érték referencia
    {

        for (int i = 0; i < rows; ++i)
        {
            for (int j = 0; j < cols; ++j)
            {
                data[i][j] /= scalar; // Az eredmény kiszámolása után a szokásos mozgatást végeztem el.
            }
        }

        return data = std::move(data);
    }

    // Egymással szorzás:
    Matrix<T> matrixProduct(const Matrix<T> &other) const
    {
        if (cols != other.rows)
        {
            std::cout << ("Dimenzió hiba!");
        }

        Matrix<T> result(rows, other.cols); // létrehozunk egy mátrixot a szorzásnak megfelelő mérettel

        for (int i = 0; i < rows; ++i) // az első mátrix sorain végig lépkedünk
        {
            for (int j = 0; j < other.cols; ++j) // iletve a második mátrix oszlopain
            {
                T sum = 0;
                for (int k = 0; k < cols; ++k) // A harmadik for ciklust arra használjuk, hogy az első mátrix sorain belüli, míg a második mátrix oszlopain belüli elemeken végig lépkedjünk.
                {
                    sum += data[i][k] * other.data[k][j];
                }
                result(i, j) = sum;
            }
        }

        return result;
    }

    Matrix<T> matrixProduct(const Matrix<T> &&other)
    {
        if (cols != other.rows)
        {
            std::cout << ("Dimezió hiba!");
        }

        Matrix<T> result(rows, other.cols); // létrehozunk egy mátrixot a szorzásnak megfelelő mérettel

        for (int i = 0; i < rows; ++i) // az első mátrix sorain végig lépkedünk
        {
            for (int j = 0; j < other.cols; ++j) // iletve a második mátrix oszlopain
            {
                T sum = 0;
                for (int k = 0; k < cols; ++k)
                {
                    sum += data[i][k] * other.data[k][j];
                }
                result(i, j) = sum;
            }
        }

        return data = std::move(result); // Minden pontosan ugyan az, csak az adatok, csak .matrixProduct() kifejezés bal oldalán található mátrixba lesznek moveolva az eredmények
    }

    Matrix(int numRows, int numCols, const std::vector<T> &values)
        : data(numRows, std::vector<T>(numCols)), rows(numRows), cols(numCols)
    {
        int index = 0;
        for (int i = 0; i < rows; ++i)
        {
            for (int j = 0; j < cols; ++j) // soronként töltjük fel.
            {
                data[i][j] = values[index++];
            }
        }
    } // Ezt a függvényt azért hoztam létre, hogy egy tetszőleges külső vektorból vett adatokkal is feltölthessük a mátrixot

    int numRows() const // segédfüggvény copy ellenőrzéshez, és a mátrix inicializálásához megadja a sorok számát
    {
        return rows;
    }

    int numCols() const // ez pedig az oszlopok számát, szintén a copy ellenőrzéséhez
    {
        return cols;
    }

    void print() const // Printelő függvény ellenőrzés végett.
    {
        for (const auto &row : data) // végig futunk a data-ban található vektorokon
        {
            for (const auto &element : row) // valamint annak az
            {
                std::cout << element << " ";
            }                       // szóközök
            std::cout << std::endl; // sortörések elhelyezése.
        }
    }
};