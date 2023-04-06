/*
Програмне забезпечення високопродуктивних комп'ютерних систем
Лабораторна робота 1, Варіант 15
Завдання:
МА= MD*MC *d + max(Z)*(MX+MM)*p
T1 = d, MA, MM
T2 = MX, MC
T4 = Z, MD, p

Бондарчук Артем Дмитрович, ІП-05
Дата 06.04.2023
*/

public class Lab1 {
    public static void main(String[] args) throws InterruptedException {

        System.out.println("N = " + Data.N + "\n");

        T1 thread1 = new T1();
        T2 thread2 = new T2();
        T3 thread3 = new T3();
        T4 thread4 = new T4();

        thread1.start();
        thread2.start();
        thread3.start();
        thread4.start();



    }
}