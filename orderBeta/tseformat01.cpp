#include "tseformat01.h"

tseFormat01::tseFormat01(){}
void tseFormat01::decodetse01(u_char* pkt_data,head inhead)
{
    dhead=inhead;
    int h=10;
    t.toString(h,6,scode,pkt_data);
    t.toArray(h,16,sname,pkt_data);
    t.toArray(h,2,sind,pkt_data);
    t.toArray(h,2,stype,pkt_data);
    t.toArray(h,2,strans,pkt_data);
    sexec = t.BCDtoD(h,1,pkt_data);
    bnote = t.tochar(h,pkt_data);
    refprice = t.todouble(h,5,3,pkt_data);
    limup = t.todouble(h,5,3,pkt_data);
    limdown = t.todouble(h,5,3,pkt_data);
    ten = t.tochar(h,pkt_data);
    rexec = t.tochar(h,pkt_data);
    pexec = t.tochar(h,pkt_data);
    dtrade = t.tochar(h,pkt_data);
    fsell = t.tochar(h,pkt_data);
    fborrow = t.tochar(h,pkt_data);
    ssec = t.BCDtoD(h,3,pkt_data);
    wcode = t.tochar(h,pkt_data);
    sprice = t.todouble(h,5,3,pkt_data);
    lsnum = t.BCDtoD(h,5,pkt_data);
    lwoff = t.BCDtoD(h,5,pkt_data);
    obalance = t.BCDtoD(h,5,pkt_data);
    ppercent = t.todouble(h,4,3,pkt_data);
    pupperb = t.todouble(h,5,3,pkt_data);
    plowerb = t.todouble(h,5,3,pkt_data);
    due = t.BCDtoD(h,4,pkt_data);
    foreign = t.tochar(h,pkt_data);
    blot = t.BCDtoD(h,3,pkt_data);
    t.toArray(h,3,ccode,pkt_data);
    minfo = t.BCDtoD(h,1,pkt_data);
    check = t.toint(h,pkt_data);
    t.tointArray(h,2,terminal,pkt_data);
}
