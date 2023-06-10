/*
Програмне забезпечення високопродуктивних комп'ютерних систем
Лабораторна робота 3, Варіант 12
Завдання:
A= sort(d*B + Z*(MM*MX))*e +max(B)*Z
T1 = d, MM
T2 = e, B, MX
T3 = -
T4 = A, Z

Комісар Кіріл Сергійович, ІП-05
Дата 10.06.2023
*/

public class Lab3 {
    public static long curTime = System.currentTimeMillis();

    public static void main(String[] args) {
        Data Monitor = new Data();
        T1 thread1 = new T1(Monitor);
        T2 thread2 = new T2(Monitor);
        T3 thread3 = new T3(Monitor);
        T4 thread4 = new T4(Monitor);

        thread1.start();
        thread2.start();
        thread3.start();
        thread4.start();
    }
}