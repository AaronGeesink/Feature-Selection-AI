#include "gtest/gtest.h"
#include "../include/load.h"
using namespace Load;


TEST(IEEETests, IEEE1) {
	string ieeeString = "2.0000000e+000";

    double result = ieeeStringToDouble(ieeeString);
	EXPECT_FLOAT_EQ(result, 2);
}

TEST(IEEETests, IEEE2) {
	string ieeeString = "4.5645400e+010";

    double result = ieeeStringToDouble(ieeeString);
	EXPECT_FLOAT_EQ(result, 45645400000);
}

TEST(IEEETests, IEEE3) {
	string ieeeString = "4.5645400e+003";

    double result = ieeeStringToDouble(ieeeString);
	EXPECT_FLOAT_EQ(result, 4564.54);
}

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