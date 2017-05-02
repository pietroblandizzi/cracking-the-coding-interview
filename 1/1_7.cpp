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

#define N 5

void rotateMatrix (int m[][N]);
void rotateMatrix90 (int m[][N]);
void mySwap(int& a, int& b);
void printMatrix (int m[][N]);

int main()
{
    int m[N][N];
    int counter =1;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            m[i][j] = counter++;
        }
    }
    printMatrix(m);
    rotateMatrix90(m);
    std::cout << std::endl << std::endl;
    printMatrix(m);
    return 0;
}

void rotateMatrix (int m[][N])
{
    for (int l = 0; l < (int)N/2; l++) {

        for (int i = l+1; i < N-l; i++) {
            mySwap(m[l][l], m[l][i]);
        }
        for (int i = l+1; i < N-l; i++) {
            mySwap(m[l][l], m[i][N-1-l]);
        }

        for (int i = N-2-l; i >= l; i--) {
            mySwap(m[l][l], m[N-1-l][i]);
        }

        for (int i = N-2-l; i >= l; i--) {
            mySwap(m[l][l], m[i][l]);
        }
    }
}

void rotateMatrix90 (int m[][N])
{
    for (int l = 0; l < (int)N/2; l++) {
        int first = l;
        int last = N-1-l;

        for (int i = first; i < last; i++) {
            int offset = i - first;
            int top = m[first][i];
            //left ->top
            m[first][i]=m[last-offset][first];
            //down->left
            m[last-offset][first] = m[last][last-offset];
            //right->down
            m[last][last-offset] = m[i][last];
            //top -> right
            m[i][last] = top;
        }
    }
}

void mySwap(int& a, int& b)
{
    int t = a;
    a = b;
    b = t;
    return;
}


void printMatrix (int m[][N])
{
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            std::cout << m[i][j] << " " ;
            if (j == N-1)
                std::cout<<std::endl;
        }
    }
}
