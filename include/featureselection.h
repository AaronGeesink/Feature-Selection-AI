#ifndef FEATURE_SELECTION_CPP
#define FEATURE_SELECTION_CPP

#include <vector>
#include <random>
#include <set>
#include <algorithm>
#include <iostream>
using namespace std;

namespace FeatureSelection {
	float kFoldCrossValidation(int k, vector<vector<double>> &dataSet, set<int> &currentSet, int featureToAdd);
	void setColumnsToZero(vector<vector<double>>& data, set<int>& consideredFeatures);
}

#endif