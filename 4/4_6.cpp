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
// my idea
NodeBT* mostLeft (NodeBT* n)
{
    if(n == nullptr)
        return nullptr;
    while (n->left!= nullptr)
        n = n->left;

    return n;
}

NodeBT* successor (NodeBT* s)
{
    if (s == nullptr)
        return nullptr;

    if (s->right == nullptr) {
        NodeBT* p = s->parent;
        while (p!=nullptr && p->data < s->data)
            p = p->parent;
        return p;
    }
    return mostLeft(s->right);
}

NodeBT* successorV2 (NodeBT* s)
{
    if (s == nullptr)
        return nullptr;

    if (s->right == nullptr) {
        NodeBT* n = s;
        NodeBT* p = s->parent;
        while (p!=nullptr && p->left != n)
            n = p;
            p = p->parent;
        return p;
    }
    return mostLeft(s->right);
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
// i will use the exercise 2 to create easily a BST

int main()
{
    //Create the three

    vector<int> v = {1,2,3,4,5,6,7,8,9,10};

    NodeBT* root =buildMinHeightBST (v);

    NodeBT* source = root->left->right; // 3
    std::cout << "source " << source->data << std::endl;
    std::cout << "parent " << source->parent->data << std::endl;
    NodeBT* succ = successor(source);
    if (succ != nullptr)
        std::cout << "Successor " <<  succ->data <<std::endl;
    succ = successorV2(source);
    if (succ != nullptr)
        std::cout << "Successor " <<  succ->data <<std::endl;

    printBSTPreOrd(root);

    return 0;
}
