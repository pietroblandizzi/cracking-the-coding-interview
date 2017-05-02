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
#include <vector>

#define N 5
#define M 6

void nullifyMatrix (int m[][M]);
void nullifyMatrixV2 (int m[][M]);
void printMatrix (int m[][M]);

int main()
{
    int m[N][M];
    int counter =1;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            m[i][j] = counter++;
        }
    }
//    m[0][0] = 0;
    m[3][3] = 0;
//    m[4][4] = 0;
    printMatrix(m);
    nullifyMatrixV2(m);
    std::cout << std::endl << std::endl;
    printMatrix(m);
    return 0;
}


void printMatrix (int m[][M])
{
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            std::cout << m[i][j] << "  " ;
            if (j == M-1)
                std::cout<<std::endl;
        }
    }
}

//my first solution
void nullifyMatrix (int m[][M])
{
    std::vector<bool> row(N);
    std::vector<bool> col(M);

    for (int i = 0; i<N; i++) {
        for (int j = 0; j<M; j++) {
            if (row[i] == false && col[j] == false && m[i][j]== 0) {
                // nullify
                for (int k = 0; k < M; k++)
                    m[i][k]=0;

                for (int k = 0; k < N; k++)
                    m[k][j]= 0;

                 row[i]= true;
                 col[j]=true;
                break;
            }
        }
    }
}

// using the matrix itself the algorithm is N^2
void nullifyMatrixV2 (int m[][M])
{
   bool firstRowZero = false, firstColZero = false;
    for (int i = 0; i < M; i++) {
        if (m[0][i]== 0) {
            firstRowZero = true;
            break;
        }
    }
    for (int i = 0; i < N; i++) {
        if (m[i][0]==0) {
            firstColZero = true;
            break;
        }
    }
  for (int i = 1; i<N; i++) {
        for (int j = 1; j<M; j++) {
            if (m[i][j] == 0) {
                 m[i][0] = 0;
                 m[0][j] = 0;
            }
        }
    }
    for (int i = 1; i < M; i++) {
        if (m[0][i] == 0 ) {
            for (int j = 0; j<N;j++)
                m[j][i]=0;
        }
    }
    for (int i = 1; i < N; i++) {
        if (m[i][0] == 0) {
            for (int j = 0; j<M;j++)
                m[i][j]=0;
        }
    }
    if (firstRowZero) {
        for (int i = 1; i < M; i++) {
            m[0][i]=0;
        }
    }
        if (firstColZero) {
        for (int i = 1; i < N; i++) {
            m[i][0]=0;
        }
    }

}

