#include "util.h"
#include "lab4.h"

int *util::fillVec(int size)
{
  int *v = new int[size];
  for (int i = 0; i < size; ++i)
    v[i] = 1;
  return v;
}

int **util::fillMtx(int rows, int cols)
{
  int **m = new int *[rows];
  for (int r = 0; r < rows; ++r)
    m[r] = fillVec(cols);
  return m;
}

int util::setScalar() { return 1; }

std::string util::str(int *matrix, int rows)
{
  std::string s = "[";
  for (int r = 0; r < rows; ++r)
  {
    s.append(" ").append(std::to_string(matrix[r])).append(" ");
  }
  s.append("]");
  return s;
}

int *util::CalculateXH(int left, int d, int *Z, int **MM, int *B)
{
  int right = left + H;
  int *temp = new int[N];
#pragma for
  for (int i = left; i < right; i++)
  {
    int part = 0;
    for (int j = 0; j < N; j++)
    {
      part += MM[i][j] * Z[j];
    }
    temp[i] = d * B[i] + part;
  }
  return temp;
}

int *util::SortVector(int *arr)
{

  int temp, i, j;
#pragma for
  for (i = 0; i < N; i++)
  {
    for (j = 0; j < N - 1; j++)
    {
      if (arr[j] > arr[i])
      {
        temp = arr[i]; // swap them
        arr[i] = arr[j];
        arr[j] = temp;
      }
    }
  }
  return arr;
}

int *util::AddVectors(int *A, int *B)
{
  int *C = new int[N];
#pragma for
  for (int i = 0; i < N; i++)
  {
    C[i] = A[i] + B[i];
  }

  return C;
}
