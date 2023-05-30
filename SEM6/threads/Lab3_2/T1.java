public class T1 extends Thread {
    Data Mon;

    int d1;
    int p1;
    int a1;
    int[][] MR1 = new int[Mon.N][Mon.N];

    int start = 0;
    int end = Mon.H;

    public T1(Data X) {
        Mon = X;
    }

    public void run() {
        System.out.println("T1 start");
        // input MC, B
        Mon.MC = Mon.insertMtxWithNum(1);
        Mon.B = Mon.insertVecWithNum(1);

        // Сигнал про введення даних
        Mon.signal_Input();
        // Чекати на введення даних в інших потоках
        Mon.wait_Input();

        // Обчислення 1
        int a1_1 = Mon.mulTwoSubVecs(Mon.B, Mon.Z, start, end);

        // Обчислення 2
        // КД1
        Mon.put_a(a1_1);

        // Сигнал про завершення обчислення а
        Mon.signal_Calc();
        // Чекати на завершення обчислення а в інших потоках
        Mon.wait_Calc();

        // КД2
        MR1 = Mon.Read_MR();
        // КД3
        d1 = Mon.Read_d();
        // КД4
        a1 = Mon.Read_a();
        // КД5
        p1 = Mon.Read_p();

        // Обчислення 3
        int[][] part1 = Mon.mulMtxAndScalars(Mon.mulSubMtx(MR1, Mon.MC, start, end), d1, 1);
        int[][] part2 = Mon.mulMtxAndScalars(Mon.mulSubMtx(Mon.MZ, Mon.MM, start, end), a1, p1);
        int[][] MAh = Mon.sumMtx(part1, part2);

        Mon.Write_MA(MAh, start, end);

        System.out.println("T1 end");
        // Сигнал про завершення обчислення MA
        Mon.signal_Out();
    }
}
