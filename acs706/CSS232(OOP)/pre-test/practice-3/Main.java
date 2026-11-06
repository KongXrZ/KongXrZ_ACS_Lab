class BamlAccount {
  private int balance;

  void BankAccount(int balance) {
      this.balance = balance;
  }

  public void withdraw(int amount) {
      if (amount > 0 && amount <= balance) {
          balance -= amount;
      } else{
        throw new IllegalArgumentException();
      }
  }

  public int getMoney() {
      return balance;
  }
}

public class Main {
}