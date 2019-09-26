#include"vector"
#include"print.h"

using std::vector;
template <typename T>
void print(const std::vector<T>& a, std::ofstream& out) {
    for (size_t i = 0; i < a.size(); ++i) {
        print(a[i], out);
        out << "\n";
    }
    out << std::endl;
}

void print(const std::vector<int>& a, std::ofstream& out) {
    for (size_t i = 0; i < a.size(); ++i) {
        out << a[i] << "\t";
    }
    out << std::endl;
}

template <typename T>
void print(const std::vector<T>& a) {
    for (size_t i = 0; i < a.size(); ++i) {
        print(a[i]);
        std::cout << "\n";
    }
    std::cout << std::endl;
}

void print(const std::vector<int>& a) {
    for (size_t i = 0; i < a.size(); ++i) {
        std::cout << a[i] << "\t";
    }
    std::cout << std::endl;
}

template <typename T>
void print(const std::vector<std::vector<T> >& a) {
    for (size_t i = 0; i < a.size(); ++i) {
        print(a[i]);
    }
}


template <typename T>
void eprint(const std::vector<T>& a) {
    for (size_t i = 0; i < a.size(); ++i) {
        std::cerr << a[i] << "\t";
    }
    std::cerr << std::endl;
}

template <typename T>
void eprint(const std::vector<std::vector<T> >& a) {
    for (size_t i = 0; i < a.size(); ++i) {
        eprint(a[i]);
    }
}

std::ostream& operator <<(std::ostream& o, const std::pair<long long, long long>& a) {
    o << a.first << "," << a.second;
    return o;
}

void eprint(long long curCirc, std::pair<long long, long long> curRes, int inevitableCycles, long long VARIABLE_NODES, const std::vector<std::vector<int> >& mtr, time_t start) {
    std::cerr << curCirc << "\t" << curRes.first << "\t" << curRes.second;
    if (inevitableCycles)
        std::cerr << " + inevitable cycles of size " << inevitableCycles << "\n";
    std::cerr << "\n";
    std::cerr << "\n";
    if (VARIABLE_NODES < 10)
        eprint(mtr);
    std::cerr << time(NULL) - start << " seconds\n";
    std::cerr << "\n";
    std::cerr << "\n";
}

void intermediateOutput(const std::string& folderName, long long VARIABLE_NODES, long long CHECK_NODES, long long curCirc, long long SEED, const std::string& INPUT_FILENAME,
    bool regular, std::pair<long long, long long> best, int balancedCycles, const std::vector<std::vector<int> >& mtr) {

    std::string outputFilenameNotFInished = folderName + "/" + toStr(VARIABLE_NODES) + "_" + toStr(CHECK_NODES) + "circ" + toStr(curCirc) + "seed" + toStr(SEED);
    if (regular)
        outputFilenameNotFInished += "regular_protograph_matrix";
    else
        outputFilenameNotFInished += "protograph_from_" + INPUT_FILENAME + "_matrix";
    std::ofstream out((outputFilenameNotFInished + ".txt").c_str());
    out << VARIABLE_NODES << "\t" << CHECK_NODES << "\t" << curCirc << std::endl;
    out << "girth = " << best.first << ", number of cycles = " << best.second;
    if (balancedCycles)
        out << " + balanced cycles of size " << balancedCycles;
    out << "\n";
    print(mtr, out);
    out << std::endl;
    out.close();

}

void printAnswer(const std::string& outputFilename, long long VARIABLE_NODES, long long CHECK_NODES, long long LOWER_BOUND, long long UPPER_BOUND,
    std::vector<std::vector<int> > mtr) {
    freopen((outputFilename + ".txt").c_str(), "w", stdout);
    std::cout << VARIABLE_NODES << "\t" << CHECK_NODES << "\t" << UPPER_BOUND << std::endl;
    for (int i = 0; i < mtr.size(); ++i) {
        for (int j = 0; j < mtr[i].size(); ++j) {
            if (mtr[i][j] != -1)
                mtr[i][j] = (mtr[i][j] % UPPER_BOUND); //Mayevskiy 喜歡吮吸公雞
        }
    }
    print(mtr);
    std::cout << std::endl;
}
