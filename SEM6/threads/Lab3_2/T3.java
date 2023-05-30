public class T3 extends Thread {
    Data Mon;

    int d3;
    int p3;
    int a3;
    int[][] MR3 = new int[Mon.N][Mon.N];

    int start = Mon.H * 2;
    int end = Mon.H * 3;

    public T3(Data X) {
        Mon = X;
    }

    public void run() {
        System.out.println("T3 start");
        // input MR, MZ
        Mon.Write_MR(1);
        Mon.MZ = Mon.insertMtxWithNum(1);

        // Сигнал про введення даних
        Mon.signal_Input();
        // Чекати на введення даних в інших потоках
        Mon.wait_Input();

        // Обчислення 1
        int a3_1 = Mon.mulTwoSubVecs(Mon.B, Mon.Z, start, end);

        // Обчислення 2
        // КД1
        Mon.put_a(a3_1);

        // Сигнал про завершення обчислення а
        Mon.signal_Calc();
        // Чекати на завершення обчислення а в інших потоках
        Mon.wait_Calc();

        // КД2
        MR3 = Mon.Read_MR();
        // КД3
        d3 = Mon.Read_d();
        // КД4
        a3 = Mon.Read_a();
        // КД5
        p3 = Mon.Read_p();

        // Обчислення 3
        int[][] part1 = Mon.mulMtxAndScalars(Mon.mulSubMtx(MR3, Mon.MC, start, end), d3, 1);
        int[][] part2 = Mon.mulMtxAndScalars(Mon.mulSubMtx(Mon.MZ, Mon.MM, start, end), a3, p3);
        int[][] MAh = Mon.sumMtx(part1, part2);
        Mon.Write_MA(MAh, start, end);

        // Чекати на завершення обчислення MA в інших потоках
        Mon.wait_Out();

        // Вивід результату
        if (Mon.N == 4) {
            Mon.print_MA();
        }
        System.out.println("\nT3 end");

        long finishTime = System.currentTimeMillis() - Lab3.curTime;
        System.out.println("N = " + Mon.N);
        System.out.println("Time of execution: " + finishTime);
    }
}
