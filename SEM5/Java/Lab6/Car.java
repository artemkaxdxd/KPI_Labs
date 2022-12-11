package Lab6;

public class Car {
    private final String model;
    private final int petrolPer100Km;

    private final int price;

    private final int speedKmPerH;

    public Car() {
        this.model = "model";
        this.petrolPer100Km = 0;
        this.price = 0;
        this.speedKmPerH = 0;
    }

    public String getModel() {
        return model;
    }

    public int getPetrolPer100Km() {
        return petrolPer100Km;
    }

    public int getPrice() {
        return price;
    }

    public int getSpeedKmPerH() {
        return speedKmPerH;
    }

    public String showData() {
        return String.format("Model: %s | Petrol/100km: %d | Price: %d | Speed(km/h): %d", getModel(), getPetrolPer100Km(), getPrice(), getSpeedKmPerH());
    }
}
