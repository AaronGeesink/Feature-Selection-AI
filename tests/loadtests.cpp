#include "gtest/gtest.h"
#include "../header/load.h"
#include <string>

using namespace std;
using namespace load;


TEST(LoadTests, IEEE1) {
	string ieeeString = "2.0000000e+000";

    double result = ieeeStringToDouble(ieeeString);
	EXPECT_EQ(result, 2);
}

TEST(LoadTests, IEEE2) {
	string ieeeString = "4.5645400e+010";

    double result = ieeeStringToDouble(ieeeString);
	EXPECT_EQ(result, 45645400000);
}

TEST(LoadTests, IEEE3) {
	string ieeeString = "4.5645400e+003";

    double result = ieeeStringToDouble(ieeeString);
	EXPECT_EQ(result, 4564.54);
}