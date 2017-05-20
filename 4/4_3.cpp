/*****************************************************************************
Copyright (c) [2017] [Blandizzi Pietro]

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*********************************************************************************/

#include <iostream>
#include <vector>
#include <queue>
#include <list>


using std::vector;
using std::queue;
using std::pair;
using std::list;

//simple BT
class NodeBT
{
public:
    int data;
    NodeBT* left;
    NodeBT* right;
};

class NodeL
{
public:
    NodeBT* data;
    NodeL* next;
};
//my Idea of doing it with BFS
void listOfDepths (NodeBT* root, vector<NodeL*>& lists)
{
    queue<pair<NodeBT*,int>> q;
    pair<NodeBT*,int> p;
    p =std::make_pair (root,0);
    q.push(p);

    while (!q.empty()) {
        pair<NodeBT*,int> n = q.front();
        q.pop();
        NodeL* l = new NodeL;
        l->data = n.first;
        l->next = nullptr;
        if (lists.empty() || lists.size()-1 < n.second) {
        lists.push_back(l);
        }
        else {
        NodeL* t =  lists[n.second];
        //tail insert
        while (t->next != nullptr)
            t = t->next;

        t->next = l;
        }
        NodeBT* left = n.first->left;
        NodeBT* right = n.first->right;
        if (left != nullptr) {
            p = std::make_pair (left, n.second+1);
            q.push (p);
        }
        if (right != nullptr) {
            p = std::make_pair (right, n.second+1);
            q.push (p);
        }
    }
}
//using stl library
void listOfDepthsV2 (NodeBT* root, vector<list<NodeBT*>>& lists)
{
   list<NodeBT*> l;
   if (root != nullptr) {
       l.push_back(root);
   }

   while (l.size()>0) {
    //add the previous level
    lists.push_back(l);
    list<NodeBT*> parents(l);
    l.clear();
    list<NodeBT*>::iterator it;

    for (it = parents.begin(); it != parents.end(); it++) {

        if ((*it)->left != nullptr) {
            l.push_back((*it)->left);
        }

        if ((*it)->right != nullptr) {
            l.push_back((*it)->right);
        }
    }
   }
}

void listOfDepthsV3 (NodeBT* root, vector<list<NodeBT*>>& lists, int level)
{
    if (root == nullptr)
        return;

    if (lists.size() == level)
    {
        list<NodeBT*> l;
        l.push_back(root);
        lists.push_back(l);

    }else {
        lists[level].push_back(root);
    }

    listOfDepthsV3 (root->left,lists,level+1);
    listOfDepthsV3 (root->right,lists,level+1);

}

typedef std::vector<NodeL*>::size_type v_size;

void printAllTheLists ( vector<NodeL*>& lists)
{
    for (v_size i = 0; i< lists.size();i++) {
        NodeL* h = lists[i];
        while (h!=nullptr) {
            std::cout << h->data->data << " ";
            h = h->next;
        }
        std::cout << std::endl;
    }
}

void printAllTheLists ( vector<list<NodeBT*>>& lists)
{
    for (v_size i = 0; i< lists.size();i++) {
        list<NodeBT*>::iterator it;
    for (it = lists[i].begin(); it != lists[i].end(); it++) {
        std::cout << (*it)->data << " ";
        }
        std::cout << std::endl;
    }
}

NodeBT* addData(int i)
{
    if (i > 3)
        return nullptr;

    NodeBT *n = new NodeBT;
    n->data = i;
    n->left = addData(i+1);
    n->right = addData(i+2);

    return n;

}

void printTree (NodeBT* n)
{
    if (n == nullptr)
        return;
    std::cout << n->data << " " << std::endl;
    printTree (n->left);
    printTree(n->right);
}


int main()
{
    //Create the three

    NodeBT* root = addData(0);

    vector<NodeL*> v;
    listOfDepths(root,v);
    std::cout << "array size" << v.size() << std::endl;
    printAllTheLists(v);
    std::cout << std::endl;
    printTree(root);

    vector<list<NodeBT*>> v1;
    listOfDepthsV2(root,v1);
    std::cout << "array size" << v1.size() << std::endl;
    printAllTheLists(v1);
    std::cout << std::endl;
    printTree(root);

    vector<list<NodeBT*>> v2;
    listOfDepthsV3(root,v2,0);
    std::cout << "array size" << v2.size() << std::endl;
    printAllTheLists(v2);
    std::cout << std::endl;
    printTree(root);

    return 0;
}
