#include "../include/featureselection.h"
using namespace FeatureSelection;

void FeatureSelection::setColumnsToZero(vector<vector<double>>& data, set<int>& consideredFeatures) {
	int numRows = data.size();
    int numCols = data[0].size();
	vector<bool> zeroColumns(numCols, true);

	// If feature exists in consideredFeatures, don't set it to zero.
	for(int i = 1; i < numCols - consideredFeatures.size(); i++) {
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

	// Print the data
	// for (const auto& row : data) {
	//     for (const auto& value : row) {
	//         std::cout << value << " ";
	//     }
	//     std::cout << "\n";
	// }
}

// Function to calculate Euclidean distance between two vectors
double FeatureSelection::calculateDistance(const vector<double>& v1, const vector<double>& v2) {
    double distance = 0.0;
    int size = v1.size();
    for (int i = 0; i < size; i++) {
        distance += pow((v1[i] - v2[i]), 2);
    }
    return sqrt(distance);
}

double FeatureSelection::kFoldCrossValidation(int k, vector<vector<double>> &dataSet, set<int> &currentSet, int featureToAdd) {
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