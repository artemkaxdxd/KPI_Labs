public class T1 extends Thread {
    private int z1_1; // max(Zh)
    private int z_1; // z
    private int d_1; // d
    private int p_1; // p

    @Override
    public void run() {
        try {
            System.out.println("1: Старт T1");

            System.out.println("1: Ввід d");
            Data.d.set(1);

            System.out.println("1: Ввід матриці MM");
            Data.MM = Data.insertMtxWithNum(1);

            System.out.println("1: T1 звільнює дозвіл для інших семафорів");
            Data.SemInput_T1.release(3);

            try {
                System.out.println("1: T1 чекає на дозвіл T2 T4 про введення даних");
                Data.SemInput_T2.acquire();
                Data.SemInput_T4.acquire();
                System.out.println("1: T1 отримує дозвіл T2 T4");

                z1_1 = Data.maxSubArr(Data.Z, 0, Data.H);
                Data.z.set(Data.setMax(Data.z, z1_1));

                Data.SemEndZ_T1.release(3);

                try {
                    System.out.println("1: T1 чекає на EndZ_T[2, 3, 4]");

                    Data.SemEndZ_T2.acquire();
                    Data.SemEndZ_T3.acquire();
                    Data.SemEndZ_T4.acquire();

                    System.out.println("1: T1 отримало на EndZ_T[2, 3, 4]");


                    z_1 = Data.z.get();
                    d_1 = Data.d.get();
                    p_1 = Data.p.get();

                    int[][] subSumMtx1 = Data.sumSubMtx(Data.MX, Data.MM, 0, Data.H);
                    int[][] part2 = Data.mulMtxAndScalars(subSumMtx1, z_1, p_1);
                    int[][] subMulMtx = Data.mulSubMtx(Data.MC, Data.MD, 0, Data.H);
                    int[][] part1 = Data.mulMtxAndScalars(subMulMtx, d_1, 1);
                    int[][] MA_1 = Data.sumMtx(part1, part2);
                    Data.saveToSubMatrix(MA_1, Data.MA, 0, Data.H);

                    System.out.println("1: T1 чекає на дозволи T2 T3 T3");
                    Data.SemEnd_T2.acquire();
                    Data.SemEnd_T3.acquire();
                    Data.SemEnd_T4.acquire();
                    System.out.println("1: T1 отримує дозволи T2 T3 T3");

                    System.out.println("1: Вивід результату MO:");
                    Data.printMatrix(Data.MA);

                } catch (Exception e) {
                    throw new RuntimeException(e);
                }


            } catch (InterruptedException e) {
                throw new RuntimeException(e);
            }


        } catch (RuntimeException e) {
            throw new RuntimeException(e);
        }
    }
}
