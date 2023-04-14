public class T2 extends Thread {
    Data Mon;

    int a2_1;
    int d2;
    int[] R2 = new int[Mon.N];
    int[] A2 = new int[Mon.N];

    int start = Mon.H;
    int end = Mon.H * 2;

    public T2(Data X) {
        Mon = X;
    }

    public void run() {
        System.out.println("T2 start");
        // input MD
        Mon.MD = Mon.insertMtxWithNum(1);

        // Сигнал про введення даних
        Mon.signal_Input();
        // Чекати на введення даних в інших потоках
        Mon.wait_Input();

        // КД1
        R2 = Mon.Read_R();

        // Обчислення 1
        int[] Ah = Mon.mulVecAndSubMtx(R2, Mon.MC, start, end);
        Mon.Write_A(Ah, start, end);

        // Обчислення 2
        int a2 = Mon.mulTwoSubVecs(Mon.B, Mon.Z, start, end);

        // Обчислення 3
        // КД2
        Mon.put_a(a2);

        // Сигнал про завершення обчислення а
        Mon.signal_Calc();
        // Чекати на завершення обчислення а в інших потоках
        Mon.wait_Calc();

        // КД3
        d2 = Mon.Read_d();
        // КД4
        A2 = Mon.Read_A();
        // КД5
        a2_1 = Mon.Read_a();

        // Обчислення 4
        int[] Xh = Mon.sumTwoVecs(
                Mon.mulVecAndSubMtx(A2, Mon.MD, start, end),
                Mon.mulSubVecAndScalars(Mon.E, a2_1, d2, start, end)
        );
        Mon.Write_X(Xh, start, end);

        // Сигнал про завершення обчислення Х
        Mon.signal_Out();
        System.out.println("T2 end");
    }
}
