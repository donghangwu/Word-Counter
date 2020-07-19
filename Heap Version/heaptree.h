#ifndef HEAPTREE_H
#define HEAPTREE_H
#include<iostream>
#include<bitset>
#include<fstream>
#include<vector>
#include<sstream>
#include<string>
#include<algorithm>
using namespace std;
enum HEAP_ERROR{HEAP_EMPTY,ILLEGAL_CHANGE};
enum HEAP_TYPE{LESSER,GREATER};

template<typename T>
class heapTree
{
public:
    //constructor
    heapTree();
    //destructor
    ~heapTree();
    //copy constructor
    heapTree(const heapTree<T>& other);
    //assignment operator
    heapTree<T> &operator =(const heapTree<T>&other);
    //insertion
    heapTree<T> &operator <<(const T& data);
    //extract data
    heapTree<T> &operator >>(T& data);
    //inerting data
    void insert(const T&data,int line,int paragraph);
    //check if empty
    bool empty();
    //return size of heap
    int size() const;
    //find data zie
    int datasize()const;
    //check if data exists
    bool find(const T &data);
    //print data
    void printnode(const T&data,ostream &out);
    //get travesal type
    HEAP_TYPE gettype();
    //set travesla type
    void setHeap_Type(HEAP_TYPE type);
    //find occuerence of data
    int occurence(const T&data);
    //return data
    T& operator [](unsigned int n);
    //return data
    T operator [](unsigned int n) const;
    vector<int>ptr;

    template<typename F>
    friend
    ostream& operator<<(std::ostream &out,  heapTree<F> &n);


    template<typename F>
    friend
    istream& operator>>(std::istream &in, heapTree<F> &n);




private:
    vector<T> mydata;
    vector<int> lineNUM;
    vector<int> paragraphNUM;
    unsigned int mysize;//lastentered
    HEAP_TYPE type;
    //find parent
    void parent(unsigned int n);
    //find child
    void child(unsigned int n);
    //delete all
    void deleteAll();
    //reheap upward
    void shuffleUp();
    //reheap downward
    void shuffleDown();
    //swap two data
    void swap(int &x, int &y);
};

template<typename T>
heapTree<T>::heapTree()
{
    mydata.clear();
    lineNUM.clear();
    paragraphNUM.clear();
    ptr.clear();
    mysize=0;
    mydata.push_back("\0");
    lineNUM.push_back(0);
    paragraphNUM.push_back(0);
    ptr.push_back(0);
    type=GREATER;
}
template<typename T>
heapTree<T>::~heapTree()
{
    mydata.clear();
    lineNUM.clear();
    paragraphNUM.clear();
    ptr.clear();
    mysize=0;
}
template<typename T>
heapTree<T>::heapTree(const heapTree<T>& other)
{
    mydata=other.mydata;
    lineNUM=other.lineNUM;
    paragraphNUM=other.paragraphNUM;
    ptr=other.ptr;
    mysize=other.mysize;
}
template<typename T>
heapTree<T> &heapTree<T>::operator =(const heapTree<T>&other)
{
    if(this!=&other)
    {
        mydata=other.mydata;
        lineNUM=other.lineNUM;
        paragraphNUM=other.paragraphNUM;
        ptr=other.ptr;
        mysize=other.mysize;
    }
    return *this;
}
template<typename T>
heapTree<T> &heapTree<T>::operator <<(const T& data)
{
    mydata.push_back(data);
    mysize++;
    if(mysize>1)
    {
        shuffleUp();
    }
}



template<typename T>
bool heapTree<T>::empty()
{
    return mydata.size()==1;
}
template<typename T>
int heapTree<T>::size()const
{
    return mysize;
}

template<typename T>
int heapTree<T>::datasize()const
{
    return mydata.size();
}
template<typename T>
HEAP_TYPE heapTree<T>::gettype()
{
    return type;
}
template<typename T>
void heapTree<T>::setHeap_Type(HEAP_TYPE t)
{
    if(mysize>0)
    {
        throw ILLEGAL_CHANGE;
    }
    type=t;
}


