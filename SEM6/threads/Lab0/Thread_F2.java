import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.util.Scanner;

public class Thread_F2 extends Thread {
    int k;
    int MF[][]=new int[Data.N][Data.N];
    int MG[][]=new int[Data.N][Data.N];

    public void run() {
        System.out.println("\nT2 is started. F2 = MF = MF*MG*k");
        //  введення даних

        if (Data.N > 1000) {
            if (Data.version == 1) {
                k = 1;
                MF = Data.insertMtxWithNum(1);
                MG = Data.insertMtxWithNum(1);
            }
            if (Data.version == 2) {
                k = (int) (Math.random()*10);
                MF = Data.generateRandMtx();
                MG = Data.generateRandMtx();
            }
            if (Data.version == 3) {
                k = (int) (Math.random()*10);
                Data.writeMtxToFile("data2.txt", "MF");
                Data.writeMtxToFile("data2.txt", "MG");
                MF = Data.readMtxFromFile("data2.txt", "MF");
                MG = Data.readMtxFromFile("data2.txt", "MG");
            }
        } else {
            Scanner console = new Scanner(System.in);

            System.out.print("(F2) Enter k: ");
            k = console.nextInt();

            System.out.printf("(F2) Enter matrix MF (%d by %d): ", Data.N, Data.N);
            for (int i = 0; i < Data.N; i++) {
                System.out.printf("\nEnter %d integers for row %d: ", Data.N, i);
                for (int j = 0; j < Data.N; j++) {
                    MF[i][j] = console.nextInt();
                }
            }

            System.out.printf("(F2) Enter matrix MG (%d by %d): ", Data.N, Data.N);
            for (int i = 0; i < Data.N; i++) {
                System.out.printf("\nEnter %d integers for row %d: ", Data.N, i);
                for (int j = 0; j < Data.N; j++) {
                    MG[i][j] = console.nextInt();
                }
            }
        }
        //  обчислення функції F2 = MF = MF*MG*k
        MF = Data.F2(MF, MG, k);

        //  виведення результатів
        System.out.println("T2 is finished. Resulting Matrix:\n");
        for (int i = 0; i < Data.N; i++) {
            for (int j = 0; j < Data.N; j++)
                System.out.print(MF[i][j] + " ");
            System.out.println();
        }
    }
}
