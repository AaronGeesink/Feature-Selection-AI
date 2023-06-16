#include "../include/load.h"
#include "../include/featureselection.h"

using namespace Load;
using namespace FeatureSelection;

int main() {
	string choice = "0";
 	vector<vector<double>> data;

	cout << "Welcome to the Geesink Twins' Feature Selection algorithm\n";

	while(data.size() == 0){
		string filename;
		cout << "Type in the name of the file to test: ";
		cin >> filename;
		data = loadFile(filename);
	}
	

	cout << "\nType the number of the algorithm you want to run\n";
	cout << "1. Forward Selection\n";
	cout << "2. Backward Selection\nChoice: ";
	Algorithm algorithm;

	while(choice == "0") {
		cin >> choice;
		if(choice == "1")
			algorithm == FORWARD;
		else if(choice == "2")
			algorithm = BACKWARD;
		else {
			cout << "Please input a valid choice";
			choice = "0";
		}
	}

	int sampleDivisor = 1;
	cout << "\nChoose the integer amount you would like to divide the data by for your sample\n";
	cout << "1 = Sample all data\n";
	cout << "2 = Sample half the data\n";
	cout << "4 = Sample a quarter of the data\n";
	cout << "Or provide your own decimal divisor\n";
	cout << "Choice: ";
	cin >> sampleDivisor;

	vector<vector<double>> sampledData = sampleData(data, sampleDivisor); // sample part of the data

	int numFolds;

	cout << "\nHow many folds would you like for k-fold cross validation?\n";
	cout << "1. n folds\n";
	cout << "2. n/2 folds\n";
	cout << "3. Custom amount\n";
	cout << "Choice: ";
	cin >> choice;

	if (choice == "1")
		numFolds = sampledData.size();
	else if (choice == "2")
		numFolds = sampledData.size()/2;
	else if (choice == "3") {
		cout << "Please provide the integer number of folds: ";
		cin >> numFolds;
	}

	// find the default leave-one-out accuracy
	int numFeatures = data[0].size()-1;
	set<int> leaveOneOutFeatures;
	if (algorithm = FORWARD) {
		for (int i = 1; i < numFeatures; i++) {
			leaveOneOutFeatures.insert(i);
		}
	}
	else
		leaveOneOutFeatures.insert(numFeatures);

	double leaveOneOutAccuracy = kFoldCrossValidation(sampledData.size(), sampledData, leaveOneOutFeatures, numFeatures, algorithm);
	cout << std::fixed << "\n\nRunning nearest neighbor with all " << numFeatures
		<< " features, using \"leave-one-out\" evaluation, I get an accuracy of " << std::setprecision(3) << leaveOneOutAccuracy*100 << "%\n\n"; 

	set<int> relevantFeatures = featureSearch(sampledData, numFolds, algorithm);

	return 0;
}