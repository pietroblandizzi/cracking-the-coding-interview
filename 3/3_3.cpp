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
{   friend class SetOfStacks;
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

/**
Using a normal stack to create the set of stacks
**/

class SetOfStacks
{
    //or i could use a Stack* and reserve some memory
    int sstack_size;
    std::vector<MyStack*> stackset;
    int n_of_stacks;
    void shift (int index);
    void shiftV2 (int index);
public:
    SetOfStacks (int s);
    void push (int data);
    int pop ();
    int peek ();
    int popAt (int index);
    int popAtV2 (int index);
};


SetOfStacks::SetOfStacks(int s)
{
  sstack_size = s;
  n_of_stacks = 0;
}

void SetOfStacks::push(int data)
{
    if (n_of_stacks == 0 || stackset[n_of_stacks-1]->isFull() ) {
        std::cout << "New stack created"<< std::endl;
        stackset.push_back(new MyStack(sstack_size));
        stackset[n_of_stacks]->push(data);
        n_of_stacks++;
    }
    else {
        stackset[n_of_stacks-1]->push(data);
    }
}

int SetOfStacks::pop ()
{
    if (n_of_stacks == 0 || stackset[n_of_stacks-1]->isEmpty())
        throw std::string("stack Empty ");

     int v =   stackset[n_of_stacks-1]->pop();
    //we do not need the stack anymore //
    if (stackset[n_of_stacks-1]->isEmpty()){
        stackset.pop_back();
        n_of_stacks--;
    }

    return v;
}

int SetOfStacks::peek ()
{
 if (n_of_stacks == 0 || stackset[n_of_stacks-1]->isEmpty())
        throw std::string("stack Empty ");

    return stackset[n_of_stacks-1]->peek();
}
/** Two way of thinking about it.
If You allow stacks to be not full then u can
use the first version of shift that move stacks just
when one is empty
Or the second version that migrate back all the elements
in order to have all the stacks full except the last one**/
int SetOfStacks::popAt (int index)
{
    if (index < 0 || index >= n_of_stacks)
            throw std::string("Out of range");

    if (n_of_stacks == 0 || stackset[index]->isEmpty())
        throw std::string("stack Empty ");

     int v =   stackset[index]->pop();
    //we do not need the stack anymore //
    if (stackset[index]->isEmpty()){
        //shift from end to index!!!
        shift (index);
        n_of_stacks--;
    }
    return v;
}

void SetOfStacks::shift (int index)
{
    if (index == n_of_stacks-1) {
        stackset.pop_back();
        return;
    }
    for (int i = index; i < n_of_stacks-1; i++) {
        //we need a correct assignment operator
        stackset[i] = stackset [i+1];
    }
    stackset.pop_back();
    std::cout << "Shift"<< std::endl;
}

int SetOfStacks::popAtV2 (int index)
{
    if (index < 0 || index >= n_of_stacks)
            throw std::string("Out of range");

        if (n_of_stacks == 0 || stackset[index]->isEmpty())
        throw std::string("stack Empty ");

     int v =   stackset[index]->pop();
        //shift from end to index!!!
        shiftV2 (index);

    return v;
}

void SetOfStacks::shiftV2 (int index)
{
    if (index == n_of_stacks-1) {
        //we pop from the last
        if (stackset[index]->isEmpty())
        stackset.pop_back();

        return;
    }
    for (int i = index; i < n_of_stacks-1; i++) {
        //we need a correct assignment operator

        while (!stackset[i]->isFull()) {
            stackset[i]->push(stackset[i+1]->values[0]);
            stackset[i+1]->leftShift();
        }
    }
        std::cout << "Shift"<< std::endl;
}

int main()
{
    try {
    SetOfStacks s(3);

    s.push(1);
    s.push(3);
    s.push(3);
    std::cout << s.pop() <<std::endl;
    s.push(3);
    std::cout << s.peek() <<std::endl;

    s.push(4);
    std::cout << s.peek() <<std::endl;
    std::cout << s.pop() <<std::endl;
    std::cout << s.peek() <<std::endl;

    //create other 2 stacks
    s.push(4);
    s.push(5);
    s.push(6);

    s.push(7);
    s.push(8);
    s.push(9);
    //lets try to pop at 1
  /*  std::cout << s.popAt(1) <<std::endl;
    std::cout << s.popAt(1) <<std::endl;
    std::cout << s.popAt(1) <<std::endl;
*/
    /**now that stack is empty and it should shift everything
    So if i pop in 2 there should be an error
    if i pop in 1 i should get 9 **/
    //std::cout << s.popAt(1) <<std::endl;

    /***V2**/
    std::cout << s.popAtV2(1) <<std::endl;
    std::cout << s.popAtV2(1) <<std::endl; // should pop 7
    std::cout << s.popAtV2(1) <<std::endl;



    }catch (std::string s) {std::cout << s << std::endl;}
    return 0;
}
