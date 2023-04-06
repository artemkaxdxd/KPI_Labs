import java.util.concurrent.Semaphore;
import java.util.concurrent.atomic.AtomicInteger;

//МА= MD*MC *d + max(Z)*(MX+MM)*p
//T1 = d, MA, MM
//T2 = MX, MC
//T4 = Z, MD, p
public class Data {
    public static int N = 4;
    public static int P = 4;
    public static int H = N/P;
    public static int[] Z = new int[N];
    public static AtomicInteger z = new AtomicInteger(0);
    public static AtomicInteger d = new AtomicInteger();
    public static AtomicInteger p = new AtomicInteger();

    public static int[][] MD = new int[N][N];
    public static int[][] MC = new int[N][N];
    public static int[][] MX = new int[N][N];
    public static int[][] MM = new int[N][N];
    public static int[][] MA = new int[N][N];
    public static int[][] subMtx1 = new int[N][N];
    public static int[][] subMtx2 = new int[N][N];

    // Введення даних в Т1 Т2 та Т4
    public static final Semaphore SemInput_T1 = new Semaphore(0);
    public static final Semaphore SemInput_T2 = new Semaphore(0);
    public static final Semaphore SemInput_T4 = new Semaphore(0);

    // Обчислення z в Т1 Т2 Т3 Т4
    public static final Semaphore SemEndZ_T1 = new Semaphore(0);
    public static final Semaphore SemEndZ_T2 = new Semaphore(0);
    public static final Semaphore SemEndZ_T3 = new Semaphore(0);
    public static final Semaphore SemEndZ_T4 = new Semaphore(0);

    // Обчислення МА в Т2 Т3 Т4
    public static final Semaphore SemEnd_T2 = new Semaphore(0);
    public static final Semaphore SemEnd_T3 = new Semaphore(0);
    public static final Semaphore SemEnd_T4 = new Semaphore(0);

    public static int maxSubArr(int[] Z, int start, int end) {
        int max = Z[start];

        for (int i = start; i < end; i++) {
            if (Z[i] < max) {
                max = Z[i];
            }
        }

        return max;
    }

    private static boolean firstMax = true;

    public static int setMax(AtomicInteger z, int z_i) {
        if (firstMax) {
            firstMax = false;
            return z_i;
        }

        return Math.max(z.get(), z_i);
    }

//    public static int[][] sumMtx(int[][] Mtx1, int[][] Mtx2) {
//        int[][] Mtx3 = new int[Mtx1.length][Mtx2[0].length];
//
//        for (int i = 0; i < Mtx3.length; i++) {
//            for (int j = 0; j < Mtx3[i].length; j++) {
//                Mtx3[i][j] = Mtx1[i][j] + Mtx2[i][j];
//            }
//        }
//
//        return Mtx3;
//    }

    public static int[][] sumMtx (int[][] Mtx1, int[][] Mtx2) {
        int[][] res = new int[Mtx1.length][Mtx1[0].length];
        for (int i = 0; i < Mtx1.length; i++) {
            for (int j = 0; j < Mtx1[0].length; j++) {
                res[i][j] = Mtx1[i][j] + Mtx2[i][j];
            }
        }
        return res;
    }

    public static int[][] sumSubMtx(int[][] Mtx1, int[][] Mtx2, int start, int end) {
        int[][] tempMtx = new int[N][end - start];

        for (int i = 0; i < tempMtx.length; i++) {
            for (int j = 0; j < tempMtx[i].length; j++) {
                tempMtx[i][j] = Mtx1[i][j] + Mtx2[i][j];
            }
        }

        return tempMtx;
    }

    public static int[][] mulMtx(int[][] Mtx1, int[][] Mtx2) {
        int m  = Mtx1.length;
        int n = Mtx2[0].length;
        int o = Mtx2.length;

        int[][] tempMtx = new int[m][n];

        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                for (int k = 0; k < o; k++) {
                    tempMtx[i][j] += Mtx1[i][k] * Mtx2[k][j];
                }
            }
        }

        return tempMtx;
    }

    public static int[][] mulSubMtx(int[][] Mtx1, int[][] Mtx2, int start, int end) {
        int[][] tempMtx = new int[N][end - start];

        for (int i = 0; i < N; i++) {
            int x = 0;
            for (int j = start; j < end; j++) {
                tempMtx[i][x] = 0;
                for (int k = 0; k < N; k++) {
                    tempMtx[i][x] += Mtx1[i][k] * Mtx2[k][j];
                }
                x++;
            }
        }

        return tempMtx;
    }

    public static int[][] mulMtxAndScalars(int[][] Mtx, int scalar1, int scalar2) {
        int[][] tempMtx = new int[Mtx.length][Mtx[0].length];

        for (int i = 0; i < tempMtx.length; i++) {
            for (int j = 0; j < tempMtx[i].length; j++) {
                tempMtx[i][j] = Mtx[i][j] * scalar1 * scalar2;
            }
        }

        return tempMtx;
    }

    public static int[][] mulSubMtxAndScalar(int[][] Mtx, int a, int start, int end) {
        int[][] tempMtx = new int[N][end-start];

        for (int i = 0; i < N; i++) {
            int k = 0;
            for (int j = start; j < end; j++) {
                tempMtx[i][k] = Mtx[i][j] * a;
                k++;
            }
        }

        return tempMtx;
    }

    public static void saveToSubMatrix(int[][] fromMtx, int[][] toMtx, int start, int end) {
        for (int i = 0; i < fromMtx.length; i++) {
            int k = 0;
            for (int j = start; j < end; j++) {
                toMtx[i][j] = fromMtx[i][k];
                k++;
            }
        }
    }

    public static int[][] insertMtxWithNum (int num) {
        int tempMtx[][] = new int[N][N];
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < N; ++j)
                tempMtx[i][j] = num;
        return tempMtx;
    }

    public static int[] insertVecWithNum (int num) {
        int tempVec[] = new int[N];
        for (int i = 0; i < N; ++i)
            tempVec[i] = num;
        return tempVec;
    }

    public static void printMatrix(int[][] Mtx) {
        for (int i = 0; i < Mtx.length; i++) {
            for (int j = 0; j < Mtx[i].length; j++) {
                System.out.printf("%-3d", Mtx[i][j]);
            }
            System.out.println();
        }
    }

}
