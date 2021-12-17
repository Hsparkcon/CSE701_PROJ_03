#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <cmath>
#include <numeric>
#include <numbers> // for PI, from C++20
#include <algorithm>
#include <exception>

#define TRACKER(x) std::cout << "Passed Point - " << x << std::endl

void print_vector(std::vector<double> &target_VEC){
    for(const auto &check_ele : target_VEC){
        std::cout << check_ele << '\n';
    }
    std::cout << '\n' << std::endl;
}
