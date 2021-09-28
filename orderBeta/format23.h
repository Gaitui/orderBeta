#ifndef FORMAT23_H
#define FORMAT23_H
#include <QString>
#include <vector>
#include "tools.h"
#include "head.h"

class format23
{
public:
    format23();
    head dhead;
    std::string scode;
    int mtime[6];
    int reveal[8];
    int limark[8];
    int state[8];
    long long tnum;
    std::vector<double> rprice;
    std::vector<long long> rnum;
    int check;
    int terminal[2];
    tools t;
    void decode23(u_char*,head);
};

#endif // FORMAT23_H
