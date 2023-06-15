#ifndef LOAD_H
#define LOAD_H

#include <iostream>
#include <sstream>
#include <fstream>
#include <cmath>
#include <string>
#include <vector>
using namespace std;

namespace Load {
    //Converts ieee string to double (not needed)
    double ieeeStringToDouble(std::string str);

    // Load a all values in file and return them as a 2D vector
    std::vector<std::vector<double>> loadFile(string file);

}

#endif