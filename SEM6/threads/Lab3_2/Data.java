// Монітор
public class Data {
    public static int N = 1600;
    private final static int P = 4;
    public static int H = N / P;

    private int a = 0; // --СР
    private int d = 0; // --СР
    private int p = 0; // --СР
    private int[][] MR = new int[N][N]; // --СР

    int[] B = new int[N];
    int[] Z = new int[N];

    int[][] MA = new int[N][N];
    int[][] MC = new int[N][N];
    int[][] MZ = new int[N][N];
    int[][] MM = new int[N][N];

    // Прапори синхронізації
    private int Flag1 = 0;
    private int Flag2 = 0;
    private int Flag3 = 0;

    // Взаємодія з СР
    public synchronized int[][] Read_MR() {
        return MR;
    }

    public synchronized int Read_a() {
        return a;
    }

    public synchronized int Read_d() {
        return d;
    }

    public synchronized int Read_p() {
        return p;
    }

    public synchronized void Write_d(int input) {
        d = input;
    }

    public synchronized void Write_p(int input) {
        p = input;
    }

    public synchronized void Write_MR(int input) {
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < N; ++j)
                MR[i][j] = input;
    }

    public synchronized void put_a(int input) {
        a = a + input;
    }

    public synchronized void Write_MA(int[][] From, int start, int end) {
        for (int i = 0; i < From.length; i++) {
            int k = 0;
            for (int j = start; j < end; j++) {
                MA[i][j] = From[i][k];
                k++;
            }
        }
    }

    // Секція синхронізації
    public synchronized void wait_Input() {
        try {
            if (Flag1 < 4)
                wait();
        } catch (Exception e) {
        }
    }

    public synchronized void signal_Input() {
        Flag1 += 1;
        if (Flag1 == 4) {
            notifyAll();
        }
    }

    public synchronized void wait_Calc() {
        try {
            if (Flag2 < 4)
                wait();
        } catch (Exception e) {
        }
    }

    public synchronized void signal_Calc() {
        Flag2 += 1;
        if (Flag2 == 4) {
            notifyAll();
        }
    }

    public synchronized void wait_Out() {
        try {
            if (Flag3 < 3)
                wait();
        } catch (Exception e) {
        }
    }

    public synchronized void signal_Out() {
        Flag3 += 1;
        if (Flag3 == 3) {
            notify();
        }
    }

    // Секція обчислень
    public static int mulTwoSubVecs(int[] A, int[] B, int start, int end) {
        int res = 0;
        for (int i = start; i < end; ++i) {
            res += A[i] * B[i];
        }
        return res;
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

    public static int[][] sumMtx(int[][] Mtx1, int[][] Mtx2) {
        int[][] res = new int[Mtx1.length][Mtx1[0].length];
        for (int i = 0; i < Mtx1.length; i++) {
            for (int j = 0; j < Mtx1[0].length; j++) {
                res[i][j] = Mtx1[i][j] + Mtx2[i][j];
            }
        }
        return res;
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

    public synchronized void print_MA() {
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                System.out.print(MA[i][j] + " ");
            }
            System.out.print("\n");
        }
    }

    // Допоміжні функції
    public static int[][] insertMtxWithNum(int num) {
        int tempMtx[][] = new int[N][N];
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < N; ++j)
                tempMtx[i][j] = num;
        return tempMtx;
    }

    public static int[] insertVecWithNum(int num) {
        int tempVec[] = new int[N];
        for (int i = 0; i < N; ++i)
            tempVec[i] = num;
        return tempVec;
    }
}
