#include "editing.h"

editing::editing()
{

    totalWordcounts=0;
    totalParagraphs=1;
    linecount=0;
}
editing::~editing()
{
    for(int i=0;i<26;++i)
    {
        orchard[i].~binaryTree();
    }
}
editing::editing(const editing& other)
{
    for(int i =0;i<26;++i)
    {
        orchard[i]=other.orchard[i];
    }
    totalWordcounts = other.totalWordcounts;
    totalParagraphs=other.totalParagraphs;
    linecount = other.linecount;
    bigten=other.bigten;
    syllables=other.syllables;
}
editing &editing::operator =(const editing&other)
{
    if(this!=&other)
    {
        for(int i =0;i<26;++i)
        {
            orchard[i]=other.orchard[i];
        }
        totalWordcounts = other.totalWordcounts;
        totalParagraphs=other.totalParagraphs;
        linecount = other.linecount;
        bigten=other.bigten;
        syllables=other.syllables;
    }
    return *this;

}
void editing::openfile(ifstream& openf,string &filename)
{
    cout<<"please enter the file name you want to open: ";
    getline(cin,filename);
    if(filename.find(".") == string::npos)
    {
        filename+=".txt";
    }
    openf.open(filename);
    while(openf.fail())
    {
        cout<<"fail to open file: "<<filename<<'\n';
        cout<<"please enter a new file name:  ";
        getline(cin,filename);
        if(filename.find(".") == string::npos)
        {
            filename+=".txt";
        }
        openf.open(filename);

    }
}


void editing::process()
{
    ifstream openf;
    string filename;
    string line,word;
    stringstream ss;
    vector<string> store;
    store.clear();
    openfile(openf,filename);
    double starttime=clock();
    while(line.size()<66)//clear the table of contents
    {
        getline(openf,line);
    }
    do
    {
        if(!line.empty())
        {
            ss=stringstream();
            linecount++;
            NONumeric(line);

            ss<<line;
            while(ss>>word)
            {
                if(checkingword(word))
                {
                    separted(word);
                }
                if(isalpha(word[0]))
                {
                    orchard[int(word[0])-97].insert(word,1,linecount,totalParagraphs);

                    tenmost(word);
                    totalWordcounts++;

                }

            }
        }
        else
        {
            totalParagraphs++;
        }
    }while(getline(openf,line));

    double endtime=clock();
    cout << "time: " << (endtime-starttime)/double(CLOCKS_PER_SEC)<<" seconds \n";
    openf.close();
}

void editing::tenmost(string word)
{
    if(bigten.size()<10)
    {
        bigten.push_back(word);
    }
    else
    {
        for(int i=0;i<9;++i)
        {
            for(int j =i+1;j<10;++j)
            {
                if(orchard[bigten[i][0]-97].dataCount(bigten[i]) <orchard[bigten[j][0]-97].dataCount(bigten[j]) )
                {
                    string temp=bigten[i];
                    bigten[i]=bigten[j];
                    bigten[j]=temp;

                }
            }
        }
        if(orchard[bigten.back()[0]-97].dataCount(bigten.back()) < orchard[int(word[0])-97].dataCount(word))
        {
            if(word!=bigten[0] &&word!=bigten[1]&&word!=bigten[2]&&word!=bigten[3]&&word!=bigten[4]&&word!=bigten[5]&&word!=bigten[6]&&word!=bigten[7]&&word!=bigten[8]&&word!=bigten[9] )
            bigten.back()=word;
        }
    }

}

void editing::countsyllables(string word)
{
    int counts=0;
    for(int i =0; i<word.size();++i)
    {
        if(word[i]=='a'||word[i]=='e'||word[i]=='i'||word[i]=='o'||word[i]=='u')
        {
            if(i+1 < word.size())
            {
                if(word[i+1]=='a'||word[i+1]=='e'||word[i+1]=='i'||word[i+1]=='o'||word[i+1]=='u')
                {

                }
                else
                {
                    counts++;
                }
            }
            else
            {
                counts++;
            }

        }
    }

    if(counts==0)
    {
        syllables++;
    }
    else
    {
        syllables+=counts;
    }
}

int editing::readinglevel()
{
     int result;
    result=(0.39*totalWordcounts / linecount )+ (11.8*syllables/totalWordcounts) -15.59;
    return abs(result);
}

