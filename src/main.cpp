#include <fmt/format.h>
#include "files.h"
#include <iostream>
#include "microtensor.h"
int main() {
    auto names = io::read_text_file("data/names.txt");
    auto a = microtensor::Tensor<int>::with_initial_value({2, 10}, 2);
    auto b = microtensor::Tensor<int>::rand_normal_distrubution({2, 10});

    std::cout << a << '\n';
    std::cout << b << '\n';

    auto c = a.element_wise_multiply(b);
    std::cout << c << '\n';

    std::cout << c[1][0][0];
}       