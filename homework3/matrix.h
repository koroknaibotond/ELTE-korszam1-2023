#include <cmath>
#include <iostream>
#include <vector>

template <typename T>
class Matrix
{
private:
    std::vector<std::vector<T>> data; // 2D vektor az mátrix tárolására
    int rows;                         // elmentem private-ba a sorok és oszlpok számát
    int cols;

public:
    Matrix(int numRows, int numCols)                                              // default konstruktor csak egyesekkel tölti fel, az adott méretet.
        : data(numRows, std::vector<T>(numCols, 1)), rows(numRows), cols(numCols) // inicializálom a sorok és oszlopok számát.
    {
    }

    Matrix(Matrix const &cpy) // copy konstruktor
        : data(cpy.data), rows(cpy.rows), cols(cpy.cols)
    {
    }

    Matrix(Matrix &&mv) // move szemantika
        : data(std::move(mv.data)), rows(mv.rows), cols(mv.cols)
    {
        mv.rows = 0;
        mv.cols = 0;
    }

    Matrix<T> &operator=(Matrix<T> const &cpy) // sima verzió
    {
        if (this != &cpy)
        {
            data = cpy.data;
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
        if (rows != other.rows or cols != other.cols)
        {
            std::cout << ("Dimension mismatch.");
        }

        Matrix<T> sum(rows, cols);

        for (int i = 0; i < rows; ++i)
        {
            for (int j = 0; j < cols; ++j)
            {
                sum.data[i][j] = data[i][j] + other.data[i][j];
            }
        }

        return sum;
    }

    Matrix<T> operator+(Matrix<T> &&other) // jobb érték referencia
    {
        if (rows != other.rows or cols != other.cols)
        {
            std::cout << ("Dimension mismatch.");
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
        if (rows != other.rows or cols != other.cols)
        {
            std::cout << ("Dimension mismatch.");
        }

        Matrix<T> diff(rows, cols);

        for (int i = 0; i < rows; ++i)
        {
            for (int j = 0; j < cols; ++j)
            {
                diff.data[i][j] = data[i][j] - other.data[i][j];
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
                other.data[i][j] -= data[i][j];
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
                result.data[i][j] = data[i][j] * scalar;
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

        return data = std::move(data);
    }

    // skalárral osztás:

    Matrix<T> operator/(const T &scalar) const
    {
        Matrix<T> result(rows, cols);

        for (int i = 0; i < rows; ++i)
        {
            for (int j = 0; j < cols; ++j)
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
                data[i][j] /= scalar;
            }
        }

        return data = std::move(data);
    }

    // Egymással szorzás:
    Matrix<T> matrixProduct(const Matrix<T> &other) const
    {
        if (cols != other.rows)
        {
            std::cout << ("Dimensions mismatch.");
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

        return result;
    }
    /*
    Miután kijelöltük pl az 1 sor első oszlopot, a harmadik for ciklussal végiglépkedünk az első mátrix első sorának elemein
    és felösszegezzük a második mátrix első oszlopának elemeivel, majd haladunk szépen tovább
    */
    Matrix<T> matrixProduct(const Matrix<T> &&other)
    {
        if (cols != other.rows)
        {
            std::cout << ("Dimensions mismatch.");
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

        return data = std::move(result);
    }

        Matrix(int numRows, int numCols, const std::vector<T> &values)
        : data(numRows, std::vector<T>(numCols)), rows(numRows), cols(numCols)
    {
        int index = 0;
        for (int i = 0; i < rows; ++i)
        {
            for (int j = 0; j < cols; ++j)
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
            } // szóközökkel és sortörésekkel kiprinteljük.
            std::cout << std::endl;
        }
    }
};