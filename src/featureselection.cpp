#include "../include/featureselection.h"
using namespace FeatureSelection;

set<int> FeatureSelection::featureSearch(vector<vector<double>> &data) {
	set<int> currentSetOfFeatures; // this set is used for considering new features
	set<int> bestSetOfFeatures; // This set is used to keep track of the best set of features (in the case of local maxima)
	int numFeatures = data.at(0).size()-1;

	for (int i = 0; i < numFeatures; i++) {
		cout << "On the " << i+1 << "th level of the search tree" << endl;
		int featureToAddThisLevel = -1;
		float bestAccuracySoFar = 0;

		for (int j = 1; j < numFeatures+1; j++) {
			set<int> consideredFeature = {j};
			set<int> intersection;
			set_intersection(currentSetOfFeatures.begin(), currentSetOfFeatures.end(),
							consideredFeature.begin(), consideredFeature.end(), inserter(intersection, intersection.begin()));
			if (intersection.size() == 0) { // if intersection set is empty, the feature is not in the current set
				cout << "Considering adding feature " << j;
				float currentAccuracy = kFoldCrossValidation(1, data, currentSetOfFeatures, j); // leave one out cross-validation
				cout << ", accuracy = " << currentAccuracy << endl;

				if (currentAccuracy > bestAccuracySoFar) {
					bestAccuracySoFar = currentAccuracy;
					featureToAddThisLevel = j;
				}
			} 
		}

		currentSetOfFeatures.insert(featureToAddThisLevel);
		cout << "On level " << i+1 << ", I added feature " << featureToAddThisLevel << " to current set" << endl;
	}

	return currentSetOfFeatures;
}

float FeatureSelection::kFoldCrossValidation(int k, vector<vector<double>> &data, set<int> &currentSet, int featureToAdd) {
	// TODO: implement k fold cross validation (current implementation is a stub)
	return rand() / (float)RAND_MAX;
}