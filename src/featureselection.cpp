#include "../include/featureselection.h"
using namespace FeatureSelection;

float FeatureSelection::kFoldCrossValidation(int k, vector<vector<double>> &data, vector<int> &currentSet, int featureToAdd) {
	// TODO: implement k fold cross validation (current implementation is a stub)
	srand(time(0));
	return rand() / (float)RAND_MAX;
}