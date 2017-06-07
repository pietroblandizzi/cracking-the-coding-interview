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
#include<vector>

using std::vector;

//simple BT
class NodeBT
{
public:
    int data;
    NodeBT* left;
    NodeBT* right;
};

class Result
{
public:
    NodeBT* n;
    bool isAncerstor;
    Result (NodeBT* node, bool a) {n = node; isAncerstor = a;}
};

NodeBT* utilityCreate (vector<int>& v, int start,int end, NodeBT* parent)
{
   if (end < start)
        return nullptr;

    NodeBT* n = new NodeBT;
    // divide the array in two
    int middle = (start+end)/2;
    n->data = v[middle];
    n->left = utilityCreate (v,start, middle-1,n);
    n->right = utilityCreate (v,middle+1, end,n);

    return n;

}

NodeBT* buildMinHeightBST (vector<int>& v)
{
    return utilityCreate(v,0,v.size()-1,nullptr);
}

Result helper (NodeBT* root, NodeBT* a, NodeBT* b)
{
    if (root == nullptr){
        return Result(nullptr,false);
    }
    //they are the same node
    if (root == a && root == b) {
         return  Result(root,true);
    }

    Result rl = helper(root->left, a,b);
        if (rl.isAncerstor) return rl;

    Result rr = helper(root->right, a ,b);
        if (rl.isAncerstor) return rl;

   if (rl.n != nullptr && rr.n != nullptr) {
     return  Result (root, true);
   }
   else if (root == a || root == b) {
        bool isAnc = rl.n !=nullptr || rr.n != nullptr;
        return  Result (root, isAnc);
   }
   else return  Result (rl.n !=nullptr ? rl.n : rr.n, false);
}


NodeBT* commonAncestor (NodeBT* root, NodeBT* a, NodeBT* b)
{
    Result r = helper (root,a,b);
    if (r.isAncerstor)
        return r.n;

    return nullptr;
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

void getNode (NodeBT* root , int data, NodeBT* &n)
{
    if (root != nullptr) {
        if (root -> data == data)
             n = root;

        getNode (root->left,data, n);
        getNode (root->right,data,n);
    }
    return;
}

int main()
{
    //Create the three i will use a bst created before

    vector<int> v = {1,2,3,4,5,6,7,8,9,10};

    NodeBT* root =buildMinHeightBST (v);

    printBSTPreOrd(root);
    NodeBT* a;
    getNode(root, 7, a);
    NodeBT* b;
    getNode(root, 10, b);


    std::cout <<std::endl;
    std::cout <<std::endl;
    NodeBT* r = commonAncestor(root,a,b );
    if (r != nullptr)
    std::cout << r->data;

    return 0;
}

