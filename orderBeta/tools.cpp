#include "tools.h"

tools::tools(){}

long long tools::BCDtoD(int &h,int n,u_char* pkt_data)
{
    long long d=0;
    for(int i=0;i<n;i++)
    {
        d=d*100+(pkt_data[h+i]>>4)*10+(pkt_data[h+i] & 0x0f);
    }
    h+=n;
    return d;
}

void tools::toArray(int &h,int n,u_char *dest,u_char* pkt_data)
{
    for(int i=0;i<n;i++)
    {
        dest[i]=pkt_data[h+i];
    }
    dest[n]='\0';
    h+=n;
}

char tools::tochar(int &h,u_char *pkt_data)
{
    h++;
    return pkt_data[h-1];
}

double tools::todouble(int &h,int n,int inum,u_char *pkt_data)
{
    int i = BCDtoD(h,inum,pkt_data);
    int f = BCDtoD(h,n-inum,pkt_data);
    return (double)i+((double)f/pow(10,(n-inum)*2));
}

int tools::toint(int &h,u_char *pkt_data)
{
    h++;
    return (int)pkt_data[h-1];
}

void tools::tointArray(int &h,int n,int *dest,u_char *pkt_data)
{
    for(int i=0;i<n;i++)
    {
        dest[i]=(int)pkt_data[i+h];
    }
    h+=n;
    return;
}

int tools::tobin(int &h,u_char *pkt_data)
{
    int d=0;
    for(int i=7;i>=0;i--)
    {
        d = d*10+((pkt_data[h]>>i) & 0x01);
    }
    h++;
    return d;
}
