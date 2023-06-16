#include <fmt/format.h>
#include "files.h"
#include <iostream>
#include "microtensor.h"
int main() {
    auto names = io::read_text_file("data/names.txt");
    auto a = microtensor::Tensor<float>::rand_normal_distrubution({4 ,1});
    auto b = microtensor::Tensor<float>::rand_normal_distrubution({4 ,1});
    std::cout << a << '\n';
    std::cout << b << '\n';

    a += b;
    std::cout << a << '\n';
}       