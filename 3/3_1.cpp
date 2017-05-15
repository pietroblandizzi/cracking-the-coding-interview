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
#include <exception>
#include <string>
/*************FIXED************************/
/*
class MultiStack
{
    const int numOfStack = 3;
    int* values;
    int stack_capacity;
    int* stack_size;

public:
    MultiStack (int s);
    ~MultiStack ();
    bool isEmpty (int n);
    bool isFull (int n);
    int peek (int n);  // n stack number
    void push (int n, int data);
    int pop (int n);
    void printAll();
};

MultiStack::MultiStack(int s)
{
    stack_capacity = s;
    stack_size = new int[numOfStack];
    values = new int[stack_capacity*numOfStack];
    for (int i = 0; i<numOfStack; i++) {
        stack_size[i] = 0;
    }
    for (int i = 0; i<stack_capacity*numOfStack; i++) {
        values[i] = 0;
    }
}

MultiStack::~MultiStack ()
{
    delete[] values;
    delete[] stack_size;
}

bool MultiStack::isEmpty(int n)
{
    return stack_size[n] == 0;
}

bool MultiStack::isFull(int n)
{
    return stack_size[n] == (stack_capacity);
}

int MultiStack::peek(int n)
{
    if (!isEmpty(n))
        return values [stack_size[n] + (n*stack_capacity)-1];

    throw  std::string("Empty stack");
}

int MultiStack::pop (int n) {
    if (isEmpty(n))
        throw std::string("Empty sack");

    int value = values [stack_size[n] + (n*stack_capacity)-1];
    stack_size[n]--;
    return value;
}

void MultiStack::push (int n,int data)
{
   if (isFull (n))
    throw std::string("stack is full");

    stack_size[n]++;
    values [stack_size[n] + (n*stack_capacity)-1] = data;
}

void MultiStack::printAll()
{
    for (int i = 0; i< stack_capacity*numOfStack;i++) {
        std::cout << values[i] << " ";
    }
    std::cout<<std::endl;
}
*/
//forward declaration
class StackInfo;

class MultiStack
{
    friend class StackInfo;
    int numOfStack;
    int* values;
    int v_size;
    StackInfo* info;

public:
    MultiStack (int numOfStacks, int defaultSize);
    ~MultiStack ();
    bool isEmpty (int n);
    int peek (int n);  // n stack number
    void push (int n, int data);
    int pop (int n);
    void printAll();
    void expand(int n);
    int numOfElements();
    int adjustIndex(int n);
    bool areAllStacksFull ();
    int previousIndex (int index);
    int nextIndex(int index);
    void shift (int n);

};

class StackInfo {
      public:
        MultiStack* parent;
        int stack_size;
        int capacity;
        int start;
        int v_size;

        StackInfo ();
        void setParam (MultiStack* ms,int s,int c,int v) {
            parent = ms;
            start = s;
            capacity = c;
            stack_size = 0;
            v_size = v;
        }

       bool isWhithinStackCapacity (int index) {
            if (index <0 || index> v_size)
                return false;

           int cInd = index < start ? index+v_size : index;
           int endStack = start+capacity;
           return start <= cInd && cInd < endStack;
       }

       int lastCapacityIndex () {
        return parent->adjustIndex (start+capacity-1);
       }

        int lastElementIndex () {
           return parent->adjustIndex (start+stack_size-1);
        }

        bool isFull () {return stack_size == capacity;}
        bool isEmpty () {return stack_size == 0;}

    };


StackInfo::StackInfo() {}

MultiStack::MultiStack (int numOfStacks, int defaultSize)
{
    numOfStack = numOfStacks;
    v_size = defaultSize*numOfStack;
    info = new StackInfo[numOfStacks];
    values = new int[v_size];
    for (int i = 0; i<numOfStack; i++) {
        info[i].setParam(this, defaultSize*i,defaultSize,v_size);
    }
    for (int i = 0; i<v_size; i++) {
        values[i] = 0;
    }
}

MultiStack::~MultiStack ()
{
    delete[] values;
    delete[] info;
}

bool MultiStack::isEmpty(int n)
{
    return info[n].stack_size == 0;
}

int MultiStack::peek(int n)
{
    if (info[n].isEmpty())
        throw  std::string("Empty stack");
    return values [info[n].lastElementIndex()];
}

int MultiStack::pop (int n) {
    if (info[n].isEmpty())
        throw  std::string("Empty stack");

    int value = values [info[n].lastElementIndex()];
    info[n].stack_size--;
    return value;
}

void MultiStack::push (int n,int data)
{
   // if all stacks are full we cannot shift values
   if (areAllStacksFull ())
    throw std::string("stacks is full");

    //if this stack is full expand it
    if (info[n].isFull()) {
        expand (n);
    }
    info[n].stack_size++;
    values[info[n].lastElementIndex()] = data;
}

void MultiStack::printAll()
{
    for (int i = 0; i< v_size;i++) {
        std::cout << values[i] << " ";
    }
    std::cout<<std::endl;
}


void MultiStack::shift(int n) {
    if (info[n].stack_size>=info[n].capacity) {
        int nextStack = (n+1)%numOfStack;
        shift(nextStack);
        info[n].capacity++;
    }
    int index = info[n].lastCapacityIndex();
    while (info[n].isWhithinStackCapacity(index)) {
        values [index] = values [previousIndex(index)];
        index = previousIndex (index);
    }
    values[info[n].start] = 0;
    info[n].start = nextIndex (info[n].start);
    info[n].capacity--;
}

void MultiStack::expand (int n)
{
    shift ((n+1)%numOfStack);
    info[n].capacity++;
}

int MultiStack::numOfElements ()
{
    int sizeTot = 0;
    for (int i = 0 ; i<numOfStack; i++) {
        sizeTot += info[i].stack_size;
    }
    return sizeTot;
}

bool MultiStack::areAllStacksFull ()
{
    return numOfElements() == v_size;
}

int MultiStack::adjustIndex (int index)
{
    return ((index%v_size)+ v_size) %v_size;
}

int MultiStack::nextIndex (int index)
{
    return adjustIndex(index + 1);
}

int MultiStack::previousIndex (int index)
{
    return adjustIndex(index - 1);
}

int main()
{
    //3 Stack array of 10 values;
    MultiStack ms(3,5);
    if (ms.isEmpty(0)) std::cout << "stack 1 empty" << std::endl;
    if (ms.isEmpty(1)) std::cout << "stack 2 empty" << std::endl;
    if (ms.isEmpty(2)) std::cout << "stack 3 empty" << std::endl;

    //adding stuff
    ms.push(0,5);
    ms.push(1,5);
    ms.push(2,5);
    ms.push(2,6);


    ms.printAll();

    std::cout << ms.peek(2) << std::endl;
    ms.pop(2);
    ms.push(2,7);
    ms.printAll();


    return 0;
}
