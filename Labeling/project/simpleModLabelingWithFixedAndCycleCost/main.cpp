/*
Copyright(c) 2014, Ilya Vorobyev und Vasiliy Usatyuk
All rights reserved.
Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met :
*Redistributions of source code must retain the above copyright
notice, this list of conditions and the following disclaimer.
* Redistributions in binary form must reproduce the above copyright
notice, this list of conditions and the following disclaimer in the
documentation and / or other materials provided with the distribution.
* Neither the name of the <organization> nor the
names of its contributors may be used to endorse or promote products
derived from this software without specific prior written permission.
THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED.IN NO EVENT SHALL <COPYRIGHT HOLDER> BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/



#include<iostream>
#include<vector>
#include<algorithm>
#include<sstream>
#include<ctime>
#include<cassert>
#include<map>
#include<set>
#include<fstream>
#undef NDEBUG
#include <assert.h> 
//#include <windows.h>


#include"print.h"
#include"readFromCMD.h"
#include"typeCasting.h"
#include"randomGen.h"
#include"getGirthAndSmth.h"
#include"comparators.h"
#include"initMtr.h"
#include"initAuxilaryVariables.h"
#include"doubleCirc.h"
#include"test.h"
using namespace std;

#define ll long long
#define pii pair<int, int>

void lift(int VARIABLE_NODES, int CHECK_NODES, int VERTICES, const vector<vector<int> >& PROTOGRAPH, int LOWER_BOUND, int UPPER_BOUND, int MAX_CIRC,
    int NUMBER_OF_ATTEMPTS_FOR_FIRST_MATRIX, int NUMBER_OF_ATTEMPTS_FOR_ONE_STEP, map<pii, int>& index, vector<pii>& invIndex,
    bool fullSearch, bool givenFirstMatrix, const vector<vector<int> >& fixedMtr, time_t& start, vector<vector<int> >& mtr, int& UP_GIRTH, 
    const set<int>& allowedCirculants, double LIFT_PEN) {
    if (!givenFirstMatrix)
        initMtr(mtr, LOWER_BOUND, NUMBER_OF_ATTEMPTS_FOR_FIRST_MATRIX, fullSearch, fixedMtr);

    vector<vector<pii> > sparse;
    vector<double> cycleCosts;
    int inevitableCycles = 0;
    pair<int, double> curRes = getGirthAndCycles(mtr, LOWER_BOUND, PROTOGRAPH, sparse, cycleCosts, index, VERTICES, inevitableCycles, fixedMtr, UP_GIRTH, LIFT_PEN);
    /*vector<int> fixedVector(VERTICES, 0);
    for (int i = 0; i < fixedMtr.size(); ++i) {
    for (int j = 0; j < fixedMtr[i].size(); ++j) {
    if (fixedMtr[i][j])
    fixedVector[index[pii(i, j)]] = 1;
    }
    }*/
    int curCirc = LOWER_BOUND;

    eprint(curCirc, curRes, inevitableCycles, VARIABLE_NODES, mtr, start);

    curCirc = curCirc * 2;
    while (curCirc <= UPPER_BOUND) {
        mtr = guess(mtr, PROTOGRAPH, curCirc, NUMBER_OF_ATTEMPTS_FOR_ONE_STEP, curRes, sparse, cycleCosts, index, invIndex, VERTICES, curRes.first, inevitableCycles, 
            fixedMtr, UP_GIRTH, MAX_CIRC, allowedCirculants, LIFT_PEN);
        //intermediateOutput(folderName, VARIABLE_NODES, CHECK_NODES, curCirc, SEED, INPUT_FILENAME, regular, curRes, balancedCycles, mtr);
        eprint(curCirc, curRes, inevitableCycles, VARIABLE_NODES, mtr, start);
        //eprint(mtr);
        curCirc *= 2;
    }
}

void run(int argc, char* argv[]) {

    //Initialization
    bool fullSearch = 0;
    bool givenFirstMatrix = 0;
    int SEED = -1;
    vector<vector<int> > PROTOGRAPH;
    int START = -1;
    int END = -1;
    int MAX_CIRC = -1;
    int NUMBER_OF_ATTEMPTS_FOR_FIRST_MATRIX = -1;
    int NUMBER_OF_ATTEMPTS_FOR_ONE_STEP = -1;
    int VARIABLE_NODES;
    int CHECK_NODES;
    string INPUT_FILENAME = "";
    int VERTICES = 0;
    bool FIXED_VALUES = 0;
    bool DISCRETE_LIFTING = 0;
    set<int> allowedCirculants;
    int UP_GIRTH = 8;
    double LIFT_PEN = -1;

    if (!readFromCmd(argc, argv, fullSearch, givenFirstMatrix,
        SEED, START, END, MAX_CIRC, NUMBER_OF_ATTEMPTS_FOR_FIRST_MATRIX, NUMBER_OF_ATTEMPTS_FOR_ONE_STEP,
        VARIABLE_NODES, CHECK_NODES, INPUT_FILENAME, FIXED_VALUES, UP_GIRTH, DISCRETE_LIFTING, LIFT_PEN))
        return;


    if (DISCRETE_LIFTING) {
        for (int ind = 0, step = 1, val = 1; ind < 61; ++ind) {
            allowedCirculants.insert(val);
            if (ind + 1 == step * 16)
                step *= 2;
            val += step;
        }
    }
    else {
        for (int i = START; i <= MAX_CIRC; ++i)
            allowedCirculants.insert(i);
    }

    srand(SEED);

    vector<vector<int> > mtr;
    vector<vector<int> > fixedMtr;
    
    readGivenMatrix(PROTOGRAPH, VARIABLE_NODES, CHECK_NODES, INPUT_FILENAME, VERTICES, mtr, FIXED_VALUES, fixedMtr);

    if (FIXED_VALUES == 0) {
        fixedMtr.assign(CHECK_NODES, vector<int>(VARIABLE_NODES, 0));
    }

    
    map<pii, int> index;
    vector<pii> invIndex;
    evaluateIndex(PROTOGRAPH, VARIABLE_NODES, CHECK_NODES, index, invIndex);


    //string folderName, outputFilename; //Mayevskiy 喜歡吮吸公雞
    //genFolderAndFilename(folderName, outputFilename, VARIABLE_NODES, CHECK_NODES, START, END, SEED, INPUT_FILENAME, regular, EIRA, RA);
    string outputFilename = "out_seed" + toStr(SEED);

    time_t start = time(NULL);
    lift(VARIABLE_NODES, CHECK_NODES, VERTICES, PROTOGRAPH, START, END, MAX_CIRC, NUMBER_OF_ATTEMPTS_FOR_FIRST_MATRIX, NUMBER_OF_ATTEMPTS_FOR_ONE_STEP,
        index, invIndex, fullSearch, givenFirstMatrix, fixedMtr, start, mtr, UP_GIRTH, allowedCirculants, LIFT_PEN);


    printAnswer(outputFilename, VARIABLE_NODES, CHECK_NODES, START, END, mtr);

    fclose(stdout);
    return;
}

int main(int argc, char* argv[]) {
    //testLift();
    run(argc, argv);
    return 0;
}
