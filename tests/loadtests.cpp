#include "gtest/gtest.h"
#include "../include/load.h"
using namespace Load;


TEST(LoadTests, LoadFile) {
	std::vector<std::vector<double>> data = loadFile("./data/test_data.txt");
	EXPECT_EQ(data[0][1], 12340000000);
	EXPECT_EQ(data[3][2], 3.0045);
}

TEST(SampleTests, SampleFileHalf) {
	vector<vector<double>> data = loadFile("./data/test_data.txt");
	vector<vector<double>> sampledData = sampleData(data, 2);
	
	EXPECT_EQ(sampledData.size(), 2);
}

TEST(SampleTests, SampleFileDecimal) {
	vector<vector<double>> data = loadFile("./data/test_data.txt");
	vector<vector<double>> sampledData = sampleData(data, 1.5);
	
	EXPECT_EQ(sampledData.size(), 3);
}