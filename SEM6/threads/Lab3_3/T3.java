import java.util.Arrays;

public class T3 extends Thread {
    Data Mon;

    int a3;
    int d3;
    int e3;
    int[] Z3 = new int[Mon.N];
    int[] X3 = new int[Mon.N];
    int[][] MM3 = new int[Mon.N][Mon.N];

    int start = Mon.H * 2;
    int end = Mon.H * 3;

    public T3(Data X) {
        Mon = X;
    }

    public void run() {
        System.out.println("T3 start");

        // Чекати на введення даних в інших потоках
        Mon.wait_Input();

        // Обчислення 1
        int[] Bh = Arrays.copyOfRange(Mon.B, start, end);
        int a3_1 = Arrays.stream(Bh).max().getAsInt();

        // Обчислення 2
        // КД1
        Mon.max_a(a3_1);

        // Сигнал про завершення обчислення а
        Mon.signal_Calc_a();
        // Чекати на завершення обчислення а в інших потоках
        Mon.wait_Calc_a();

        // КД2
        d3 = Mon.Read_d();
        // КД3
        Z3 = Mon.Read_Z();
        // КД4
        MM3 = Mon.Read_MM();
        // КД5
        e3 = Mon.Read_e();

        // Обчислення 3
        Mon.multiplyVectorOnNumber(Bh, d3);
        int[][] part1 = Mon.mulSubMtx(MM3, Mon.MX, start, end);
        int[] part2 = Mon.multiplyMatrixOnVector(Z3, part1);
        Mon.Xh_T3 = Mon.sumVector(Bh, part2);
        Arrays.sort(Mon.Xh_T3);
        Mon.multiplyVectorOnNumber(Mon.Xh_T3, e3);

        Mon.signal_Xh_T3();
        Mon.wait_X_T4();

        // КД6
        X3 = Mon.Read_X();
        // КД7
        a3 = Mon.Read_a();

        // Обчислення 6
        int[] Zh = Mon.Read_Z();
        Mon.multiplyVectorOnNumber(Zh, a3);
        int[] Ah = Mon.sumVector(X3, Zh);

        Mon.Write_A(Ah, start, end);

        System.out.println("T3 end");
        // Сигнал про завершення обчислення MA
        Mon.signal_Out();
    }
}
