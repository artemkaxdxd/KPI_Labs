import java.util.Arrays;

public class T2 extends Thread {
    Data Mon;

    int a2;
    int d2;
    int e2;
    int[] Z2 = new int[Mon.N];
    int[] X2 = new int[Mon.N];
    int[][] MM2 = new int[Mon.N][Mon.N];

    int start = Mon.H;
    int end = Mon.H * 2;

    public T2(Data X) {
        Mon = X;
    }

    public void run() {
        System.out.println("T2 start");
        // input e, B, MX
        Mon.Write_e(1);
        Mon.B = Mon.insertVecWithNum(1);
        Mon.MX = Mon.insertMtxWithNum(1);

        // Сигнал про введення даних
        Mon.signal_Input();
        // Чекати на введення даних в інших потоках
        Mon.wait_Input();

        // Обчислення 1
        int[] Bh = Arrays.copyOfRange(Mon.B, start, end);
        int a2_1 = Arrays.stream(Bh).max().getAsInt();

        // Обчислення 2
        // КД1
        Mon.max_a(a2_1);

        // Сигнал про завершення обчислення а
        Mon.signal_Calc_a();
        // Чекати на завершення обчислення а в інших потоках
        Mon.wait_Calc_a();

        // КД2
        d2 = Mon.Read_d();
        // КД3
        Z2 = Mon.Read_Z();
        // КД4
        MM2 = Mon.Read_MM();
        // КД5
        e2 = Mon.Read_e();

        // Обчислення 3
        Mon.multiplyVectorOnNumber(Bh, d2);
        int[][] part1 = Mon.mulSubMtx(MM2, Mon.MX, start, end);
        int[] part2 = Mon.multiplyMatrixOnVector(Z2, part1);
        Mon.Xh_T2 = Mon.sumVector(Bh, part2);
        Arrays.sort(Mon.Xh_T2);
        Mon.multiplyVectorOnNumber(Mon.Xh_T2, e2);

        Mon.signal_Xh_T2();
        Mon.wait_X_T4();

        // КД6
        X2 = Mon.Read_X();
        // КД7
        a2 = Mon.Read_a();

        // Обчислення 6
        int[] Zh = Mon.Read_Z();
        Mon.multiplyVectorOnNumber(Zh, a2);
        int[] Ah = Mon.sumVector(X2, Zh);

        Mon.Write_A(Ah, start, end);

        System.out.println("T2 end");
        // Сигнал про завершення обчислення MA
        Mon.signal_Out();
    }
}
