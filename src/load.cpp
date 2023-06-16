#include "../include/load.h"
using namespace Load;

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