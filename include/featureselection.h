#ifndef FEATURE_SELECTION_CPP
#define FEATURE_SELECTION_CPP

#include <vector>
#include <set>
#include <algorithm>
#include <iterator>
#include <iostream>
#include <cmath>
#include <string>
#include <iomanip>
using namespace std;

namespace FeatureSelection {
	enum Algorithm {FORWARD, BACKWARD};

	string printFeatures(set<int> &featureSet, int newFeature);
	string printFeatures(set<int> &featureSet);
	set<int> featureSearch(vector<vector<double>> &data, int numFolds, Algorithm algo);
	double kFoldCrossValidation(int k, vector<vector<double>> &dataSet, set<int> &currentSet, int featureToChange, Algorithm algo);
	void setColumnsToZero(vector<vector<double>>& data, set<int>& consideredFeatures);
	double calculateDistance(const std::vector<double>& v1, const std::vector<double>& v2);
}

#endif