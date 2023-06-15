CMAKE_MINIMUM_REQUIRED(VERSION 3.0)
project(feature-selection-ai)

ADD_SUBDIRECTORY(googletest)

ADD_EXECUTABLE(featureSelection
    src/main.cpp
	src/load.cpp
	src/featureselection.cpp
)

ADD_EXECUTABLE(test
    tests/test.cpp
	tests/featureselectiontests.cpp
	tests/loadtests.cpp
	src/load.cpp
	src/featureselection.cpp
)

TARGET_LINK_LIBRARIES(test gtest)
TARGET_COMPILE_DEFINITIONS(test PRIVATE gtest_disable_pthreads=ON)