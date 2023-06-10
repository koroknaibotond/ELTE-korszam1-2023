#include <iostream>
#include "matrix.h"

int main()
{
    std::vector<int> datas = {1, 2, 3, 4};
    std::vector<int> datas2 = {5, 6, 7, 8};

    Matrix<int> matrixdefault(4, 4);       // Default konsturktór tesztelése
    Matrix<int> matrixcopy(matrixdefault); // Copy konstuktór tesztelése

    std::cout << " A Default konstruktór mátrixa:" << std::endl;
    matrixdefault.print();
    std::cout << '\n';
    std::cout << "A Copy konstruktór mátrixa:" << std::endl;
    matrixcopy.print();

    std::cout << '\n';
    Matrix<int> movematrix(std::move(matrixcopy)); // ezzel a lépéssel matrixcopyt megszűntetem.
    std::cout << "movematrixba mozgattam a matrixcopy-t \n";
    std::cout << "Ellenőrzés képpen kiiratom a matrixcopy sorainak és oszlopainak számát, hogy valóban megszűnt-e? \n";
    std::cout << "A sorok száma:" << matrixcopy.numRows() << std::endl; // 0,0 - át adott vissza megszűnt a copymatrix
    std::cout << "Az oszlpok száma:" << matrixcopy.numCols() << std::endl;

    std::cout << '\n';
    std::cout << "= operátor ellenőrzése:" << std::endl;
    Matrix<int> matrixtest1(2, 2, datas);  // az 1,2,3,4 ből álló mátrixot
    Matrix<int> matrixtest2(2, 2, datas2); // egyenlővé teszem az 5,6,7,8-ból állóval
    matrixtest1 = matrixtest2;
    matrixtest1.print();

    std::cout << '\n';
    std::cout << "indexelés tesztelése:" << std::endl;
    int value11 = matrixtest1(1, 1); // szokás szerint 0-tól indexelünk.
    std::cout << "A matrixtest11(2,2) értéke így = " << value11 << std::endl;

    std::cout << '\n';
    std::cout << "összeadás tesztelése:" << std::endl;
    Matrix<int> sum = matrixtest1 + matrixtest2;
    sum.print();
    std::cout << '\n';
    std::cout << "kivonás tesztelése:" << std::endl;

    Matrix<int> matrixdiff1(2, 2, datas);
    Matrix<int> matrixtdiff2(2, 2, datas2);
    Matrix<int> diff = matrixdiff1 - matrixtdiff2;
    diff.print();

    std::cout << '\n';
    std::cout << "Skalárral szorzás tesztelése:" << std::endl;
    Matrix<int> product = matrixdefault * 3;
    product.print();

    std::cout << '\n';
    std::cout << "Skalárral osztás tesztelése:" << std::endl;
    std::vector<int> datas3 = {3, 6, 9, 12};
    Matrix<int> divmatrix(2, 2, datas3);
    Matrix<int> divide = divmatrix / 3;
    divide.print();

    std::cout << '\n';
    std::cout << "Mátrixszorzás tesztelése:" << std::endl;
    std::vector<int> testdata1 = {2, 2, 2, 2};
    std::vector<int> testdata2 = {3, 3, 3, 3};
    Matrix<int> dot1(2, 2, testdata1);
    Matrix<int> dot2(2, 2, testdata2);
    Matrix<int> dotfinal = dot1.matrixProduct(dot2);
    dotfinal.print();

    return 0;
}