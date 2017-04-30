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

};

class List {
    Node* head;
public:
    List() {head = nullptr;}
    Node* getHead() {return head;}
    void addNode (int data);
    void addNodeHead(int data);
    Node* KthElementToLastRec (Node* n, int k,int& index);
    Node* KthElementToLast (Node* n, int k);
    void PrintList ();

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

Node* List::KthElementToLastRec (Node* n, int k,int& index)
{
    //i have to arrive to the end
    if (n == nullptr) {
        return nullptr;
    }
    Node* refNode = KthElementToLastRec(n->next,k,index);
    //i am in the last node
    index++;
    if (index == k)
        return n;

    return refNode;
}

Node* List::KthElementToLast (Node* n, int k)
{
    //i have to arrive to the end
    if (n == nullptr) {
        return nullptr;
    }

    Node *p1 = head, *p2 = head;

    for (int i  = 0; i<k; i++) {
        if (p1 == nullptr) return nullptr;
        p1 = p1->next;
    }
    while (p1!=nullptr) {
        p1 = p1->next;
        p2 = p2->next;
    }
    return p2;
}

int main()
{
   //Create the list and adding some elements
    List l;
    l.addNode(5);
    l.addNode(5);
    l.addNode(6);
    l.addNode(5);
    l.addNode(7);
    l.addNode(5);
    l.addNode(8);
    l.addNode(9);


    l.PrintList();
    std::cout  << std::endl;
    int counter = 0;
    Node* n = l.KthElementToLastRec(l.getHead(),8,counter);
    std::cout <<  n->getData() << std::endl;
    n = l.KthElementToLast(l.getHead(),8);
    std::cout <<  n->getData();

    return 0;
}
