#include <complex.hpp>

bool testOperatorPlus(){
    Complex complex_num = Complex(1.0);
    Complex complex_num_2 = Complex(2.0);
    complex_num += complex_num_2;
    bool allTrue = false;

    if(complex_num.re == 3.0){
        allTrue = true;
    }
    return allTrue;
}

bool testConstructor(double re, double im){
    Complex complex_num = Complex(re);
    return complex_num.re == re; // только не так сравнивайте, а через epsilon
}

// Комлексное число состоит из действительной части и мнимой
// re == 1.2
// im == 4.3
// complex_number: 1.2 + 4.3i

int main(){
    // желательно тестировать не только на одной паре параметров
    // а рассматривать несколько комбинаций
    // в том числе если есть какие-то особые случаи
    std::cout << (testConstructor(1.2, 4.3) ? "True\n" : "False\n");
    std::cout << (testOperatorPlus() ? "True\n" : "False\n");

}
