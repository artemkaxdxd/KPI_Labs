package Lab6;

public class Cargo extends Car {

    @Override
    public String getModel() {
        return "Mercedes Sprinter";
    }

    @Override
    public int getPetrolPer100Km() {
        return 14;
    }

    @Override
    public int getPrice() {
        return 350;
    }

    @Override
    public int getSpeedKmPerH() { return 60; }
}
