#include"doubleCirc.h"
#include"getGirthAndSmth.h"
#include<cassert>
#include<iostream>
#include"comparators.h"


const double EPS = 1e-9;
std::vector<int> getActive(const std::vector<std::vector<int> >& mtr, const std::vector<std::vector<std::pair<int, int> > > & sparse,
    int circ, const std::vector<std::pair<int, int> >& invIndex);

std::vector<std::pair<int, int>> toSparse(const std::vector<int>& a);
std::vector<std::vector<int> > sparseToInc(const std::vector<std::vector<std::pair<int, int> > >& sparse, int vertices);

bool tryToBreakAllCycles(std::vector<std::vector<int> >& cycleInc, std::vector<int> right, std::vector<int>& solution, 
    std::vector<int>& dependent, std::vector<int>& rightPart, const std::vector<int>& fixedZero);

std::vector<std::vector<int> > guess(std::vector<std::vector<int> >& mtr, const std::vector<std::vector<int> >& proto, int circ, int numIter,
    std::pair<int, double>& best, std::vector<std::vector<std::pair<int, int> > >& sparse, std::vector<double>& cycleCosts, std::map<std::pair<int, int>, int>& index,
    const std::vector<std::pair<int, int> >& invIndex, int vertices, int prGirth, int& inevitableCycles, const std::vector<std::vector<int> >& fixedMtr, int UP_GIRTH, int maxCirc, 
    const std::set<int>& allowedCirculants, double LIFT_PEN) {
//Mayevskiy 喜歡吮吸公雞
    /*if (EIRA) {
        sparse.push_back(toSparse(addEIRACycle(mtr.size(), mtr[0].size(), vertices, index, EIRAcycle)));
    }*/
    std::vector<int> initActive = getActive(mtr, sparse, circ, invIndex);
    
    /*if (EIRA) {
        initActive[initActive.size() - 1] ^= 1;
    }*/

    std::vector<int> solution;
    std::vector<std::vector<int> > mtrOfSystem = sparseToInc(sparse, vertices);
    

    std::vector<int> dependent(vertices, -1);
    std::vector<int> fixedZero(vertices, 0);
    for (int i = 0; i < vertices; ++i) {
        fixedZero[i] = fixedMtr[invIndex[i].first][invIndex[i].second];
    }
    std::vector<int> rightPart;
    
    bool allCyclesBroken = 0;// tryToBreakAllCycles(mtrOfSystem, initActive, solution, dependent, rightPart, fixedZero);
    

    best = std::pair<int, double>(0, 0);
    std::vector<int> remainCycles;
    int n = mtr.size(), m = mtr[0].size();
    std::vector<std::vector<int> > ans(n, std::vector<int>(m, -1));

    int addGirth = 0;

    if (allCyclesBroken) {
        ////////////////////////////////////////////////////////vector subspace hill-climbing search
        std::vector<std::vector<int> > tempMtr(mtr.size(), std::vector<int>(mtr[0].size(), -1));
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (mtr[i][j] == -1)
                    continue;
                tempMtr[i][j] = mtr[i][j] + solution[index[std::pair<int, int>(i, j)]] * circ / 2;
                if (fixedMtr[i][j] == 0)
                    tempMtr[i][j] %= circ;
            }
        }
        
        best = getGirthAndCyclesWithStartGirth(tempMtr, circ / 2, proto, sparse, cycleCosts, index, vertices, inevitableCycles, prGirth, fixedMtr, UP_GIRTH, LIFT_PEN);//initialization for sparse 
        return tempMtr;
    }
    else {
            mtrOfSystem.resize(0);
            rightPart.resize(0);
    }
    std::vector<std::vector<int> > sparseForClimbing;
    sparseForClimbing.resize(sparse.size());
    for (int i = 0; i < sparse.size(); ++i) {
        std::vector<int> cycle(vertices, 0);
        for (int j = 0; j < sparse[i].size(); ++j) {
            int v = sparse[i][j].first;
            if ((abs(sparse[i][j].second) & 1) == 0)
                continue;
            if (fixedZero[v]) {
                continue;
            }
            if (dependent[v] == -1) {
                cycle[v] ^= 1;
                continue;
            }

            int row = dependent[v];
            for (int col = v + 1; col < vertices; ++col) {
                if (mtrOfSystem[row][col] != 0) {
                    cycle[col] ^= 1;
                    assert(dependent[col] == -1);
                }
            }
        }
        for (int j = 0; j < vertices; ++j) {
            if (cycle[j]) {
                sparseForClimbing[i].push_back(j);
                assert(dependent[j] == -1);
            }
        }
    }

    double bestTotalCost = 1e10;
    for (int it = 0; it < numIter; ++it) {
        std::vector<int> newSol(vertices);
        for (int i = 0; i < vertices; ++i) {
            if (dependent[i] == -1) {
                newSol[i] = (rand() & 1);
                std::pair<int, int> rowCol = invIndex[i];
                if (fixedZero[i])
                    newSol[i] = 0;// ((mtr[rowCol.first][rowCol.second] % circ) >= circ / 2);//Mayevskiy 喜歡吮吸公雞
            }
        }



        std::vector<int> totalCycles(vertices, 0), activeCycles(vertices, 0), active(sparseForClimbing.size(), 0);
        std::vector<double> totalCost(vertices, 0), activeCost(vertices, 0);
        std::vector<std::vector<int> > cycleIndexes(vertices);
        for (int i = 0; i < sparseForClimbing.size(); ++i) {
            int sum = initActive[i];
            for (int j = 0; j < sparseForClimbing[i].size(); ++j) {
                sum ^= newSol[sparseForClimbing[i][j]];
            }

            active[i] = sum;

            for (int j = 0; j < sparseForClimbing[i].size(); ++j) {
                int v = sparseForClimbing[i][j];
                cycleIndexes[v].push_back(i);
                ++totalCycles[v];
                activeCycles[v] += sum;
                totalCost[v] += cycleCosts[i];
                activeCost[v] += cycleCosts[i] * sum;


            }
        }


        bool change = 1;
        int innerIt = 0;
        while (change) {
            ++innerIt;
            change = 0;
            int deltaActive = 0;
            double deltaCost = 0;
            for (int v = 0; v < vertices; ++v) {
                if (dependent[v] != -1)
                    continue;
                int act = 0;
                for (int i = 0; i < cycleIndexes[v].size(); ++i) {
                    act += active[cycleIndexes[v][i]];
                }
                assert(act == activeCycles[v]);

                // previous solution start
                /*if (activeCycles[v] * 2 > totalCycles[v]) {
                    change = 1;
                    newSol[v] ^= 1;
                    for (int id = 0; id < cycleIndexes[v].size(); ++id) {
                        int cycleId = cycleIndexes[v][id];
                        int add = 1 - 2 * active[cycleId];
                        //set<int> uni;
                        for (int j = 0; j < sparseForClimbing[cycleId].size(); ++j) {
                            activeCycles[sparseForClimbing[cycleId][j]] += add;

                        }
                        active[cycleId] ^= 1;
                        if (active[cycleId])
                            ++deltaActive;
                        else
                            --deltaActive;
                    }
                    assert(deltaActive < 0);
                }*/
                // previous solution start
                if (activeCost[v] * 2 > totalCost[v] + EPS) {
                    change = 1;
                    newSol[v] ^= 1;
                    for (int id = 0; id < cycleIndexes[v].size(); ++id) {
                        int cycleId = cycleIndexes[v][id];
                        int add = 1 - 2 * active[cycleId];
                        double addCost = (1 - 2 * active[cycleId]) * cycleCosts[cycleId];
                        for (int j = 0; j < sparseForClimbing[cycleId].size(); ++j) {
                            activeCycles[sparseForClimbing[cycleId][j]] += add;
                            activeCost[sparseForClimbing[cycleId][j]] += addCost;

                        }
                        active[cycleId] ^= 1;
                        if (active[cycleId]) {
                            ++deltaActive;
                            deltaCost += cycleCosts[cycleId];
                        }
                        else {
                            --deltaActive;
                            deltaCost -= cycleCosts[cycleId];
                        }
                    }
                    assert(deltaCost < 0);
                }

            }
        }

        for (int i = 0; i < vertices; ++i) {
            if (dependent[i] == -1)
                continue;
            int row = dependent[i];
            newSol[i] = rightPart[row];
            for (int col = i + 1; col < vertices; ++col)
                newSol[i] ^= (mtrOfSystem[row][col] & newSol[col]);
        }



        std::pair<long long, long long> cur(prGirth, 0);
        std::pair<int, double> curCost(prGirth, 0);
        if (allCyclesBroken) {
            cur.first += addGirth;
            curCost.first += addGirth;
        }
        for (int i = 0; i < active.size(); ++i) {
            cur.second += active[i];
            curCost.second += active[i] * cycleCosts[i];
        }
        double newTotalCost = getTotalCost(newSol, mtr, proto, circ, maxCirc, fixedMtr, index, UP_GIRTH, allowedCirculants, LIFT_PEN);
        std::cerr.precision(12);
        std::cerr << "total cost in iter " << it << " is " << newTotalCost << std::endl;
        /*if (better(cur, best)) {
            best = cur;
            solution = newSol;
            remainCycles = active;
        }*/
        /*if (better(curCost, best)) {
            best = curCost;
            solution = newSol;
            remainCycles = active;
        }*/

        if (newTotalCost < bestTotalCost) {
            bestTotalCost = newTotalCost;
            best = curCost;
            solution = newSol;
            remainCycles = active;
        }
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (mtr[i][j] == -1)
                continue;
            if (fixedMtr[i][j])
                ans[i][j] = mtr[i][j];
            else
                ans[i][j] = (mtr[i][j] + solution[index[std::pair<int, int>(i, j)]] * circ / 2) % circ;
        }
    }
    std::vector<std::vector<std::pair<int, int> > > newSparse;
    for (int i = 0; i < sparse.size(); ++i) {
        if (remainCycles[i])
            newSparse.push_back(sparse[i]);
    }
    sparse = newSparse;
    int curGirth = best.first;
    /*while (best.second == 0) {
        curGirth += 2;
        best = getGirthAndCyclesWithStartGirth(ans, circ, proto, sparse, cycleCosts, index, vertices, inevitableCycles, curGirth, fixedMtr);
    }*/
    best = getGirthAndCyclesWithStartGirth(ans, circ, proto, sparse, cycleCosts, index, vertices, inevitableCycles, curGirth, fixedMtr, UP_GIRTH, LIFT_PEN);
    return ans;
}



