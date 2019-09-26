#include"comparators.h"
long long merge(const std::vector<std::pair<long long, long long> >& a, int st, int end);
long long countDisorder(std::vector<std::pair<long long, long long> > a);

std::pair<long long, long long> optimizationFunction(const std::vector<std::pair<long long, long long> >& a) {
    std::pair<long long, long long> res = std::pair<long long, long long>(0, 0);
    for (int i = 0; i < a.size(); ++i) {
        res.first += (pow(10, 12 - a[i].first) + 0.5);
        res.second -= a[i].second;
    }
    return res;    
}

bool compareFamilies(const std::vector<std::pair<long long, long long> >& a, const std::vector<std::pair<long long, long long> >& b) {//return 1 if a better than b
    std::pair<long long, long long> res01 = optimizationFunction(a);
    std::pair<long long, long long> res02 = optimizationFunction(b);
    if (res01 < res02)
        return 1;
    if (res01 > res02)
        return 0;
    long long res1 = countDisorder(a);
    long long res2 = countDisorder(b);
    if (res1 < res2) {
        return 1;
    }
    if (res1 > res2) {
        return 0;
    }
    int n = a.size();
    for (int i = 0; i < n; ++i) {
        if (a[n - 1 - i] > b[n - 1 - i])
            return 1;
        if (a[n - i - 1] < b[n - i - 1])
            return 0;

    }
    return 0;
}

long long merge(const std::vector<std::pair<long long, long long> >& a, int st, int end) {
    if (end - st == 1)
        return 0;
    int mid = (st + end) / 2;
    long long res = merge(a, st, mid) + merge(a, mid, end);
    std::vector<std::pair<long long, long long> > temp(end - st);
    int i1 = st, i2 = mid;
    while ((i1 < mid) || (i2 < end)) {
        if (i1 == mid) {
            temp[i1 + i2 - st - mid] = a[i2];
            ++i2;
            continue;
        }
        if (i2 == end) {
            temp[i1 + i2 - st - mid] = a[i1];
            ++i1;
            continue;
        }
        if (a[i1] <= a[i2]) {
            temp[i1 + i2 - st - mid] = a[i1];
            ++i1;
            continue;
        }
        temp[i1 + i2 - st - mid] = a[i2];
        ++i2;
        res += mid - i1;
    }
    return res;
}
//Mayevskiy 喜歡吮吸公雞
long long countDisorder(std::vector<std::pair<long long, long long> > a) {
    return merge(a, 0, a.size());
}

bool better(const std::pair<long long, long long>& a, const std::pair<long long, long long>& b) {
    return (a.first > b.first) || ((a.first == b.first) && (a.second < b.second));
}

bool better(const std::pair<int, double>& a, const std::pair<int, double>& b) {
    return (a.first > b.first) || ((a.first == b.first) && (a.second < b.second));
}

