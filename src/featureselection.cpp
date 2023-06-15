#include "../include/featureselection.h"
using namespace FeatureSelection;

float kFoldCrossValidation(int k, vector<vector<double>> &data, vector<int> &currentSet, int featureToAdd) {
	// TODO: implement k fold cross validation (current implementation is a stub)
	return static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/100));
}