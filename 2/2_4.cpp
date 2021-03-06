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
    void Partition (int data);
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

// first implementation
void List::Partition (int data)
{
    List newList; // start creating a new List in which i will attach the nodes
    if (head == nullptr)
        return;

    Node *n = head;
    while (n!=nullptr) {
        if (n->data >= data)
            newList.addNode(n->data);
        else (newList.addNodeHead(n->data));

        n = n->next;
    }

    //destroy the new list and make the head pointing to the old head;
    n = head;
    while (n!=nullptr) {
        Node * tmp = n;
        n = n->next;
        delete (tmp);
       tmp=nullptr;
    }
   head = newList.head;
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
    l.addNode(8);


    l.PrintList();
    std::cout  << std::endl;
    l.Partition(5);
    l.PrintList();

    return 0;
}
