import java.util.Arrays;

public class T4 extends Thread {
    Data Mon;

    int a4;
    int d4;
    int e4;
    int[] Z4 = new int[Mon.N];
    int[] X4 = new int[Mon.N];
    int[][] MM4 = new int[Mon.N][Mon.N];

    int start = Mon.H * 3;
    int end = Mon.N;

    public T4(Data X) {
        Mon = X;
    }

    public void run() {
        System.out.println("T4 start");
        // input Z
        Mon.Write_Z(1);

        // Сигнал про введення даних
        Mon.signal_Input();
        // Чекати на введення даних в інших потоках
        Mon.wait_Input();

        // Обчислення 1
        int[] Bh = Arrays.copyOfRange(Mon.B, start, end);
        int a4_1 = Arrays.stream(Bh).max().getAsInt();

        // Обчислення 2
        // КД1
        Mon.max_a(a4_1);

        // Сигнал про завершення обчислення а
        Mon.signal_Calc_a();
        // Чекати на завершення обчислення а в інших потоках
        Mon.wait_Calc_a();

        // КД2
        d4 = Mon.Read_d();
        // КД3
        Z4 = Mon.Read_Z();
        // КД4
        MM4 = Mon.Read_MM();
        // КД5
        e4 = Mon.Read_e();

        // Обчислення 3
        Mon.multiplyVectorOnNumber(Bh, d4);
        int[][] part1 = Mon.mulSubMtx(MM4, Mon.MX, start, end);
        int[] part2 = Mon.multiplyMatrixOnVector(Z4, part1);
        int[] Xh_T4 = Mon.sumVector(Bh, part2);

        Arrays.sort(Xh_T4);
        Mon.multiplyVectorOnNumber(Xh_T4, e4);

        Mon.wait_Xh_T3();

        // Обчислення 4
        int[] X2h_4 = Mon.merge(Xh_T4, Mon.Xh_T3);

        Mon.wait_X2h_T1();

        // Обчислення 4
        int[] X = Mon.merge(X2h_4, Mon.X2h);
        Mon.Write_X(X);
        Mon.signal_X_T4();

        // КД6
        X4 = Mon.Read_X();
        // КД7
        a4 = Mon.Read_a();

        // Обчислення 6
        int[] Zh = Mon.Read_Z();
        Mon.multiplyVectorOnNumber(Zh, a4);
        int[] Ah = Mon.sumVector(X4, Zh);
        Mon.Write_A(Ah, start, end);

        // Чекати на завершення обчислення MA в інших потоках
        Mon.wait_Out();

        // Вивід результату
        if (Mon.N == 4) {
            Mon.print_A();
        }
        System.out.println("\nT4 end");

        long finishTime = System.currentTimeMillis() - Lab3.curTime;
        System.out.println("N = " + Mon.N);
        System.out.println("Time of execution: " + finishTime);
    }
}
