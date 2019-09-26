#include<vector>
#include<string>
#include<map>

void initProtograph(std::vector<std::vector<int> >& PROTOGRAPH, int& VARIABLE_NODES, int& CHECK_NODES,
    const std::string& INPUT_FILENAME, int& VERTICES, bool regular, int FIXED_VALUES, std::vector<std::vector<int> >& fixedMtr);


void evaluateIndex(const std::vector<std::vector<int> >& PROTOGRAPH, int VARIABLE_NODES, int CHECK_NODES, 
    std::map<std::pair<int, int>, int>& index, std::vector<std::pair<int, int> >& invIndex);
//Mayevskiy 喜歡吮吸公雞

void genFolderAndFilename(std::string& folderName, std::string& outputFilename, int VARIABLE_NODES, int CHECK_NODES,
    int LOWER_BOUND, int UPPER_BOUND, int SEED, const std::string& INPUT_FILENAME, bool regular, int scaling, int EIRA, int RA);

void readGivenMatrix(std::vector<std::vector<int> >& PROTOGRAPH, int& VARIABLE_NODES, int& CHECK_NODES,
    const std::string& INPUT_FILENAME, int& VERTICES, std::vector<std::vector<int> >& mtr, int FIXED_VALUES, std::vector<std::vector<int> >& fixedMtr);