void editing::saving()
{
    ofstream savefile;
    string answer,filename;
    cout<<"\ndo you want to save anything? \n"
          " enter 0 to save the summary "
          "enter 1-26 to save all words start with that alphabet\n"
          "enter any word to save the information about that word \n"
          "just hit enter key to exit the program \n";
    getline(cin,answer);
    if(!answer.empty())
    {
        cout<<"please enter a filename :\n";
        getline(cin,filename);
    }
    else
    {
        exit(66);
    }
    if(filename.find(".")==string::npos)
    {
        filename+=".txt";
    }
    savefile.open(filename);

    do
    {
     if(answer[0]=='0')
     {
         savefile<<"word count: "<<totalWordcounts<<'\n';
         savefile<<"paragraph: "<<totalParagraphs<<'\n';
         savefile<<"reading level: "<<readinglevel()<<"th grade \n";
         savefile<<"most frequntly words are: \n";
         for(int i =0;i<10;i++)
         {
             bigten[i][0]=toupper(bigten[i][0]);
             savefile<<bigten[i]<<'\n';
             bigten[i][0]=tolower(bigten[i][0]);
             savefile<<": "<<orchard[bigten[i][0]-97].dataCount(bigten[i]) <<'\n';
         }
         for(int i =0;i<26;++i)
         {
             savefile<<char('A'+i)<<": "<<orchard[i].totalDataCount()<<"     ";
             if((i+2)%3==1)
             {
                 savefile<<'\n';
             }
         }
     }
     else if(answer.size()==2&& isdigit(answer[0]) && !isdigit(answer[1]))
     {
         cout<<"you cannot do this \n";
     }
     else if(isdigit(answer[0]) && answer.size()<=2 &&stoi(answer)<=26)
     {
         int index=stoi(answer)-1;
         if(!orchard[index].empty())
            {savefile<<orchard[index];
            orchard[index].clear();}
         else
         {
             cout<<"could not find data \n";
         }
     }
     else
     {
         for(int i=0;i<answer.size();i++)
         {
             if(isalpha(answer[i]))
             {
                 answer[i]=tolower(answer[i]);
             }
         }
        if(isalpha(answer[0])&& orchard[answer[0]-97].find(answer))
        {

          savefile<<'\n'<<*(orchard[answer[0]-97].findnode(answer));
          orchard[answer[0]-97].removeAll(answer);
        }
        else
        {
            cout<<"could not found the word you entered\n";
        }
     }
        cout<<"do you want to save anything else? \n";
        answer.clear();
        getline(cin,answer);
    }while((answer.length()>0));

    savefile.close();

}

//clear numbers and hyphen
void editing::NONumeric(string &line)
{
    for(int i =0;i<line.size();i++)
    {
        if(isdigit(line[i]))
        {
            line.erase(line.begin()+i);
            --i;
        }
    }
    for(int i =0; i<line.size();++i)
    {
        if(line[i]=='-'||line[i]=='/'||line[i]==','||line[i]=='.'||line[i]=='?'||line[i]=='*'||line[i]=='('||line[i]==')')
        {
            line[i]=' ';
        }
    }
    if(line.size()>8&&line.substr(0,7)=="CHAPTER")
    {
        line.erase(line.begin()+7,line.end());
    }
}
bool editing::checkingword(string word)
{
    for(int i =0;i<word.size();i++)
    {
        if(isalpha(word[i]))
        {
            return true;
        }
    }
    return false;
}
void editing::separted(string &word)
{
    while(!isalpha(word[0]))
    {
        word.erase(word.begin());
    }
    while (!isalpha(word[word.length()-1]))
    {
        word.erase(word.end()-1);
    }
    for(int i=0;i<word.size();++i)
    {
        if(isalpha(word[i]))
        {
            word[i]=tolower(word[i]);
        }
    }
}

void editing::summary()
{
    cout<<"word count: "<<totalWordcounts<<'\n';
    cout<<"paragraph: "<<totalParagraphs<<'\n';

    cout<<"reading level: "<<readinglevel()<<"th grade \n";
    cout<<"most frequntly words are: \n";
    for(int i =0;i<10;i++)
    {
        bigten[i][0]=toupper(bigten[i][0]);
        cout<<bigten[i];
        bigten[i][0]=tolower(bigten[i][0]);
          cout    <<": "<<orchard[bigten[i][0]-97].dataCount(bigten[i]) <<'\n';
    }
    for(int i =0;i<26;++i)
    {
        cout<<char('A'+i)<<": "<<orchard[i].totalDataCount()<<"     ";
        if((i+2)%3==1)
        {
            cout<<'\n';
        }
    }
    string start;
    cout<<"\n press enter to start print each words\n";
    getline(cin,start);
    for(int i =0 ;i<26;i++)
    {
        cout<<char('A'+i)<<": \n";
        cout<<orchard[i]<<'\n';
    }

}
