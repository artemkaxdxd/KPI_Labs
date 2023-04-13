/*
Програмне забезпечення високопродуктивних комп'ютерних систем
Лабораторна робота 3, Варіант 19
Завдання:
X = (R * MC) * MD + (B * Z) * E * d
T1 = R, Z
T2 = MD
T3 = X, B, d
T4 = MC, E

Бондарчук Артем Дмитрович, ІП-05
Дата 14.04.2023
*/

import javax.management.monitor.Monitor;

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