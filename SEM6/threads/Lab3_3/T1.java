import java.util.Arrays;

public class T1 extends Thread {
    Data Mon;

    int a1;
    int d1;
    int e1;
    int[] Z1 = new int[Mon.N];
    int[] X1 = new int[Mon.N];
    int[][] MM1 = new int[Mon.N][Mon.N];

    int start = 0;
    int end = Mon.H;

    public T1(Data X) {
        Mon = X;
    }

    public void run() {
        System.out.println("T1 start");
        // input d, MM
        Mon.Write_d(1);
        Mon.Write_MM(1);

        // Сигнал про введення даних
        Mon.signal_Input();
        // Чекати на введення даних в інших потоках
        Mon.wait_Input();

        // Обчислення 1
        int[] Bh = Arrays.copyOfRange(Mon.B, start, end);
        int a1_1 = Arrays.stream(Bh).max().getAsInt();

        // Обчислення 2
        // КД1
        Mon.max_a(a1_1);

        // Сигнал про завершення обчислення а
        Mon.signal_Calc_a();
        // Чекати на завершення обчислення а в інших потоках
        Mon.wait_Calc_a();

        // КД2
        d1 = Mon.Read_d();
        // КД3
        Z1 = Mon.Read_Z();
        // КД4
        MM1 = Mon.Read_MM();
        // КД5
        e1 = Mon.Read_e();

        // Обчислення 3
        Mon.multiplyVectorOnNumber(Bh, d1);
        int[][] part1 = Mon.mulSubMtx(MM1, Mon.MX, start, end);
        int[] part2 = Mon.multiplyMatrixOnVector(Z1, part1);
        int[] Xh_T1 = Mon.sumVector(Bh, part2);
        Arrays.sort(Xh_T1);
        Mon.multiplyVectorOnNumber(Xh_T1, e1);

        Mon.wait_Xh_T2();

        // Обчислення 4
        Mon.X2h = Mon.merge(Xh_T1, Mon.Xh_T2);

        Mon.signal_X2h_T1();
        Mon.wait_X_T4();

        // КД6
        X1 = Mon.Read_X();
        // КД7
        a1 = Mon.Read_a();

        // Обчислення 6
        int[] Zh = Mon.Read_Z();
        Mon.multiplyVectorOnNumber(Zh, a1);
        int[] Ah = Mon.sumVector(X1, Zh);

        Mon.Write_A(Ah, start, end);

        System.out.println("T1 end");
        // Сигнал про завершення обчислення A
        Mon.signal_Out();
    }
}
