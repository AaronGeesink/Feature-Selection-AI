#include "../include/load.h"
#include "../include/featureselection.h"

using namespace Load;
using namespace FeatureSelection;

int main() {
	string filename;
	cout << "Welcome to the Geesink Twins' Feature Selection algorithm\n";
	cout << "Type in the name of the file to test: ";
	cin >> filename;
	cout << "\n";

	string algorithm;
	cout << "Type the number of the algorithm you want to run\n";
	cout << "1. Forward Selection\n";
	cout << "2. Backward Selection\nChoice:";
	cin >> algorithm;

	vector<vector<double>> data = loadFile(filename);
	set<int> relevantFeatures = featureSearch(data);
	double accuracy = kFoldCrossValidation(data.size(), data, currentSet, featureToAdd);
	cout << accuracy << "\n";
	//accuracy = floorf(accuracy*1000)/1000;
	return 0;
}