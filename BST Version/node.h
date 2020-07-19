#ifndef NODE_H
#define NODE_H
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <typeinfo>
#include <string>
#include <sstream>
#include<vector>
#include<algorithm>
using namespace std;
template<typename T>
struct node
{
    T data;
    unsigned int count;
    vector<int>line,paragraph;

    node<T>* lesser;
    node<T>* greater;
    //constructor
    node(T d=T(),int c=1,int l=0,int p=0);
    //constructor
    node(T d=T(),int c=1,vector<int> l=vector<int>(),vector<int> p=vector<int>());
    //destructor
    ~node();
    //copy constructor
    node(const node<T> &other);
    //assignment
    node<T>& operator=(const node<T> &other);
    //deleter repeat
    void deleterepeat(vector<int>&a);

    template<typename f>
    friend
    ostream& operator <<(ostream &out,const node<f>& source);

    template<typename f>
    friend
    istream&operator >>(istream &in,node<f>&takein);

    template<typename f>
    friend
    bool operator !=(const node<f> &lhs,const node<f>& rhs);

    template<typename f>
    friend
    bool operator == (const node<f> &lhs,const node<f>& rhs);

    template<typename f>
    friend
    bool operator <(const node<f> &lhs,const node<f>& rhs);

};

template<typename T>
 node<T>::node(T d, int c, int l, int p)
{
    data=d;
    count=c;
    line.clear();
    paragraph.clear();
    line.push_back(l);
    paragraph.push_back(p);
    lesser=NULL;
    greater=NULL;

}
 template<typename T>
  node<T>::node(T d, int c,vector<int> l, vector<int> p)
 {
     data=d;
     count=c;
     line=l;
     paragraph=p;
     lesser=NULL;
     greater=NULL;

 }
template<typename T>
node<T>::~node()
{
    data=T();
    count=0;
    line.clear();
    paragraph.clear();

    lesser=greater=NULL;
}
template<typename T>
node<T>::node(const node<T> &other)
{
    data=other.data;
    count = other.count;
    line =other.line;
    paragraph=other.paragraph;
    lesser=greater=NULL;
}
template<typename T>
node<T>& node<T>::operator=(const node<T> &other)
{
    if(this!=&other)
    {
        lesser=greater=NULL;
        data=other.data;
        count = other.count;
    }
}
template<typename T>
void node<T>::deleterepeat( vector<int> &a)
{
    sort( a.begin(), a.end() );
    a.erase( unique( a.begin(), a.end() ), a.end() );
}
template<typename f>
ostream& operator <<(ostream &out, node<f>& source)
{

       source.deleterepeat(source.line);
        source.deleterepeat(source.paragraph);
        f an;
        an=source.data;
        an[0]=toupper(an[0]);
        out<<"data: "<<an<<" count: "<<source.count<<" lines: ";
        for(int i=0;i<source.line.size();++i)
        {
            out<<source.line[i]<<" ";
        }
        out<<" paragraph: ";
        for(int i=0;i<source.paragraph.size();++i)
        {
            out<<source.paragraph[i]<<" ";
        }
        out<<'\n'<<'\n';


    return out;
}

template<typename f>
istream&operator >>(istream &in,node<f>&takein)
{
    string line;
    stringstream ss;

    if(&in == &cin)
    {
        cout<<"data: ";
        getline(cin,line);
        if(!line.empty())
        {
            ss<<line;
            ss>>takein.data;
            cout<<"count: ";
            cin>>takein.count;
        }
        else
        {
            getline(in,line);
            ss<<line.substr(0,line.find('\a'));
            ss>>takein.data;
            takein.count=stoi(line.substr((line.find('\a')+1),line.size()));

        }
    }
    return in;
}

template<typename f>
bool operator !=(const node<f> &lhs,const node<f>& rhs)
{
    return lhs.data!=rhs.data;
}

template<typename f>
bool operator == (const node<f> &lhs,const node<f>& rhs)
{
    return lhs.data==rhs.data;
}

template<typename f>
bool operator <(const node<f> &lhs,const node<f>& rhs)
{
    return lhs.data<rhs.data;
}

#endif // NODE_H
