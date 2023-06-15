#ifndef LOAD_H
#define LOAD_H

#include <iostream>
#include <sstream>
#include <fstream>
#include <cmath>
#include <string>
#include <vector>
#include <algorithm>
#include <random>
using namespace std;

namespace Load {
    // Converts ieee string to double (not needed)
    double ieeeStringToDouble(std::string str);

    // Loads all values in file and return them as a 2D vector
    std::vector<std::vector<double>> loadFile(string file);

    // Samples a subset of values from the loaded data
    // Larger sampleDivisor means a smaller sample size
    std::vector<std::vector<double>> sampleData(std::vector<std::vector<double>> data, double sampleDivisor);
}

#endif