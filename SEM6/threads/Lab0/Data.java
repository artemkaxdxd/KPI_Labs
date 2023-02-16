import java.io.*;
import java.util.Arrays;
import java.util.Random;
import java.util.Scanner;

public class Data {
    public static final int N = 4;
    public static int version = 0;
    private static final Random ran = new Random();

    public static int[] F1 (int[] A, int[] B, int[][] MA, int[][] MC, int e) {
        int C[] = new int[N];

        //  обчислення функції F1 = C = A – B*(MA*MС)*е

        // множення матриці на матрицю на скаляр
        int tempMtx[][] = new int[N][N];
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                for (int k = 0; k < N; k++)
                    tempMtx[i][j] += MA[i][k] * MC[k][j] * e;
            }
        }

        // множення матриці на вектор
        int tempVec[] = new int[N];
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < N; ++j)
                tempVec[i] += tempMtx[i][j] * B[j];

        // віднімання вектора від вектора
        for (int i = 0; i < N; i++) {
            C[i] = A[i] - tempVec[i];
        }

        return C;
    }

    public static int[][] F2 (int[][] MF, int[][] MG, int k) {
        //  обчислення функції F2 = MF = MF*MG*k
        int tempMtx[][] = new int[N][N];
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                for (int e = 0; e < N; e++)
                    tempMtx[i][j] += MF[i][e] * MG[e][j] * k;
            }
        }
        return tempMtx;
    }

    public static int[] F3 (int[] P, int[][] MR, int[][] MT) {
        int O[] = new int[N];
        //  обчислення функції F3 = O = SORT(P)*(MR*MT)
        Arrays.sort(P);

        int tempMtx[][] = new int[N][N];
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                for (int k = 0; k < N; k++)
                    tempMtx[i][j] += MR[i][k] * MT[k][j];
            }
        }

        for (int i = 0; i < N; ++i)
            for (int j = 0; j < N; ++j)
                O[i] += tempMtx[i][j] * P[j];

        return O;
    }

    public static int[][] insertMtxWithNum (int num) {
        int tempMtx[][] = new int[N][N];
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < N; ++j)
                tempMtx[i][j] = num;
        return tempMtx;
    }

    public static int[] insertVecWithNum (int num) {
        int tempVec[] = new int[N];
        for (int i = 0; i < N; ++i)
            tempVec[i] = num;
        return tempVec;
    }

    public static int[][] generateRandMtx () {
        int tempMtx[][] = new int[N][N];
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                tempMtx[i][j] = ran.nextInt();
            }
        }
        return tempMtx;
    }

    public static int[] generateRandVec () {
        int tempVec[] = new int[N];
        for (int i = 0; i < N; ++i)
            tempVec[i] = ran.nextInt();
        return tempVec;
    }

    public static void writeMtxToFile(String fileName, String mtxName) {
        try {
            FileWriter writer = new FileWriter(fileName, true);

            int tempMtx[][] = new int[N][N];
            writer.write(mtxName + "\n");
            for (int i = 0; i < N; i++) {
                for (int j = 0; j < N; j++) {
                    if (j == N - 1) {
                        writer.write(ran.nextInt(10) + "\n");
                        break;
                    }
                    writer.write(ran.nextInt(10) + ", ");
                }
            }

            writer.close();


        } catch (IOException e) {
            System.out.println("An error occurred.");
            e.printStackTrace();
        }
    }

    public static void writeVecToFile(String fileName, String vecName) {
        try {
            FileWriter writer = new FileWriter(fileName, true);

            writer.write(vecName + "\n");
            for (int j = 0; j < N; j++) {
                if (j == N - 1) {
                    writer.write(ran.nextInt(10) + "\n");
                    break;
                }
                writer.write(ran.nextInt(10) + ", ");
            }

            writer.close();

        } catch (IOException e) {
            System.out.println("An error occurred.");
            e.printStackTrace();
        }
    }

    public static int[][] readMtxFromFile(String fileName, String mtxName) {
        int tempMtx[][] = new int[N][N];
        try {
            FileReader reader = new FileReader(fileName);
            Scanner scan = new Scanner(reader);
            boolean isMtx = false;
            int rows = 0;

            while(scan.hasNextLine()) {
                String line = scan.nextLine();
                if (rows >= N){
                    break;
                }
                if (isMtx) {
                    String[] row = line.split(", ");
                    for (int i = 0; i < row.length; i++){
                        tempMtx[rows][i] = Integer.parseInt(row[i]);
                    }
                    rows++;
                }
                if(line.equals(mtxName)){
                    isMtx = true;
                }
            }
            reader.close();
        } catch (Exception e) {
            System.out.println("An error occurred.");
            e.printStackTrace();
        }
        return tempMtx;
    }

    public static int[] readVecFromFile(String fileName, String vecName) {
        int tempVec[] = new int[N];
        try {
            FileReader reader = new FileReader(fileName);
            Scanner scan = new Scanner(reader);
            boolean isVec = false;

            while(scan.hasNextLine()) {
                String line = scan.nextLine();
                if (isVec) {
                    String[] row = line.split(", ");
                    for (int i = 0; i < row.length; i++){
                        tempVec[i] = Integer.parseInt(row[i]);
                    }
                    break;
                }
                if(line.equals(vecName)){
                    isVec = true;
                }
            }
            reader.close();
        } catch (Exception e) {
            System.out.println("An error occurred.");
            e.printStackTrace();
        }
        for (int i = 0; i < tempVec.length; ++i)
            tempVec[i] = ran.nextInt();
        return tempVec;
    }

}
