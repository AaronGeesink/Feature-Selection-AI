#ifndef FEATURE_SELECTION_CPP
#define FEATURE_SELECTION_CPP

#include <vector>
#include <set>
#include <random>
#include <iostream>
#include <algorithm>
using namespace std;

namespace FeatureSelection {
	set<int> featureSearch(vector<vector<double>> &data);
	float kFoldCrossValidation(int k, vector<vector<double>> &data, set<int> &currentSet, int featureToAdd);
}

#endif