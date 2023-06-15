#include "gtest/gtest.h"
#include "../header/load.h"
#include <string>

using namespace load;


TEST(IEEETests, IEEE1) {
	string ieeeString = "2.0000000e+000";

    float result = ieeeStringToDouble(ieeeString);
	EXPECT_FLOAT_EQ(result, 2);
}

TEST(IEEETests, IEEE2) {
	string ieeeString = "4.5645400e+010";

    float result = ieeeStringToDouble(ieeeString);
	EXPECT_FLOAT_EQ(result, 45645400000);
}

TEST(IEEETests, IEEE3) {
	string ieeeString = "4.5645400e+003";

    float result = ieeeStringToDouble(ieeeString);
	EXPECT_FLOAT_EQ(result, 4564.54);
}

TEST(LoadTests, LoadFile) {
	std::vector<std::vector<double>> data = loadFile("/home/csgrads/ggees001/Feature-Selection-AI/data/test_data.txt");
	EXPECT_EQ(data[0][1], 12340000000);
	EXPECT_EQ(data[3][2], 3.0045);
}