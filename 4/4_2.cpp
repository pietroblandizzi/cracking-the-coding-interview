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
#include <algorithm>
using std::vector;


//Simple BST
class Node
{
public:
    int data;
    Node* left;
    Node* right;
};
typedef vector<Node*>::size_type v_size;

Node* utilityCreate (vector<int>& v, int start,int end)
{
   if (end < start)
        return nullptr;

    Node* n = new Node;
    // divide the array in two
    int middle = (start+end)/2;

    n->data = v[middle];
    n->left = utilityCreate (v,start, middle-1);
    n->right = utilityCreate (v,middle+1, end);

    return n;

}
Node* buildMinHeightBST (vector<int>& v)
{
    return utilityCreate(v,0,v.size()-1);
}
//preorder
void printBSTPreOrd (Node* root)
{
    if (root != nullptr) {
    std::cout << root->data << std::endl;
    printBSTPreOrd (root->left);
    printBSTPreOrd (root->right);
    }
    return;
}

void printBSTInOrd (Node* root)
{
    if (root != nullptr) {
    printBSTInOrd (root->left);
    std::cout << root->data << std::endl;
    printBSTInOrd (root->right);
    }
    return;
}

int main()
{
    vector<int> v = {1,2,3,4,5,6,7,8,9,10};

    Node* n =buildMinHeightBST (v);

    printBSTInOrd (n);

    std::cout << "root" << n->data;

    return 0;
}
