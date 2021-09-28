#ifndef OTCFORMAT01_H
#define OTCFORMAT01_H
#include "head.h"
#include "tools.h"

class otcformat01
{
public:
    otcformat01();
    head dhead;
    std::string scode;
    u_char sname[17];
    u_char sind[3];
    u_char stype[3];
    u_char strans[3];
    int sexec;
    u_char cnote;
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
    int blot;
    u_char ccode[4];
    int minfo;
    int check;
    int terminal[2];
    tools t;
    void decodeotc01(u_char*,head);
};

#endif // OTCFORMAT01_H
