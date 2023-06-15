#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <sstream>
#include <fstream>
#include <cmath>
using namespace std;

void setColumnsToZero(vector<vector<double>>& data, set<int>& consideredFeatures) {
	int numRows = data.size();
    int numCols = data[0].size();
	vector<bool> zeroColumns(numCols, true);

	// If feature exists in consideredFeatures, don't set it to zero.
	for(int i = 1; i < numCols; i++) {
		if (find(consideredFeatures.begin(), consideredFeatures.end(), i) != consideredFeatures.end()) // If (Value exists in considered Features)
			zeroColumns[i] = false;
	}

	// Set the columns to zero that are marked in the zeroColumns vector
    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < numCols; j++) {
            if (zeroColumns[j]) {
                //erase(data[i][j]); // Maybe useful for optimization
				data[i][j] = 0;
            }
        }
    }

	//Print the data
	for (const auto& row : data) {
	    for (const auto& value : row) {
	        std::cout << value << " ";
	    }
	    std::cout << "\n";
	}
}

// Function to calculate Euclidean distance between two vectors
double calculateDistance(const vector<double>& v1, const vector<double>& v2) {
    double distance = 0.0;
    int size = v1.size();
    for (int i = 0; i < size; i++) {
        distance += pow((v1[i] - v2[i]), 2);
    }
	//cout << distance << "\t";
    return sqrt(distance);
}

double kFoldCrossValidation(int k, vector<vector<double>> &dataSet, set<int> &currentSet, int featureToAdd) {
	vector<vector<double>> data = dataSet;
	set<int> consideredFeatures = currentSet;
	consideredFeatures.insert(featureToAdd);
	
	setColumnsToZero(data, consideredFeatures);

	int numberCorrectlyClassified = 0;

	for(int i = 0; i < data.size(); i++) {
		vector<double> objectToClassify = data[i];

		double nearestNeighborDistance = 999999999;
		int nearestNeighborIndex = 99999;
		int nearestNeighborLabel = 999;

		for(int j = 0; j < data.size(); j++) {
			// Calculate the distance from this object to all other objects
				//Print the data
				for (int i = 0; i < objectToClassify.size(); i++) {
				    //std::cout << objectToClassify[i] << ", " << data[j][i] << '\t';
				}
			double distance = calculateDistance(objectToClassify, data[j]);
			if(distance < nearestNeighborDistance && i != j) {
				nearestNeighborDistance = distance;
				nearestNeighborIndex = j;
				nearestNeighborLabel = dataSet[j][0];
				//cout << dataSet[j][0] << "\t";
			}
		}
		//cout << dataSet[nearestNeighborIndex][0] << "\t" << dataSet[i][0] << "\t";
		if(nearestNeighborLabel == dataSet[i][0])
			numberCorrectlyClassified++;
	}
	cout << numberCorrectlyClassified << "\n";
	return numberCorrectlyClassified / (double)data.size();
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

int main() {
	vector<vector<double>> data = loadFile("C:\\Users\\rover\\Desktop\\School\\cs205\\Feature-Selection-AI\\data\\CS170_small_Data__33.txt");
	set<int> currentSet = {8,7};
	int featureToAdd = 3;
	double accuracy = kFoldCrossValidation(1, data, currentSet, featureToAdd);
	cout << accuracy << "\n";
	//accuracy = floorf(accuracy*1000)/1000;
	return 0;
}