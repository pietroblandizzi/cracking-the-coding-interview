#include <iostream>
#include <exception>
#include <string>

class MultiStack
{
    const int numOfStack = 3;
    int* values;
    int v_size;
    int* stack_size;

public:
    MultiStack (int s);
    ~MultiStack ();
    bool isEmpty (int n);
    int peek (int n);  // n stack number
    void push (int n, int data);
    int pop (int n);
    void printAll();
};

MultiStack::MultiStack(int s)
{
    v_size = s*numOfStack;
    stack_size = new int[numOfStack];
    values = new int[v_size];
    for (int i = 0; i<numOfStack; i++) {
        stack_size[i] = 0;
    }
    for (int i = 0; i<v_size; i++) {
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

int MultiStack::peek(int n)
{
    if (!isEmpty(n))
        return values [stack_size[n-1] + (n*v_size/3)];

    throw  std::string("Empty stack");
}

int MultiStack::pop (int n) {
    if (stack_size[n]!=0)
        stack_size[n]--;
}

void MultiStack::push (int n,int data)
{
   if (isFull (n))
    throw std::string("stack is full");

   stack_size[n]++;

    if (stack_size[n] < v_size/3)
    values [stack_size[n] + (n*v_size/3)] = data;
    stack_size[n]++;
}

void MultiStack::printAll()
{
    for (int i = 0; i< v_size;i++) {
        std::cout << values[i] << " ";
    }
    std::cout<<std::endl;
}


int main()
{
    //3 Stack array of 10 values;
    MultiStack ms(3);
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
