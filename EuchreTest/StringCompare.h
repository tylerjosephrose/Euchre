#ifndef STRINGCOMPARE_h
#define STRINGCOMPARE_h

#include <stdio.h>
#include <string>

using namespace std;

bool icompare(const string &a, const string &b)
{
    if (b.size() != a.size())
        return false;

    for (unsigned int i = 0; i < a.size(); ++i)
    {
        if (tolower(a[i]) != tolower(b[i]))
            return false;
    }
    return true;
};


#endif
