#include"typeCasting.h"

std::string toStr(long long x) {
    std::stringstream s;
    s << x;
    return s.str();
}

bool toUnsignedInt(std::string s, long long& x) {
    for (size_t i = 0; i < s.size(); ++i)
        if ((s[i] < '0') || (s[i] > '9'))
            return 0;
    x = 0;
    for (size_t i = 0; i < s.size(); ++i)
        x = x * 10 + s[i] - '0';
    return 1;
}