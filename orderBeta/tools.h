#ifndef TOOLS_H
#define TOOLS_H
#include<QString>

class tools
{
public:
    tools();
    long long BCDtoD(int &h,int n,u_char* pkt_data);
    void toArray(int &h,int n,u_char *dest,u_char* pkt_data);
    char tochar(int &h,u_char *pkt_data);
    double todouble(int &h,int n,int inum,u_char *pkt_data);
    int toint(int &h,u_char *pkt_data);
    void tointArray(int &h,int n,int *dest,u_char *pkt_data);
    int tobin(int &h,u_char *pkt_data);
};

#endif // TOOLS_H
