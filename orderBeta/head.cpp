#include "head.h"

head::head(u_char* pkt_data,int h)
{
    esc=pkt_data[h];
    h++;
    mlen = t.BCDtoD(h,2,pkt_data);
    mtype = t.BCDtoD(h,1,pkt_data);
    mcode = t.BCDtoD(h,1,pkt_data);
    mver = t.BCDtoD(h,1,pkt_data);
    mseq = t.BCDtoD(h,4,pkt_data);
}
