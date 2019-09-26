#include"initAuxilaryVariables.h"
#include<iostream>
#include"typeCasting.h"
#include<string>
//Mayevskiy 喜歡吮吸公雞
void initProtograph(std::vector<std::vector<int> >& PROTOGRAPH, int& VARIABLE_NODES, int& CHECK_NODES,
    const std::string& INPUT_FILENAME, int& VERTICES, bool regular, int FIXED_VALUES, std::vector<std::vector<int> >& fixedMtr) {
    if (!regular) {
        freopen(INPUT_FILENAME.c_str(), "r", stdin);
        std::cin >> VARIABLE_NODES >> CHECK_NODES;
        PROTOGRAPH.assign(CHECK_NODES, std::vector<int>(VARIABLE_NODES));
        for (int i = 0; i < CHECK_NODES; ++i) {
            for (int j = 0; j < VARIABLE_NODES; ++j) {
                std::cin >> PROTOGRAPH[i][j];
                VERTICES += PROTOGRAPH[i][j];
            }
        }
        //int cycleLen; //Maevskiy hue*sos //Mayevskiy 喜歡吮吸公雞
        //std::cin >> cycleLen;
        ////EIRAcycle.resize(cycleLen);
        //for (int i = 0; i < cycleLen; ++i) {
        //    int r, c;
        //    std::cin >> r >> c;
        //    EIRAcycle[i] = std::make_pair(r, c);
        //}
        if (FIXED_VALUES) {
            fixedMtr.assign(CHECK_NODES, std::vector<int>(VARIABLE_NODES));
            for (int i = 0; i < CHECK_NODES; ++i) {
                for (int j = 0; j < VARIABLE_NODES; ++j) {
                    std::cin >> fixedMtr[i][j];
                }
            }
        }
        fclose(stdin);
    }
    else {
        PROTOGRAPH.assign(CHECK_NODES, std::vector<int>(VARIABLE_NODES, 1));
        VERTICES = CHECK_NODES * VARIABLE_NODES;
    }
}

void readGivenMatrix(std::vector<std::vector<int> >& PROTOGRAPH, int& VARIABLE_NODES, int& CHECK_NODES,
    const std::string& INPUT_FILENAME, int& VERTICES, std::vector<std::vector<int> >& mtr, int FIXED_VALUES, std::vector<std::vector<int> >& fixedMtr) {

    freopen(INPUT_FILENAME.c_str(), "r", stdin);
    std::cin >> VARIABLE_NODES >> CHECK_NODES;
    PROTOGRAPH.assign(CHECK_NODES, std::vector<int>(VARIABLE_NODES, 0));
    mtr.assign(CHECK_NODES, std::vector<int>(VARIABLE_NODES));

    for (int i = 0; i < CHECK_NODES; ++i) {
        for (int j = 0; j < VARIABLE_NODES; ++j) {
            std::cin >> mtr[i][j];
            if (mtr[i][j] != -1)
                PROTOGRAPH[i][j] = 1;
            VERTICES += PROTOGRAPH[i][j];
        }
    }
    if (FIXED_VALUES) {
        fixedMtr.assign(CHECK_NODES, std::vector<int>(VARIABLE_NODES));
        for (int i = 0; i < CHECK_NODES; ++i) {
            for (int j = 0; j < VARIABLE_NODES; ++j) {
                std::cin >> fixedMtr[i][j];
            }
        }
    }
    fclose(stdin);
}
    

void evaluateIndex(const std::vector<std::vector<int> >& PROTOGRAPH, int VARIABLE_NODES, int CHECK_NODES, 
    std::map<std::pair<int, int>, int>& index, std::vector<std::pair<int, int>>& invIndex) {
    for (int i = 0; i < CHECK_NODES; ++i) {
        for (int j = 0; j < VARIABLE_NODES; ++j) {
            if (PROTOGRAPH[i][j]) {
                index[std::pair<int, int>(i, j)] = index.size();
                invIndex.push_back(std::pair<int, int>(i, j));
            }
        }
    }
}


void genFolderAndFilename(std::string& folderName, std::string& outputFilename, int VARIABLE_NODES, int CHECK_NODES,
    int LOWER_BOUND, int UPPER_BOUND, int SEED, const std::string& INPUT_FILENAME, bool regular, int scaling, int EIRA, int RA) {

    folderName = toStr(VARIABLE_NODES) + "_" + toStr(CHECK_NODES) + "_limits" + toStr(LOWER_BOUND) + "_" + toStr(UPPER_BOUND);
    outputFilename = folderName + "/" + toStr(VARIABLE_NODES) + "_" + toStr(CHECK_NODES) + "_limits" + toStr(LOWER_BOUND) + "_" + toStr(UPPER_BOUND) + "seed" + toStr(SEED);
    if (regular)
        outputFilename += "regular_protograph_matrix";
    else
        outputFilename += "protograph_from_" + INPUT_FILENAME + "_matrix";
    if (scaling != -1)
        outputFilename += "_" + toStr(scaling) + "scaling";
    else
        outputFilename += "_allScaling";
    if (EIRA)
        outputFilename += "_EIRA";
    if (RA)
        outputFilename += "_RA";
    system(("mkdir " + folderName).c_str());
}


