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
// first implementation without hint
/*
class StackWithMin
{
    int* values;
    int v_size;
    int s_min;
    int stack_size;

    void recomputeMin ();

public:
    StackWithMin (int v);
    ~StackWithMin ();
    void push (int data);
    int  pop ();
    int peek ();
    bool isEmpty ();
    bool isFull ();
    int getMin ();
};

StackWithMin::StackWithMin(int v)
{
  v_size = v;
  values = new int[v];
  s_min = INT_MAX;
  stack_size = 0;
  for (int i = 0; i < v_size; i++)
        values[i] = 0;
}

StackWithMin::~StackWithMin ()
{
    delete[] values;
    values = nullptr;
}

void StackWithMin::push(int data)
{
    if (isFull())
        throw std::string("stack full");

    if (data < s_min)
        s_min = data;

    values[stack_size] = data;
    stack_size++;
}

int StackWithMin::pop ()
{
    if (isEmpty())
        throw std::string("stack Empty");

    stack_size--;
    if (values[stack_size] == s_min)
        recomputeMin();

    return values[stack_size];
}

int StackWithMin::peek ()
{
    if (isEmpty())
        throw std::string("stack Empty");

    return values[stack_size-1];
}

bool StackWithMin::isEmpty ()
{
    return stack_size == 0;
}

bool StackWithMin::isFull ()
{
    return stack_size == v_size;
}

int StackWithMin::getMin ()
{
    if (isEmpty())
        throw std::string("stack Empty");

    return s_min;
}
// problem this is O(n) more or less but it happer rarely
void StackWithMin::recomputeMin()
{
    s_min = values[0];

    for (int i = 1; i < stack_size; i++) {
        if (values[i] < s_min)
        s_min = values[i];
    }
}
*/
//Cont hint
class StackData {
public:
    int data;
    int subMin;
};
/**Instead of the data we could have another stack that
take just the min in order to use less space */
class StackWithMin
{
    StackData* values;
    int v_size;
    int s_min;
    int stack_size;

public:
    StackWithMin (int v);
    ~StackWithMin ();
    void push (int data);
    int  pop ();
    int peek ();
    bool isEmpty ();
    bool isFull ();
    int getMin ();
};

StackWithMin::StackWithMin(int v)
{
  v_size = v;
  values = new StackData[v];
  stack_size = 0;
  for (int i = 0; i < v_size; i++) {
        values[i].data = 0;
        values[i].subMin = 0;
    }
}

StackWithMin::~StackWithMin ()
{
    delete[] values;
    values = nullptr;
}

void StackWithMin::push(int data)
{
    if (isFull())
        throw std::string("stack full");

    if (isEmpty()) {
    values[stack_size].data = data;
    values[stack_size].subMin = data;
    stack_size++;
    }
    else {
        if (data < values[stack_size-1].subMin) {
            values[stack_size].subMin = data;
        }
        else {
            values[stack_size].subMin = values[stack_size-1].subMin;
        }
        values[stack_size].data = data;
        stack_size++;
    }
}

int StackWithMin::pop ()
{
    if (isEmpty())
        throw std::string("stack Empty");

    stack_size--;
    return values[stack_size].data;
}

int StackWithMin::peek ()
{
    if (isEmpty())
        throw std::string("stack Empty");

    return values[stack_size-1].data;
}

bool StackWithMin::isEmpty ()
{
    return stack_size == 0;
}

bool StackWithMin::isFull ()
{
    return stack_size == v_size;
}

int StackWithMin::getMin ()
{
    if (isEmpty())
        throw std::string("stack Empty");

    return values[stack_size-1].subMin;
}


int main()
{
    try {
    StackWithMin s(10);

    s.push(5);
    std::cout << s.getMin()<< std::endl;
    s.push(3);
    std::cout << s.getMin()<< std::endl;
    std::cout << s.peek()<< std::endl;
    s.push(6);
    s.push(2);
    std::cout << s.getMin()<< std::endl;
    s.pop();
    std::cout << s.getMin()<< std::endl;
    }catch (std::string s) {std::cout << s << std::endl;}
    return 0;
}
