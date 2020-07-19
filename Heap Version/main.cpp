#include <iostream>
#include<ctime>
#include"heaptree.h"
#include"editing.h"
using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    editing test;
    test.process();
    test.summary(cout);
    string start;
    cout<<"\n press enter to start print each words\n";
    getline(cin,start);
    test.A_Z();
    return 0;
}
