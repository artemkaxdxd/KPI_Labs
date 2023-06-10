// Монітор
public class Data {
    public static int N = 2400;
    private final static int P = 4;
    public static int H = N / P;

    private int a = 0; // --СР
    private int d = 0; // --СР
    private int e = 0; // --СР

    private int[] Z = new int[N]; // --СР
    private int[] X = new int[N]; // --СР

    private int[][] MM = new int[N][N]; // --СР

    int[] A = new int[N];
    int[] B = new int[N];

    int[] Xh_T2 = new int[N];
    int[] Xh_T3 = new int[N];
    int[] X2h = new int[N];

    int[][] MX = new int[N][N];

    // Прапори синхронізації
    private int Flag1 = 0;
    private int Flag2 = 0;
    private int Flag3 = 0;
    private int Flag4 = 0;
    private int Flag5 = 0;
    private int Flag6 = 0;
    private int Flag7 = 0;

    // Взаємодія з СР
    public synchronized int[][] Read_MM() {
        return MM;
    }

    public synchronized int[] Read_Z() {
        return Z;
    }

    public synchronized int[] Read_X() {
        return X;
    }

    public synchronized int Read_a() {
        return a;
    }

    public synchronized int Read_d() {
        return d;
    }

    public synchronized int Read_e() {
        return e;
    }

    public synchronized void Write_d(int input) {
        d = input;
    }

    public synchronized void Write_e(int input) {
        e = input;
    }

    public synchronized void Write_MM(int input) {
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < N; ++j)
                MM[i][j] = input;
    }

    public synchronized void max_a(int ai) {
        a = Math.max(a, ai);
    }

    public synchronized void Write_Z(int input) {
        for (int i = 0; i < N; ++i)
            Z[i] = input;
    }

    public synchronized void Write_A(int[] From, int start, int end) {
        int j = 0;
        for (int i = start; i < end; ++i) {
            A[i] = From[j];
            j++;
        }
    }

    public synchronized void Write_X(int[] From) {
        int j = 0;
        for (int i = 0; i < N; ++i) {
            X[i] = From[j];
            j++;
        }
    }

    // Секція синхронізації
    public synchronized void wait_Input() {
        try {
            if (Flag1 < 3)
                wait();
        } catch (Exception e) {
        }
    }

    public synchronized void signal_Input() {
        Flag1 += 1;
        if (Flag1 == 3) {
            notifyAll();
        }
    }

    public synchronized void wait_Calc_a() {
        try {
            if (Flag2 < 4)
                wait();
        } catch (Exception e) {
        }
    }

    public synchronized void signal_Calc_a() {
        Flag2 += 1;
        if (Flag2 == 4) {
            notifyAll();
        }
    }

    public synchronized void wait_Xh_T3() {
        try {
            if (Flag3 < 1)
                wait();
        } catch (Exception e) {
        }
    }

    public synchronized void signal_Xh_T3() {
        Flag3 += 1;
        if (Flag3 == 1) {
            notifyAll();
        }
    }

    public synchronized void wait_Xh_T2() {
        try {
            if (Flag4 < 1)
                wait();
        } catch (Exception e) {
        }
    }

    public synchronized void signal_Xh_T2() {
        Flag4 += 1;
        if (Flag4 == 1) {
            notifyAll();
        }
    }

    public synchronized void wait_X2h_T1() {
        try {
            if (Flag5 < 1)
                wait();
        } catch (Exception e) {
        }
    }

    public synchronized void signal_X2h_T1() {
        Flag5 += 1;
        if (Flag5 == 1) {
            notifyAll();
        }
    }

    public synchronized void wait_X_T4() {
        try {
            if (Flag6 < 1)
                wait();
        } catch (Exception e) {
        }
    }

    public synchronized void signal_X_T4() {
        Flag6 += 1;
        if (Flag6 == 1) {
            notifyAll();
        }
    }

    public synchronized void wait_Out() {
        try {
            if (Flag7 < 3)
                wait();
        } catch (Exception e) {
        }
    }

    public synchronized void signal_Out() {
        Flag7 += 1;
        if (Flag7 == 3) {
            notify();
        }
    }

    // Секція обчислень
    public static void multiplyVectorOnNumber(int[] vector, int number) {
        for (int i = 0; i < vector.length; i++) {
            vector[i] = vector[i] * number;
        }
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

    public int[] multiplyMatrixOnVector(int[] Vec, int[][] Mtx) {
        int[] res = new int[Vec.length];
        for (int i = 0; i < Mtx.length; i++) {
            for (int j = 0; j < Mtx[0].length; j++) {
                res[i] += Vec[i] * Mtx[i][j];
            }
        }
        return res;
    }

    public int[] sumVector(int[] firstVector, int[] secondVector) {
        int[] res = new int[firstVector.length];
        for (int i = 0; i < firstVector.length; i++) {
            res[i] = firstVector[i] + secondVector[i];
        }
        return res;
    }

    public int[] merge(int[] a, int[] b) {
        int[] result = new int[a.length + b.length];
        int aIndex = 0;
        int bIndex = 0;
        int i = 0;

        while (i < result.length) {
            result[i] = a[aIndex] < b[bIndex] ? a[aIndex++] : b[bIndex++];
            if (aIndex == a.length) {
                System.arraycopy(b, bIndex, result, ++i, b.length - bIndex);
                break;
            }
            if (bIndex == b.length) {
                System.arraycopy(a, aIndex, result, ++i, a.length - aIndex);
                break;
            }
            i++;
        }
        return result;
    }

    // Допоміжні функції
    public synchronized void print_A() {
        for (int i = 0; i < N; ++i) {
            System.out.print(A[i] + " ");
        }
    }

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
