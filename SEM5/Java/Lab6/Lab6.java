package Lab6;

import java.util.ArrayList;

public class Lab6 {
    public static void main(String[] args) {
        Cargo cargoCar = new Cargo();
        Business businessCar = new Business();
        Economy economyCar = new Economy();

        Car[] cars = {businessCar, economyCar, cargoCar};

        TaxiPark park = new TaxiPark(cars);

        System.out.printf("\n* Price of all cars in taxi park: %d\n", park.priceOfCars());

        // Print cars data before sorting
        System.out.println("\n* Cars before sorting by petrol consumption: \n");

        for (Car car : cars) {
            System.out.println(car.showData());
        }

        // Sort cars by petrol
        park.carsByPetrol();

        // Print cars data after sorting
        System.out.println("\n* Cars after sorting by petrol consumption: \n");

        for (Car car : cars) {
            System.out.println(car.showData());
        }

        final int aboveSpeed = 60;
        final int belowSpeed = 100;

        final ArrayList<String> carsSpeeds = park.findBySpeed(aboveSpeed, belowSpeed);
        if (!carsSpeeds.isEmpty()) {
            System.out.printf("\n* Cars found with matching speeds: \n%s\n", carsSpeeds);
        } else {
            System.out.printf("\n* Cars within this speed range don't exist, range: \nAbove: %d | Below: %d",
                    aboveSpeed, belowSpeed);
        }
    }
}

// C13 = 9 - Визначити ієрархію легкових автомобілів.
// Створити таксопарк.
// Порахувати вартість автопарку.
// Провести сортування автомобілів парку за витратами палива.
// Знайти автомобіль у компанії, що відповідає заданому діапазону швидкості автомобіля.