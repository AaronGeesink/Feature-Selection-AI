#include "gtest/gtest.h"
#include "../include/load.h"
#include "../include/featureselection.h"
using namespace Load;
using namespace FeatureSelection;

TEST(KFoldTests, Small32Test) {
	vector<vector<double>> data = loadFile("./data/CS170_small_Data__32.txt");
	vector<int> currentSet = {3,1};
	int featureToAdd = 5;
	float accuracy = kFoldCrossValidation(1, data, currentSet, featureToAdd);
	accuracy = floorf(accuracy*1000)/1000;
	EXPECT_EQ(accuracy, 0.954);
}

TEST(KFoldTests, Small33Test) {
	vector<vector<double>> data = loadFile("./data/CS170_small_Data__33.txt");
	vector<int> currentSet = {8,7};
	int featureToAdd = 3;
	float accuracy = kFoldCrossValidation(1, data, currentSet, featureToAdd);
	accuracy = floorf(accuracy*1000)/1000;
	EXPECT_EQ(accuracy, 0.949);
}

TEST(KFoldTests, Large32Test) {
	vector<vector<double>> data = loadFile("./data/CS170_large_Data__33.txt");
	vector<int> currentSet = {3,7};
	int featureToAdd = 6;
	float accuracy = kFoldCrossValidation(1, data, currentSet, featureToAdd);
	accuracy = floorf(accuracy*1000)/1000;
	EXPECT_EQ(accuracy, 0.963);
}