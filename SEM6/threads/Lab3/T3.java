public class T3 extends Thread {
    Data Mon;

    int a3_1;
    int d3;
    int[] R3 = new int[Mon.N];
    int[] A3 = new int[Mon.N];

    int start = Mon.H * 2;
    int end = Mon.H * 3;

    public T3(Data X) {
        Mon = X;
    }

    public void run() {
        System.out.println("T3 start");
        // input B, d
        Mon.B = Mon.insertVecWithNum(1);
        Mon.Write_d(1);

        // Сигнал про введення даних
        Mon.signal_Input();
        // Чекати на введення даних в інших потоках
        Mon.wait_Input();

        // КД1
        R3 = Mon.Read_R();

        // Обчислення 1
        int[] Ah = Mon.mulVecAndSubMtx(R3, Mon.MC, start, end);
        Mon.Write_A(Ah, start, end);

        // Обчислення 2
        int a3 = Mon.mulTwoSubVecs(Mon.B, Mon.Z, start, end);

        // Обчислення 3
        // КД2
        Mon.put_a(a3);

        // Сигнал про завершення обчислення а
        Mon.signal_Calc();
        // Чекати на завершення обчислення а в інших потоках
        Mon.wait_Calc();

        // КД3
        d3 = Mon.Read_d();
        // КД4
        A3 = Mon.Read_A();
        // КД5
        a3_1 = Mon.Read_a();

        // Обчислення 4
        int[] Xh = Mon.sumTwoVecs(
                Mon.mulVecAndSubMtx(A3, Mon.MD, start, end),
                Mon.mulSubVecAndScalars(Mon.E, a3_1, d3, start, end)
        );
        Mon.Write_X(Xh, start, end);

        // Чекати на завершення обчислення Х в інших потоках
        Mon.wait_Out();

        // Вивід результату
        Mon.print_X();
        System.out.println("\nT3 end");

        long finishTime = System.currentTimeMillis() - Lab3.curTime;
        System.out.println("N = "+ Mon.N);
        System.out.println("Time of execution: " + finishTime);
    }
}
