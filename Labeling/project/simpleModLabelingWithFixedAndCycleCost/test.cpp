#include"test.h"
#include<vector>
#include<ctime>
#include<map>
#include"initMtr.h"
#include"getGirthAndSmth.h"
#include"initAuxilaryVariables.h"
#include"print.h"
#include"doubleCirc.h"
using namespace std;
#define ll long long
#define pii pair<int, int>
#define pll pair<ll, ll>
//Mayevskiy 喜歡吮吸公雞 Gandon
/*
void test() {
    bool fullSearch = 0;
    int VARIABLE_NODES = 6;
    int CHECK_NODES = 3;
    vector<vector<int> > PROTOGRAPH(CHECK_NODES, vector<int>(VARIABLE_NODES, 1));
    int LOWER_BOUND = 4;
    int UPPER_BOUND = 512;
    int NUMBER_OF_ATTEMPTS_FOR_FIRST_MATRIX = 1000;
    int NUMBER_OF_ATTEMPTS_FOR_ONE_STEP = 1000000;
    vector<vector<int> > mtr;
    time_t start = time(NULL);
    srand(321);
    int VERTICES = CHECK_NODES * VARIABLE_NODES;
    int EIRA = 0;
    vector<pii> EIRACycle(0);
    map<pii, int> index;
    vector<pii> invIndex;
    evaluateIndex(PROTOGRAPH, VARIABLE_NODES, CHECK_NODES, index, invIndex);

    vector<vector<pii> > sparse;

    mtr = initMtr(PROTOGRAPH, LOWER_BOUND, NUMBER_OF_ATTEMPTS_FOR_FIRST_MATRIX, fullSearch);

    int balancedCycles = 0;
    pll curRes = getGirthAndCycles(mtr, LOWER_BOUND, PROTOGRAPH, sparse, index, VERTICES, balancedCycles);
    int curCirc = LOWER_BOUND;
    eprint(curCirc, curRes, balancedCycles, VARIABLE_NODES, mtr, start);


    curCirc = LOWER_BOUND * 2;
    while (curCirc / 2 < UPPER_BOUND) {
        mtr = guess(mtr, PROTOGRAPH, curCirc, NUMBER_OF_ATTEMPTS_FOR_ONE_STEP, curRes, sparse, index, invIndex, VERTICES, curRes.first, balancedCycles, EIRA, EIRACycle);
        eprint(curCirc, curRes, balancedCycles, VARIABLE_NODES, mtr, start);
        curCirc *= 2;
    }

    cout << VARIABLE_NODES << "\t" << CHECK_NODES << "\t" << LOWER_BOUND << "-" << UPPER_BOUND << endl;
    print(mtr);
    cout << endl;
}*/

