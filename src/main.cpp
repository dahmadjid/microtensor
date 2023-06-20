#include <fmt/format.h>
#include "files.h"
#include "microtensor.h"
#include <chrono>
using std::chrono::high_resolution_clock;
int main() {
    auto names = io::read_text_file("data/names.txt");
    std::cout << 6816232977 /1000 /1000 << '\n';
    auto now = high_resolution_clock::now();
    auto a = microtensor::Tensor<double>::rand_normal_distrubution({1024, 1024});
    auto b = microtensor::Tensor<double>::rand_normal_distrubution({1024, 1024});
    std::cout << high_resolution_clock::now() - now << "\n";
    // std::cout << a << '\n';
    // std::cout << b << '\n';
    auto now2 = high_resolution_clock::now();
    auto c = a * b;
    std::cout << high_resolution_clock::now() - now2 << "\n";
    // std::cout << c << '\n';
}       