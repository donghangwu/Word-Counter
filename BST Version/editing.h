#ifndef EDITING_H
#define EDITING_H
#include<string>
#include<sstream>
#include<iostream>
#include<fstream>
#include<ctime>
#include"binarytree.h"
enum alphabet{a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s,t,u,v,w,x,y,z};
class editing
{
public:
    binaryTree<string> orchard[26];

    //constructor
    editing();
    //destructor
    ~editing();
    //copy constructor
    editing(const editing& other);
    //assigment operator
    editing &operator =(const editing&other);
    //process the book
    void process();
    //check if is a word
    bool checkingword(string word);
    //separte puncuation
    void separted(string &word);
    //no numeric constant
    void NONumeric(string &line);
    //inserting
    void putin(string word, int l, int p);
    //open reading file
    void openfile(ifstream &openf, string &filename);
    //summary of book
    void summary();
    //count syllables
    void countsyllables(string word);
    //determine reading level
    int readinglevel();
    //find ten most frequency words
    void tenmost(string word);
    //saving file
    void saving();
    unsigned int totalWordcounts;
    unsigned int totalParagraphs;
    unsigned int linecount;
    vector<string> bigten;
    unsigned long int syllables;

private:


};



#endif // EDITING_H
