#ifndef HEAD_H
#define HEAD_H
#include "tools.h"
#include <QString>

class head
{
public:
    head(std::string,int);
    int esc;
    int mlen;
    int mtype;
    int mcode;
    int mver;
    int mseq;
    tools t;
};

#endif // HEAD_H
