#include <iostream>
#include<fstream>
#include"editing.h"
using namespace std;
int main()
{
    ios_base::sync_with_stdio(false);

    editing test;
    test.process();
    test.summary();

    test.saving();

    return 0;
}
