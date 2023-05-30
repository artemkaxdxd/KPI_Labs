public class T4 extends Thread {
    Data Mon;

    int d4;
    int p4;
    int a4;
    int[][] MR4 = new int[Mon.N][Mon.N];

    int start = Mon.H * 3;
    int end = Mon.N;

    public T4(Data X) {
        Mon = X;
    }

    public void run() {
        System.out.println("T4 start");
        // input MR, MZ
        Mon.Write_MR(1);
        Mon.MZ = Mon.insertMtxWithNum(1);

        // Сигнал про введення даних
        Mon.signal_Input();
        // Чекати на введення даних в інших потоках
        Mon.wait_Input();

        // Обчислення 1
        int a4_1 = Mon.mulTwoSubVecs(Mon.B, Mon.Z, start, end);

        // Обчислення 2
        // КД1
        Mon.put_a(a4_1);

        // Сигнал про завершення обчислення а
        Mon.signal_Calc();
        // Чекати на завершення обчислення а в інших потоках
        Mon.wait_Calc();

        // КД2
        MR4 = Mon.Read_MR();
        // КД3
        d4 = Mon.Read_d();
        // КД4
        a4 = Mon.Read_a();
        // КД5
        p4 = Mon.Read_p();

        // Обчислення 3
        int[][] part1 = Mon.mulMtxAndScalars(Mon.mulSubMtx(MR4, Mon.MC, start, end), d4, 1);
        int[][] part2 = Mon.mulMtxAndScalars(Mon.mulSubMtx(Mon.MZ, Mon.MM, start, end), a4, p4);
        int[][] MAh = Mon.sumMtx(part1, part2);
        Mon.Write_MA(MAh, start, end);

        System.out.println("T4 end");
        // Сигнал про завершення обчислення MA
        Mon.signal_Out();
    }
}
