#ifndef EDITING_H
#define EDITING_H
#include<vector>
#include<string>
#include<sstream>
#include<algorithm>
#include<iostream>
#include<fstream>
#include"heaptree.h"
#include<iomanip>
using namespace std;
class editing
{
public:
    //constructor
    editing();
    //destructor
    ~editing();
    //copy constructor
    editing(const editing& other);
    //assigment operator
    editing &operator =(const editing&other);
    //processing book
    void process();
    //check if is word
    bool checkingword(string word);
    //spearte the puncuation
    void separted(string &word);
    //no numeric constant
    void NONumeric(string &line);
    //open reading file
    void openfile(ifstream &openf, string &filename);
    //summary of book
    void summary(ostream &out);
    //count syllables
    void countsyllables(string word);
    //determin reading level
    int readinglevel();
    //find ten most frequency words
    void tenmost();
    //saving datas
    void saving(const string &realwhole);
    //sorting top ten words
    void sorting(vector<string>&words, vector<int> &counts);
    //check no repeats
    bool norepeat(vector<string> words, string word);
    //print A-Z words;
    void A_Z();

private:
    heapTree<string> orchard[26];
    unsigned int totalWordcounts;
    unsigned int totalParagraphs;
    unsigned int linecount;
    vector<string> bigten;
    vector<int> tencount;
    unsigned long int syllables;
};



#endif // EDITING_H
