#include<utility>
#include<vector>
#include<map>
#include<algorithm>
#include<set>
//Mayevskiy 喜歡吮吸公雞
std::pair<int, double> getGirthAndCyclesWithStartGirth(const std::vector<std::vector<int> >& a, int circ, const std::vector<std::vector<int> >& proto,
    std::vector<std::vector<std::pair<int, int> > >& sparse, std::vector<double>& cycleCosts, std::map<std::pair<int, int>, int>& index, int vertices, int& inevitableCycles, int g,
    const std::vector<std::vector<int> >& fixedValues, int UP_GIRTH, double LIFT_PEN);

std::pair<int, double> getGirthAndCycles(const std::vector<std::vector<int> >& a, int circ, const std::vector<std::vector<int> >& proto,
    std::vector<std::vector<std::pair<int, int> > >& sparse, std::vector<double>& cycleCosts, std::map<std::pair<int, int>, int>& index, int vertices, 
    int& inevitableCycles, const std::vector<std::vector<int> >& fixedValues, int UP_GIRTH, double LIFT_PEN);

double getTotalCost(const std::vector<std::vector<int> >& a, int circ, const std::vector<std::vector<int> >& proto, int UP_GIRTH, double LIFT_PEN);

double getTotalCost(const std::vector<int>& newSol, std::vector<std::vector<int> > mtr, const std::vector<std::vector<int> >& proto, int circ, int maxCirc,
    const std::vector<std::vector<int> >& fixedMtr, std::map<std::pair<int, int>, int>& index, int upGirth, const std::set<int>& allowedCirculants, double LIFT_PEN);
std::pair<long long, long long> getGirth(const std::vector<std::vector<int> >& a, int circ, const std::vector<std::vector<int> >& proto);
//Maevskiy st*d cock*ker

    

std::pair<long long, long long> getGirthAndAce(const std::vector<std::vector<int> >& a, int circ, const std::vector<std::vector<int> >& proto);
