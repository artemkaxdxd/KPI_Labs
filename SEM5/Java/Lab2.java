public class Lab2 {
    public static void main(String[] args) {
        float[][] matrix1 = {
                {0, 1, 2, 3},
                {4, 5, 6, 7},
                {8, 9, 5, 6} };
        float[][] matrix2 = {
                {9, 8},
                {7, 6}
        };
        int lengthM1 = matrix1.length;
        int lengthM2 = matrix2.length;
        int rowsM1 = matrix1[0].length;
        int rowsM2 = matrix2[0].length;

        int n = lengthM1 + lengthM2;
        int m = rowsM1 + rowsM2;

        float[][] matrix3 = new float[n][m];
        for (int i = 0; i < lengthM1; i++) {
            for (int j = 0; j < rowsM1; j++){
                matrix3[i][j] = matrix1[i][j];
            }
        }
        for (int i = 0; i < lengthM2; i++) {
            for (int j = 0; j < rowsM2; j++) {
                matrix3[i + lengthM1][j + rowsM1] = matrix2[i][j];
            }
        }

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                System.out.print( matrix3[i][j]  + "\t");
            }
            System.out.println();
        }

        float[] avg = new float[n];
        for(int i = 0; i < n; i++) {
            float sum = 0;
            for(int j = 0; j < m; j++) {
                sum += matrix3[i][j];
            }
            avg[i] = sum / m;
            System.out.printf("Average for %d row: %f\n", i,  avg[i]);
        }
    }
}
