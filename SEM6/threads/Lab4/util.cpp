#include "util.h"

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