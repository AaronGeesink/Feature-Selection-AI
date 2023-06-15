#ifndef LOAD_CPP
#define LOAD_CPP

#include <iostream>
#include <sstream>
#include <fstream>
#include <cmath>
#include <string>

using namespace std;

namespace load {
    //Converts ieee string to double (not needed)
    double ieeeStringToDouble(std::string str) {
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

    // Load a all values in file and return them as a 2D vector
    std::vector<std::vector<double>> loadFile(string file) {
        std::vector<std::vector<double>> data;
        std::ifstream inputFile(file);
        if (!inputFile) {
            std::cerr << "Failed to open the file." << std::endl;
            return data;
        }

        std::string line;
        while (std::getline(inputFile, line)) {
            std::istringstream iss(line);
            std::vector<double> row;

            double value;
            while (iss >> value) {
                row.push_back(value);
            }
            data.push_back(row);
        }

        // Print the loaded data
        // for (const auto& row : data) {
        //     for (const auto& value : row) {
        //         std::cout << value << " ";
        //     }
        //     std::cout << std::endl;
        // }

        return data;
    }

}

#endif