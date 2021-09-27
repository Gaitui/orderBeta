#include "format06.h"

format06::format06(){}

void format06::decode06(std::string pkt_data, head inhead)
{
    dhead = inhead;
    int h=0;
    int len = inhead.mlen-10;
    t.toArray(h,6,scode,pkt_data);
    //mtime = t.BCDtoD(h,6,pkt_data);
    t.tointArray(h,6,mtime,pkt_data);
    t.tobin(h,reveal,pkt_data);
    t.tobin(h,limark,pkt_data);
    t.tobin(h,state,pkt_data);
    tnum = t.BCDtoD(h,4,pkt_data);

    while(h<len-3)
    {
        rprice.push_back(t.todouble(h,5,3,pkt_data));
        rnum.push_back(t.BCDtoD(h,4,pkt_data));
    }
    check = t.toint(h,pkt_data);
    t.tointArray(h,2,terminal,pkt_data);
}
