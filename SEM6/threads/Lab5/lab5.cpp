/*
Програмне забезпечення високопродуктивних комп'ютерних систем
Лабораторна робота 5, Варіант 20
Завдання:
MZ = MM * (MR * MC) - max(R) * MS
T1 = MZ, MR, MM, R, MC, MS
T2 = -
T3 = -
T4 = -
Бондарчук Артем Дмитрович, ІП-05
Дата 17.05.2023
*/

using namespace std;

#pragma region Includes
#include <iostream>
#include <string>
#include <mpi.h>
#include <chrono>
#include "matrix.h"
#pragma endregion

#pragma region Constants
const int N = 800;
const int P = 8;
const int H = N / P;
const int INPUT = 1;

const int TAG0 = 0;
const int TAG1 = 1;
const int TAG2 = 2;
const int TAG3 = 3;
const int TAG4 = 4;
const int TAG5 = 5;
const int TAG6 = 6;
const int TAG7 = 7;
const int TAG8 = 8;
const int TAG9 = 9;
const int TAG10 = 10;
const int TAG11 = 11;
const int TAG12 = 12;
const int TAG13 = 13;
const int TAG14 = 14;
const int TAG15 = 15;
const int TAG16 = 16;
const int TAG17 = 17;
const int TAG18 = 18;
const int TAG19 = 19;
const int TAG20 = 20;
const int TAG21 = 21;
#pragma endregion

struct mtxH
{
  Matrix<int> arr = Matrix<int>(H, N);
};

int operation1(int Ah[])
{
  int max = INT_MIN;
  for (int i = 0; i < H; i++)
    if (Ah[i] > max)
      max = Ah[i];
  return max;
}

int operation2(int num1, int num2)
{
  return num1 > num2 ? num1 : num2;
}

struct mtxH mulMtx(Matrix<int> mat1, Matrix<int> mat2)
{
  mtxH res;

  for (int i = 0; i < H; i++)
  {
    for (int j = 0; j < N; j++)
    {
      res.arr(i, j) = 0;
      for (int k = 0; k < N; k++)
        res.arr(i, j) += mat1(i, j) * mat2(i, j);
    }
  }
  return res;
}

// MZ = MM * (MR * MC) - r * MS
struct mtxH operation3(Matrix<int> MMh, Matrix<int> MRh, Matrix<int> MCh, int r, Matrix<int> MSh)
{
  mtxH MZh;
  mtxH part1;
  mtxH part2;
  part1 = mulMtx(MRh, MCh);
  part2 = mulMtx(MMh, part1.arr);

  // MM * (MR * MC) - r * MS
  for (int i = 0; i < H; i++)
  {
    for (int j = 0; j < N; j++)
    {
      MZh.arr(i, j) = part2.arr(i, j) - (MSh(i, j) * r);
    }
  }
  return MZh;
}

