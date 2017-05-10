#include <iostream>
#include <exception>
#include <string>

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


int main()
{
    try {
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
    std::cout << ms.pop(2) << std::endl;
    ms.push(2,7);
    ms.push(2,7);
    ms.push(0,7);
    ms.printAll();

    }catch (std::string e) {std::cout << e;}
    return 0;
}
