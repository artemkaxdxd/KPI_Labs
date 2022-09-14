public class Lab1 {
    public static void main(String[] args){
        double a = 12;
        double b = 13;
        int n = 50;
        int m = 51;
        double sum = 0;
        for (double i = a; i <= n; i++) {
            for (double j = b; j <= m; j++) {
                double numerator = (i + j);
                double denominator = (i - 2);
                if (denominator != 0) {
                    sum += numerator / denominator;
                }
            }
        }
        System.out.println(sum);
    }
}