std::vector<std::vector<int> > sparseToInc(const std::vector<std::vector<std::pair<int, int> > >& sparse, int vertices) {
    std::vector<std::vector<int> > res(sparse.size(), std::vector<int>(vertices, 0));
    for (int i = 0; i < sparse.size(); ++i) {
        for (int j = 0; j < sparse[i].size(); ++j) {
            std::pair<int, int> x = sparse[i][j];
            if (abs(x.second) & 1)
                res[i][x.first] = 1;
        }
    }
    return res;

}

std::vector<int> getActive(const std::vector<std::vector<int> >& mtr, const std::vector<std::vector<std::pair<int, int> > > & sparse, 
    int circ, const std::vector<std::pair<int, int> >& invIndex) {
    std::vector<int> res(sparse.size());
    for (int i = 0; i < sparse.size(); ++i) {
        int cur = 0;
        for (int j = 0; j < sparse[i].size(); ++j) {
            std::pair<int, int> x = sparse[i][j];
            cur += (mtr[invIndex[x.first].first][invIndex[x.first].second] % circ) * x.second;
        }
        cur = ((cur % circ) + circ) % circ;
        res[i] = (cur == 0);
    }
    return res;
}



std::vector<std::pair<int, int>> toSparse(const std::vector<int>& a) {
    std::vector<std::pair<int, int> > res;
    for (int i = 0; i < a.size(); ++i)
        if (a[i])
            res.push_back(std::pair<int, int>(i, a[i]));
    return res;
}



