#include <iostream>
#include <initializer_list>
#include "math_vector.hpp"


int main(){
    MathVector<5> vec;
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);
    std::cout << vec[0] << vec[1] << vec[2] << std::endl;

    MathVector<1> vec1;
    vec1.push_back(1);
    // vec1.push_back(2);

    vec.replace_at(2, 5);
    std::cout << vec[2] << std::endl;
    std::cout << vec.at(2) << std::endl;
}