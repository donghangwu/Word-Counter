#include "editing.h"

editing::editing()
{

    totalWordcounts = 0;
    totalParagraphs=0;
    linecount = 0;

    syllables=0;
}

editing::~editing()
{

    totalWordcounts = 0;
    totalParagraphs=0;
    linecount = 0;
    syllables=0;
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
    tencount=other.tencount;
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
        tencount=other.tencount;
        syllables=other.syllables;
    }
    return *this;

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
                    orchard[int(word[0])-97].insert(word,linecount,totalParagraphs);
                    totalWordcounts++;

                }

            }
        }
        else
        {
            totalParagraphs++;
        }
    }while(getline(openf,line));
    tenmost();
    totalParagraphs-=orchard[2].occurence("chapter");


    double endtime=clock();
    cout << "time: " << (endtime-starttime)/double(CLOCKS_PER_SEC)<<" seconds \n";
}

void editing::openfile(ifstream &openf, string &filename)
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
        cout<<"fail to open file: "<<filename<<endl;
        cout<<"please enter a new file name:  ";
        getline(cin,filename);
        if(filename.find(".") == string::npos)
        {
            filename+=".txt";
        }
        openf.open(filename);

    }
}

void editing::countsyllables(string word)
{
    int counts;
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
void editing::tenmost()
{

    heapTree<string> copysub[26];
    for(int i =0;i<26;++i)
    {
        copysub[i]=orchard[i];
    }

    int smallest=0;
    int counts=0;
    string newstr;
    for(int i=0;i<26;++i)
    {
        do
        {
            copysub[i]>>newstr;
            counts++;
            if(newstr != copysub[i][1])
            {
                if(bigten.size()<10)
                {
                    if(bigten.size()<1||bigten.back()!=newstr)
                    {
                        bigten.push_back(newstr);
                        tencount.push_back(counts);
                    }
                }
                else
                {
                    if(norepeat(bigten,newstr))
                    {
                        for(int n=0;n<10;n++)
                        {
                            if(tencount[smallest] > tencount[n])
                            {
                                smallest=n;
                            }
                        }
                        if(tencount[smallest] < counts  )
                        {
                            tencount[smallest]=counts;
                            bigten[smallest]=newstr;
                            smallest=0;
                        }
                    }
                }
                counts=0;
            }
        }while(copysub[i].ptr.size()>0);
    }
    sorting(bigten,tencount);

for(int i =0;i<10;++i)
{
    bigten[i][0]=toupper(bigten[i][0]);
}

}

void editing::sorting(vector<string>&words,vector<int>& counts)
{
    int temp;
    string str;
    for(int i =0;i<10;++i)
    {
        for(int n=0;n<10;++n)
        {
            if(counts[i] >counts[n])
            {
                temp=counts[i];
                counts[i]=counts[n];
                counts[n]=temp;
                str=words[i];
                words[i]=words[n];
                words[n]=str;
            }
        }
    }
}

bool editing::norepeat(vector<string> words,string word)
{
    for(int i = 0;i<words.size();++i)
    {
        if(words[i] == word)
        {
            return false;
        }
    }
    return true;
}

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

void editing::summary(ostream &out)
{

    out<<"word count: "<<totalWordcounts<<endl;
    out<<"paragraph: "<<totalParagraphs<<endl;
    out<<"top ten words are: \n";
    for(int i =0;i<10;++i)
    {
        out<<setw(8)<<bigten[i]<<": "<<setw(12)<<tencount[i]<<"   ";
        if((i+2)%4==1)
        {
            out<<'\n';
        }
    }
    out<<'\n';
    for(int i =0;i<26;i++)
    {
        out<<char('A'+i)<<": "<<orchard[i].datasize()-1<<"    ";
        if((i+2)%4==1)
        {
            out<<'\n';
        }
    }
    out<<'\n';
    out<<"reading level: "<<readinglevel()<<"th grade \n";


}
void editing::A_Z()
{
    stringstream ss;
    string copys;
    string line;
    for(int i =0 ;i<26;i++)
    {
        ss<<char('A'+i)<<": \n";
        ss<<orchard[i]<<endl;
     }
    while(getline(ss,line))
    {
        copys+=line;
        cout<<line<<endl;
    }
    saving(copys);
}
void editing::saving(const string& realwhole)
{
    ofstream savefile;
    string answer,filename;
    cout<<"\ndo you want to save anything? \n"
          " enter 0 to save the summary "
          "enter 1-26 to save all the words start with that alphbet\n"
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
    if(savefile.fail())
    {
        cout<<"fail to open "<<filename<<"\n";
        exit(3);
    }

    do
    {
     if(answer[0]=='0')
     {
         summary(savefile);
     }
     else if(answer.size()==2&& isdigit(answer[0]) && !isdigit(answer[1]))
     {
         cout<<"you cannot do this \n";
     }
     else if(isdigit(answer[0])&&answer.size()<=2 && stoi(answer)<=26)
     {
         if(isdigit(answer[0]))
         {
             answer=stoi(answer)+64;
             answer[0]=toupper(answer[0]);
             answer=answer+=": ";
             string whole,fragment,next;
            whole=realwhole.substr(realwhole.find(answer),realwhole.size());
            if(answer[0]!=90)
            {
                next=answer[0]+1;
                next+=": ";
                fragment=whole.substr(0,whole.find(next));
            }
            else
            {
                fragment=whole;
            }
            savefile<<fragment;

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
            answer[0]=toupper(answer[0]);
            cout<<"saving "<<answer<<endl;
            answer+=" count";
            string whole,fragment;

               whole=realwhole.substr(realwhole.find(answer),realwhole.size());
               fragment=whole.substr(0,whole.find('\a'));

           savefile<<fragment<<'\n';
        }
        else
        {
            cout<<"could not found the word you entered\n";
        }
     }
        cout<<"do you want to save anything else? \n";
        getline(cin,answer);
    }while((answer.length()>=1));

    savefile.close();

}