int main(int argc, char **argv)
{
  // Declare new datatype for matrix
  MPI_Datatype row_type;
  // Initialize the MPI environment
  MPI_Init(&argc, &argv);

  int R[N];
  Matrix<int> MM = Matrix<int>(N, N);
  Matrix<int> MR = Matrix<int>(N, N);
  Matrix<int> MC = Matrix<int>(N, N);
  Matrix<int> MS = Matrix<int>(N, N);
  mtxH MZ;
  int r;

  // rank of the calling process
  int t_id;
  MPI_Comm_rank(MPI_COMM_WORLD, &t_id);

  if (t_id == 0)
  { // T1
    printf("Lab started\n");
    printf("T1 start\n");
    auto start = chrono::high_resolution_clock::now();

    // Введення MR, MM, R, MC, MS
    for (int i = 0; i < N; i++)
    {
      for (int j = 0; j < N; j++)
      {
        MR(i, j) = INPUT;
        MM(i, j) = INPUT;
        MC(i, j) = INPUT;
        MS(i, j) = INPUT;
      }
      R[i] = INPUT;
    }

    // Надіслати 2 частини в T2
    int partsT2 = H * 2;
    MPI_Send(R + H, partsT2, MPI_INT, 1, TAG0, MPI_COMM_WORLD);
    MPI_Send(&MR(0, 0), N * N, MPI_INT, 1, TAG0, MPI_COMM_WORLD);
    MPI_Send(&MM(0, 0), N * N, MPI_INT, 1, TAG0, MPI_COMM_WORLD);
    MPI_Send(&MC(H, 0), partsT2 * N, MPI_INT, 1, TAG0, MPI_COMM_WORLD);
    MPI_Send(&MS(H, 0), partsT2 * N, MPI_INT, 1, TAG0, MPI_COMM_WORLD);

    // Надіслати 1 частину в T3
    MPI_Send(R + H * 3, H, MPI_INT, 2, TAG1, MPI_COMM_WORLD);
    MPI_Send(&MR(0, 0), N * N, MPI_INT, 2, TAG1, MPI_COMM_WORLD);
    MPI_Send(&MM(0, 0), N * N, MPI_INT, 2, TAG1, MPI_COMM_WORLD);
    MPI_Send(&MC(H * 3, 0), H * N, MPI_INT, 2, TAG1, MPI_COMM_WORLD);
    MPI_Send(&MS(H * 3, 0), H * N, MPI_INT, 2, TAG1, MPI_COMM_WORLD);

    // Надіслати 4 частини в T5
    int partsT5 = H * 4;
    MPI_Send(R + H * 4, partsT5, MPI_INT, 4, TAG2, MPI_COMM_WORLD);
    MPI_Send(&MR(0, 0), N * N, MPI_INT, 4, TAG2, MPI_COMM_WORLD);
    MPI_Send(&MM(0, 0), N * N, MPI_INT, 4, TAG2, MPI_COMM_WORLD);
    MPI_Send(&MC(H * 4, 0), partsT5 * N, MPI_INT, 4, TAG2, MPI_COMM_WORLD);
    MPI_Send(&MS(H * 4, 0), partsT5 * N, MPI_INT, 4, TAG2, MPI_COMM_WORLD);

    // Обчислення 1
    r = operation1(R);

    // Прийняти r3 від T3, Обчсилення 2
    int r3;
    MPI_Recv(&r3, 1, MPI_INT, 2, TAG3, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    r = operation2(r, r3);

    // Прийняти r2 від T2, Обчсилення 2
    int r2;
    MPI_Recv(&r2, 1, MPI_INT, 1, TAG4, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    r = operation2(r, r2);

    // Прийняти r5 від T5, Обчсилення 2
    int r5;
    MPI_Recv(&r5, 1, MPI_INT, 4, TAG5, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    r = operation2(r, r5);

    // Надіслати r в T2, T3, T5
    MPI_Send(&r, 1, MPI_INT, 1, TAG6, MPI_COMM_WORLD);
    MPI_Send(&r, 1, MPI_INT, 2, TAG6, MPI_COMM_WORLD);
    MPI_Send(&r, 1, MPI_INT, 4, TAG6, MPI_COMM_WORLD);

    // Обчислення 3
    MZ = operation3(MM, MR, MC, r, MS);

    // Прийняти частини MZ від T2, T3, T5
    MPI_Recv(&MZ.arr(H, 0), partsT2 * N, MPI_INT, 1, TAG7, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    MPI_Recv(&MZ.arr(H * 3, 0), H * N, MPI_INT, 2, TAG7, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    MPI_Recv(&MZ.arr(H * 4, 0), partsT5 * N, MPI_INT, 4, TAG21, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

    // Виведення результатів
    if (N == 8)
    {
      printf("Results:\n");
      for (int i = 0; i < N; i++)
      {
        for (int j = 0; j < N; j++)
        {
          cout << MZ.arr(i, j) << " ";
        }
        cout << endl;
      }
    }
    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(stop - start);
    cout << "T1 end"
         << endl;
    cout << "Lab finished in " << duration.count() << " ms, N = " << N << endl;
  }
  else if (t_id == 1)
  { // T2
    printf("T2 start\n");

    // Прийняти 2 частини від T1
    int partsT2 = H * 2;
    MPI_Recv(R, partsT2, MPI_INT, 0, TAG0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    MPI_Recv(&MR(0, 0), N * N, MPI_INT, 0, TAG0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    MPI_Recv(&MM(0, 0), N * N, MPI_INT, 0, TAG0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    MPI_Recv(&MC(0, 0), partsT2 * N, MPI_INT, 0, TAG0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    MPI_Recv(&MS(0, 0), partsT2 * N, MPI_INT, 0, TAG0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

    // Надіслати 1 частину в T4
    MPI_Send(R + H, H, MPI_INT, 3, TAG11, MPI_COMM_WORLD);
    MPI_Send(&MR(0, 0), N * N, MPI_INT, 3, TAG11, MPI_COMM_WORLD);
    MPI_Send(&MM(0, 0), N * N, MPI_INT, 3, TAG11, MPI_COMM_WORLD);
    MPI_Send(&MC(H, 0), H * N, MPI_INT, 3, TAG11, MPI_COMM_WORLD);
    MPI_Send(&MS(H, 0), H * N, MPI_INT, 3, TAG11, MPI_COMM_WORLD);

    int r2 = operation1(R);

    int r4;
    MPI_Recv(&r4, 1, MPI_INT, 3, TAG9, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    r2 = operation2(r2, r4);

    MPI_Send(&r2, 1, MPI_INT, 0, TAG4, MPI_COMM_WORLD);

    int r1;
    MPI_Recv(&r1, 1, MPI_INT, 0, TAG6, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    MPI_Send(&r1, 1, MPI_INT, 3, TAG8, MPI_COMM_WORLD);

    MZ = operation3(MM, MR, MC, r1, MS);

    MPI_Recv(&MZ.arr(H, 0), H * N, MPI_INT, 3, TAG7, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    MPI_Send(&MZ.arr(0, 0), H * 2 * N, MPI_INT, 0, TAG7, MPI_COMM_WORLD);

    printf("T2 end\n");
  }
  else if (t_id == 2)
  { // T3
    printf("T3 start\n");
    MPI_Recv(R, H, MPI_INT, 0, TAG1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    MPI_Recv(&MR(0, 0), N * N, MPI_INT, 0, TAG1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    MPI_Recv(&MM(0, 0), N * N, MPI_INT, 0, TAG1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    MPI_Recv(&MC(0, 0), H * N, MPI_INT, 0, TAG1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    MPI_Recv(&MS(0, 0), H * N, MPI_INT, 0, TAG1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

    int r3 = operation1(R);
    MPI_Send(&r3, 1, MPI_INT, 0, TAG3, MPI_COMM_WORLD);

    int r1;
    MPI_Recv(&r1, 1, MPI_INT, 0, TAG6, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

    MZ = operation3(MM, MR, MC, r1, MS);

    MPI_Send(&MZ.arr(0, 0), H * N, MPI_INT, 0, TAG7, MPI_COMM_WORLD);

    printf("T3 end\n");
  }
  else if (t_id == 3)
  { // T4
    printf("T4 start\n");
    MPI_Recv(R, H, MPI_INT, 1, TAG11, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    MPI_Recv(&MR(0, 0), N * N, MPI_INT, 1, TAG11, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    MPI_Recv(&MM(0, 0), N * N, MPI_INT, 1, TAG11, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    MPI_Recv(&MC(0, 0), H * N, MPI_INT, 1, TAG11, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    MPI_Recv(&MS(0, 0), H * N, MPI_INT, 1, TAG11, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

    int r4 = operation1(R);
    MPI_Send(&r4, 1, MPI_INT, 1, TAG9, MPI_COMM_WORLD);

    int r1;
    MPI_Recv(&r1, 1, MPI_INT, 1, TAG8, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

    MZ = operation3(MM, MR, MC, r1, MS);

    MPI_Send(&MZ.arr(0, 0), H * N, MPI_INT, 1, TAG7, MPI_COMM_WORLD);

    printf("T4 end\n");
  }
  else if (t_id == 4)
  { // T5
    printf("T5 start\n");

    int partsT5 = H * 4;
    MPI_Recv(R, partsT5, MPI_INT, 0, TAG2, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    MPI_Recv(&MR(0, 0), N * N, MPI_INT, 0, TAG2, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    MPI_Recv(&MM(0, 0), N * N, MPI_INT, 0, TAG2, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    MPI_Recv(&MC(0, 0), partsT5 * N, MPI_INT, 0, TAG2, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    MPI_Recv(&MS(0, 0), partsT5 * N, MPI_INT, 0, TAG2, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

    // Надіслати 1 частину в T6
    MPI_Send(R + H, H, MPI_INT, 5, TAG10, MPI_COMM_WORLD);
    MPI_Send(&MR(0, 0), N * N, MPI_INT, 5, TAG10, MPI_COMM_WORLD);
    MPI_Send(&MM(0, 0), N * N, MPI_INT, 5, TAG10, MPI_COMM_WORLD);
    MPI_Send(&MC(H, 0), H * N, MPI_INT, 5, TAG10, MPI_COMM_WORLD);
    MPI_Send(&MS(H, 0), H * N, MPI_INT, 5, TAG10, MPI_COMM_WORLD);

    // Надіслати 4 частини в T7
    int partsT7 = H * 2;
    MPI_Send(R + H * 2, partsT7, MPI_INT, 6, TAG12, MPI_COMM_WORLD);
    MPI_Send(&MR(0, 0), N * N, MPI_INT, 6, TAG12, MPI_COMM_WORLD);
    MPI_Send(&MM(0, 0), N * N, MPI_INT, 6, TAG12, MPI_COMM_WORLD);
    MPI_Send(&MC(H * 2, 0), partsT7 * N, MPI_INT, 6, TAG12, MPI_COMM_WORLD);
    MPI_Send(&MS(H * 2, 0), partsT7 * N, MPI_INT, 6, TAG12, MPI_COMM_WORLD);

    int r5 = operation1(R);

    int r6;
    MPI_Recv(&r6, 1, MPI_INT, 5, TAG13, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    r5 = operation2(r5, r6);

    int r7;
    MPI_Recv(&r7, 1, MPI_INT, 6, TAG14, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    // r5 = operation2(r5, r7);
    MPI_Send(&r5, 1, MPI_INT, 0, TAG5, MPI_COMM_WORLD);

    int r1;
    MPI_Recv(&r1, 1, MPI_INT, 0, TAG6, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

    MPI_Send(&r1, 1, MPI_INT, 5, TAG17, MPI_COMM_WORLD);
    MPI_Send(&r1, 1, MPI_INT, 6, TAG17, MPI_COMM_WORLD);

    MZ = operation3(MM, MR, MC, r1, MS);

    MPI_Recv(&MZ.arr(H, 0), H * N, MPI_INT, 5, TAG19, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    MPI_Recv(&MZ.arr(H * 2, 0), H * 2 * N, MPI_INT, 6, TAG19, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

    MPI_Send(&MZ.arr(0, 0), H * 4 * N, MPI_INT, 0, TAG21, MPI_COMM_WORLD);

    printf("T5 end\n");
  }
  else if (t_id == 5)
  { // T6
    printf("T6 start\n");
    MPI_Recv(R, H, MPI_INT, 4, TAG10, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    MPI_Recv(&MR(0, 0), N * N, MPI_INT, 4, TAG10, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    MPI_Recv(&MM(0, 0), N * N, MPI_INT, 4, TAG10, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    MPI_Recv(&MC(0, 0), H * N, MPI_INT, 4, TAG10, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    MPI_Recv(&MS(0, 0), H * N, MPI_INT, 4, TAG10, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

    int r6 = operation1(R);
    MPI_Send(&r6, 1, MPI_INT, 4, TAG13, MPI_COMM_WORLD);

    int r1;
    MPI_Recv(&r1, 1, MPI_INT, 4, TAG17, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

    MZ = operation3(MM, MR, MC, r1, MS);

    MPI_Send(&MZ.arr(0, 0), H * N, MPI_INT, 4, TAG19, MPI_COMM_WORLD);

    printf("T6 end\n");
  }
  else if (t_id == 6)
  { // T7
    printf("T7 start\n");

    int partsT5 = H * 2;
    MPI_Recv(R, partsT5, MPI_INT, 4, TAG12, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    MPI_Recv(&MR(0, 0), N * N, MPI_INT, 4, TAG12, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    MPI_Recv(&MM(0, 0), N * N, MPI_INT, 4, TAG12, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    MPI_Recv(&MC(0, 0), partsT5 * N, MPI_INT, 4, TAG12, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    MPI_Recv(&MS(0, 0), partsT5 * N, MPI_INT, 4, TAG12, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

    // Надіслати 1 частину в T8
    MPI_Send(R + H, H, MPI_INT, 7, TAG15, MPI_COMM_WORLD);
    MPI_Send(&MR(0, 0), N * N, MPI_INT, 7, TAG15, MPI_COMM_WORLD);
    MPI_Send(&MM(0, 0), N * N, MPI_INT, 7, TAG15, MPI_COMM_WORLD);
    MPI_Send(&MC(H, 0), H * N, MPI_INT, 7, TAG15, MPI_COMM_WORLD);
    MPI_Send(&MS(H, 0), H * N, MPI_INT, 7, TAG15, MPI_COMM_WORLD);

    int r7 = operation1(R);

    int r8;
    MPI_Recv(&r8, 1, MPI_INT, 7, TAG16, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    r7 = operation2(r7, r8);

    MPI_Send(&r7, 1, MPI_INT, 4, TAG14, MPI_COMM_WORLD);

    int r1;
    MPI_Recv(&r1, 1, MPI_INT, 4, TAG17, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    MPI_Send(&r1, 1, MPI_INT, 7, TAG17, MPI_COMM_WORLD);

    MZ = operation3(MM, MR, MC, r1, MS);

    MPI_Recv(&MZ.arr(H, 0), H * N, MPI_INT, 7, TAG20, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    MPI_Send(&MZ.arr(0, 0), H * 2 * N, MPI_INT, 4, TAG19, MPI_COMM_WORLD);

    printf("T7 end\n");
  }
  else if (t_id == 7)
  { // T8
    printf("T8 start\n");
    MPI_Recv(R, H, MPI_INT, 6, TAG15, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    MPI_Recv(&MR(0, 0), N * N, MPI_INT, 6, TAG15, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    MPI_Recv(&MM(0, 0), N * N, MPI_INT, 6, TAG15, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    MPI_Recv(&MC(0, 0), H * N, MPI_INT, 6, TAG15, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    MPI_Recv(&MS(0, 0), H * N, MPI_INT, 6, TAG15, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

    int r8 = operation1(R);
    MPI_Send(&r8, 1, MPI_INT, 6, TAG16, MPI_COMM_WORLD);

    int r1;
    MPI_Recv(&r1, 1, MPI_INT, 6, TAG17, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

    MZ = operation3(MM, MR, MC, r1, MS);

    MPI_Send(&MZ.arr(0, 0), H * N, MPI_INT, 6, TAG20, MPI_COMM_WORLD);

    printf("T8 end\n");
  }

  MPI_Finalize();
}