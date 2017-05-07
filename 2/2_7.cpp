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

Node* listIntersectionV1 ( List& l1,  List& l2)
{
  int s1 = l1.getLength();
  int s2 = l2.getLength();
  Node* lg, *sh;

  if (s1 >= s2) {
    lg = l1.getHead();
    sh = l2.getHead();

  }
  else if (s1 < s2) {
    lg = l2.getHead();
    sh = l1.getHead();
  }
    for (int i = abs(s1-s2); i>0; i--)
        lg = lg->getNext();

    while (lg!=nullptr) { // same length now
        if (lg == sh)
            return lg;

        lg = lg->getNext();
        sh = sh->getNext();
    }
    return nullptr;
}
int getListSizeAndTail (Node* n, Node **t)
{
    Node* trav = n;
    int length = 0;
    while (trav->getNext()!= nullptr) {
        length++;
        trav = trav->getNext();
    }
    (*t) = trav;
    return length+1;
}

Node* listIntersectionV2 (Node* n1,Node* n2)
{
    Node *t1, *t2;
    int s1 = getListSizeAndTail (n1,&t1);
    int s2 = getListSizeAndTail (n2,&t2);

    if (t1!=t2)
        return nullptr;

    Node *lg,*sh;
  if (s1 >= s2) {
    lg = n1;
    sh = n2;

  }
  else if (s1 < s2) {
    lg = n2;
    sh = n1;
  }
    for (int i = abs(s1-s2); i>0; i--)
        lg = lg->getNext();

    while (lg!=nullptr) { // same length now
        if (lg == sh)
            return lg;

        lg = lg->getNext();
        sh = sh->getNext();
    }
    return nullptr;
}


int main()
{
   //Create the list and adding some elements
    List l,l1;
    l.addNode(1);
    l.addNode(2);
    l.addNode(3);
    l.addNode(4);
    l.addNode(5);
    l.addNode(6);
    l.addNode(7);

    l1.addNode(8);
    l1.addNode(7);
    l1.addNode(6);
    l1.addNode(5);

    //makeIntersection
    Node *n1,*n2;
    n1 = l.getHead();
    n2 = l1.getHead();

    //intersection after five
    while (n1->getData()!=5)
        n1 = n1->getNext();

    while (n2->getNext()!=nullptr)
        n2 = n2->getNext();

    n2->setNext(n1->getNext());

    l.PrintList();
    std::cout  << std::endl;
    l1.PrintList();
    std::cout  << std::endl;

    Node* res = listIntersectionV2(l.getHead(),l1.getHead());
    if (res  != nullptr)
        std::cout<< "Intersection in: "<<res->getData();

    else
        std::cout<< "No intersection";

    return 0;
}
