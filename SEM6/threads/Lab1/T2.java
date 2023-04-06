import java.util.Arrays;

public class T2 extends Thread {
    private int z2_1; // max(Zh)
    private int z_2; // z
    private int d_2; // d
    private int p_2; // p
    //МА= MD*MCh *d + max(Z)*(MXh+MMh)*p

    // Input MX, MC

    // calc max Z
    // z_1 = set max Z
    // subSumMtx1 = MX_1 + MM_1
    // Part2 = subSumMtx1 * z * p
    // subMulMtx1_2 = MC_1 * MD
    // Part1 = subMulMtx1_2 * d
    // save sub MA 1 = subMulMtx1_3 + firstPart

    @Override
    public synchronized void run() {
        try {
            System.out.println("2: Старт T2");

            System.out.println("2: Ввід матриці MX");
            Data.MX = Data.insertMtxWithNum(1);

            System.out.println("2: Ввід матриці MC");
            Data.MC = Data.insertMtxWithNum(1);

            System.out.println("2: T2 звільнює дозвіл для інших семафорів");
            Data.SemInput_T2.release(3);

            try {
                System.out.println("2: T2 чекає на дозвіл T1 T4 про введення даних");
                Data.SemInput_T1.acquire();
                Data.SemInput_T4.acquire();
                System.out.println("2: T2 отримує дозвіл T1 T4");

                z2_1 = Data.maxSubArr(Data.Z, Data.H, Data.H * 2);
                Data.z.set(Data.setMax(Data.z, z2_1));

                Data.SemEndZ_T2.release(3);

                try {
                    System.out.println("2: T2 чекає на EndZ_T[1, 3, 4]");
                    Data.SemEndZ_T1.acquire();
                    Data.SemEndZ_T3.acquire();
                    Data.SemEndZ_T4.acquire();

                    System.out.println("2: T2 отримало на EndZ_T[1, 3, 4]");

                    z_2 = Data.z.get();
                    d_2 = Data.d.get();
                    p_2 = Data.p.get();

                    int[][] subSumMtx1 = Data.sumSubMtx(Data.MX, Data.MM, Data.H, Data.H * 2);
                    int[][] part2 = Data.mulMtxAndScalars(subSumMtx1, z_2, p_2);
                    int[][] subMulMtx = Data.mulSubMtx(Data.MC, Data.MD, Data.H, Data.H * 2);
                    int[][] part1 = Data.mulMtxAndScalars(subMulMtx, d_2, 1);
                    int[][] MA_1 = Data.sumMtx(part1, part2);
                    //Lab1.savePartMtx(Data.H, MA_1);
                    Data.saveToSubMatrix(MA_1, Data.MA, Data.H, Data.H * 2);

                    Data.SemEnd_T2.release(1);

                    System.out.println("2: T2 stopped");

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
