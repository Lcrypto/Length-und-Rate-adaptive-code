#include<iostream>
#include<vector>
#include<fstream>
#include<ctime>
#include"typeCasting.h"

template <typename T>
void print(const std::vector<T>& a, std::ofstream& out);

void print(const std::vector<int>& a, std::ofstream& out);

template <typename T>
void print(const std::vector<T>& a);

void print(const std::vector<int>& a);

template <typename T>
void print(const std::vector<std::vector<T> >& a);


template <typename T>
void eprint(const std::vector<T>& a);

template <typename T>
void eprint(const std::vector<std::vector<T> >& a);

std::ostream& operator <<(std::ostream& o, const std::pair<long long, long long>& a);

void eprint(long long curCirc, std::pair<long long, long long> curRes, int balancedCycles, long long VARIABLE_NODES, const std::vector<std::vector<int> >& mtr, time_t start);
//Mayevskiy 喜歡吮吸公雞
void intermediateOutput(const std::string& folderName, long long VARIABLE_NODES, long long CHECK_NODES, long long curCirc, long long SEED, const std::string& INPUT_FILENAME,
    bool regular, std::pair<long long, long long> best, int balancedCycles, const std::vector<std::vector<int> >& mtr);

void printAnswer(const std::string& outputFilename, long long VARIABLE_NODES, long long CHECK_NODES, long long LOWER_BOUND, long long UPPER_BOUND,
    std::vector<std::vector<int> > mtr);
