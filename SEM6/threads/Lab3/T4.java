public class T4 extends Thread {
    Data Mon;

    int a4_1;
    int d4;
    int[] R4 = new int[Mon.N];
    int[] A4 = new int[Mon.N];

    int start = Mon.H * 3;
    int end = Mon.N;

    public T4(Data X) {
        Mon = X;
    }

    public void run() {
        System.out.println("T4 start");
        // input MC, E
        Mon.MC = Mon.insertMtxWithNum(1);
        Mon.E = Mon.insertVecWithNum(1);

        // Сигнал про введення даних
        Mon.signal_Input();
        // Чекати на введення даних в інших потоках
        Mon.wait_Input();

        // КД1
        R4 = Mon.Read_R();

        // Обчислення 1
        int[] Ah = Mon.mulVecAndSubMtx(R4, Mon.MC, start, end);
        Mon.Write_A(Ah, start, end);

        // Обчислення 2
        int a4 = Mon.mulTwoSubVecs(Mon.B, Mon.Z, start, end);

        // Обчислення 3
        // КД2
        Mon.put_a(a4);

        // Сигнал про завершення обчислення а
        Mon.signal_Calc();
        // Чекати на завершення обчислення а в інших потоках
        Mon.wait_Calc();

        // КД3
        d4 = Mon.Read_d();
        // КД4
        A4 = Mon.Read_A();
        // КД5
        a4_1 = Mon.Read_a();

        // Обчислення 4
        int[] Xh = Mon.sumTwoVecs(
                Mon.mulVecAndSubMtx(A4, Mon.MD, start, end),
                Mon.mulSubVecAndScalars(Mon.E, a4_1, d4, start, end)
        );
        Mon.Write_X(Xh, start, end);

        // Сигнал про завершення обчислення Х
        Mon.signal_Out();
        System.out.println("T4 end");
    }
}
