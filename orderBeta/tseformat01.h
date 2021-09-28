#ifndef TSEFORMAT01_H
#define TSEFORMAT01_H
#include "head.h"
#include "tools.h"

class tseFormat01
{
public:
    tseFormat01();
    head dhead;
    std::string scode;
    u_char sname[17];
    u_char sind[3];
    u_char stype[3];
    u_char strans[3];
    int sexec;
    u_char bnote;
    double refprice;
    double limup;
    double limdown;
    u_char ten;
    u_char rexec;
    u_char pexec;
    u_char dtrade;
    u_char fsell;
    u_char fborrow;
    int ssec;
    u_char wcode;
    double sprice;
    long long lsnum;
    long long lwoff;
    long long obalance;
    double ppercent;
    double pupperb;
    double plowerb;
    int due;
    char foreign;
    int blot;
    u_char ccode[4];
    int minfo;
    int check;
    int terminal[2];
    tools t;
    void decodetse01(u_char*,head);
};

#endif // TSEFORMAT01_H