//void testLift() {
//    bool regular = 1;
//    bool fullSearch = 0;
//    bool givenFirstMatrix = 0;
//    ll SEED = 321;
//    //vector<vector<int> > PROTOGRAPH;
//    ll LOWER_BOUND = 37;
//    ll UPPER_BOUND = 592;
//   
//    ll NUMBER_OF_ATTEMPTS_FOR_FIRST_MATRIX = 1;
//    ll NUMBER_OF_ATTEMPTS_FOR_ONE_STEP = 100;
//    ll VARIABLE_NODES = 10;
//    ll CHECK_NODES = 5;
//    ll OVERALL_NUMBER_OF_ITERATIONS = 1;
//    ll NUMBER_OF_SCALING_MULTS = 1;
//    string INPUT_FILENAME = "";
//    
//    int EIRA = 1;//0-nope, 1-EIRA
//    vector<pii> EIRAcycle = { make_pair(0, 5), make_pair(4, 5), make_pair(4, 9), 
//        make_pair(3, 9), make_pair(3, 8), make_pair(2, 8), make_pair(2, 7), make_pair(1, 7), make_pair(1, 6), make_pair(0, 6) };
//    int RA = 0;//0-nope, 1-RA
//
//    /*
//    vector<vector<int> > PROTOGRAPH = {
//            {0, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
//            {0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
//            {1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0},
//            {0, 0, 1, 0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0},
//            {0, 0, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0},
//            {0, 0, 0, 0, 0, 1, 1, 0, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0},
//            {0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0},
//            {0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0},
//            {1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0},
//            {0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0},
//            {1, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1},
//            {0, 0, 1, 0, 0, 1, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1} };*/
//
//    vector<vector<int> > PROTOGRAPH = {
//        { 0, 1, 0, 1, 1, 1, 1, 0, 0, 0 },
//        { 0, 0, 0, 1, 1, 0, 1, 1, 0, 0 },
//        { 1, 0, 0, 0, 1, 1, 0, 1, 1, 0 },
//        { 0, 0, 1, 1, 1, 0, 0, 0, 1, 1 },
//        { 0, 0, 1, 0, 1, 1, 0, 0, 0, 1 } };
//        
//
//    srand(315);
//    ll VERTICES = 0;
//    for (int i = 0; i < PROTOGRAPH.size(); ++i)
//        for (int j = 0; j < PROTOGRAPH[i].size(); ++j)
//            VERTICES += PROTOGRAPH[i][j];
//    vector<vector<int> > mtr;
//    /*if (givenFirstMatrix)
//        readGivenMatrix(PROTOGRAPH, VARIABLE_NODES, CHECK_NODES, INPUT_FILENAME, VERTICES, mtr);
//    else
//        initProtograph(PROTOGRAPH, VARIABLE_NODES, CHECK_NODES, INPUT_FILENAME, VERTICES, regular, givenFirstMatrix);*/
//    map<pii, int> index;
//    vector<pii> invIndex;
//    evaluateIndex(PROTOGRAPH, VARIABLE_NODES, CHECK_NODES, index, invIndex);
//
//
//    string folderName, outputFilename;
//    genFolderAndFilename(folderName, outputFilename, VARIABLE_NODES, CHECK_NODES, LOWER_BOUND, UPPER_BOUND, SEED, INPUT_FILENAME, regular, NUMBER_OF_SCALING_MULTS, EIRA, RA);
//
//    time_t start = time(NULL);
//    int iter = 0;
//    int power = 2;
//    while (true) {
//        srand(iter);
//        ++iter;
//        if (iter == power) {
//            cerr << "iteration = " << iter << endl;
//            power *= 2;
//        }
//        //srand(iter);
//        if (!givenFirstMatrix)
//            mtr = initMtr(PROTOGRAPH, LOWER_BOUND, NUMBER_OF_ATTEMPTS_FOR_FIRST_MATRIX, fullSearch);
//        //eprint(mtr);
//
//        if (EIRA) {
//            toEIRA(mtr, VARIABLE_NODES, CHECK_NODES, LOWER_BOUND, EIRAcycle);
//        }
//        //eprint(mtr);
//        vector<vector<pii> > sparse;
//        int balancedCycles = 0;
//        pll curRes = getGirthAndCycles(mtr, LOWER_BOUND, PROTOGRAPH, sparse, index, VERTICES, balancedCycles);
//        int curCirc = LOWER_BOUND;
//
//        //eprint(curCirc, curRes, balancedCycles, VARIABLE_NODES, mtr, start);
//
//        curCirc = curCirc * 2;
//        while (curCirc <= UPPER_BOUND) {
//            mtr = guess(mtr, PROTOGRAPH, curCirc, NUMBER_OF_ATTEMPTS_FOR_ONE_STEP, curRes, sparse, index, invIndex, VERTICES, curRes.first, balancedCycles, EIRA, EIRAcycle);
//            //cerr << curCirc << endl;
//            //eprint(mtr);
//            //cerr << endl;
//
//            //intermediateOutput(folderName, VARIABLE_NODES, CHECK_NODES, curCirc, SEED, INPUT_FILENAME, regular, curRes, balancedCycles, mtr);
//            //eprint(curCirc, curRes, balancedCycles, VARIABLE_NODES, mtr, start);
//            //eprint(mtr);
//            curCirc *= 2;
//        }
//        curCirc /= 2;
//        pll g1 = getGirth(mtr, curCirc, PROTOGRAPH);
//        //eprint(mtr);
//        if (EIRA) {
//            toEIRA(mtr, VARIABLE_NODES, CHECK_NODES, curCirc, EIRAcycle);
//        }
//        if (RA)
//            toRA(mtr, VARIABLE_NODES, CHECK_NODES, curCirc);
//
//        cerr << endl;
//        eprint(mtr);
//        cerr << endl;
//        pll g2 = getGirth(mtr, curCirc, PROTOGRAPH);
//        if (g1 != g2) {
//            cerr << endl;
//            cerr << "1111111111111111111111111\n";
//            cerr << g1.first << " " << g1.second << endl;
//            cerr << g2.first << " " << g2.second << endl;
//            cerr << "iter = " << iter << endl;
//            cerr << endl;
//
//        }
//        pll g = getGirth(mtr, curCirc, PROTOGRAPH);
//        //if (g.first != curRes.first) {
//        //    cerr << endl;
//        //    cerr << "22222222222222222222222222\n";
//        //    cerr << g.first << " " << g.second << endl;
//        //    cerr << curRes.first << " " << curRes.second << endl;
//        //    cerr << "iter = " << iter << endl;
//        //    cerr << endl;
//        //    //break;
//        //}
//    }
//
//}

bool noCyclesOfLength4(const vector<vector<int> >& a, int m) {
    int j = a.size();
    int l = a[0].size();
    for (int r1 = 0; r1 < j; ++r1) {
        for (int r2 = r1 + 1; r2 < j; ++r2) {
            for (int c1 = 0; c1 < l; ++c1) {
                if ((a[r1][c1] == -1) || (a[r2][c1] == -1))
                    continue;
                for (int c2 = c1 + 1; c2 < l; ++c2) {
                    if ((a[r1][c2] == -1) || (a[r2][c2] == -1))
                        continue;
                    if ((a[r1][c1] + a[r2][c2] - a[r1][c2] - a[r2][c1] + 2 * m) % m == 0) {
                        return 0;
                    }
                }
            }
        }
    }
    return 1;
}

