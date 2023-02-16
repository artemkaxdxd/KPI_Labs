/*
Програмне забезпечення високопродуктивних комп'ютерних систем
Лабораторна робота 0, Варіант 3
F1: C = A – B*(MA*MС)*е
F2: MF = MF*MG*k
F3: O = SORT(P)*(MR*MT)
Бондарчук Артем Дмитрович, ІП-05
Дата 15.02.2023
*/

import java.io.FileWriter;
import java.io.IOException;
import java.util.Scanner;

public class Lab0 {
    public static void main(String[] args) {
        Thread_F1 T1 = new Thread_F1();
        Thread_F2 T2 = new Thread_F2();
        Thread_F3 T3 = new Thread_F3();

        if (Data.N > 1000) {
            System.out.print("Execution versions: (1) (2) (3)\n");
            System.out.print("\n1 - Filling data with same integers\n");
            System.out.print("\n2 - Filling data with random integers\n");
            System.out.print("\n3 - Generating random data, writing to files, reading from files\n");
            System.out.print("\nEnter execution version: ");

            Scanner console = new Scanner(System.in);
            int ver = console.nextInt();
            if (ver > 0 && ver < 4)
                Data.version = ver;
            if (ver == 3) {
                try {
                    new FileWriter("data1.txt", false).close();
                    new FileWriter("data2.txt", false).close();
                    new FileWriter("data3.txt", false).close();

                } catch (IOException e) {
                    System.out.println("An error occurred.");
                    e.printStackTrace();
                }
            }

            T1.start();
            T2.start();
            T3.start();
        } else {
            T1.start();
            try {
                T1.join();
            }
            catch(Exception e){
                System.out.println(e);
            }

            T2.start();
            try {
                T2.join();
            }
            catch(Exception e){
                System.out.println(e);
            }

            T3.start();
            try {
                T3.join();
            }
            catch(Exception e){
                System.out.println(e);
            }
            System.out.println("\nAll threads finished!");
        }
    }
}
