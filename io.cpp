#include<cstdio>
#include<cctype>

int gc()
{
    static char buf[1<<16],*p1=buf,*p2=buf;
    if(p2==p1)
    {
        p2=(p1=buf)+fread(buf,1,1<<16,stdin);
        if(p2==p1)return EOF;
    }
    return *p1++;
}

template<typename T>
void read(T& x)
{
    x=0;
    bool sym=0;
    char c=gc();
    while(!isdigit(c))sym^=(c=='-'),c=gc();
    while(isdigit(c))x=x*10-'0'+c;
    if(sym)x=-x;
}

void read(char& c)
{
    c=gc();
}

void read(char* str)
{
    char c=gc();
    while(isblank(c))c=gc();
    while(!isblank(c))*str++=c=gc();
}

template<typename T,typename... Args>
void read(T& x,Args&... args)
{
    read(x);
    read(args...);
}

template<typename T>
void write(T x)
{
    if(x<0)
    {
        putchar('-');
        return write(-x);
    }
    if(x>=10)write(x/10);
    putchar(x%10+'0');
}

void write(char c)
{
    putchar(c);
}

void write(char* str)
{
    fputs(str,stdout);
}

template<typename T,typename... Args>
void write(T x,Args... args)
{
    write(x);
    write(args...);
}