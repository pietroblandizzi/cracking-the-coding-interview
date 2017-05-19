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

using  std::string;

//without hints
/***
with one list
we can search for the first dog or cat in O(n)
with two lists we can have O(1) but we need to
keep another pointer or a counter to see who is the oldest
**/
/*
struct Node
{
 string type;
 Node* next;
};

class AnimalShelter
{
    Node* head;
    Node*tail;

 public:
     AnimalShelter ();
     void enqueue (string& s);
     Node* dequeueAny ();
     Node* dequeueDog ();
     Node* dequeueCat ();

     bool isEmpty ();
     void printAll ();

};

AnimalShelter::AnimalShelter ()
{
    head = tail = nullptr;
}

bool AnimalShelter::isEmpty()
{

    return (head == nullptr && tail == nullptr);
}

void AnimalShelter::enqueue(string& s)
{
    Node* n = new Node;
    n->type = s;
    n->next = nullptr;

    //empty queue
    if (head == nullptr && tail == nullptr) {
       head = tail = n;
    }else {
    Node * t = tail;
    t->next = n;
    tail = n;
    }
}
//someone has to free the memory after
Node* AnimalShelter::dequeueAny()
{
    if (head == nullptr && tail == nullptr)
        return nullptr;

    Node* t = head;
    head = head->next;
    return t;
}

Node* AnimalShelter::dequeueDog()
{
    if (head == nullptr && tail == nullptr)
        return nullptr;

    if (head->type.compare("dog")==0){
        return dequeueAny();
    }
    Node* prev = head;
    Node* t = head->next;
    while (t != nullptr && t->type.compare("dog")!=0) {
        prev = t;
        t = t->next;
    }
    if (t == nullptr)
        return nullptr;

    prev ->next = t->next;

    return t;
}

Node* AnimalShelter::dequeueCat()
{
    if (head == nullptr && tail == nullptr)
        return nullptr;

    if (head->type.compare("cat")==0){
        return dequeueAny();
    }
    Node* prev = head;
    Node* t = head->next;
    while (t != nullptr && t->type.compare("cat")!=0) {
        prev = t;
        t = t->next;
    }
    if (t == nullptr)
        return nullptr;

    prev ->next = t->next;

    return t;
}

void AnimalShelter::printAll()
{
    std::cout <<  std::endl;
    if (head == nullptr && tail == nullptr)
        return;
    Node* t = head;

     while (t != nullptr) {
        std::cout << t->type << std::endl;
        t = t->next;
    }
    std::cout <<  std::endl;
    return;
}

*/
struct Node
{
 string type;
 Node* next;
 int order;
};

class AnimalShelter
{
    int ord;
    Node* headDog, *headCat;
    Node* tailDog, *tailCat;
    void enqueueDog();
    void enqueueCat();

 public:
     AnimalShelter ();
     void enqueue (string& s);
     Node* dequeueAny ();
     Node* dequeueDog ();
     Node* dequeueCat ();

     bool isEmpty ();
     void printAll ();

};

AnimalShelter::AnimalShelter ()
{
    headDog = tailDog = nullptr;
    headCat = tailCat = nullptr;
    ord = 0;
}

bool AnimalShelter::isEmpty()
{
    return (headDog == nullptr && headCat == nullptr);
}

void AnimalShelter::enqueue(string& s)
{
    if (s.compare("dog")== 0)
        enqueueDog();
    else
        enqueueCat();
}

void AnimalShelter::enqueueDog()
{
    Node* n = new Node;
    n->type = "dog";
    n->next = nullptr;
    n->order = ord;
    ord++;
    //empty queue
    if (headDog == nullptr && tailDog == nullptr) {
       headDog = tailDog = n;
    }else {
    Node * t = tailDog;
    t->next = n;
    tailDog = n;
    }
}

void AnimalShelter::enqueueCat()
{
    Node* n = new Node;
    n->type = "cat";
    n->next = nullptr;
    n->order = ord;
    ord++;

    //empty queue
    if (headCat == nullptr && tailCat == nullptr) {
       headCat = tailCat = n;
    }else {
    Node * t = tailCat;
    t->next = n;
    tailCat = n;
    }
}

Node* AnimalShelter::dequeueAny()
{
    if (isEmpty())
        return nullptr;

    Node* td = headDog;
    Node* tc = headCat;

    if (td == nullptr) {
        headCat = headCat->next;
        return tc;
    }
    if (tc == nullptr) {
        headDog = headDog->next;
        return td;
    }

    if (tc->order < td->order )
    {
        headCat = headCat->next;
        return tc;
    }
    headDog = headDog->next;
    return td;
}

Node* AnimalShelter::dequeueDog()
{
    if (headDog == nullptr && tailDog == nullptr)
        return nullptr;

    Node* t = headDog;
    headDog = headDog->next;

    return t;
}

Node* AnimalShelter::dequeueCat()
{
    if (headCat == nullptr && tailCat == nullptr)
        return nullptr;

    Node* t = headCat;
    headCat = headCat->next;

    return t;
}

int main()
{
    AnimalShelter as;
    string typeC = "cat";
    string typeD = "dog";

    as.enqueue(typeC);
    as.enqueue(typeD);
    as.enqueue(typeC);
    as.enqueue(typeC);
    as.enqueue(typeD);
    as.enqueue(typeC);

    Node* p = as.dequeueAny();

    std::cout << p->type << std::endl;
    delete p;
    p = as.dequeueCat();

    std::cout << p->type << std::endl;
    delete p;



    as.enqueue(typeC);

     p = as.dequeueCat();

    std::cout << p->type << std::endl;
    delete p;

    return 0;
}
