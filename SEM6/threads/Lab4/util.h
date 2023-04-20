#ifndef UTIL_H
#define UTIL_H

#include <string>

namespace util
{
  int *fillVec(int);
  int **fillMtx(int, int);
  int setScalar();
  std::string str(int *, int);
}

#endif // UTIL_H