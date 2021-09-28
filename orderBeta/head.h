#ifndef HEAD_H
#define HEAD_H
#include "tools.h"
#include <QString>

class head
{
public:
    head();
    int esc;
    int mlen;
    int mtype;
    int mcode;
    int mver;
    int mseq;
    tools t;
    void decode(u_char*,int);
};

#endif // HEAD_H
