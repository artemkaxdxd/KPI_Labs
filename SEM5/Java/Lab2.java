public class Lab2 {
    public static void main(String[] args) {
        final float[][] matrix1 = {
                {0, 1, 2, 3},
                {4, 5, 6, 7, 3},
                {8, 9, 5, 6}
        };
        final float[][] matrix2 = {
                {9, 8},
                {7, 6,3}
        };
        final int columnsM1 = matrix1.length;
        final int columnsM2 = matrix2.length;

        int rowsM1 = matrix1[0].length;
        int rowsM2 = matrix2[0].length;
        int tempRows;

        for (int i = 0; i < columnsM1; i++) {
            tempRows = matrix1[i].length;
            if (tempRows > rowsM1) {
                rowsM1 = tempRows;
            }
        }
        for (int i = 0; i < columnsM2; i++) {
            tempRows = matrix2[i].length;
            if (tempRows > rowsM2) {
                rowsM2 = tempRows;
            }
        }
        final int n = columnsM1 + columnsM2;
        final int m = rowsM1 + rowsM2;

        float[][] matrix3 = new float[n][m];
        for (int i = 0; i < columnsM1; i++) {
            for (int j = 0; j < matrix1[i].length; j++){
                matrix3[i][j] = matrix1[i][j];
            }
        }
        for (int i = 0; i < columnsM2; i++) {
            for (int j = 0; j < matrix2[i].length; j++) {
                matrix3[i + columnsM1][j + rowsM1] = matrix2[i][j];
            }
        }

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                System.out.print(matrix3[i][j]  + "\t");
            }
            System.out.println();
        }

        float sum;
        for(int i = 0; i < n; i++) {
            sum = 0;
            for(int j = 0; j < m; j++) {
                sum += matrix3[i][j];
            }
            System.out.printf("Average for %d row: %f\n", i,  sum / m);
        }
    }
}
