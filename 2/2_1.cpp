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

};

class List {
    Node* head;
public:
    List() {head = nullptr;}
    void addNode (int data);
    void addNodeHead(int data);
    void RemoveDuplicate ();
    void RemoveDuplicateV2 ();
    void RemoveDuplicateV3 ();
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
//first implementation
void List::RemoveDuplicate()
{
    //head is  or has just one element return ;
      if (head == nullptr || head->next == nullptr) {
        return;
    }
    //create a buffer;
    List b;
    b.addNodeHead(head->data);

    Node* t = head->next;
    Node* prev = head;

    while (t != nullptr) {
        Node* t1 = b.head;
        while (t1 != nullptr) {
            if (t1->data == t->data){
                //remove and finish the cycle
                Node *r = t;
                t = t->next;
                prev->next = t;
                delete(r);
                break;
            }
            t1 = t1->next;
        }
         if (t1 == nullptr) {
                //we did not find anything so we add the node in the buffer
                // I add in head
                b.addNode(t->data);
                t = t->next;
                prev = prev->next;
        }
    }
    return;
}

//first hint hashTable
void List::RemoveDuplicateV2()
{
    //head is  or has just one element return ;
      if (head == nullptr || head->next == nullptr) {
        return;
    }
    //create an hash table;
    std::map <int, int> b;
    b[head->data] = head ->data;

    Node* t = head->next;
    Node* prev = head;

    while (t != nullptr) {
        std::map<int,int>::iterator it;
        it  = b.find(t->data);
        if (it != b.end()) {
             //remove and finish the cycle
            Node *r = t;
            t = t->next;
            prev->next = t;
            delete(r);
        }else {
            b[t->data] = t->data;
            t = t->next;
            prev = prev->next;
        }
    }
    return;
}
//second hint -> 2 pointers no buffer
void List::RemoveDuplicateV3()
{
    //head is  or has just one element return ;
      if (head == nullptr || head->next == nullptr) {
        return;
    }

    Node* t = head;
    while (t!=nullptr && t->next != nullptr) {
        Node* t1 = t->next;
        Node* prev = t;
        while (t1 != nullptr) {
            if (t1->data == t->data){
                //remove and finish the cycle
                Node *r = t;
                t1 = t1 ->next;
                prev->next = t1;
                delete(r);
                //PrintList();
            }
            else {
                t1 = t1->next;
                prev = prev->next;
            }
        }
        t = t->next;
    }
    return;
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
    l.addNode(8);


    l.PrintList();
    std::cout  << std::endl;
    l.RemoveDuplicateV3();
    std::cout  << std::endl;
    l.PrintList();

    return 0;
}
