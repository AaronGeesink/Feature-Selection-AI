# Feature-Selection-AI
A program that uses the nearest neighbor algorithm on a dataset with class labels to search for features that are relevant to determining the class labels.

# How to run
This program contains a CmakeLists.txt and uses CMake to build. To build the Feature Selection program, go to the root of the repository in your terminal and use the command `cmake --build . --target featureSelection`, and then use `make`. You can then run your executable using `./featureSelection`

The program accepts relative file paths as well as absolute file paths for the dataset file. To run using the existing datasets within the data directory, use `./data/name_of_dataset.txt`

# Unit Tests
We also created unit tests to test the different algorithms. To run the unit tests, make sure to get the googletest submodule by using `git submodule update --init --recursive`. Then, uses `cmake .` followed by `make` to build the unit test exectuable. run the unit test executable using `./test`
