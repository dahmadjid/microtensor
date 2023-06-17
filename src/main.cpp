#include <fmt/format.h>
#include "files.h"
#include "microtensor.h"

int main() {
    auto names = io::read_text_file("data/names.txt");
    auto a = microtensor::Tensor<int>({1, 2, 3, 4, 5, 6} ,{3, 2});
    auto b = microtensor::Tensor<int>({1, 2, 3 ,4, 5,6, 7, 8, 9 ,10 ,11 ,12}, {2, 6});
    std::cout << a << '\n';
    std::cout << b << '\n';
    auto c = a * b;
    std::cout << c << '\n';
}       