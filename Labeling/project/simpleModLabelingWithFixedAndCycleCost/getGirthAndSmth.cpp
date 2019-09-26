#include"getGirthAndSmth.h"
#include<iostream>
#include"cycleEnum.h"
#include<set>

double getCycleCostByProto(const vector<entry>& cycle, const vector<vector<int> >& sparseVars, double LIFT_PEN);
double getCycleCostByLifted(const vector<entry>& cycle, const vector<vector<int> >& sparseVars, const vector<vector<int> >& a, int circulant, double LIFT_PEN);
//Mayevskiy 喜歡吮吸公雞
vector<vector<int> > getSparseVars(const vector<vector<int> >& proto);
vector<pair<vector<pair<int, int> >, double> > sumCostByEq(vector<pair<vector<pair<int, int> >, double> >& sparse);
double getCostByAceAndGirth(int ace, int girth, double LIFT_PEN);
double getCostByEmdAndGirth(int emd, int girth, double LIFT_PEN);



double getTotalCost(const vector<vector<int> >& a, int circ, const vector<vector<int> >& proto, int UP_GIRTH, double LIFT_PEN) {

    double res = 0;
    vector<vector<int> > sparseVars = getSparseVars(proto);

    for (int g = 4; g <= UP_GIRTH; g += 2) {
        CycleEnum enumerator(g, proto);
        if (!enumerator.init()) {
            continue;
        }
        do {
            vector<entry> cycle = enumerator.cycle;
            int sum = 0;
            bool allFixed = 1;
            for (int i = 0; i < g; ++i) {
                int x = a[cycle[i].r][cycle[i].c] % circ;
                if (i & 1)
                    sum += x;
                else
                    sum -= x;
            }
            sum = (((sum % circ) + circ) % circ);
            if (sum == 0) {
                res += getCycleCostByLifted(cycle, sparseVars, a, circ, LIFT_PEN);
            }
        } while (enumerator.next());
    }
    return res;
}

double getTotalCost(const std::vector<int>& newSol, std::vector<std::vector<int> > mtr, const vector<vector<int> >& proto, int circ, int maxCirc,
    const std::vector<std::vector<int> >& fixedMtr, map<pair<int, int>, int>& index, int upGirth, const set<int>& allowedCircs, double LIFT_PEN) {
    double res = 0;
    for (int i = 0; i < mtr.size(); ++i) {
        for (int j = 0; j < mtr[i].size(); ++j) {
            if (mtr[i][j] == -1)
                continue;
            if (!fixedMtr[i][j])
                mtr[i][j] = (mtr[i][j] + newSol[index[std::pair<int, int>(i, j)]] * circ / 2) % circ;
        }
    }

    for (int curCirc = circ; curCirc < (2 * circ, maxCirc + 1); ++curCirc) {
        if (allowedCircs.find(curCirc) != allowedCircs.end())
            res = max(res, getTotalCost(mtr, curCirc, proto, upGirth, LIFT_PEN));
    }
    return res;
}

        


