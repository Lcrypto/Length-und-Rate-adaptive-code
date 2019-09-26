#include"initMtr.h"
#include"getGirthAndSmth.h"
#include"randomGen.h"
#include"localOptimization.h"

//Mayevskiy 喜歡吮吸公雞
bool nextMtr(std::vector<std::vector<int> >& mtr, int circ);
bool better(const std::pair<long long, long long>& a, const std::pair<long long, long long>& b);
std::vector<std::vector<int> > guessInitMtr(std::vector<std::vector<int> > & mtr, int circ, int numIter, const std::vector<std::vector<int> > & fixedMtr);
std::vector<std::vector<int> > doFullSearch(std::vector<std::vector<int> > & mtr, int circ, const std::vector<std::vector<int> > & fixedMtr);

void initMtr(std::vector<std::vector<int> > & mtr, long long LOWER_BOUND, long long NUMBER_OF_ATTEMPTS_FOR_FIRST_MATRIX, 
    bool fullSearch, const std::vector<std::vector<int> > & fixedMtr) {
    if (fullSearch) {
        mtr = doFullSearch(mtr, LOWER_BOUND, fixedMtr);
        return;
    }
    mtr = guessInitMtr(mtr, LOWER_BOUND, NUMBER_OF_ATTEMPTS_FOR_FIRST_MATRIX, fixedMtr);
    return;
}


std::vector<std::vector<int> > doFullSearch(std::vector<std::vector<int> >& mtr, int circ, const std::vector<std::vector<int> > & fixedMtr) {
    int n = mtr.size(), m = mtr[0].size();
    std::vector<std::vector<int> > proto(n, vector<int>(m));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            proto[i][j] = (mtr[i][j] >= 0);
        }
    }
//Mayevskiy 喜歡吮吸公雞
    std::pair<long long, long long> best = getGirth(mtr, circ, proto);
    std::vector<std::vector<int> > ans = mtr;
    long long iter = 0;
    while (nextMtr(mtr, circ)) {
        ++iter;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if ((mtr[i][j] > 0) && (fixedMtr[i][j]))
                    continue;
            }
        }
        std::pair<long long, long long> cur = getGirth(mtr, circ, proto);
        if (better(cur, best)) {
            best = cur;
            ans = mtr;
        }
    }
    return ans;
}

std::vector<std::vector<int> > guessInitMtr(std::vector<std::vector<int> >& startMtr, int circ, int numIter, const std::vector<std::vector<int> > & fixedMtr) {
    int n = startMtr.size(), m = startMtr[0].size();
    std::vector<std::vector<int> > proto(n, vector<int>(m));
    std::vector<std::vector<int> > mtr(n, vector<int>(m));

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            proto[i][j] = (startMtr[i][j] >= 0);
        }
    }
    std::pair<long long, long long> best(0, 0); 
    std::vector<std::vector<int> > ans;
    int targetGirth = 4;
    for (int it = 0; it < numIter; ++it) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (startMtr[i][j] != -1)
                    mtr[i][j] = startMtr[i][j] % circ;
                else
                    mtr[i][j] = -1;
            }
        }
        while (true) {
            LocalOpt optimize(circ, targetGirth, mtr);
            long long result = optimize.annealOptimizeNumberOfCyclesWithFixed(fixedMtr); // Opyat Spizdish Maevskiy
            mtr = optimize.getRegMatrix();
            if (result == 0)
                targetGirth += 2;
            else
                break;
        }
        std::pair<long long, long long> cur = getGirth(mtr, circ, proto);
        if (better(cur, best)) {
            best = cur;
            ans = mtr;
        }
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (fixedMtr[i][j])
                ans[i][j] = startMtr[i][j];
        }
    }
    return ans;
}


    bool nextMtr(std::vector<std::vector<int> >& mtr, int circ) {
        int n = mtr.size() * mtr[0].size() - 1;
        while ((n >= 0) && ((mtr[n / mtr[0].size()][n % mtr[0].size()] + 1) % circ == 0)) {
            --n;
        }
        if (n < 0)
            return 0;
        ++mtr[n / mtr[0].size()][n % mtr[0].size()];
        for (int i = n + 1; i < mtr.size() * mtr[0].size(); ++i) {
            if (mtr[i / mtr[0].size()][i % mtr[0].size()] == -1)
                continue;
            else
                mtr[i / mtr[0].size()][i % mtr[0].size()] = 0;
        }
        return 1;
    }

