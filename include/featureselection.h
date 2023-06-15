#ifndef FEATURE_SELECTION_CPP
#define FEATURE_SELECTION_CPP

#include <vector>
#include <random>
using namespace std;

namespace FeatureSelection {
	float kFoldCrossValidation(int k, vector<vector<double>> &data, vector<int> &currentSet, int featureToAdd);
}

#endif