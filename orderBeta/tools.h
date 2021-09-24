#ifndef TOOLS_H
#define TOOLS_H
#include<QString>

class tools
{
public:
    tools();
    long long BCDtoD(int &h,int n,std::string pkt_data);
    void toArray(int &h,int n,u_char *dest,std::string pkt_data);
    char tochar(int &h,std::string pkt_data);
    double todouble(int &h,int n,int inum,std::string pkt_data);
    int toint(int &h,std::string pkt_data);
    void tointArray(int &h,int n,int *dest,std::string pkt_data);
    int tobin(int &h,std::string pkt_data);
};

#endif // TOOLS_H
