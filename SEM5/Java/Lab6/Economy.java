package Lab6;

public class Economy extends Car {

    @Override
    public String getModel() {
        return "Hyundai Elantra";
    }

    @Override
    public int getPetrolPer100Km() {
        return 8;
    }

    @Override
    public int getPrice() {
        return 75;
    }

    @Override
    public int getSpeedKmPerH() { return 80; }
}
