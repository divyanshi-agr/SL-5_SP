#include<bits/stdc++.h>
using namespace std;
int S();
int E();
int T();
int E1();
int T1();
int F();
void match(char);

//Grammar 
/*
S->E
E->TE1
T->FT1
E1-> +TE1 | -TE1 | null
T1-> *FT1 | /FT1 | null
F-> no | alphabet
*/
string input;
int i=0;
int main()
{
    getline(cin,input);
    int err=S();
    if(err==1 && i==input.length())
    {
        cout<<"Accepted\n";
    }
    else
    {
        cout<<"Rejected\n";
    }
    return 0;
}

int S()
{
    cout<<"S\n";
    int err1=E();
    if(err1==-1)
    {
        return -1;
    }
    return 1;
}
int E()
{
    cout<<"E\n";
    int err1=T();
    int err2=E1();
    if(err1==-1 || err2==-1)
    {
        return -1;
    }
    return 1;
}
int T()
{
    cout<<"T\n";
    int err1=F();
    int err2=T1();
    if(err1==-1 || err2==-1)
    {
        return -1;
    }
    return 1;
}
int E1()
{
    cout<<"E1\n";
    if(input[i]=='+')
    {
        match('+');
        int err1=T();
        int err2=E1();
        if(err1==-1 || err2==-1)
        {
            return -1;
        }
    }
    else if(input[i]=='-')
    {
        match('-');
        int err1=T();
        int err2=E1();
        if(err1==-1 || err2==-1)
        {
            return -1;
        }
    }
    else
    {
        return 1;
    }
    return 1;
    
}
int T1()
{
    cout<<"T1\n";
    if(input[i]=='*')
    {
        match('*');
        int err1=F();
        int err2=T1();
        if(err1==-1 || err2==-1)
        {
            return -1;
        }
    }
    else if(input[i]=='/')
    {
        match('/');
        int err1=F();
        int err2=T1();
        if(err1==-1 || err2==-1)
        {
            return -1;
        }
    }
    else
    {
        return 1;
    }
    return 1;
    
}

int F()
{
    cout<<"F\n";
    if(input[i]>='0' && input[i]<='9')
    {
        match(input[i]);
        return 1;
    }
    else if(input[i]>='a' && input[i]<='z')
    {
        match(input[i]);
        return 1;
    }
    return -1;
}

void match(char t)
{
    cout<<"match\n";
    if(input[i]==t)
    {
        i++;
    }
    else
    {
        cout<<"Error\n";
    }
}