import java.util.Arrays;
import java.util.Comparator;

public class Lab4 {
    public static void main(String[] args) {
        // initialize array of objects
        Furniture[] store = new Furniture[5];

        // add random data to object array
        store[0] = new Furniture("sofa", "green", "suede", 3, 300);
        store[1] = new Furniture("sofa", "red", "leather", 5, 700);
        store[2] = new Furniture("table", "brown", "wood", 2, 450);
        store[3] = new Furniture("chair", "brown", "wood", 6, 100);
        store[4] = new Furniture("chair", "red", "plastic", 12, 75);

        // Compare data by 'inStock' in ascending order
        Comparator<Furniture> inStockAsc = Comparator.comparing(Furniture::getInStock);
        // Sort array by comparator
        Arrays.sort(store, inStockAsc);

        // Compare data by 'price' in descending order
        Comparator<Furniture> priceDesc = Comparator.comparing(Furniture::getPrice).reversed();
        // Sort array by comparator
        Arrays.sort(store, priceDesc);

        for (Furniture piece: store) {
            System.out.println(piece.showData());
        }
    }
}

// C11 = 8 (Визначити клас меблі, який складається як мінімум з 5-и полів.)
class Furniture {
    // Name of the piece of furniture
    public String name;

    // Color of furniture
    public String color;

    // Material of furniture
    public String material;

    // How much is in stock
    private int inStock;

    // Price of furniture
    private int price;

    public int getInStock() {
        return this.inStock;
    }

    public int getPrice() {
        return this.price;
    }

    public String showData() {
        return String.format("%s, %s, %s, %d, %d", name, color, material, inStock, price);
    }

    public Furniture(String name, String color, String material, int inStock, int price) {
        this.name = name;
        this.color = color;
        this.material = material;
        this.inStock = inStock;
        this.price = price;
    }
}