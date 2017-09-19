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
#include <string>
#include <sstream>

using std::vector;
using std::string;

//simple BT
class NodeBT
{
public:
    int data;
    NodeBT* left;
    NodeBT* right;
    NodeBT* parent;
};


NodeBT* utilityCreate (vector<int>& v, int start,int end, NodeBT* parent)
{
   if (end < start)
        return nullptr;

    NodeBT* n = new NodeBT;
    // divide the array in two
    int middle = (start+end)/2;
    n->parent = parent;
    n->data = v[middle];
    n->left = utilityCreate (v,start, middle-1,n);
    n->right = utilityCreate (v,middle+1, end,n);

    return n;

}

NodeBT* buildMinHeightBST (vector<int>& v)
{
    return utilityCreate(v,0,v.size()-1,nullptr);
}

//preorder
void printBSTPreOrd (NodeBT* root)
{
    if (root != nullptr) {
    std::cout << root->data << std::endl;
    printBSTPreOrd (root->left);
    printBSTPreOrd (root->right);
    }
    return;
}

void printBSTInOrd (NodeBT* root)
{
    if (root != nullptr) {
    printBSTInOrd (root->left);
    std::cout << root->data << std::endl;
    printBSTInOrd (root->right);
    }
    return;
}
/**
First try without hints... bugs? case i did not consider?
**/
bool checkAll (NodeBT* n1, NodeBT* n2)
{
    if (n1 == nullptr && n2 == nullptr )
        return true;

    if (n1 == nullptr || n2 == nullptr )
        return false;

    if (n1->data != n2->data)
        return false;

    int l = checkAll(n1->left, n2->left);
    int r = checkAll(n1->right, n2->right);

     if (l == true && r == true)
        return true;

    return false;
}

bool subTree (NodeBT* n1, NodeBT* n2)
{
    if (n1 == nullptr && n2 == nullptr )
        return true;

    if (n1 == nullptr || n2 == nullptr )
        return false;

    // if the content of the nodes are the same
    if (n1->data == n2->data) {

        bool isSubTree = checkAll (n1,n2);
        if (isSubTree)
            return true;
        else return false;
    }

    int l = subTree (n1->left, n2);
    int r = subTree (n1->right, n2);

    if (l == true || r == true)
        return true;

    return false;
}
/** End first try **/
// using string in preOrder
void stringBSTPreOrd (NodeBT* node, string& s)
{
    if (node == nullptr) {
        s.append("X");
        return;
    }

    std::ostringstream ss;
    ss << node->data;

    s.append(ss.str());
    stringBSTPreOrd(node->left,s);
    stringBSTPreOrd(node->right,s);

    return;
}

bool containTree (NodeBT* n1, NodeBT* n2)
{
   string s1,s2;

   stringBSTPreOrd(n1,s1);
   stringBSTPreOrd(n2,s2);

   std::cout << "S1: " << s1 << " \nS2: " << s2 << std::endl;

   auto found = s1.find(s2);

   if (found != string::npos)
    return true;

return false;
}

int main()
{
    //Create the three

    vector<int> v = {1,2,3,4,5,6,7,8,9,10};
    NodeBT* root = buildMinHeightBST (v);

    //build test
    NodeBT* T2 = new NodeBT;
    T2->data = 2;
    T2->left = nullptr;
    T2->right = nullptr;
    NodeBT* n1 = new NodeBT;
    n1->data = 1;
    n1->left = nullptr;
    n1->right = nullptr;
    NodeBT* n2 = new NodeBT;
    n2->data = 3;
    n2->left = nullptr;
    n2->right = nullptr;
    NodeBT* n3 = new NodeBT;
    n3->data = 4;
    n3->left = nullptr;
    n3->right = nullptr;

    T2->left = n1;
    n2->right = n3;
    T2->right = n2;

    //with this node is a no
    NodeBT* n4 = new NodeBT;
    n4->data = 7;
    n4->left = nullptr;
    n4->right = nullptr;

    n3->right = n4;

    bool isSubTree = subTree (root, T2);

    if (isSubTree)
        std::cout << "Yes\n" << std::endl;
    else
        std::cout << "No\n" << std::endl;

         std::cout << std::endl << "Second Method\n" << std::endl;

    if (containTree(root,T2))
        std::cout << "Yes\n" << std::endl;
    else
        std::cout << "No\n" << std::endl;



    printBSTPreOrd(root);
    std::cout  << std::endl;
    printBSTPreOrd(T2);

    return 0;
}

