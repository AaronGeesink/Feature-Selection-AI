#include "gtest/gtest.h"
#include "../include/load.h"
#include "../include/featureselection.h"
using namespace Load;
using namespace FeatureSelection;

TEST(KFoldTests, SimpleDatasetTest) {
	vector<vector<double>> data = {{1,1,1}, {1,2,2}, {1,3,3}, {1,4,4}, {0,6,6}, {0,-1,-1}, {0,-2,-2}, {0,-3,-3}, {0,-4,-4}, {0,-5,-5}};
	set<int> currentSet = {1};
	int featureToAdd = 2;
	double accuracy = kFoldCrossValidation(1, data, currentSet, featureToAdd);
	//cout << accuracy << "\n";
	accuracy = round(accuracy*1000)/1000;
	EXPECT_EQ(accuracy, 0.900);
}

TEST(KFoldTests, Small32Test) {
	vector<vector<double>> data = loadFile("./data/CS170_small_Data__32.txt");
	set<int> currentSet = {3,1};
	int featureToAdd = 5;
	double accuracy = kFoldCrossValidation(1, data, currentSet, featureToAdd);
	//cout << accuracy << "\n";
	accuracy = round(accuracy*1000)/1000;
	EXPECT_EQ(accuracy, 0.954);
}

TEST(KFoldTests, Small33Test) {
	vector<vector<double>> data = loadFile("./data/CS170_small_Data__33.txt");
	set<int> currentSet = {8,7};
	int featureToAdd = 3;
	double accuracy = kFoldCrossValidation(1, data, currentSet, featureToAdd);
	//cout << accuracy << "\n";
	accuracy = round(accuracy*1000)/1000;
	EXPECT_EQ(accuracy, 0.949);
}

TEST(KFoldTests, Large32Test) {
	vector<vector<double>> data = loadFile("./data/CS170_large_Data__32.txt");
	set<int> currentSet = {3,7};
	int featureToAdd = 6;
	double accuracy = kFoldCrossValidation(1, data, currentSet, featureToAdd);
	//cout << accuracy << "\n";
	accuracy = round(accuracy*1000)/1000;
	EXPECT_EQ(accuracy, 0.963);
}

TEST(distanceTests, distanceTest) {
	std::vector<double> v1 = {5.0, 1.0, 1.0, 5.0};
    std::vector<double> v2 = {1.0, 5.0, 5.0, 1.0};
	double distance = calculateDistance(v1, v2);

	EXPECT_EQ(distance, 8);
}