pair<int, double> getGirthAndCyclesWithStartGirth(const vector<vector<int> >& a, int circ, const vector<vector<int> >& proto,
    vector<vector<pair<int, int> > >& sparse, vector<double>& cycleCosts, map<pair<int, int>, int>& index, int vertices, 
    int& inevitableCycles, int LOW_GIRTH, const vector<vector<int> >& fixedMtr, int UP_GIRTH, double LIFT_PEN) {

    vector<vector<int> > sparseVars = getSparseVars(proto);
    vector<pair<vector<pair<int, int> >, double> > sparseAndCost;
    sparse.resize(0);
    cycleCosts.resize(0);
    int g = LOW_GIRTH;
    pair<int, int> cur(UP_GIRTH, 0);
    while (g <= UP_GIRTH) {
        CycleEnum enumerator(g, proto);
        if (!enumerator.init()) {
            g += 2;
            continue;
        }

        do {
            vector<entry> cycle = enumerator.cycle;
            int sum = 0;
            bool allFixed = 1;
            for (int i = 0; i < g; ++i) {
                int x = a[cycle[i].r][cycle[i].c] % circ;
                if (i & 1)
                    sum += x;
                else
                    sum -= x;
            }
            //sum = (((sum % circ) + circ) % circ);
            if (sum == 0) {
                double cycleCost = getCycleCostByProto(cycle, sparseVars, LIFT_PEN);
                vector<int> cycleRC(vertices, 0);
                for (int i = 0; i < g; ++i) {
                    int pos = index[pair<int, int>(cycle[i].r, cycle[i].c)];
                    cycleRC[pos] += ((i & 1) * 2 - 1);// *(1 - fixedMtr[cycle[i].r][cycle[i].c]);
                }
                vector<pair<int, int>> sparseVec;
                for (int i = 0; i < vertices; ++i) {
                    if (cycleRC[i] != 0) {
                        sparseVec.push_back(pair<int, int>(i, cycleRC[i]));
                    }
                }
                sort(sparseVec.begin(), sparseVec.end());
                for (int i = 0; i < fixedMtr.size(); ++i) {
                    for (int j = 0; j < fixedMtr[i].size(); ++j) {
                        if ((fixedMtr[i][j] == 0) && (a[i][j] != -1)) {
                            if (cycleRC[index[make_pair(i, j)]] != 0)
                                allFixed = 0;
                        }
                    }
                }
                if ((sparseVec.empty()) || (allFixed)) {
                    if (inevitableCycles == 0)
                        inevitableCycles = g;
                    //inevitable cycle aren't counted 
                }
                else {
                    cur.first = min(cur.first, g);
                    if (sparseVec[0].second < 0)
                        for (int i = 0; i < sparseVec.size(); ++i)
                            sparseVec[i].second *= -1;
                    sort(sparseVec.begin(), sparseVec.end());
                    sparseAndCost.push_back(make_pair(sparseVec, cycleCost));
                }
            }
        } while (enumerator.next());
        
        g += 2;
    }
    sort(sparseAndCost.begin(), sparseAndCost.end());
    sparseAndCost = sumCostByEq(sparseAndCost);
    //sparse.resize(unique(sparse.begin(), sparse.end()) - sparse.begin());
    cur.second += sparseAndCost.size();
    //if ((cur.second != 0) || (inevitableCycles > 0)) {
        pair<int, double> res(cur.first, 0);
        for (int i = 0; i < sparseAndCost.size(); ++i) {
            sparse.push_back(sparseAndCost[i].first);
            cycleCosts.push_back(sparseAndCost[i].second);
            res.second += cycleCosts[i];
        }
        return res;
}

pair<int, double> getGirthAndCycles(const vector<vector<int> >& a, int circ, const vector<vector<int> >& proto, 
    vector<vector<pair<int, int> > >& sparse, vector<double>& cycleCosts, map<pair<int, int>, int>& index, int vertices, 
    int& inevitableCycles, const vector<vector<int> >& fixedMtr, int UP_GIRTH, double LIFT_PEN) {
    int g = 4;
    return getGirthAndCyclesWithStartGirth(a, circ, proto, sparse, cycleCosts, index, vertices, inevitableCycles, g, fixedMtr, UP_GIRTH, LIFT_PEN);
}

pair<long long, long long> getGirth(const vector<vector<int> >& a, int circ, const vector<vector<int> >& proto) {
    int g = 4;
    while (true) {
        pair<long long, long long> cur(g, 0);
        CycleEnum enumerator(g, proto);
        if (!enumerator.init()) {
            g += 2;
            continue;
        }
        do {
            vector<entry> cycle = enumerator.cycle;
            int res = 0;
            for (int i = 0; i < g; ++i) {
                int x = a[cycle[i].r][cycle[i].c] % circ;
                if (i & 1)
                    res += x;
                else
                    res -= x;
            }
            res = (((res % circ) + circ) % circ);
            if (res == 0) {
                ++cur.second;
                /*for (int i = 0; i < cycle.size(); ++i) {
                    cerr << cycle[i].r << "," << cycle[i].c << endl;
                }*/
            }
        } while (enumerator.next());
        if (cur.second != 0) {
            cur.second /= g;
            return cur;
        }
        g += 2;
    }
}

