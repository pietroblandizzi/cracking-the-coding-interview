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
#include <climits>
#include <vector>

using std::vector;

// first implementation without hint
class MyStack
{   
    int *values;
    int v_size;
    int stack_size;

public:
    MyStack (int v);
    //rule of the three
    ~MyStack ();
   // MyStack(const MyStack& o);
    MyStack& operator= (const MyStack& o);

    void push (int data);
    int  pop ();
    int peek ();
    bool isEmpty ();
    bool isFull ();
    void leftShift ();
};

MyStack::MyStack(int v)
{
  v_size = v;
  values = new int[v];
  stack_size = 0;
  for (int i = 0; i < v_size; i++) {
        values[i] = 0;
    }
}

MyStack& MyStack::operator= (const MyStack& o)
{

    if (this != &o) {
        int * new_array = new int[o.v_size];
        std::copy(o.values, o.values + o.v_size, new_array);
        delete [] values;
        values = new_array;
        v_size = o.v_size;
        stack_size = o.stack_size;
    }
    return *this;
}
/*
MyStack::MyStack(const MyStack& o)
{
    v_size = o.v_size;
    values = new int[o.v_size];
    stack_size = 0;
    std::copy (o.values,o.values + o.v_size,values);
}*/

MyStack::~MyStack ()
{
    delete[] values;
    values = nullptr;
}

void MyStack::push(int data)
{
    if (isFull())
        throw std::string("stack full");

        values[stack_size] = data;
        stack_size++;
}

int MyStack::pop ()
{
    if (isEmpty())
        throw std::string("stack Empty");

    stack_size--;
    return values[stack_size];
}

int MyStack::peek ()
{
    if (isEmpty())
        throw std::string("stack Empty");

    return values[stack_size-1];
}

bool MyStack::isEmpty ()
{
    return stack_size == 0;
}

bool MyStack::isFull ()
{
    return stack_size == v_size;
}

void MyStack::leftShift ()
{
    for (int i = 0; i<stack_size-1;i++) {
        values[i] = values[i+1];
    }
}

class MyQueue
{
    //or i could use a Stack* and reserve some memory
    int q_size, q_capacity;
    MyStack* mainStack, *refillStack;
    void refill ();
public:
    MyQueue (int s);
    ~MyQueue ();
    // copy constructor and assignment operator
    void push (int data);
    int pop ();
    int peek ();
    bool isEmpty () {return q_size == 0;}

};


MyQueue::MyQueue(int s)
{
  q_capacity = s;
  q_size = 0;
  mainStack = new MyStack (s);
  refillStack = new MyStack (s);
}

MyQueue::~MyQueue()
{
    delete mainStack;
    mainStack = nullptr;
    delete refillStack;
    refillStack = nullptr;
}

void MyQueue::push(int data)
{
    if(q_size == q_capacity)
        throw std::string("queue Full ");

    mainStack->push(data);
    q_size++;
}

int MyQueue::pop ()
{
    if (refillStack->isEmpty()) {
        if (mainStack->isEmpty())
            throw std::string("queue Empty ");

        refill ();
    }
    q_size--;
    return refillStack->pop();
}

int MyQueue::peek ()
{
    if (refillStack->isEmpty()) {
        if (mainStack->isEmpty())
            throw std::string("queue Empty ");

        refill ();
    }
    return refillStack->peek();
}

void MyQueue::refill ()
{
    while (!mainStack->isEmpty())
        refillStack->push(mainStack->pop());
    return;
}



int main()
{
    try {
    MyQueue s(3);

    s.push(1);
    s.push(2);
    s.push(3);
    std::cout << s.pop() <<std::endl;
    s.push(5);
    std::cout << s.pop() <<std::endl;
    std::cout << s.pop() <<std::endl;
    std::cout << s.pop() <<std::endl;

    s.push(4);
    s.push(3);
    s.push(2);
    std::cout << s.pop() <<std::endl;
    s.push(5);
    std::cout << s.peek() <<std::endl;
    std::cout << s.pop() <<std::endl;
    std::cout << s.pop() <<std::endl;
    std::cout << s.pop() <<std::endl;

    }catch (std::string s) {std::cout << s << std::endl;}
    return 0;
}
