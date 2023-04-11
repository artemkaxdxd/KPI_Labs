namespace Lab2
{
  internal class T1
  {
    int a1;
    int p1;
    int[] X1 = new int[Lab2.N];

    int a_1;
    int d_1;
    int[] Z_1 = new int[Lab2.N];

    int[,] MMh = new int[Lab2.N, Lab2.H - 0];
    int[] Bh = new int[Lab2.H - 0];
    int[] Zh = new int[Lab2.H - 0];

    int[] Ah = new int[Lab2.N];

    int start = 0;
    int end = Lab2.H;

    public void Work()
    {
      Console.WriteLine("Start T1");

      // Введення даних
      Lab2.MM = Lab2.insertMtxWithNum(1);
      Lab2.B = Lab2.insertVecWithNum(1);
      Lab2.MX = Lab2.insertMtxWithNum(1);

      // Сигнал про введення
      Lab2.SemInput_T1.Release(3);

      // Очікує введення даних
      Lab2.SemInput_T3.WaitOne();
      Lab2.SemInput_T4.WaitOne();

      // КД1
      Interlocked.Exchange(ref d_1, Lab2.d);

      // КД2
      Console.WriteLine("T1 +mutex");
      Lab2.Mutex.WaitOne();
      for (int i = 0; i < Lab2.N; i++)
      {
        Z_1[i] = Lab2.Z[i];
      }
      Lab2.Mutex.ReleaseMutex();
      Console.WriteLine("T1 -mutex");

      // Обчислення 1
      Bh = Lab2.copyOfRangeVec(Lab2.B, start, end);
      MMh = Lab2.copyOfRangeMtx(Lab2.MM, start, end);

      int[] part1 = Lab2.MultiplyVectorAndScalar(Bh, d_1);

      int[] part2 = Lab2.MultiplyMatrixAndVector(MMh, Z_1);

      int[] sumOfParts = Lab2.sumVectors(part1, part2);

      Lab2.Xh_1 = Lab2.SortVector(sumOfParts);

      Lab2.SemEndXh_T2.WaitOne();

      // Обчислення 2
      Lab2.X2h_1 = Lab2.SortVector(Lab2.ConcatVectors(Lab2.Xh_1, Lab2.Xh_2));
      Lab2.SemEndX2h_T3.WaitOne();

      // Обчислення 3
      Lab2.X = Lab2.SortVector(Lab2.ConcatVectors(Lab2.X2h_1, Lab2.X2h_2));

      Lab2.EventEndX.Set();

      // Обчислення 4
      a_1 = Lab2.MultiplySubScalar(Lab2.B, Lab2.Z, start, end);

      // КД3
      // Обчислення 5
      Interlocked.Add(ref Lab2.a, a_1);

      Lab2.SemEnda_T1.Release(3);

      Lab2.SemEnda_T2.WaitOne();
      Lab2.SemEnda_T3.WaitOne();
      Lab2.SemEnda_T4.WaitOne();

      // КД4
      Interlocked.Exchange(ref p1, Lab2.p);

      // КД5
      lock (Lab2.CS)
      {
        for (int i = 0; i < Lab2.N; i++)
        {
          X1[i] = Lab2.X[i];
        }
      }

      // КД6
      Interlocked.Exchange(ref a1, Lab2.a);

      // Обчислення 6
      int[,] Mtx = Lab2.MultiplySubMatrix(Lab2.MX, Lab2.MT, start, end);
      int[] Vec = Lab2.MultiplyMatrixAndVector(Mtx, X1);

      int[] part3 = Lab2.MultiplyVectorAndScalar(Vec, p1);

      Zh = Lab2.copyOfRangeVec(Lab2.Z, start, end);
      int[] part4 = Lab2.MultiplyVectorAndScalar(Zh, a1);

      Ah = Lab2.sumVectors(part3, part4);
      Lab2.writeToSubVector(Lab2.A, Ah, start, end);

      Lab2.Barrier.SignalAndWait();

      Console.WriteLine("T1 - end");
    }
  }
}