namespace Lab2
{
  internal class T2
  {
    int a2;
    int p2;
    int[] X2 = new int[Lab2.N];

    int a_2;
    int d_2;
    int[] Z_2 = new int[Lab2.N];

    int[,] MMh = new int[Lab2.N, Lab2.H];
    int[] Bh = new int[Lab2.H];
    int[] Zh = new int[Lab2.H];

    int[] Ah = new int[Lab2.N];

    int start = Lab2.H;
    int end = Lab2.H * 2;

    public void Work()
    {
      Console.WriteLine("Start T2");

      Lab2.SemInput_T1.WaitOne();
      Lab2.SemInput_T3.WaitOne();
      Lab2.SemInput_T4.WaitOne();

      // КД1
      Interlocked.Exchange(ref d_2, Lab2.d);

      // КД2
      Console.WriteLine("T2 +mutex");
      Lab2.Mutex.WaitOne();
      for (int i = 0; i < Lab2.N; i++)
      {
        Z_2[i] = Lab2.Z[i];
      }
      Lab2.Mutex.ReleaseMutex();
      Console.WriteLine("T2 -mutex");

      // Обчислення 1
      Bh = Lab2.copyOfRangeVec(Lab2.B, start, end);

      MMh = Lab2.copyOfRangeMtx(Lab2.MM, start, end);

      int[] part1 = Lab2.MultiplyVectorAndScalar(Bh, d_2);

      int[] part2 = Lab2.MultiplyMatrixAndVector(MMh, Z_2);

      int[] sumOfParts = Lab2.sumVectors(part1, part2);

      Lab2.Xh_2 = Lab2.SortVector(sumOfParts);

      Lab2.SemEndXh_T2.Release(1);

      // Обчислення 4
      a_2 = Lab2.MultiplySubScalar(Lab2.B, Lab2.Z, start, end);

      // Обчислення 5
      Interlocked.Add(ref Lab2.a, a_2);
      Lab2.SemEnda_T2.Release(3);

      Lab2.EventEndX.WaitOne();

      Lab2.SemEnda_T1.WaitOne();
      Lab2.SemEnda_T3.WaitOne();
      Lab2.SemEnda_T4.WaitOne();

      // КД4
      Interlocked.Exchange(ref p2, Lab2.p);

      // КД5
      lock (Lab2.CS)
      {
        for (int i = 0; i < Lab2.N; i++)
        {
          X2[i] = Lab2.X[i];
        }
      }

      // КД6
      Interlocked.Exchange(ref a2, Lab2.a);

      // Обчислення 6
      int[,] Mtx = Lab2.MultiplySubMatrix(Lab2.MX, Lab2.MT, start, end);
      int[] Vec = Lab2.MultiplyMatrixAndVector(Mtx, X2);

      int[] part3 = Lab2.MultiplyVectorAndScalar(Vec, p2);

      Zh = Lab2.copyOfRangeVec(Lab2.Z, start, end);
      int[] part4 = Lab2.MultiplyVectorAndScalar(Zh, a2);

      Ah = Lab2.sumVectors(part3, part4);
      Lab2.writeToSubVector(Lab2.A, Ah, start, end);


      Lab2.Barrier.SignalAndWait();

      Console.WriteLine("T2 - end");
    }
  }
}