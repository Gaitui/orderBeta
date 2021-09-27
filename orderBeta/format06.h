#ifndef FORMAT06_H
#define FORMAT06_H
#include <QString>
#include <vector>
#include "tools.h"
#include "head.h"

class format06
{
public:
    format06();
    head dhead;
    std::string scode;
    int mtime[6];
    int reveal[8];
    int limark[8];
    int state[8];
    int tnum;
    std::vector<double> rprice;
    std::vector<int> rnum;
    int check;
    int terminal[2];
    tools t;
    void decode06(std::string,head);
};

#endif // FORMAT06_H
