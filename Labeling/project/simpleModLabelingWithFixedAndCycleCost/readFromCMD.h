#include<string>
#include<iostream>

bool readFromCmd(int argc, char* argv[], bool& fullSearch, bool& givenFirstMatrix,
    int& SEED, int& START, int& END, int& MAX_CIRC, int& NUMBER_OF_ATTEMPTS_FOR_FIRST_MATRIX, int& NUMBER_OF_ATTEMPTS_FOR_ONE_STEP,
    int& VARIABLE_NODES, int& CHECK_NODES, std::string& INPUT_FILENAME, bool& FIXED_VALUES, int& UP_GIRTH, bool& DISCRETE_LIFTING, double& LIFT_PEN);
