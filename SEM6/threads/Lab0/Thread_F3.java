import java.util.Scanner;

public class Thread_F3 extends Thread {
    int O[] = new int[Data.N];
    int P[] = new int[Data.N];
    int MR[][]=new int[Data.N][Data.N];
    int MT[][]=new int[Data.N][Data.N];
    public void run() {
        System.out.println("\nT3 is started. O = SORT(P)*(MR*MT)");
        //  введення даних

        if (Data.N > 1000) {
            if (Data.version == 1) {
                P = Data.insertVecWithNum(1);
                MR = Data.insertMtxWithNum(1);
                MT = Data.insertMtxWithNum(1);
            }
            if (Data.version == 2) {
                P = Data.generateRandVec();
                MR = Data.generateRandMtx();
                MT = Data.generateRandMtx();
            }
            if (Data.version == 3) {
                Data.writeVecToFile("data3.txt", "P");
                Data.writeMtxToFile("data3.txt", "MR");
                Data.writeMtxToFile("data3.txt", "MT");

                P = Data.readVecFromFile("data3.txt", "P");
                MR = Data.readMtxFromFile("data3.txt", "MR");
                MT = Data.readMtxFromFile("data3.txt", "MT");
            }
        } else {
            Scanner console = new Scanner(System.in);

            System.out.printf("(F3) Enter vector P (%d integers): ", Data.N);
            for (int i = 0; i < Data.N; i++) {
                P[i] = console.nextInt();
            }
            System.out.print(P);

            System.out.printf("(F3) Enter matrix MR (%d by %d): ", Data.N, Data.N);
            for (int i = 0; i < Data.N; i++) {
                System.out.printf("\nEnter %d integers for row %d: ", Data.N, i);
                for (int j = 0; j < Data.N; j++) {
                    MR[i][j] = console.nextInt();
                }
            }

            System.out.printf("(F3) Enter matrix MT (%d by %d): ", Data.N, Data.N);
            for (int i = 0; i < Data.N; i++) {
                System.out.printf("\nEnter %d integers for row %d: ", Data.N, i);
                for (int j = 0; j < Data.N; j++) {
                    MT[i][j] = console.nextInt();
                }
            }
        }
        //  обчислення функції F3 = O = SORT(P)*(MR*MT)
        O = Data.F3(P, MR, MT);

        //  виведення результатів
        System.out.printf("\nT3 is finished. Vector:\n");
        for (int i = 0; i < Data.N; ++i)
            System.out.printf("%d  ", O[i]);
    }
}
