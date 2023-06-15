#include "../include/featureselection.h"
using namespace FeatureSelection;

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

set<int> FeatureSelection::featureSearch(vector<vector<double>> &data, int numFolds, Algorithm algo) {
	set<int> currentSetOfFeatures; // this set is used for considering new features
	set<int> bestSetOfFeatures; // This set is used to keep track of the best set of features (in the case of local maxima)
	double bestAccuracyOverall = 0;
	bool accuracyDecreased = false;
	int numFeatures = data.at(0).size()-1;

	if (algo == BACKWARD) { // if using backward elimination, fill the initial feature set with all features
		for (int i = 0; i < numFeatures; i++)
		currentSetOfFeatures.insert(i+1);
	}

	cout << "Beginning search.\n\n";
	cout << fixed;

	for (int i = 0; i < numFeatures; i++) {
		int featureToChangeThisLevel = -1;
		double bestAccuracyThisLevel = 0; // best accuracy found for this level

		for (int j = 1; j < numFeatures+1; j++) {
			set<int> consideredFeature = {j};
			set<int> intersection;
			set_intersection(currentSetOfFeatures.begin(), currentSetOfFeatures.end(),
							consideredFeature.begin(), consideredFeature.end(), inserter(intersection, intersection.begin()));
			// If intersection set is empty during forward selection OR size 1 during backward elemination,
			// the feature has not been processed yet
			if ((intersection.size() == 0 && algo == FORWARD) || (intersection.size() == 1 && algo == BACKWARD)) {
				double currentAccuracy = kFoldCrossValidation(numFolds, data, currentSetOfFeatures, j, algo); // k-fold cross-validation

				// display the information about the current feature
				set<int> featuresToDisplay = currentSetOfFeatures;
				if (algo == FORWARD) featuresToDisplay.insert(j);
				else featuresToDisplay.erase(j);
				cout << "\tUsing feature(s) " << printFeatures(featuresToDisplay) << " accuracy is "
					<< setprecision(3) << currentAccuracy*100 << "%\n";

				if (currentAccuracy > bestAccuracyThisLevel) {
					bestAccuracyThisLevel = currentAccuracy;
					featureToChangeThisLevel = j;
				}
			} 
		}
		// add or delete the feature depending on if the algorithm is forward selection or backward elimination
		if (algo == FORWARD)
			currentSetOfFeatures.insert(featureToChangeThisLevel); // forward selection
		else
			currentSetOfFeatures.erase(featureToChangeThisLevel); // backward elimination

		if (bestAccuracyThisLevel > bestAccuracyOverall) {
			bestAccuracyOverall = bestAccuracyThisLevel;
			bestSetOfFeatures = currentSetOfFeatures;
			accuracyDecreased = false;
		}
		else if (!accuracyDecreased){
			cout << "\n(Warning, Accuracy has decreased! Continuing search in case of local maxima)";
			accuracyDecreased = true;
		}
		else {
			break;
		}
		cout << "\nFeature set " << printFeatures(currentSetOfFeatures) << " was best, accuracy is "
			<< setprecision(3) << bestAccuracyThisLevel*100 << "%\n\n";
	}

	cout << "\nFinished search!! The best feature subset is " << printFeatures(bestSetOfFeatures)
		<< ", which has an accuracy of " << setprecision(3) << bestAccuracyOverall*100 << "%\n\n";
	return bestSetOfFeatures;
}

void FeatureSelection::setColumnsToZero(vector<vector<double>>& data, set<int>& consideredFeatures) {
	int numRows = data.size();
    int numCols = data[0].size();
	vector<bool> zeroColumns(numCols, true);

	// If feature exists in consideredFeatures, don't set it to zero.
	for(int i = 1; i < numCols; i++) {
		// If (Value exists in considered Features)
		if (find(consideredFeatures.begin(), consideredFeatures.end(), i) != consideredFeatures.end())
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
    return sqrt(distance);
}

double FeatureSelection::kFoldCrossValidation(int k, vector<vector<double>> &dataSet, set<int> &currentSet, int featureToChange, Algorithm algo) {
	vector<vector<double>> data = dataSet;
	set<int> consideredFeatures = currentSet;
	if (algo == FORWARD)
		consideredFeatures.insert(featureToChange); // forward selection
	else
		consideredFeatures.erase(featureToChange); // backward elimination
	
	setColumnsToZero(data, consideredFeatures);

	int foldSize = data.size() / k;
	int numberCorrectlyClassified = 0;

	for(int m = 0; m < k; m++) { // The fold we are on
		for(int i = 0; i < foldSize; i++) { // The value in the fold we are on
			vector<double> objectToClassify = data[m * foldSize + i];

			double nearestNeighborDistance = 999999999;
			int nearestNeighborIndex = 99999;
			int nearestNeighborLabel = 999;

			for(int j = 0; j < data.size(); j++) {
				if(j >= m * foldSize && j < m * foldSize + foldSize - 1) // Skip the current fold
					continue;
				// Calculate the distance from this object to all other objects
				double distance = calculateDistance(objectToClassify, data[j]);
				if(distance < nearestNeighborDistance && m * foldSize + i != j) {
					nearestNeighborDistance = distance;
					nearestNeighborIndex = j;
					nearestNeighborLabel = dataSet[j][0];
				}
			}
			if(nearestNeighborLabel == dataSet[m * foldSize + i][0])
				numberCorrectlyClassified++;	
		}
	}
	return numberCorrectlyClassified / (double)data.size();
}