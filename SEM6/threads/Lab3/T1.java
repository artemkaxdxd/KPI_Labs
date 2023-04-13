public class T1 extends Thread {
    Data Mon;

    int a1_1;
    int d1;
    int[] R1 = new int[Mon.N];
    int[] A1 = new int[Mon.N];

    int start = 0;
    int end = Mon.H;

    public T1(Data X) {
        Mon = X;
    }

    public void run() {
        System.out.println("T1 start");
        // input R, Z
        Mon.R = Mon.insertVecWithNum(1);
        Mon.Z = Mon.insertVecWithNum(1);

        // Сигнал про введення даних
        Mon.signal_Input();
        // Чекати на введення даних в інших потоках
        Mon.wait_Input();

        // КД1
        R1 = Mon.Read_R();

        // Обчислення 1
        int[] Ah = Data.mulVecAndSubMtx(R1, Mon.MC, start, end);
        Mon.insertPartVec(Ah, Mon.A, start, end);

        // Обчислення 2
        int a1 = Data.mulTwoSubVecs(Mon.B, Mon.Z, start, end);

        // Обчислення 3
        // КД2
        Mon.put_a(a1);

        // Сигнал про завершення обчислення а
        Mon.signal_Calc();
        // Чекати на завершення обчислення а в інших потоках
        Mon.wait_Calc();

        // КД3
        d1 = Mon.Read_d();
        // КД4
        A1 = Mon.Read_A();
        // КД5
        a1_1 = Mon.Read_a();

        // Обчислення 4
        int[] Xh = Mon.sumTwoVecs(
                Mon.mulVecAndSubMtx(A1, Mon.MD, start, end),
                Mon.mulSubVecAndScalars(Mon.E, a1_1, d1, start, end)
        );
        Mon.insertPartVec(Xh, Mon.X, start, end);

        // Сигнал про завершення обчислення Х
        Mon.signal_Out();
        System.out.println("T1 end");
    }
}
