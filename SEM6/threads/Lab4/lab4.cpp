/*
Програмне забезпечення високопродуктивних комп'ютерних систем
Лабораторна робота 4, Варіант 26
Завдання:
V = sort(d*B + Z*MM) * (MX*MT) + (B*Z)*B
T1 = MM, B, MX
T2 = V, Z
T3 = -
T4 = MT, d
Бондарчук Артем Дмитрович, ІП-05
Дата 20.04.2023
*/

#include <iostream>
#include <omp.h>
#include <chrono>

#include "lab4.h"
#include "util.cpp"

int main(int argc, char *argv[])
{
  std::cout << "--Start" << std::endl;
  auto start = std::chrono::high_resolution_clock::now();
  int threadId;

  int d, a;
  int *V, *Z, *B, *X;
  int **MM, **MX, **MT;
  a = 0;
  omp_lock_t lock_sortX;
  omp_init_lock(&lock_sortX);

  int cp_d, cp_a;
  int *cp_Z, *cp_X;
  int **cp_MX;

  V = new int[N];
  X = new int[N];
  int part = 0;

  omp_set_num_threads(4);

#pragma omp parallel default(shared) private(threadId, cp_d, cp_a, cp_Z, cp_X, cp_MX, part)
  {
    threadId = omp_get_thread_num();

#pragma omp critical(io)
    std::cout << "Thread " << threadId << " started" << std::endl;

    // Input
    switch (threadId)
    {
    case 0:
      // Input MM, B, MX on thread 1
      MM = util::fillMtx(N, N);
      B = util::fillVec(N);
      MX = util::fillMtx(N, N);
      break;
    case 1:
      // Input Z on thread 2
      Z = util::fillVec(N);
      break;
    case 3:
      // Input MT, d on thread 4
      MT = util::fillMtx(N, N);
      d = util::setScalar();
      break;
    default:
      break; // noop
    }
#pragma omp barrier // Очікування на завершення вводу даних

#pragma omp critical(CS1) // КД1 - Копіювання d
    {
      cp_d = d;
    }

#pragma omp critical(CS2) // КД2 - Копіювання Z
    {
      cp_Z = Z;
    }

    // Обчислення 1 -- sort(d*Bh + Z*MMh)
#pragma omp for
    for (int i = 0; i < N; i++)
    {
      int part = 0;

      for (int j = 0; j < N; j++)
      {
        part += MM[i][j] * cp_Z[j];
      }
      X[i] = cp_d * B[i] + part;
    }

#pragma omp for
    for (int i = 0; i < N; i++)
    {
      for (int j = 0; j < N - i; j++)
      {
        if (X[j] > X[j + 1])
        {
          std::swap(X[j], X[j + 1]);
        }
      }
    }

#pragma omp barrier // Очікування обчислення X

    // Обчислення 2 -- (Bh * Zh)
#pragma omp for
    for (int i = 0; i < N; i++)
    {
      a += B[i] * Z[i];
    }
#pragma omp barrier // Очікування обчислення a

#pragma omp critical(CS3) // КД3 - Копіювання X
    {
      cp_X = X;
    }

#pragma omp critical(CS4) // КД4 - Копіювання a
    {
      cp_a = a;
    }

#pragma omp critical(CS5) // КД5 - Копіювання MX
    {
      cp_MX = MX;
    }

    // Обчислення 3 -- X * (MX * MTh) + a * Bh
#pragma omp for
    for (int i = 0; i < N; i++)
    {
      for (int j = 0; j < N; j++)
      {
        part = 0;
        for (int k = 0; k <= N; k++)
        {
          part += cp_X[k] * (cp_MX[i][j] * MT[i][j]);
        }
      }
      V[i] = cp_a * B[i] + part;
    }

#pragma omp barrier // Очікування обчислення V

    if (threadId == 1)
    {
#pragma omp critical(io)
      {
        if (N == 4)
        {
          std::cout << util::str(V, N) << std::endl;
        }
        std::cout << "N = " << N << std::endl;
        auto stop = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
        std::cout << "Time of calculation: " << duration.count() << std::endl;
      }
    }
#pragma omp critical(io)
    {

      std::cout << "Thread " << threadId << " finished" << std::endl;
    }
  }
  for (int i = 0; i < N; ++i)
  {
    delete[] MX[i];
    delete[] MT[i];
    delete[] MM[i];
  }
  delete[] Z;
  delete[] B;
  delete[] V;
  delete[] MX;
  delete[] MT;
  delete[] MM;

  std::cout << "lab 04 finished" << std::endl;
}