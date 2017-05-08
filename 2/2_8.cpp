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


class Node {
    friend class List;
    int data;
    Node *next;

public:
    int getData () {return data;}
    Node* getNext () {return next;}
    void setNext (Node* n) {next = n;}
};

class List {
    Node* head;
public:
    Node* getHead() {return head;}
    List() {head = nullptr;}
    void addNode (int data);
    void addNodeHead(int data);
    void PrintList ();
    int getLength ();

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

int List::getLength ()
{
    int res = 0;
    Node* n = head;
    while (n != nullptr) {
        res++;
        n = n->next;
    }
    return res;
}

Node* listLoopDetection (Node* h)
{
    if (h == nullptr || h->getNext() == nullptr)
        return nullptr;

    if (h->getNext() == h)
            return h;

    Node* fast = h->getNext()->getNext();
    Node* slow = h->getNext();


    while (fast!=nullptr && slow!=nullptr &&
           fast->getNext()!= nullptr &&  fast!=slow ) {
        fast = fast->getNext()->getNext();
            slow = slow->getNext();
    }
    //here them are the same or nullptr
    if (fast == nullptr || slow == nullptr)
        return nullptr;

    fast = h;
    while (fast != slow) {
        fast = fast->getNext();
        slow = slow->getNext();
    }
    //fast and slow point to the same node so i return one
    return fast;
}


int main()
{
   //Create the list and adding some elements
    List l;
    l.addNode(1);
    l.addNode(2);
    l.addNode(3);
    l.addNode(4);
    l.addNode(5);
    l.addNode(6);
    l.addNode(7);


    //makeIntersection
    Node *n1,*n2;
    n1 = l.getHead();
    n2 = l.getHead();

    //generate the loop
    while (n1->getNext() != nullptr)
        n1 = n1->getNext();
    //n1 is pointing to the last element

    while (n2->getData()!=4)
        n2 = n2->getNext();

    n1->setNext(n2);

    //l.PrintList();
    std::cout  << std::endl;

    Node* res = listLoopDetection(l.getHead());
    if (res  != nullptr)
        std::cout<< "Loop start in: "<<res->getData();

    else
        std::cout<< "No Loop detected";

    return 0;
}
