import java.util.Arrays;

public class T3 extends Thread {
    private int z3_1; // max(Zh)
    private int z_3; // z
    private int d_3; // d
    private int p_3; // p
    //МА= MD*MCh *d + max(Z)*(MXh+MMh)*p

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
            System.out.println("3: Старт T3");
            System.out.println("3: T3 чекає на дозвіл T1 T2 T4 про введення даних");
            Data.SemInput_T1.acquire();
            Data.SemInput_T2.acquire();
            Data.SemInput_T4.acquire();
            System.out.println("3: T3 отримує дозвіл T1 Т2 T4");

            z3_1 = Data.maxSubArr(Data.Z, Data.H * 2, Data.H * 3);
            Data.z.set(Data.setMax(Data.z, z3_1));

            Data.SemEndZ_T3.release(3);

            try {
                System.out.println("3: T3 чекає на EndZ_T[1, 2, 4]");
                Data.SemEndZ_T1.acquire();
                Data.SemEndZ_T3.acquire();
                Data.SemEndZ_T4.acquire();
                System.out.println("3: T3 отримало на EndZ_T[1, 2, 4]");

                z_3 = Data.z.get();
                d_3 = Data.d.get();
                p_3 = Data.p.get();

                int[][] subSumMtx1 = Data.sumSubMtx(Data.MX, Data.MM, Data.H * 2, Data.H * 3);
                int[][] part2 = Data.mulMtxAndScalars(subSumMtx1, z_3, p_3);
                int[][] subMulMtx = Data.mulSubMtx(Data.MC, Data.MD, Data.H * 2, Data.H * 3);
                int[][] part1 = Data.mulMtxAndScalars(subMulMtx, d_3, 1);
                int[][] MA_1 = Data.sumMtx(part1, part2);
                //Lab1.savePartMtx(Data.H * 2, MA_1);
                Data.saveToSubMatrix(MA_1, Data.MA, Data.H * 2, Data.H * 3);

                Data.SemEnd_T3.release(1);

                System.out.println("3: T3 stopped");

            } catch (Exception e) {
                throw new RuntimeException(e);
            }


        } catch (InterruptedException e) {
            throw new RuntimeException(e);
        }
    }

}
