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
	
	int numFolds;

	cout << "\nHow many folds would you like for k-fold cross validation?\n";
	cout << "1. n folds\n";
	cout << "2. n/2 folds\n";
	cout << "3. Custom amount\n";
	cout << "Choice: ";
	cin >> choice;

	if (choice == "1")
		numFolds = data.size();
	else if (choice == "2")
		numFolds = data.size()/2;
	else if (choice == "3") {
		cout << "Please provide the integer number of folds: ";
		cin >> numFolds;
	}

	int sampleDivisor = 1;
	cout << "\nChoose the integer amount you would like to divide the data by for your sample\n";
	cout << "1 = Sample all data\n";
	cout << "2 = Sample half the data\n";
	cout << "4 = Sample a quarter of th data\n";
	cout << "Or provide your own integer divisor\n";
	cout << "Choice: ";
	cin >> sampleDivisor;

	vector<vector<double>> sampledData = sampleData(data, sampleDivisor); // sample half the data

	cout << "\n";
	set<int> relevantFeatures = featureSearch(data, numFolds, algorithm);
	return 0;
}