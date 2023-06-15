#include "../include/load.h"
using namespace Load;

double Load::ieeeStringToDouble(std::string str) {
	// Extracting the significand and exponent parts from the string
	size_t ePos = str.find('e');
	string significandStr = str.substr(0, ePos);
	string exponentStr = str.substr(ePos + 1);

	// Converting the significand and exponent strings to double values
	istringstream significandIss(significandStr);
	istringstream exponentIss(exponentStr);
	double significand, exponent;
	significandIss >> significand;
	exponentIss >> exponent;

	// Calculating the final value
	return significand * pow(10, exponent);
}

// Load a all values in file and return them as a 2D vector
vector<vector<double>> Load::loadFile(string file) {
	vector<vector<double>> data;
	ifstream inputFile(file);
	if (!inputFile) {
		cout << "Failed to open the file." << "\n";
		return data;
	}

	string line;
	while (getline(inputFile, line)) {
		istringstream iss(line);
		vector<double> row;

		double value;
		while (iss >> value) {
			row.push_back(value);
		}
		data.push_back(row);
	}

	return data;
}

// Sample a subset of the loaded data.
// The original data is shuffled, and then a subset of it is sampled based on the sampleDivisor
// Larger sampleDivisor means a smaller sample size
vector<vector<double>> Load::sampleData(vector<vector<double>> data, double sampleDivisor) {
	
	// randomly shuffle the data
	auto rng = default_random_engine {};
	shuffle(data.begin(), data.end(), rng);

	// divide the dataset into a number of subsets equal to SampleDivisor, and grab the first subset.
	if(sampleDivisor > data.size())
		sampleDivisor = data.size();

	vector<vector<double>> sampledData;
	int sampleSize = data.size() / sampleDivisor;

	for (int i = 0; i < sampleSize; i++) {
		sampledData.push_back(data[i]);
	}
	return sampledData;
}