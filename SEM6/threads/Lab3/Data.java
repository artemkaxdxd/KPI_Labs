// Монітор
public class Data {
    public static int N = 4;
    private final static int P = 4;
    public static int H = N/P;

    private int a = 0; // --СР
    private int d = 0; // --СР
    private int[] A = new int[N]; // --СР
    private int[] R = new int[N]; // --СР
    int[] B = new int[N];
    int[] Z = new int[N];
    int[] E = new int[N];
    int[] X = new int[N];
    int[][] MC = new int[N][N];
    int[][] MD = new int[N][N];

    // Прапори синхронізації
    private int Flag1 = 0;
    private int Flag2 = 0;
    private int Flag3 = 0;

    // Взаємодія з СР
    public synchronized int[] Read_A() {
        return A;
    }

    public synchronized int[] Read_R() {
        return R;
    }

    public synchronized int Read_a() {
        return a;
    }

    public synchronized int Read_d() {
        return d;
    }

    public synchronized void Write_d(int input) { d = input; }
    public synchronized void Write_R(int input) {
        for (int i = 0; i < N; ++i)
            R[i] = input;
    }
    public synchronized void put_a(int input) {
        a = a + input;
    }
    public synchronized void Write_A(int[] From, int start, int end) {
        int j = 0;
        for (int i = start; i < end; ++i) {
            A[i] = From[j];
            j++;
        }
    }

    // Секція синхронізації
    public synchronized void wait_Input() {
        try{
            if (Flag1 < 4) wait();
        } catch(Exception e) {}
    }

    public synchronized void signal_Input() {
        Flag1 += 1;
        if (Flag1 == 4) {
            notifyAll();
        }
    }

    public synchronized void wait_Calc() {
        try{
            if (Flag2 < 4) wait();
        } catch(Exception e) {}
    }

    public synchronized void signal_Calc() {
        Flag2 += 1;
        if (Flag2 == 4) {
            notifyAll();
        }
    }

    public synchronized void wait_Out() {
        try{
            if (Flag3 < 3) wait();
        } catch(Exception e) {}
    }

    public synchronized void signal_Out() {
        Flag3 += 1;
        if (Flag3 == 3) {
            notify();
        }
    }

    // Секція обчислень
    public static int[] mulVecAndSubMtx(int[] Vec, int[][] Mtx, int start, int end) {
        int resVec[] = new int[N];
        int k = -1;
        for (int i = start; i < N; ++i) {
            k++;
            for (int j = 0; j < end; ++j) {
                resVec[k] += Mtx[i][j] * Vec[k];
            }
        }
        return resVec;
    }

    public static int mulTwoSubVecs(int[] A, int[] B, int start, int end) {
        int res = 0;
        for (int i = start; i < end; ++i) {
            res += A[i] * B[i];
        }
        return res;
    }

    public static int[] mulSubVecAndScalars(int[] E, int a, int d, int start, int end) {
        int resVec[] = new int[N];
        for (int i = start; i < end; ++i) {
            resVec[i] = a * d * E[i];
        }
        return resVec;
    }

    public static int[] sumTwoVecs(int[] A, int[] B) {
        int resVec[] = new int[N];
        for (int i = 0; i < A.length; ++i) {
            resVec[i] = A[i] + B[i];
        }
        return resVec;
    }

    public synchronized void Write_X(int[] From, int start, int end) {
        int j = 0;
        for (int i = start; i < end; ++i) {
            X[i] = From[j];
            j++;
        }
    }

    public synchronized void print_X() {
        for (int i = 0; i < N; ++i) {
            System.out.print(X[i] + " ");
        }
    }

    // Допоміжні функції
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
}
