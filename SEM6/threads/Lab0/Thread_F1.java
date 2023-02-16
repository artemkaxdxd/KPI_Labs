import java.util.Scanner;

public class Thread_F1 extends Thread {
    int e;
    int A[] = new int[Data.N];
    int B[] = new int[Data.N];
    int C[] = new int[Data.N];
    int MA[][]=new int[Data.N][Data.N];
    int MC[][]=new int[Data.N][Data.N];

    public void run() {
        System.out.println("\nT1 is started. Function: C = A – B*(MA*MС)*е");

        if (Data.N > 1000) {
            if (Data.version == 1) {
                e = 1;
                A = Data.insertVecWithNum(1);
                B = Data.insertVecWithNum(1);
                MA = Data.insertMtxWithNum(1);
                MC = Data.insertMtxWithNum(1);
            }
            if (Data.version == 2) {
                e = (int) (Math.random()*10);
                A = Data.generateRandVec();
                B = Data.generateRandVec();
                MA = Data.generateRandMtx();
                MC = Data.generateRandMtx();
            }
            if (Data.version == 3) {
                e = (int) (Math.random()*10);

                Data.writeVecToFile("data1.txt", "A");
                Data.writeVecToFile("data1.txt", "B");
                Data.writeMtxToFile("data1.txt", "MA");
                Data.writeMtxToFile("data1.txt", "MC");
                A = Data.readVecFromFile("data1.txt", "A");
                B = Data.readVecFromFile("data1.txt", "B");
                MA = Data.readMtxFromFile("data1.txt", "MA");
                MC = Data.readMtxFromFile("data1.txt", "MC");
            }
        } else {
            //  введення даних
            Scanner console = new Scanner(System.in);

            System.out.print("(F1) Enter e: ");
            e = console.nextInt();

            System.out.printf("(F1) Enter vector A (%d integers): ", Data.N);
            for (int i = 0; i < Data.N; i++) {
                A[i] = console.nextInt();
            }

            System.out.printf("(F1) Enter vector B (%d integers): ", Data.N);
            for (int i = 0; i < Data.N; i++) {
                B[i] = console.nextInt();
            }

            System.out.printf("(F1) Enter matrix MA (%d by %d): ", Data.N, Data.N);
            for (int i = 0; i < Data.N; i++) {
                System.out.printf("\nEnter %d integers for row %d: ", Data.N, i);
                for (int j = 0; j < Data.N; j++) {
                    MA[i][j] = console.nextInt();
                }
            }

            System.out.printf("(F1) Enter matrix MC (%d by %d): ", Data.N, Data.N);
            for (int i = 0; i < Data.N; i++) {
                System.out.printf("\nEnter %d integers for row %d: ", Data.N, i);
                for (int j = 0; j < Data.N; j++) {
                    MC[i][j] = console.nextInt();
                }
            }
        }


        C = Data.F1(A, B, MA, MC, e);

        //  виведення результатів
        System.out.printf("\nT1 is finished. Vector:\n");
        for (int i = 0; i < Data.N; ++i)
            System.out.printf("%d  ", C[i]);
    }
}
