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
#include <stdlib.h>
#include <algorithm>
#include <limits.h>




//simple BT
class NodeBT
{
public:
    int data;
    NodeBT* left;
    NodeBT* right;
};

int computeHeight (NodeBT* n,bool& balanced)
{
    if (n == nullptr) {
        balanced = true;
        return 0;
    }
    if (balanced == false)
        return 0;

    int h_left = computeHeight (n->left,balanced);
    int h_right = computeHeight (n->right,balanced);

    if (abs (h_left-h_right) > 1)
        balanced = false;

    else balanced = true;

    return std::max(h_left,h_right) +1;
}

bool isBalanced (NodeBT* n)
{
    bool balanced = true;
    int h = computeHeight(n,balanced);

    if (!balanced)
        return false;

    return true;
}

// from the solution
int checkHeight (NodeBT* n)
{
    if (n == nullptr)
        return -1;
    int leftH = checkHeight(n->left);
    if (leftH == INT_MIN)
        return INT_MIN;

    int rightH = checkHeight(n->right);
    if (rightH == INT_MIN)
        return INT_MIN;

    if (abs(leftH-rightH)>1)
            return INT_MIN;

    else return std::max(leftH,rightH)+1;
}

bool isBalancedV2(NodeBT* n)
{
    return checkHeight(n) != INT_MIN;
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

    //create the unbalance

    NodeBT* t = root;
    while (t->left!= nullptr)
        t = t->left;


    NodeBT* node = new NodeBT;
    NodeBT* node1 = new NodeBT;
    node->data = 50;
    node1->data = 55;
    node->left = node1;
    node->right = nullptr;
    node1->left = nullptr;
    node1->right = nullptr;
    t->left = node;
/*
    NodeBT* node = new NodeBT;
    node->data = 50;
    node->left = nullptr;
    node->right = nullptr;
    t->left = node;
*/
    if (isBalanced(root))
        std::cout << "yes" << std::endl;

    else
        std::cout << "no" << std::endl;

    if (isBalancedV2(root))
        std::cout << "yes" << std::endl;

    else
        std::cout << "no" << std::endl;
    printTree(root);

    return 0;
}
