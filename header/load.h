#ifndef LOAD_CPP
#define LOAD_CPP

#include <iostream>
#include <sstream>
#include <cmath>
#include <string>

using namespace std;

namespace load {
    double ieeeStringToDouble(string str) {
        // Extracting the significand and exponent parts from the string
        size_t ePos = str.find('e');
        std::string significandStr = str.substr(0, ePos);
        std::string exponentStr = str.substr(ePos + 1);

        // Converting the significand and exponent strings to double values
        std::istringstream significandIss(significandStr);
        std::istringstream exponentIss(exponentStr);
        double significand, exponent;
        significandIss >> significand;
        exponentIss >> exponent;

        // Calculating the final value
        return significand * pow(10, exponent);
    }
}

#endif