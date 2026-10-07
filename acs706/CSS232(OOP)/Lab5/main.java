class SeatPool {
    private final int capacity;
    private int booked;

    SeatPool(int capacity) {
        if (capacity <= 0)
            throw new IllegalArgumentException();
        this.capacity = capacity;
    }

    public boolean reserve() {
        if (booked == capacity)
            return false;
        booked++;
        return true;
    }

    public int remaining() {
        return capacity - booked;
    }

    public boolean cancel() {
        if (booked == 0) {
            return false;
        }
        booked--;
        return true;
    }
}