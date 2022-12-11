package Lab6;

public class Business extends Car {

    @Override
    public String getModel() { return "Lexus ES"; }

    @Override
    public int getPetrolPer100Km() {
        return 10;
    }

    @Override
    public int getPrice() {
        return 280;
    }

    @Override
    public int getSpeedKmPerH() {
        return 130;
    }
}
