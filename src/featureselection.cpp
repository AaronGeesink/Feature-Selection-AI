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
        for (int j = 1; j < numCols; j++) {
            if (zeroColumns[j]) {
                //erase(data[i][j]); // Maybe useful for optimization
				data[i][j] = 0;
            }
        }
    }

	// //Print the loaded data
	// for (const auto& row : data) {
	//     for (const auto& value : row) {
	//         std::cout << value << " ";
	//     }
	//     std::cout << "\n";
	// }
}

float FeatureSelection::kFoldCrossValidation(int k, vector<vector<double>> &dataSet, set<int> &currentSet, int featureToAdd) {
	vector<vector<double>> data = dataSet;
	set<int> consideredFeatures = currentSet;
	consideredFeatures.insert(featureToAdd);
	
	setColumnsToZero(data, consideredFeatures);

	for(int i = 0; i < data.size(); i++) {
		data[i][featureToAdd] = 0;
	}

	int numberCorrectlyClassified = 0;

	for(int i = 0; i < data.size(); i++) {
		vector<double> objectToClassify = data[i];
		int labelOfObjectToClassify = data[i][0];

		nearestNeighborDistance = 999999999;
		nearestNeighborLocation = 999999999;

		for(int i = 0; i < data.size(); i++) {
			// Calculate the distance from this object to all other objects
		}
	}

	return rand() / (float)RAND_MAX;
}