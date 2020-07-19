#ifndef BINARYTREE_H
#define BINARYTREE_H
#include <iostream>
#include <fstream>
#include <cstdlib>
#include "node.h"

using namespace std;

enum BINARY_TREE_TRAVERSAL {INORDER, PREORDER, POSTORDER};
template<typename T>
class binaryTree
{
public:
    //constructor
    binaryTree();
    //overload constructor
    binaryTree(const T &data, unsigned int c = 1);
    //destructor
    ~binaryTree();
    //copy constructor
    binaryTree(const binaryTree<T> &other);
    //assignment operator
    binaryTree<T>& operator=(const binaryTree<T> &other);

    //check empty
    bool empty() const;
    //return the smallestnode
    T smallestNode() const;
    //return largest node
    T largestNode() const;
    //find node
    node<T>* findnode(const T&data);
    //return total data occuerance
    unsigned int totalDataCount();
    //data count
    unsigned int dataCount(const T &d) const;
    //how many node
    unsigned int nodeCount();
    //level #
    unsigned int depth() const;
    //check balacned or not
    bool balanced();
    //recursive call balance
    bool balanced(node<T> *current);
    //rebalance the tree
    void rebalance();
    //clear the tree;
    void clear();
    //set traversal
    void setTraversal(BINARY_TREE_TRAVERSAL t);
    //get traversal type
    BINARY_TREE_TRAVERSAL getTraversal();
    //extract data
    binaryTree<T>& operator<<(const T &data);
    //insert data
    void insert(const T& data, unsigned int c = 1, unsigned int line=0, unsigned int paragraph=0, vector<int> linev=vector<int>(), vector<int> paragraphv=vector<int>());
    //remove data
    bool remove(const T &data, unsigned int c = 1);
    //remove all data
    bool removeAll(const T & data);
    //find data
    bool find(const T & data) const;

    //outputing
    template<typename S>
    friend
    std::ostream& operator<<(std::ostream &out, const binaryTree<S> &tree);

    //inputting
    template<typename S>
    friend
    std::istream& operator>>(std::istream &in, binaryTree<S> &tree);


private:


    node<T>*root;
    BINARY_TREE_TRAVERSAL method;

    //copy
    void copy(node<T> *other_root);
    //delete all node
    void deleteAll(node<T>* &todelete);
    //return node
    node<T>& nodeNumbered(int nodeNumber) const;
    //find level
    unsigned int depth(node<T>* currentNode);
    //count node
    unsigned int nodeCount(node<T> * current);
    //count total data
    unsigned int totalDataCount(node<T>* currentNode);
    //count data
    unsigned int DataCount(const T &data, node<T>* currentNode, bool &check) const;
    //move one node
    void removing(node<T> *currentNode, const T& d, int c);
    //find leftest node
    node<T>*furtherestleft(node<T>* tofind);
    //find parent node
    node<T>* findparent(node<T>* child, bool &grandparentleft, bool &grandparentright);
    //find max
    int max(int x, int y);
    //recursive print
    void print(std::ostream &out, node<T> *roott) const;
    //find Depest Inbalance Node
    void findDepestInbalanceNode(node<T> *current, node<T> *&findit, bool &finish);
    //find closest To Root Inbalance Node
    void findclosestToRootInbalanceNode(node<T> *current, node<T> *&findit);



};

template<typename T>
binaryTree<T>::binaryTree()
{

        root=NULL;

    method=INORDER;


}
template<typename T>
node<T>* binaryTree<T>::findnode(const T&data)
{
    node<T> *parent,*child;

    child = root;

        while(child->data!=data)
        {
            if(data < child->data)
            {
                parent=child;
                child=child->lesser;

            }
            else//data > current.data
            {
                parent=child;
                child=child->greater;

            }
        }
        return child;

}


template<typename T>
binaryTree<T>::binaryTree(const T &data, unsigned int c)
{
    method=INORDER;
    insert(data,c);
}
template<typename T>
binaryTree<T>::~binaryTree()
{
    deleteAll(root);
}
template<typename T>
binaryTree<T>::binaryTree(const binaryTree<T> &other)
{
    copy(other);
}

