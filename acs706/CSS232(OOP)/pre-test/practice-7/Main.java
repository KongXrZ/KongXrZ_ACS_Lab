class Vehicle {
    String brand;

    void start() {
        System.out.println("Vehicle started");
    }
}

class Car extends Vehicle {
    int seats;

    void showInfo() {
        System.out.println("Brand: " + brand);
        System.out.println("Seats: " + seats);
    }
}

public class Main {
    public static void main(String[] args) {
        Car car = new Car();
        car.brand = "Toyota";
        car.seats = 5;
        car.start();
        car.showInfo();
    }
}