/*
Програмне забезпечення високопродуктивних комп'ютерних систем
Лабораторна робота 2, Варіант 16
Завдання:
A = p * sort(d*B + Z*MM) * (MX*MT) + (B*Z)*Z
T1 = MM, B, MX
T2 = -
T3 = p
T4 = A, Z, MT, d

Бондарчук Артем Дмитрович, ІП-05
Дата 09.04.2023
*/
using System.Diagnostics;

namespace Lab2
{
  internal class Lab2
  {
    public static int N = 800;
    public static int P = 4;
    public static int H = N / P;

    public static int p = 0;
    public static int d = 0;

    public static int a = 0;

    public static int[] A = new int[N];
    public static int[] B = new int[N];
    public static int[] Z = new int[N];

    public static int[,] MM = new int[N, N];
    public static int[,] MX = new int[N, N];
    public static int[,] MT = new int[N, N];

    public static int[] X = new int[N];

    public static int[] Xh_1 = new int[H];
    public static int[] Xh_2 = new int[H];
    public static int[] Xh_3 = new int[H];
    public static int[] Xh_4 = new int[H];

    public static int[] X2h_1 = new int[H * 2];
    public static int[] X2h_2 = new int[H * 2];

    public static Semaphore SemInput_T1 = new Semaphore(0, 3);
    public static Semaphore SemInput_T3 = new Semaphore(0, 3);
    public static Semaphore SemInput_T4 = new Semaphore(0, 3);

    public static Semaphore SemEndXh_T2 = new Semaphore(0, 3);
    public static Semaphore SemEndXh_T4 = new Semaphore(0, 3);

    public static Semaphore SemEndX2h_T3 = new Semaphore(0, 3);

    public static Semaphore SemEnda_T1 = new Semaphore(0, 3);
    public static Semaphore SemEnda_T2 = new Semaphore(0, 3);
    public static Semaphore SemEnda_T3 = new Semaphore(0, 3);
    public static Semaphore SemEnda_T4 = new Semaphore(0, 3);

    public static EventWaitHandle EventEndX = new EventWaitHandle(false, EventResetMode.ManualReset);
    public static Mutex Mutex = new Mutex();
    public static object CS = new object();
    public static Barrier Barrier = new Barrier(participantCount: 4);

    static Stopwatch watch = new Stopwatch();

    static void Main(string[] args)
    {
      watch.Start();

      Thread T1 = new Thread(new T1().Work);
      Thread T2 = new Thread(new T2().Work);
      Thread T3 = new Thread(new T3().Work);
      Thread T4 = new Thread(new T4().Work);

      T1.Start();
      T2.Start();
      T3.Start();
      T4.Start();

      T1.Join();
      T2.Join();
      T3.Join();
      T4.Join();

      watch.Stop();
      Console.WriteLine("N = " + N);
      Console.WriteLine("Time for calculation = " + watch.ElapsedMilliseconds);
    }

    // Calculation section

    public static int[] SortVector(int[] A)
    {
      for (int i = 0; i < A.Length; i++)
      {
        for (int j = 0; j < A.Length - 1; j++)
        {
          if (A[j] > A[j + 1])
          {
            Swap(ref A[j], ref A[j + 1]);
          }
        }
      }

      return A;
    }

    public static void Swap(ref int a, ref int b)
    {
      int temp = a;
      a = b;
      b = temp;
    }

    public static int[] ConcatVectors(int[] A, int[] B)
    {
      int[] C = new int[A.Length + B.Length];
      int index = 0;

      for (int i = 0; i < A.Length; i++)
      {
        C[index++] = A[i];
      }

      for (int i = 0; i < B.Length; i++)
      {
        C[index++] = B[i];
      }

      return C;
    }

    public static int MultiplySubScalar(int[] A, int[] B, int start, int end)
    {
      int result = 0;

      for (int i = start; i < end; i++)
      {
        result += A[i] * B[i];
      }

      return result;
    }

    public static int[,] MultiplySubMatrix(int[,] MA, int[,] MB, int start, int end)
    {
      int[,] MX = new int[N, end - start];

      for (int i = 0; i < N; i++)
      {
        int x = 0;
        for (int j = start; j < end; j++)
        {
          MX[i, x] = 0;
          for (int k = 0; k < N; k++)
          {
            MX[i, x] += MA[i, k] * MB[k, j];
          }
          x++;
        }
      }

      return MX;
    }

    public static int[] MultiplyMatrixAndVector(int[,] MA, int[] B)
    {
      int[] X = new int[MA.GetLength(1)];

      for (int i = 0; i < MA.GetLength(0); i++)
      {
        for (int j = 0; j < MA.GetLength(1); j++)
        {
          X[j] += MA[i, j] * B[i];
        }
      }

      return X;
    }

    public static int[] MultiplyVectorAndScalar(int[] A, int b)
    {
      int[] B = new int[A.Length];

      for (int i = 0; i < B.Length; i++)
      {
        B[i] = A[i] * b;
      }

      return B;
    }

    public static int[] sumVectors(int[] A, int[] B)
    {
      int[] X = new int[A.Length];

      for (int i = 0; i < X.Length; i++)
      {
        X[i] = A[i] + B[i];
      }

      return X;
    }

    // Helper section

    public static void writeToSubVector(int[] A, int[] B, int start, int end)
    {
      int index = 0;
      for (int i = start; i < end; i++)
      {
        A[i] = B[index++];
      }
    }

    public static int[] copyOfRangeVec(int[] src, int start, int end)
    {
      int len = end - start;
      int[] dest = new int[len];
      Array.Copy(src, start, dest, 0, len);
      return dest;
    }

    public static int[,] copyOfRangeMtx(int[,] src, int start, int end)
    {
      int len = end - start;
      int[,] dest = new int[N, len];
      Array.Copy(src, start, dest, 0, len);
      return dest;
    }

    public static int[,] insertMtxWithNum(int num)
    {
      int[,] tempMtx = new int[N, N];
      for (int i = 0; i < N; i++)
      {
        for (int j = 0; j < N; j++)
        {
          tempMtx[i, j] = num;
        }
      }
      return tempMtx;
    }

    public static int[] insertVecWithNum(int num)
    {
      int[] tempVec = new int[N];
      for (int i = 0; i < N; i++)
      {
        tempVec[i] = num;
      }
      return tempVec;
    }

    public static void PrintVec(int[] Vec)
    {
      Console.WriteLine("\nResult:");
      for (int i = 0; i < Vec.Length; i++)
      {
        Console.Write(Vec[i] + " ");
      }
      Console.WriteLine();
    }
  }
}