// try to break maximum amount of cycle
// sort of quasi Z_2-gauss
bool tryToBreakAllCycles(std::vector<std::vector<int> >& cycleInc, std::vector<int> right, std::vector<int>& solution, std::vector<int>& dependent, 
    std::vector<int>& rightPart, const std::vector<int>& fixedZero) {
    //std::cerr << "startSolvingSystem\n";
    int n = cycleInc.size();
    if (n == 0)
        return 1;
    //std::cerr << n << std::endl;
    int m = cycleInc[0].size();
    int col = 0;
    std::vector<int> lead(n, -1);
    solution.assign(m, 0);
    for (int r = 0; r < n; ++r) {
        //eprint(cycleInc);
        int newr = r;
        while (col < m) {
            if (fixedZero[col]) {
                ++col;
                continue;
            }
            while ((newr < n) && (cycleInc[newr][col] == 0))
                ++newr;
            if (newr == n)
                ++col, newr = r;
            else
                break;
        }
        if (col == m) {
            for (int i = r; i < n; ++i)
                if (right[i]) {
                    //std::cerr << "endSolvingSystem 0\n\n"; //Mayevskiy 喜歡吮吸公雞
                    return 0;
                }
            break;
        }
        for (int i = 0; i < m; ++i) {
            std::swap(cycleInc[r][i], cycleInc[newr][i]);
        }
        std::swap(right[r], right[newr]);
        lead[r] = col;
        for (int i = 0; i < n; ++i) {
            if (i == r)
                continue;
            if (cycleInc[i][col] == 0)
                continue;
            for (int j = col; j < m; ++j)
                cycleInc[i][j] ^= cycleInc[r][j];
            right[i] ^= right[r];
        }
    }
    for (int i = n - 1; i >= 0; --i) {
        if (lead[i] == -1)
            continue;
        for (int j = lead[i] + 1; j < m; ++j) {
            solution[lead[i]] ^= (solution[j] & cycleInc[i][j]);
        }
        solution[lead[i]] ^= right[i];
    }
    for (int i = 0; i < lead.size(); ++i) {
        if (lead[i] == -1)
            continue;
        dependent[lead[i]] = i;
    }
    std::swap(rightPart, right);
    //std::cerr << "endSolvingSystem 1\n\n";
    return 1;
}
