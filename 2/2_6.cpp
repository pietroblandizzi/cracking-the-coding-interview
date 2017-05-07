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
#include <stack>

class Node {
    friend class List;
    int data;
    Node *next;

};

class List {
    Node* head;
public:
    Node* getHead() {return head;}
    List() {head = nullptr;}
    void addNode (int data);
    void addNodeHead(int data);
    bool isListPlaindrome ();
    bool isListPlaindromeV2 ();
    bool isListPlaindromeV3 (Node* n, Node** next,int  length);
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

bool List::isListPlaindrome ()
{
    //reverting the list
    List reveseList;
    Node* n = head;
    while (n!= nullptr) {
        reveseList.addNodeHead(n->data);
        n = n->next;
    }
    n = head;
    Node *n1=reveseList.getHead();
    while (n!= nullptr) {
       if (n->data != n1->data)
            return false;

        n = n->next;
        n1 = n1->next;
    }

 return true;
}
//using a stack
bool List::isListPlaindromeV2 ()
{
    std::stack<int> s;
    Node* fast = head;
    Node* slow = head;
 /*   while (fast!= nullptr) {
        if (fast->next != nullptr) {
            fast = fast->next->next;
            s.push(slow->data);
            slow = slow->next;
        }
        else {
            fast = fast->next;
            slow = slow->next; // skip the middle element
        }
    }
*/
    while (fast != nullptr && fast->next) {
        s.push(slow->data);
        slow = slow->next;
        fast = fast->next->next;

    }
    if (fast!=nullptr) { // odd number
        slow = slow->next;
    }
    while (slow!= nullptr) {
       if (slow->data != s.top())
            return false;

        s.pop();
        slow = slow->next;
    }
 return true;
}

bool List::isListPlaindromeV3 (Node* n, Node** compare,int length)
{
    if (n == nullptr || length <= 0) {
        *compare = n;
        std::cout << " compare " <<(*compare)->data <<std::endl;
        return true;
    } else if (length == 1) {
        (*compare) = n->next;
        return true;
    }
     // I always pass the next
     bool res = isListPlaindromeV3(n->next,compare,length-2);
     // compare point to one after the middle
     if (!res || compare == nullptr) {
         return res;
     }
        std::cout << "n "<<n->data << " compare " <<(*compare)->data <<std::endl;
      res = n->data == (*compare)->data ? 1 : 0;
      (*compare) = (*compare)->next;
      return res;
}

int main()
{
   //Create the list and adding some elements
    List l;
    l.addNode(1);
    l.addNode(2);
    l.addNode(3);
  //  l.addNode(1);
    l.addNode(3);
    l.addNode(2);
    l.addNode(1);
    l.addNode(1);



    l.PrintList();
    std::cout  << std::endl;
  /*  if (l.isListPlaindromeV2())
        std::cout << "yes";
    else
        std::cout << "no";
*/
    Node* compare;
    if (l.isListPlaindromeV3(l.getHead(),&compare,7))
        std::cout << "yes";
    else
        std::cout << "no";

    return 0;
}
