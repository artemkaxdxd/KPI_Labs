package Lab6;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.Comparator;

public class TaxiPark {
    private final Car[] park;

    public TaxiPark(Car[] park) {
        this.park = park;
    }

    public int priceOfCars() {
        int sum = 0;
        for(Car car : park) {
            sum += car.getPrice();
        }
        return sum;
    }

    public Car[] carsByPetrol() {
        Comparator<Car> carsByPetrol = Comparator.comparing(Car::getPetrolPer100Km);
        Arrays.sort(park, carsByPetrol);
        return park;
    }

    public ArrayList<String> findBySpeed(int above, int below) {
        ArrayList<String> carsBySpeed = new ArrayList<String>();
        for(Car car : park){
            if(car.getSpeedKmPerH() >= above && car.getSpeedKmPerH() <= below) {
                carsBySpeed.add(car.getModel());
            }
        }
        return carsBySpeed;
    }
}
