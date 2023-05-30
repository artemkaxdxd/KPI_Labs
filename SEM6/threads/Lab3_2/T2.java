public class T2 extends Thread {
    Data Mon;

    int d2;
    int p2;
    int a2;
    int[][] MR2 = new int[Mon.N][Mon.N];

    int start = Mon.H;
    int end = Mon.H * 2;

    public T2(Data X) {
        Mon = X;
    }

    public void run() {
        System.out.println("T2 start");
        // input Z, d, p
        Mon.Z = Mon.insertVecWithNum(1);
        Mon.Write_d(1);
        Mon.Write_p(1);

        // Сигнал про введення даних
        Mon.signal_Input();
        // Чекати на введення даних в інших потоках
        Mon.wait_Input();

        // Обчислення 1
        int a2_1 = Mon.mulTwoSubVecs(Mon.B, Mon.Z, start, end);

        // Обчислення 2
        // КД1
        Mon.put_a(a2_1);

        // Сигнал про завершення обчислення а
        Mon.signal_Calc();
        // Чекати на завершення обчислення а в інших потоках
        Mon.wait_Calc();

        // КД2
        MR2 = Mon.Read_MR();
        // КД3
        d2 = Mon.Read_d();
        // КД4
        a2 = Mon.Read_a();
        // КД5
        p2 = Mon.Read_p();

        // Обчислення 3
        int[][] part1 = Mon.mulMtxAndScalars(Mon.mulSubMtx(MR2, Mon.MC, start, end), d2, 1);
        int[][] part2 = Mon.mulMtxAndScalars(Mon.mulSubMtx(Mon.MZ, Mon.MM, start, end), a2, p2);
        int[][] MAh = Mon.sumMtx(part1, part2);
        Mon.Write_MA(MAh, start, end);

        System.out.println("T2 end");
        // Сигнал про завершення обчислення MA
        Mon.signal_Out();
    }
}