template<typename T>
T& heapTree<T>:: operator [](unsigned int n)
{
    return mydata[ptr[n]];
}
template<typename T>
T heapTree<T>:: operator [](unsigned int n) const
{
    return mydata[ptr[n]];
}
template<typename T>
void  heapTree<T>::deleteAll()
{
    mydata.clear();
    mysize=0;
}
template<typename T>
void  heapTree<T>::shuffleUp()
{
    unsigned int location;
    location=mysize;
    if(type==LESSER)
    {
        while(location>1 && mydata[ptr[location]] > mydata[ptr[(location)/2]])
        {
            swap(ptr[location],ptr[(location)/2]);
            location=location/2;
        }
    }
    else
    {
        while(location>1 && mydata[ptr[location]] <  mydata[ptr[(location)/2]])
        {
            swap(ptr[location],ptr[(location)/2]);
            location=location/2;
        }
    }

}
template<typename T>
void  heapTree<T>::shuffleDown()
{
    unsigned int location;
    location = 1;
    if(type==LESSER)
    {
        while ((location *2 <=mysize && mydata[ptr[location]] < mydata[ptr[location *2] ])
               ||((location *2) +1 <=mysize && mydata[ptr[location]] < mydata[ptr[(location*2) +1]]))
        {

            if((location *2 < mysize) && ((location*2)+1 <mysize) && mydata[ptr[location]] < mydata[ptr[location *2] ]
                    && mydata[ptr[location]] < mydata[ptr[(location *2)+1] ])
            {
                if(mydata[ptr[location*2]]< mydata[ptr[(2*location)+1]] )
                {
                    swap(ptr[location],ptr[(2*location)+1]);
                    location=(location*2)+1;
                }
                else
                {
                    swap(ptr[location],ptr[(2*location)]);
                    location=location*2;
                }
            }
            else if((location *2 <mysize && mydata[ptr[location]] < mydata[ptr[location *2 ]]))
            {
                swap(ptr[location],ptr[(2*location)]);
                location=(location*2);

            }
            else if((location *2) +1 < mysize && mydata[ptr[location]] < mydata[ptr[(location*2)+1]])
            {
                swap(ptr[location],ptr[(2*location)+1]);
                location=(location*2)+1;

            }
        }
    }else
    {
        while ((location *2 <mysize && mydata[ptr[location]] > mydata[ptr[location *2] ])
               ||((location *2) +1 < mysize && mydata[ptr[location]] > mydata[ptr[(location*2)+1]]))
        {
            if((location *2 < mysize) && ((location*2)+1 <mysize)
                    && mydata[ptr[location]] > mydata[ptr[location *2] ]
                    && mydata[ptr[location]] > mydata[ptr[(location *2)+1]])
            {
                if(mydata[ptr[location*2]]> mydata[ptr[(2*location)+1]] )
                {
                    swap(ptr[location],ptr[(2*location)+1]);
                    location=(location*2)+1;
                }
                else
                {
                    swap(ptr[location],ptr[(2*location)]);
                    location=(location*2);

                }
            }
            else if((location *2 <mysize && mydata[ptr[location]] > mydata[ptr[location *2]]))
            {
                swap(ptr[location],ptr[(2*location)]);
                location=(location*2);
            }
            else if((location *2) +1 < mysize && mydata[ptr[location]] > mydata[ptr[(location*2)+1]])
            {
                swap(ptr[location],ptr[(2*location)+1]);
                location=(location*2)+1;

            }
        }
    }

}
template<typename T>
int heapTree<T>::occurence(const T&data)
{
    int count=0;
    for(int i =0;i<mysize;++i)
    {
        if(mydata[ptr[i]] == data)
        {
            count++;
        }
    }
    return count;
}

template<typename T>
void heapTree<T>::insert(const T&data,int line,int paragraph)
{
    mydata.push_back(data);
    ptr.push_back(mydata.size()-1);
    lineNUM.push_back(line);
    paragraphNUM.push_back(paragraph);
    mysize++;
    if(mysize>1)
    {
        shuffleUp();
    }
}


template<typename T>
void  heapTree<T>::swap(int& x, int& y)
{
    x ^= y ^= x ^= y;
}


template<typename T>
bool heapTree<T>::find(const T&data)
{

    for(int i =1;i<mydata.size();i++)
    {
        if(mydata[i]==data)
        {
            return true;
        }
    }
    return false;
}
template<typename T>
void heapTree<T>::printnode(const T&data,ostream &out)
{
    for(int i =1;i<mysize;i++)
    {
        if(mydata[ptr[i]]==data)
        {
            if(mydata[ptr[i-1]] != data )//only print data once
            {
                out<<mydata[ptr[i]];
            }
            out<<" Line:"<<lineNUM[ptr[i]]<<" Paragraph: "<<paragraphNUM[ptr[i]];
        }
    }
    out<<'\n';
}

template<typename T>
heapTree<T> &heapTree<T>::operator >>(T& data)
{
    if(empty())
    {
        cout<<"empty!!"<<endl;
        throw HEAP_EMPTY;
    }
    data=mydata[ptr[1]];

    ptr[1]=ptr.back();
    ptr.pop_back();

    shuffleDown();
    mysize--;
}

template<typename F>
ostream& operator<<(std::ostream &out, heapTree<F> &n)
{

    vector<int>line,paragraph;
    int counts=0;
    string newstr;
    do
    {
        line.push_back(n.lineNUM[n.ptr[1]]);
        paragraph.push_back(n.paragraphNUM[n.ptr[1]]);
        n>>newstr;
        counts++;

        if(newstr != n[1])
        {
            newstr[0]=toupper(newstr[0]);
            if(n.ptr.empty())
            {
                counts--;
            }
            sort(line.begin(),line.end());
            line.erase( unique( line.begin(), line.end() ), line.end() );
            sort(paragraph.begin(),paragraph.end());
            paragraph.erase( unique( paragraph.begin(), paragraph.end() ), paragraph.end() );

            out<<"data: "<<newstr<<" count: "<<counts<<'\n';
            newstr[0]=tolower(newstr[0]);
            counts=0;

            out<<"line: ";
            for(int i=0;i<line.size();++i)
            {
                    out<<line[i]<<" ";
            }
            out<<'\n';
            out<<"paragraph: ";
            for(int i=0;i<paragraph.size();++i)
            {
                    out<<paragraph[i]<<" ";
            }
            out<<'\n';
            line.clear();
            paragraph.clear();
            out<<"\a";
        }
    }while(n.ptr.size()>0);



    return out;
}


template<typename F>
istream& operator>>(std::istream &in, heapTree<F> &n)
{
    string line;
    stringstream ss;
    F data;
    if(&in==&cin)
    {
        do
        {
            cout<<"data: ";
            cin>>line;
            if(!line.empty())
            {
                ss=stringstream();
                ss<<line;
                ss>>data;
                n<<data;
            }

        }while(!line.empty());
    }
    else
    {
        while(in>>data)
        {
            n<<data;
        }
    }
    return in;

}

#endif // HEAPTREE_H
