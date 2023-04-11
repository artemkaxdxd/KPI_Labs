namespace Lab2
{
  internal class T3
  {
    int a3;
    int p3;
    int[] X3 = new int[Lab2.N];

    int a_3;
    int d_3;
    int[] Z_3 = new int[Lab2.N];

    int[,] MMh = new int[Lab2.N, Lab2.H];
    int[] Bh = new int[Lab2.H];
    int[] Zh = new int[Lab2.H];

    int[] Ah = new int[Lab2.N];

    int start = Lab2.H * 2;
    int end = Lab2.H * 3;

    public void Work()
    {
      Console.WriteLine("Start T3");

      Lab2.p = 1;

      Lab2.SemInput_T3.Release(3);

      Lab2.SemInput_T1.WaitOne();
      Lab2.SemInput_T4.WaitOne();

      // КД1
      Interlocked.Exchange(ref d_3, Lab2.d);

      // КД2
      Console.WriteLine("T3 +mutex");
      Lab2.Mutex.WaitOne();
      for (int i = 0; i < Lab2.N; i++)
      {
        Z_3[i] = Lab2.Z[i];
      }
      Lab2.Mutex.ReleaseMutex();
      Console.WriteLine("T3 -mutex");

      // Обчислення 1
      Bh = Lab2.copyOfRangeVec(Lab2.B, start, end);
      MMh = Lab2.copyOfRangeMtx(Lab2.MM, start, end);

      int[] part1 = Lab2.MultiplyVectorAndScalar(Bh, d_3);

      int[] part2 = Lab2.MultiplyMatrixAndVector(MMh, Z_3);

      int[] sumOfParts = Lab2.sumVectors(part1, part2);

      Lab2.Xh_3 = Lab2.SortVector(sumOfParts);

      Lab2.SemEndXh_T4.WaitOne();

      // Обчислення 2
      Lab2.X2h_2 = Lab2.SortVector(Lab2.ConcatVectors(Lab2.Xh_3, Lab2.Xh_4));
      Lab2.SemEndX2h_T3.Release(1);

      // Обчислення 4
      a_3 = Lab2.MultiplySubScalar(Lab2.B, Lab2.Z, start, end);

      // КД3
      // Обчислення 5
      Interlocked.Add(ref Lab2.a, a_3);

      Lab2.SemEnda_T3.Release(3);

      Lab2.EventEndX.WaitOne();

      Lab2.SemEnda_T1.WaitOne();
      Lab2.SemEnda_T2.WaitOne();
      Lab2.SemEnda_T4.WaitOne();

      // КД4
      Interlocked.Exchange(ref p3, Lab2.p);

      // КД5
      lock (Lab2.CS)
      {
        for (int i = 0; i < Lab2.N; i++)
        {
          X3[i] = Lab2.X[i];
        }
      }

      // КД6
      Interlocked.Exchange(ref a3, Lab2.a);

      // Обчислення 6
      int[,] Mtx = Lab2.MultiplySubMatrix(Lab2.MX, Lab2.MT, start, end);
      int[] Vec = Lab2.MultiplyMatrixAndVector(Mtx, X3);

      int[] part3 = Lab2.MultiplyVectorAndScalar(Vec, p3);

      Zh = Lab2.copyOfRangeVec(Lab2.Z, start, end);
      int[] part4 = Lab2.MultiplyVectorAndScalar(Zh, a3);

      Ah = Lab2.sumVectors(part3, part4);
      Lab2.writeToSubVector(Lab2.A, Ah, start, end);

      Lab2.Barrier.SignalAndWait();

      Console.WriteLine("T3 - end");
    }
  }
}