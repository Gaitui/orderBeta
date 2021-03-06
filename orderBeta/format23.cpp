#include "format23.h"

format23::format23(){}

void format23::decode23(u_char* pkt_data,head inhead)
{
    dhead = inhead;
    int h=10;
    int len = inhead.mlen;
    t.toString(h,6,scode,pkt_data);
    t.BCDtoArray(h,6,mtime,pkt_data);
    t.tobin(h,reveal,pkt_data);
    t.tobin(h,limark,pkt_data);
    t.tobin(h,state,pkt_data);
    tnum = t.BCDtoD(h,6,pkt_data);

    while(h<len-3)
    {
        rprice.push_back(t.todouble(h,5,3,pkt_data));
        rnum.push_back(t.BCDtoD(h,6,pkt_data));
    }
    check = t.toint(h,pkt_data);
    t.tointArray(h,2,terminal,pkt_data);
}
