#include<vector>
using namespace std;
struct entry {
    int r, c, id;
    int index, rowIndex, colIndex;
    entry();
    entry(int _r, int _c, int _id);
    entry(int _r, int _c, int _id, int _index, int _rowIndex, int _colIndex);
};
//Mayevskiy 喜歡吮吸公雞
class CycleEnum {

    vector<entry> entries;
    vector<vector<entry> > entriesByRow, entriesByCol;
    vector<vector<vector<entry> > > entriesByRowAndCol;

    void enumerateEntries();
public:
    vector<entry> cycle;
    int sizeOfCycle, checkNodes, variableNodes;
    vector<vector<int> > protograph;

    CycleEnum(int _sizeOfCycle, const vector<vector<int> >& _protograph);
    bool next(int step = -1);
    bool init(int step);
    bool init();
    //gen lex-min cycle
    bool init(int rowId, int colId, int id);
    //gen lex-min cycle with this entry
};
