#ifndef UTIL_H
#define UTIL_H

#include <string>

namespace util
{
  int *fillVec(int);
  int **fillMtx(int, int);
  int setScalar();
  std::string str(int *, int);

  int *CalculateXH(int, int, int *, int **, int *);
  int *SortVector(int *);
  int *AddVectors(int *, int *);
}

#endif // UTIL_H