template<typename T>
binaryTree<T>& binaryTree<T>::operator=(const binaryTree<T> &other)
{
    if(this!=&other)
    {
        copy(other.root);
    }
}
template<typename T>
bool binaryTree<T>::empty() const
{
    return root==NULL;
}
template<typename T>
T binaryTree<T>::smallestNode() const
{
    node<T> *temp=root;
    while(temp)
    {
        if(temp->lesser==NULL)
        {
            return temp->data;
        }
        else
            temp=temp->lesser;
    }
}
template<typename T>
T binaryTree<T>::largestNode() const
{
    node<T>* temp=root;
    while(temp)
    {
        if(temp->greater==NULL)
        {
            return temp->data;
        }
        else
        {
            temp=temp->greater;
        }

    }
}
template<typename T>
unsigned int binaryTree<T>::totalDataCount()
{
    return totalDataCount(root);
}
template<typename T>

unsigned int binaryTree<T>::dataCount(const T &d) const
{
    int co=0;
    bool check=false;
    node<T> *ptr=root;
    if(root)
    {
        co= DataCount(d,ptr,check);
        if(check)
        {
            return co;
        }
        else
        {
            return 0;
        }
    }
    else
    {
        return 0;
    }
}
template<typename T>
unsigned int binaryTree<T>::nodeCount()
{
    return nodeCount(root);
}
template<typename T>
unsigned int binaryTree<T>::depth() const
{
    return depth(root);
}
template<typename T>
node<T>* binaryTree<T>::findparent(node<T>* child,bool&grandparentleft,bool&grandparentright)
{
    node<T>* parent=root;
    if(child==root)
    {
        return NULL;
    }
    while(parent->lesser!=child && parent->greater!=child)
    {
        if(parent->data>child->data)
        {
            parent=parent->lesser;
        }
        else
        {
            parent=parent->greater;
        }
    }
    if(parent->lesser==child)
    {
        grandparentleft=true;
        grandparentright=false;
    }
    else
    {
        grandparentleft=false;
        grandparentright=true;
    }
    return parent;
}
template<typename T>
bool binaryTree<T>::balanced()
{
    return balanced(root);
}
template<typename T>
bool binaryTree<T>::balanced(node<T>* current)
{
    if(current)
    {
        if((abs(int(depth(current->lesser) - depth(current->greater))) <= 1)&&balanced(current->lesser)&&balanced(current->greater))
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else
        return true;
}
template<typename T>
void binaryTree<T>::findclosestToRootInbalanceNode(node<T> *current, node<T> *&findit)
{
    if(current)
    {
        if(abs(int((depth(current->lesser)-depth(current->greater)))) >1)
        {
            findit=current;
            return ;

        }
        else
        {
            findclosestToRootInbalanceNode(current->lesser,findit);
            findclosestToRootInbalanceNode(current->greater,findit);
        }
    }
}
template<typename T>
void binaryTree<T>::findDepestInbalanceNode(node<T> *current, node<T> *&findit,bool &finish)
{
    if(current)
    {
        findDepestInbalanceNode(current->lesser,findit,finish);
        findDepestInbalanceNode(current->greater,findit,finish);

        if((abs(int((depth(current->lesser)-depth(current->greater)))) >1) &&!finish)
        {
            findit=current;
            finish=true;
        }

    }
}
template<typename T>
void binaryTree<T>::rebalance()
{
    node<T> *parent,*child,//mid node
            *grandparent;
    bool grandparentleft,grandparentright,finsih=false;
    parent=child=root;
    while(!balanced(root))
    {

        {
            findclosestToRootInbalanceNode(root,parent);//might be rightt
            if(depth(parent->lesser) > depth(parent->greater))
            {
                child=parent->lesser;
            }
            else
            {
                child=parent->greater;
            }
        }
        if(depth(parent->lesser)>depth(parent->greater))//LEFT-
        {
            if(depth(child->lesser) >= depth(child->greater))
                //LEFT-LEFT
            {
                grandparent=findparent(parent,grandparentleft,grandparentright);
                if(parent==root)
                {
                    parent->lesser=child->greater;
                    child->greater=parent;
                    root=child;
                }
                else if(grandparentleft)
                {
                    parent->lesser=child->greater;
                    child->greater=parent;
                    grandparent->lesser=child;
                }
                else if(grandparentright)
                {
                    parent->lesser=child->greater;
                    child->greater=parent;
                    grandparent->greater=child;
                }
            }
            else if(depth(child->lesser) < depth(child->greater))
                //LEFT-RIGHT
            {
                grandparent=findparent(parent,grandparentleft,grandparentright);
                node<T> *grandchild=child->greater;
                child->greater=grandchild->lesser;
                grandchild->lesser=child;
                parent->lesser=grandchild->greater;
                grandchild->greater=parent;
                if(parent==root)
                {
                    root=grandchild;
                }
                else if(grandparentleft)
                {
                    grandparent->lesser=grandchild;
                }
                else if(grandparentright)
                {
                    grandparent->greater=grandchild;
                }
            }
            else//unexpect happens
            {
            }
        }
        else if(depth(parent->lesser)<depth(parent->greater))//RIGHT-
        {
            if(depth(child->lesser) <= depth(child->greater))
                //RIGHT-RIGHT
            {
                grandparent=findparent(parent,grandparentleft,grandparentright);
                if(parent==root)
                {
                    parent->greater=child->lesser;
                    child->lesser=parent;
                    root=child;
                }
                else if(grandparentleft)
                {
                    parent->greater=child->lesser;
                    child->lesser=parent;
                    grandparent->lesser=child;
                }
                else if(grandparentright)
                {
                    parent->greater=child->lesser;
                    child->lesser=parent;
                    grandparent->greater=child;
                }
            }
            else if(depth(child->lesser) > depth(child->greater))
                //RIGHT-LEFT
            {
                grandparent=findparent(parent,grandparentleft,grandparentright);
                node<T>* grandchild;
                grandchild=child->lesser;
                child->lesser=grandchild->greater;
                grandchild->greater=child;
                parent->greater=grandchild->lesser;
                grandchild->lesser=parent;
                if(parent==root)
                {
                  root=grandchild;
                }
                else if(grandparentleft)
                {

                    grandparent->lesser=grandchild;
                }
                else
                {
                    grandparent->greater=grandchild;
                }

            }
            else//unexpect
            {
            }
        }
        else
        {
        }

    }
}
template<typename T>
void binaryTree<T>::clear()
{
    deleteAll(root);
    root=NULL;
}
template<typename T>
void binaryTree<T>::setTraversal(BINARY_TREE_TRAVERSAL t)
{
    method=t;
}
template<typename T>
BINARY_TREE_TRAVERSAL binaryTree<T>::getTraversal()
{
    return method;
}
template<typename T>
binaryTree<T>& binaryTree<T>::operator<<(const T &data)
{
    insert(data);
}
template<typename T>
void binaryTree<T>::insert(const T& data, unsigned int c, unsigned int line, unsigned int paragraph,vector<int>linev,vector<int>paragraphv)
{

    node<T>* newnode;
    if(line&&paragraph)
    {
        newnode= new node<T>(data,c,line,paragraph);
    }
    else
    {
        newnode =  new node<T>(data,c,linev,paragraphv);
    }
    node<T>* top=root;
    bool exist=true;
    if(root==NULL)
    {
        root=newnode;
        return;
    }
    else
    {
        while(top&& exist)
        {
            if(top->data == data)
            {
                top->count+=newnode->count;
                top->line.push_back(line);
                top->paragraph.push_back(paragraph);
                delete newnode;
                exist=false;
                return;
            }
            else if(data < top->data)
            {
                if(top->lesser)
                {
                    top=top->lesser;
                }
                else
                {
                    exist=false;
                }

            }
            else if(data>top->data)
            {
                if(top->greater)
                {
                    top=top->greater;
                }
                else
                {
                    exist=false;
                }

            }

        }
        if(data< top->data)
        {
            top->lesser=newnode;
        }
        else
        {
            top->greater=newnode;
        }
        rebalance();
    }

}
template<typename T>
bool binaryTree<T>::remove(const T &data, unsigned int c )
{
    node<T> *ptr=root;
    if(find(data))
    {
        if(dataCount(data)<=c)
        {
            removeAll(data);
        }
        else
        {
            cout<<"removing "<<data<<endl;
            removing(ptr,data,c);
            return true;
        }

    }
    else
    {
        return 0;
    }
}
template<typename T>
void binaryTree<T>::removing(node<T> *currentNode,const T& d,int c)
{
    if(currentNode)
    {
        if(currentNode->data==d)
        {
            currentNode->count-=c;
            return;
        }
        else
        {
            removing(currentNode->lesser,d,c);
            removing(currentNode->greater,d,c);
        }
    }
}
template<typename T>
bool binaryTree<T>::removeAll(const T & data)
{
    node<T> *parent,*child;
    bool left=false,right=false;
    child = root;
    if(find(data))
    {
        while(child->data!=data)
        {
            if(data < child->data)
            {
                parent=child;
                child=child->lesser;
                left=true;
                right = false;
            }
            else
            {
                parent=child;
                child=child->greater;
                right = true;
                left = false;
            }
        }
        if(child==root)
        {
            node<T> *leftchild;
            if(root->greater)
            {
                if(root->lesser)
                {
                    leftchild=furtherestleft(root->greater);
                    leftchild->lesser=root->lesser;
                    root=root->greater;
                }
                else
                {
                    root = root->greater;
                }
            }
            else
            {
                root=root->lesser;
            }
        }
        else if(left)
        {
            node<T> *leftchild,*rightchild;
            if(child->greater)
            {
                if(child->lesser)
                {
                    leftchild=furtherestleft(child->greater);
                    leftchild->lesser=child->lesser;
                    parent->lesser=child->greater;
                }
                else
                {
                    parent->lesser=child->greater;

                }
            }
            else
            {
                parent->lesser=child->lesser;
            }
        }
        else if(right)
        {
            node<T> *leftchild;
            if(child->greater)
            {
                if(child->lesser)
                {
                    leftchild=furtherestleft(child->greater);
                    leftchild->lesser=child->lesser;
                    parent->greater=child->greater;
                }
                else
                {
                    parent->greater=child->greater;

                }
            }
            else
            {
                parent->greater=child->lesser;
            }
        }
        delete child;
        rebalance();
        return true;
    }
    else
    {
        return 0;
    }
}
template<typename T>
node<T>* binaryTree<T>::furtherestleft(node<T>* tofind)
{
    if(tofind->lesser==NULL)
    {
        return tofind;
    }
    while(tofind->lesser)
    {
        tofind=tofind->lesser;
    }
    return tofind;
}
template<typename T>
bool binaryTree<T>::find(const T & data) const
{
    return dataCount(data);
}

template<typename T>
void binaryTree<T>::copy( node<T>* other_root)
{
    if(other_root)
    {
        insert(other_root->data,other_root->count,0,0,other_root->line,other_root->paragraph);
        copy(other_root->lesser);
        copy(other_root->greater);
    }
}
template<typename T>
void binaryTree<T>::deleteAll(node<T>* &todelete)
{
    if(todelete)
    {
        deleteAll(todelete->lesser);
        deleteAll(todelete->greater);
        delete todelete;
        todelete=NULL;
    }
}


template<typename T>
unsigned int binaryTree<T>::depth(node<T>* currentNode)
{
    if(currentNode)
    {
        return 1+ max(depth(currentNode->lesser),depth(currentNode->greater));
    }
    else
    {
        return 0;
    }
}
template<typename T>
unsigned int binaryTree<T>::nodeCount(node<T>* currentNode)
{
    if(currentNode)
    {
        return (1+ nodeCount(currentNode->lesser) + nodeCount(currentNode->greater));
    }
    else
    {
        return 0;
    }
}
template<typename T>
unsigned int binaryTree<T>::totalDataCount(node<T>* currentNode)
{
    if(currentNode)
    {
        return (currentNode->count + totalDataCount(currentNode->lesser) + totalDataCount(currentNode->greater));

    }
    else
    {
        return 0;
    }
}
template<typename T>
unsigned int binaryTree<T>::DataCount(const T& data,node<T>* currentNode,bool&check)const
{
    if(currentNode)
    {
        if(currentNode->data==data)
        {
            check=true;
            return currentNode->count;
        }
        else
        {
            if(data<currentNode->data)
            {DataCount(data,currentNode->lesser,check);}
            else
            {DataCount(data,currentNode->greater,check);}
        }
    }

}

template<typename T>
int binaryTree<T>::max(int x, int y)
{
    if(x>y)
    {
        return x;
    }
    else
    {
        return y;
    }
}
template<typename T>
void binaryTree<T>::print(std::ostream &out, node<T>* roott) const
{
    if(roott)
    {
        if(method==PREORDER)
            out<<(*roott);
        print(out,roott->lesser);
        if(method== INORDER)
            out<<(*roott);
        print(out,roott->greater);
        if(method==POSTORDER)
            out<<(*roott);
    }
}


template<typename S>
std::ostream& operator<<(std::ostream &out, const binaryTree<S> &tree)
{
    tree.print(out,tree.root);
    return out;
}


template<typename S>
std::istream& operator>>(std::istream &in, binaryTree<S> &tree)
{
    string line;
    stringstream ss;
    node<S> newnode;
    do
    {
        ss=stringstream();
        getline(in,line);

        if(!line.empty())
        {
            ss<<line;
            ss>>newnode;
            tree.insert(newnode.data,newnode.count);
        }
    }while(!line.empty());
    return in;
}


#endif // BINARYTREE_H
