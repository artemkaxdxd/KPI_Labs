import java.util.Arrays;

public class T4 extends Thread {

    //МА= MD*MCh *d + max(Z)*(MXh+MMh)*p

    // Input Z, MD, p

    // calc max Z
    // z_1 = set max Z
    // subSumMtx1 = MX_1 + MM_1
    // Part2 = subSumMtx1 * z * p
    // subMulMtx1_2 = MC_1 * MD
    // Part1 = subMulMtx1_2 * d
    // save sub MA 1 = subMulMtx1_3 + firstPart

    private int z4_1; // max(Zh)
    private int z_4; // z
    private int d_4; // d
    private int p_4; // p

    @Override
    public synchronized void run() {
        try {
            System.out.println("4: Старт T4");

            System.out.println("4: Ввід Вектору Z");
            Data.Z = Data.insertVecWithNum(1);

            System.out.println("4: Ввід матриці MD");
            Data.MD = Data.insertMtxWithNum(1);

            System.out.println("4: Ввід z");
            Data.p.set(1);

            System.out.println("S4_1: T4 звільнює дозвіл для інших семафорів");
            Data.SemInput_T4.release(3);

            try {
                System.out.println("W4_1-2: T4 чекає на дозвіл T1 T4 про введення даних");
                Data.SemInput_T1.acquire();
                Data.SemInput_T2.acquire();
                System.out.println("4: T4 отримує дозвіл T1 T2");

                z4_1 = Data.maxSubArr(Data.Z, Data.H * 3, Data.N);
                Data.z.set(Data.setMax(Data.z, z4_1));

                System.out.println("S4_2: T4 звільнює дозвіл для інших семафорів");
                Data.SemEndZ_T4.release(3);

                try {
                    System.out.println("W4_3-5: T4 чекає на EndZ_T[1, 2, 3]");
                    Data.SemEndZ_T1.acquire();
                    Data.SemEndZ_T2.acquire();
                    Data.SemEndZ_T3.acquire();
                    System.out.println("4: T4 отримало на EndZ_T[1, 2, 3]");

                    z_4 = Data.z.get();
                    d_4 = Data.d.get();
                    p_4 = Data.p.get();

                    int[][] subSumMtx1 = Data.sumSubMtx(Data.MX, Data.MM, Data.H * 3, Data.N);
                    int[][] part2 = Data.mulMtxAndScalars(subSumMtx1, z_4, p_4);
                    int[][] subMulMtx = Data.mulSubMtx(Data.MC, Data.MD, Data.H * 3, Data.N);
                    int[][] part1 = Data.mulMtxAndScalars(subMulMtx, d_4, 1);
                    int[][] MA_1 = Data.sumMtx(part1, part2);
                    //Lab1.savePartMtx(Data.H, MA_1);
                    Data.saveToSubMatrix(MA_1, Data.MA, Data.H * 3, Data.N);

                    Data.SemEnd_T4.release(1);

                    System.out.println("4: T4 stopped");

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