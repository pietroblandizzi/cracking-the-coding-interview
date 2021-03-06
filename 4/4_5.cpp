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

bool isSmaller (NodeBT*, int );

NodeBT* utilityCreate (vector<int>& v, int start,int end)
{
   if (end < start)
        return nullptr;

    NodeBT* n = new NodeBT;
    // divide the array in two
    int middle = (start+end)/2;

    n->data = v[middle];
    n->left = utilityCreate (v,start, middle-1);
    n->right = utilityCreate (v,middle+1, end);

    return n;

}
/** My solution is maybe a bit complicate
It check for each subtree is a BST
checking if left < n < data and then
compute the max value in the left three
and check if it is bigger than it
and the same with the min value of the right
and check if it is smaller than it
**
Some int suggest to flip the logic
we can check if curr is always big then left
and always smaller then right
**/

/***** first solution****/
int biggestLeft (NodeBT* n)
{
    if (n == nullptr)
        return INT_MIN;

    return std::max (n->data,biggestLeft(n->left));
}

int smallestRight (NodeBT* n)
{
    if (n == nullptr)
        return INT_MAX;

    return std::min (n->data, smallestRight(n->right));
}

NodeBT* buildMinHeightBST (vector<int>& v)
{
    return utilityCreate(v,0,v.size()-1);
}


// idea from the solution we do an in-order traversal and check
 bool checkBST (NodeBT* n, int& prev)
 {
     if (n == nullptr)
        return true;
     //go left
     if (!checkBST(n->left, prev))
        return false;
     //check the current
     if (prev != INT_MIN && n->data <= prev)
        return false;

     prev = n->data;

     //go right
     if (!checkBST(n->right,prev))
        return false;

     return true;
 }

 //with min and max
 bool checkBSTV2 (NodeBT* n, int& r_min, int& r_max)
 {
    if (n == nullptr)
        return true;

    if (n->data <= r_min || n->data > r_max )
        return false;

    bool left = checkBSTV2 (n->left, r_min, n->data);
    bool right = checkBSTV2 (n->right,n->data,r_max);

    return left && right;

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


     int d = INT_MIN;
    if (checkBST(root,d))
        std::cout << "yes" << std::endl;

    else
        std::cout << "no" << std::endl;

     int r_min = INT_MIN;
     int r_max = INT_MAX;

    if (checkBSTV2(root,r_min,r_max))
        std::cout << "yes" << std::endl;

    else
        std::cout << "no" << std::endl;


    printBSTPreOrd(root);

    std::cout<< "root " << root->right->data ;

    return 0;
}
