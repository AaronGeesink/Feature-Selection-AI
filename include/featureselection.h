#ifndef FEATURE_SELECTION_CPP
#define FEATURE_SELECTION_CPP

#include <vector>
#include <set>
#include <algorithm>
#include <iterator>
#include <iostream>
#include <cmath>
#include <string>
using namespace std;

namespace FeatureSelection {
	string printFeatures(set<int> &featureSet, int newFeature);
	string printFeatures(set<int> &featureSet);
	set<int> featureSearch(vector<vector<double>> &data);
	double kFoldCrossValidation(int k, vector<vector<double>> &dataSet, set<int> &currentSet, int featureToAdd);
	void setColumnsToZero(vector<vector<double>>& data, set<int>& consideredFeatures);
	double calculateDistance(const std::vector<double>& v1, const std::vector<double>& v2);
}

#endif