pair<long long, long long> getGirthAndAce(const vector<vector<int> >& a, int circ, const vector<vector<int> >& proto) {
    int g = 4;
    vector<int> degVar(a[0].size(), 0), degCheck(a.size(), 0);

    for (int r = 0; r < a.size(); ++r) {
        for (int c = 0; c < a[r].size(); ++c) {
            if (a[r][c] == -1)
                continue;
            ++degVar[c];
            ++degCheck[r];
        }
    }
    //eprint(a);
    //eprint(degVar);
    //eprint(degCheck);
    //Sleep(10000);

    bool noCycles = 1;
    pair<long long, long long> cur;
    while (noCycles) {
        cur = pair<long long, long long>(g, -1);

        CycleEnum enumerator(g, proto);
        if (!enumerator.init()) {
            g += 2;
            continue;
        }
        do {
            vector<entry> cycle = enumerator.cycle;
            int res = 0;
            for (int i = 0; i < g; ++i) {
                int x = a[cycle[i].r][cycle[i].c] % circ;
                if (i & 1)
                    res += x;
                else
                    res -= x;
            }
            res = (((res % circ) + circ) % circ);
            if (res == 0) {
                noCycles = 0;
                int curAce = 0;
                for (int i = 0; i < cycle.size(); ++i) {
                    if (i & 1)
                        curAce += degCheck[cycle[i].r] - 2;
                    else
                        curAce += degVar[cycle[i].c] - 2;
                }
                if ((cur.second == -1) || (curAce < cur.second))
                    cur.second = curAce;
            }
        } while (enumerator.next());
        g += 2;
    }
    return cur;
}

double getCycleCostByProto(const vector<entry>& cycle, const vector<vector<int> >& sparseVars, double LIFT_PEN) {
    int ace = 0;
    for (int i = 0; i < cycle.size(); i += 2) {
        ace += sparseVars[cycle[i].c].size() - 2;
    }
    return getCostByAceAndGirth(ace, cycle.size(), LIFT_PEN);
}
//Maevskiy c**cks*cker
double getCycleCostByLifted(const vector<entry>& cycle, const vector<vector<int> >& sparseVars, const vector<vector<int> >& mtr, int circulant, double LIFT_PEN) {
    vector<pair<int, int> > varNodes(1, pair<int, int>(cycle[0].c, 0));
    for (int i = 1; i < cycle.size(); i += 2) {
        varNodes.push_back(pair<int, int>(cycle[i].c,
            (varNodes[i / 2].second + mtr[cycle[i].r][cycle[i].c] -
            mtr[cycle[i - 1].r][cycle[i - 1].c] + circulant) % circulant));
    }
    sort(varNodes.begin(), varNodes.end());
    varNodes.resize(unique(varNodes.begin(), varNodes.end()) - varNodes.begin());
    int res = 0;
    for (int r = 0; r < mtr.size(); ++r) {
        vector<int> ls;
        for (int i = 0; i < varNodes.size(); ++i) {
            if (mtr[r][varNodes[i].first] == -1)
                continue;
            ls.push_back((mtr[r][varNodes[i].first] - varNodes[i].second + circulant) % circulant);
        }
        sort(ls.begin(), ls.end());
        for (int i = 0; i < ls.size(); ++i) {
            if ((i > 0) && (ls[i] == ls[i - 1]))
                continue;
            if ((i + 1 < ls.size()) && (ls[i] == ls[i + 1]))
                continue;
            ++res;
        }
    }
    return getCostByEmdAndGirth(res, cycle.size(), LIFT_PEN);

}



double getCostByAceAndGirth(int ace, int girth, double LIFT_PEN) {
    return 1000000 * pow(ace + 1, LIFT_PEN) * pow(5, -girth);
}

double getCostByEmdAndGirth(int emd, int girth, double LIFT_PEN) {
    return 1000000 * pow(emd + 1, LIFT_PEN) * pow(5, -girth);
}


vector<vector<int> > getSparseVars(const vector<vector<int> >& proto) {
    int m = proto.size();
    int n = proto[0].size();
    vector<vector<int> > res(n);
    for (int i = 0; i < m; ++i)
        for (int j = 0; j < n; ++j)
            if (proto[i][j])
                res[j].push_back(i);
    return res;
}

vector<pair<vector<pair<int, int> >, double> > sumCostByEq(vector<pair<vector<pair<int, int> >, double> >& sparse) {
    vector<pair<vector<pair<int, int> >, double> > res;
    if (sparse.empty())
        return res;
    res.push_back(sparse[0]);
    for (int i = 1; i < sparse.size(); ++i) {
        if (sparse[i].first == sparse[i - 1].first)
            res[res.size() - 1].second += sparse[i].second;
        else
            res.push_back(sparse[i]);
    }
    return res;
}
