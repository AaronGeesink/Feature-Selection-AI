#include "../include/featureselection.h"
using namespace FeatureSelection;

string FeatureSelection::printFeatures(set<int> &featureSet, int newFeature) {
	string features = "{" + to_string(newFeature);
	if (featureSet.size() != 0)
		features += ",";
	for (auto it = featureSet.begin(); it != featureSet.end();) {
		features += to_string(*it);
		advance(it,1);
		if (it != featureSet.end()) {
			features += ",";
		}
	}
	features += "}";
	return features;
}

string FeatureSelection::printFeatures(set<int> &featureSet) {
	string features = "{";
	for (auto it = featureSet.begin(); it != featureSet.end();) {
		features += to_string(*it);
		advance(it,1);
		if (it != featureSet.end()) {
			features += ",";
		}
	}
	features += "}";
	return features;
}

set<int> FeatureSelection::featureSearch(vector<vector<double>> &data) {
	set<int> currentSetOfFeatures; // this set is used for considering new features
	set<int> bestSetOfFeatures; // This set is used to keep track of the best set of features (in the case of local maxima)
	double bestAccuracyOverall = 0;
	bool accuracyDecreased = false;
	int numFeatures = data.at(0).size()-1;

	cout << "Beginning search.\n\n";

	for (int i = 0; i < numFeatures; i++) {
		int featureToAddThisLevel = -1;
		double bestAccuracyThisLevel = 0; // best accuracy found for this level

		for (int j = 1; j < numFeatures+1; j++) {
			set<int> consideredFeature = {j};
			set<int> intersection;
			set_intersection(currentSetOfFeatures.begin(), currentSetOfFeatures.end(),
							consideredFeature.begin(), consideredFeature.end(), inserter(intersection, intersection.begin()));
			if (intersection.size() == 0) { // if intersection set is empty, the feature is not in the current set
				double currentAccuracy = kFoldCrossValidation(1, data, currentSetOfFeatures, j); // leave one out cross-validation
				cout << "\tUsing feature(s) " << printFeatures(currentSetOfFeatures, j) << " accuracy is " << currentAccuracy << "%\n";

				if (currentAccuracy > bestAccuracyThisLevel) {
					bestAccuracyThisLevel = currentAccuracy;
					featureToAddThisLevel = j;
				}
			} 
		}

		currentSetOfFeatures.insert(featureToAddThisLevel);
		if (bestAccuracyThisLevel > bestAccuracyOverall) {
			bestAccuracyOverall = bestAccuracyThisLevel;
			bestSetOfFeatures.insert(currentSetOfFeatures.begin(), currentSetOfFeatures.end());
			accuracyDecreased = false;
		}
		else if (!accuracyDecreased){
			cout << "\n(Warning, Accuracy has decreased! Continuing search in case of local maxima)";
			accuracyDecreased = true;
		}
		else {
			break;
		}
		cout << "\nFeature set " << printFeatures(currentSetOfFeatures) << " was best, accuracy is " << bestAccuracyThisLevel << "%\n\n";
	}

	cout << "\nFinished search!! The best feature subset is " << printFeatures(bestSetOfFeatures)
		<< ", which has an accuracy of " << bestAccuracyOverall << "%\n\n";
	return bestSetOfFeatures;
}

void FeatureSelection::setColumnsToZero(vector<vector<double>>& data, set<int>& consideredFeatures) {
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
}

// Function to calculate Euclidean distance between two vectors
double FeatureSelection::calculateDistance(const vector<double>& v1, const vector<double>& v2) {
    double distance = 0.0;
    int size = v1.size();
    for (int i = 0; i < size; i++) {
        distance += pow((v1[i] - v2[i]), 2);
    }
	//cout << distance << "\t";
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
	//cout << numberCorrectlyClassified << "\n";
	return numberCorrectlyClassified / (double)data.size();
}