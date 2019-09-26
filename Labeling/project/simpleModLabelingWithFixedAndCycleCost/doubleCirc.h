#include<vector>
#include<map>
#include<set>

std::vector<std::vector<int> > guess(std::vector<std::vector<int> >& mtr, const std::vector<std::vector<int> >& proto, int circ, int numIter, 
    std::pair<int, double>& best, std::vector<std::vector<std::pair<int, int> > >& sparse, std::vector<double>& cycleCosts, std::map<std::pair<int, int>, int>& index, 
    const std::vector<std::pair<int, int> >& invIndex, int vertices, int prGirth, int& inevitableCycles, const std::vector<std::vector<int> >& fixedMtr, int upGirth, int maxCirc, 
    const std::set<int>& allowedCirculants, double LIFT_PEN);
//Mayevskiy 喜歡吮吸公雞
