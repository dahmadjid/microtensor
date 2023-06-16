#pragma once
#include <cstddef>
#include <iostream>
#include <fmt/format.h>
#include <vector>
#include <random>

namespace microtensor {

template<typename T>
class Tensor {  
public:
    std::vector<T> m_data;
    std::vector<int> m_dimensions;
    
    Tensor(const std::vector<T>& data, const std::vector<int>& dimensions) {
        m_data = data;
        m_dimensions = dimensions;
    }
    
    Tensor(std::vector<T>&& data, std::vector<int>&& dimensions) noexcept {
        m_data = std::forward<std::vector<T>>(data);
        m_dimensions = std::forward<std::vector<int>>(dimensions);
    }   

    static Tensor with_initial_value(const std::vector<int>& dimensions, const T& initial_value) {
        int size = 1; 
        for (int dim: dimensions) {
            size *= dim;
        }
        return Tensor(std::vector<T>(size, initial_value), dimensions);
    }

    static Tensor zeros(const std::vector<int>& dimensions) {
        return with_initial_value(dimensions, static_cast<T>(0));
    }

    static Tensor rand_normal_distrubution(const std::vector<int>& dimensions) {
        std::random_device device {};
        std::mt19937 generator {device()};

        // mean of 0 and variance of 1
        std::normal_distribution<double> standard_normal_distribution {0, 1};
        int size = 1; 
        for (int dim: dimensions) {
            size *= dim;
        }
        auto data = std::vector<T>(size);
        for (size_t i = 0; i < data.size(); i++) {
            data[i] = static_cast<T>(standard_normal_distribution(generator));
        }
        return Tensor(data, dimensions);
    }

    Tensor(const Tensor& t) = default;
    Tensor& operator=(const Tensor& t) = default;
    Tensor(Tensor&& t) = default;
    Tensor& operator=(Tensor&& t) = default;
    

    Tensor& operator+=(const Tensor& rhs) {
        if (m_data.size() < rhs.m_data.size()) {
            for (size_t i = 0; i < m_data.size(); i++) {
                m_data[i] += rhs.m_data[i];
            }
        } else {
            for (size_t i = 0; i < rhs.m_data.size(); i++) {
                m_data[i] += rhs.m_data[i];
            }
        }
        return *this;
    }

    Tensor operator+(const Tensor& rhs) {
        Tensor new_tensor = Tensor(*this);
        new_tensor += rhs;
        return new_tensor;
    };
    
    friend Tensor operator+(const Tensor& lhs, const Tensor& rhs) {
        return lhs + rhs;
    }
    
    Tensor operator*(const Tensor& rhs) {
        
    };

    friend Tensor operator*(const Tensor& lhs, const Tensor& rhs) {
        return lhs * rhs;
    }

    Tensor& operator-=(const Tensor& rhs) {
         if (m_data.size() < rhs.m_data.size()) {
            for (size_t i = 0; i < m_data.size(); i++) {
                m_data[i] -= rhs.m_data[i];
            }
        } else {
            for (size_t i = 0; i < rhs.m_data.size(); i++) {
                m_data[i] -= rhs.m_data[i];
            }
        }
        return *this;
    }

    Tensor operator-(const Tensor& rhs) {
        Tensor new_tensor = Tensor(*this);
        new_tensor -= rhs;
        return new_tensor;
    };

    friend Tensor operator-(const Tensor& lhs, const Tensor& rhs) {
        return lhs - rhs;
    }

    Tensor& operator/=(const Tensor& rhs) {
        if (m_data.size() < rhs.m_data.size()) {
            for (size_t i = 0; i < m_data.size(); i++) {
                m_data[i] /= rhs.m_data[i];
            }
        } else {
            for (size_t i = 0; i < rhs.m_data.size(); i++) {
                m_data[i] /= rhs.m_data[i];
            }
        }
        return *this;
    }

    Tensor operator/(const Tensor& rhs) {
        Tensor new_tensor = Tensor(*this);
        new_tensor /= rhs;
        return new_tensor;
    };
    friend Tensor operator/(const Tensor& lhs, const Tensor& rhs) {
        return lhs / rhs;
    }


    friend bool operator==(const Tensor& lhs, const Tensor& rhs) { 
        if (lhs.m_data.size() != rhs.m_data.size()) {
            return false;
        }
        if (lhs.m_dimensions.size() != rhs.m_data.size()) {
            return false;
        }
        return lhs.m_data == rhs.m_data;
    }

    friend bool operator!=(const Tensor& lhs, const Tensor& rhs) {
        return !(lhs == rhs);
    }

    Tensor& element_wise_multiply(const Tensor& rhs) {
        if (m_data.size() < rhs.m_data.size()) {
            for (size_t i = 0; i < m_data.size(); i++) {
                m_data[i] *= rhs.m_data[i];
            }
        } else {

            for (size_t i = 0; i < rhs.m_data.size(); i++) {
                m_data[i] *= rhs.m_data[i];
            }
        }
        return *this;
    };

    std::string as_string() const {

        std::string output = fmt::format("Shape = ");
        for (size_t j = 0; j < m_dimensions.size(); j++) {
            output+= fmt::format("{}, ", m_dimensions[j]);
        }
        output += "\n";

        std::vector<int> dims_extended = m_dimensions;
        for (int j = m_dimensions.size() - 2; j >= 0 ; j--) {
            dims_extended[j] *= dims_extended[j + 1];
        }


        for (size_t i = 0; i < m_data.size(); i++) {
            std::vector<int> dim_modulos(m_dimensions.size()); 
            
            for (size_t j = 0; j < m_dimensions.size(); j++) {
                dim_modulos[j] = (i % dims_extended[j]);
            }
            output += fmt::format("{}", m_data[i]);

            if (dim_modulos[dim_modulos.size() - 1] == dims_extended[dims_extended.size() -1] -1 ) {
                output += "\n";
                for (size_t j = 1; j < dim_modulos.size() -1; j++) {
                    if (dim_modulos[j] == dims_extended[j] - 1) {
                        output += "\n";
                    }
                }
            } else {
                output += ", ";
            }
        }
        return output.substr(0, output.size() - m_dimensions.size() + 1);
    }


    friend std::ostream& operator<<(std::ostream &os, Tensor const &t) {
        return os << t.as_string();
    }

    Tensor operator[](int index) {
        if (m_dimensions.size() == 1) {
            return Tensor({m_data[index]}, {1});
        }
        int new_size = 1;
        std::vector<int> new_dimension(m_dimensions.size() - 1);
        for (size_t i = 0; i < new_dimension.size(); i++) {
            new_dimension[i] = m_dimensions[i+1];
            new_size *= new_dimension[i];
        }
        std::vector<T> new_data(new_size);
        std::cout << new_size << ">>>>>>>>>>\n";
        for (int i = 0; i < new_size; i++) {
            new_data[i] = m_data[i + index * new_size];
        }
        return Tensor(new_data, new_dimension);
    }
};
}