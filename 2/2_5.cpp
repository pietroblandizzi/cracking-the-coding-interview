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
#include <map>

class Node {
    friend class List;
    int data;
    Node *next;

public:
    int getData(){return data;}
    Node* getNext () {return next;}
};

class List {
    Node* head;
public:
    List() {head = nullptr;}
    Node* getHead() {return head;}
    void addNode (int data);
    void addNodeHead(int data);
    void PrintList ();
    void PrintListWithDummy ();

};

void List::addNodeHead(int data)
{
    Node *n = new Node;
    n->data = data;
    n->next = nullptr;

    //head is null;
    if (head == nullptr) {
        head = n;
        return;
    }
    //insert in head
    Node* t = head;
    n->next = t;
    head = n;

    return;
}

void List::addNode(int data)
{
    Node *n = new Node;
    n->data = data;
    n->next = nullptr;

    //head is null;
    if (head == nullptr) {
        head = n;
        return;
    }
    //insert in head
    Node* t = head;
    while (t->next != nullptr) {
        t = t->next;
    }
    t->next =n;

    return;
}

void List::PrintList()
{
    //head is null;
    if (head == nullptr) {
        return;
    }
    Node* t = head;
    while (t != nullptr) {
        std::cout << t->data << " ";
        t = t->next;
    }
    return;
}

void List::PrintListWithDummy()
{
    //head is null;
    if (head == nullptr) {
        return;
    }
    Node* t = head;
    while (t != nullptr && t->data  != -1) {
        std::cout << t->data << " ";
        t = t->next;
    }
    return;
}

void sumReverseLists (List& l1, List& l2, List& sum)
{
    int carry = 0;
    int s = 0;
    Node* n1 = l1.getHead();
    Node* n2 = l2.getHead();
    //sum of the common part
    while (n1!=nullptr && n2!=nullptr) {
        s = n1->getData() + n2->getData() + carry;
        carry = 0;
        if (s >= 10) {
            carry = 1;
            s = s - 10;
        }
        sum.addNode(s);
        n1 = n1->getNext();
        n2 = n2->getNext();
    }
    //one of the two lists might contain elements
    while (n1!=nullptr) {
        s = n1->getData()+ carry;
        carry = 0;
        if (s >= 10) {
            carry = 1;
            s = s - 10;
        }

        sum.addNode(s);
        n1 = n1->getNext();
    }
    while (n2!=nullptr) {
        s = n2->getData()+ carry;
        carry = 0;
        if (s >= 10){
            carry = 1;
            s = s - 10;
        }
        sum.addNode(s);
        n2 = n2->getNext();
    }
     if (carry == 1)
        sum.addNode(1);
    return;
}

int sumData(Node* n1, Node* n2, List& sum)
{
    if (n1 == nullptr && n2 == nullptr)
        return 0;

    int carry = sumData(n1->getNext(),n2->getNext(),sum);
    int s = n1->getData()+n2->getData()+carry;
    if (s > 10) {
        sum.addNodeHead(s-10);
        return 1;
    }
    sum.addNodeHead(s);
    return 0;

}

void sumLists (List& l1, List& l2, List& sum)
{
    //length of the strings
    int s1 = 0, s2 = 0;
    Node* n1 = l1.getHead();
    Node* n2 = l2.getHead();
    while (n1!=nullptr) {
        s1++;
        n1 = n1->getNext();
    }
    while (n2!=nullptr) {
        s2++;
        n2 = n2->getNext();
    }

    if (s1>s2) {
        //add zero to the head of l2
        for (int i = s1-s2; i>0;i--) {
            l2.addNodeHead(0);
        }
    }
    else  if (s2>s1) {
        //add zero to the head of l2
        for (int i = s2-s1; i>0;i--) {
            l1.addNodeHead(0);
        }
    }
    n1 = l1.getHead();
    n2 = l2.getHead();

    // we need to do it recursively
    int carry = sumData (n1,n2,sum);
    if (carry == 1)
        sum.addNodeHead(1);

return;
}


int main()
{
   //Create the list and adding some elements
/*    List l;
    l.addNode(1);
    l.addNode(2);
    l.addNode(3);
    l.addNode(4);
    l.addNode(5);
    l.addNode(6);
    l.addNode(7);
    l.addNode(8);

    l.PrintList();
    std::cout  << std::endl;
    l.Partition(5);
    l.PrintList();
*/

    List l1,l2,sum;
    l1.addNode(6);
    l1.addNode(1);
    l1.addNode(7);

    l2.addNode(2);
    l2.addNode(9);
    l2.addNode(5);

    sumLists(l1,l2,sum);
    std::cout << " The sum is: " << std::endl;
    sum.PrintList();

    return 0;
}
