namespace Lab2
{
  internal class T4
  {
    int a4;
    int p4;
    int[] X4 = new int[Lab2.N];

    int a_4;
    int d_4;
    int[] Z_4 = new int[Lab2.N];

    int[,] MMh = new int[Lab2.N, Lab2.H];
    int[] Bh = new int[Lab2.H];
    int[] Zh = new int[Lab2.H];

    int[] Ah = new int[Lab2.N];

    int start = Lab2.H * 3;
    int end = Lab2.N;

    public void Work()
    {
      Console.WriteLine("Start T4");

      Lab2.MT = Lab2.insertMtxWithNum(1);
      Lab2.Z = Lab2.insertVecWithNum(1);
      Lab2.d = 1;

      Lab2.SemInput_T4.Release(3);

      Lab2.SemInput_T1.WaitOne();
      Lab2.SemInput_T3.WaitOne();

      // КД1
      Interlocked.Exchange(ref d_4, Lab2.d);

      // КД2
      Console.WriteLine("T4 +mutex");
      Lab2.Mutex.WaitOne();
      for (int i = 0; i < Lab2.N; i++)
      {
        Z_4[i] = Lab2.Z[i];
      }
      Lab2.Mutex.ReleaseMutex();
      Console.WriteLine("T4 -mutex");

      // Обчислення 1
      Bh = Lab2.copyOfRangeVec(Lab2.B, start, end);
      MMh = Lab2.copyOfRangeMtx(Lab2.MM, start, end);

      int[] part1 = Lab2.MultiplyVectorAndScalar(Bh, d_4);

      int[] part2 = Lab2.MultiplyMatrixAndVector(MMh, Z_4);

      int[] sumOfParts = Lab2.sumVectors(part1, part2);

      Lab2.Xh_4 = Lab2.SortVector(sumOfParts);

      Lab2.SemEndXh_T4.Release(1);

      // Обчислення 4
      a_4 = Lab2.MultiplySubScalar(Lab2.B, Lab2.Z, start, end);

      // Обчислення 5
      // КД3
      Interlocked.Add(ref Lab2.a, a_4);
      Lab2.SemEnda_T4.Release(3);

      Lab2.EventEndX.WaitOne();

      Lab2.SemEnda_T1.WaitOne();
      Lab2.SemEnda_T2.WaitOne();
      Lab2.SemEnda_T3.WaitOne();

      // КД4
      Interlocked.Exchange(ref p4, Lab2.p);

      // КД5
      lock (Lab2.CS)
      {
        for (int i = 0; i < Lab2.N; i++)
        {
          X4[i] = Lab2.X[i];
        }
      }

      // КД6
      Interlocked.Exchange(ref a4, Lab2.a);

      // Обчислення 6
      int[,] Mtx = Lab2.MultiplySubMatrix(Lab2.MX, Lab2.MT, start, end);
      int[] Vec = Lab2.MultiplyMatrixAndVector(Mtx, X4);

      int[] part3 = Lab2.MultiplyVectorAndScalar(Vec, p4);

      Zh = Lab2.copyOfRangeVec(Lab2.Z, start, end);
      int[] part4 = Lab2.MultiplyVectorAndScalar(Zh, a4);

      Ah = Lab2.sumVectors(part3, part4);
      Lab2.writeToSubVector(Lab2.A, Ah, start, end);

      Lab2.Barrier.SignalAndWait();
      Lab2.PrintVec(Lab2.A);
      Console.WriteLine("T4 - end");
    }
  }
}