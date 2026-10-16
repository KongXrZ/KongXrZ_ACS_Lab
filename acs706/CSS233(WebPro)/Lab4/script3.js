const createBankAccount = (initialBalance) => {
    let balance = initialBalance;

    const getBalance = () => {
        return balance;
    };

    const deposit = (amount) => {
        if (amount < 0) {
            console.log("Deposit amount must be positive.");
            return;
        }
        balance += amount;
    };

    const withdraw = (amount) => {
        if (amount < 0) {
            console.log("Withdrawal amount must be positive.");
            return;
        }
        if (amount > balance) {
            console.log("Insufficient funds: withdrawal not allowed.");
            return;
        }
        balance -= amount;
    };
    return {
        getBalance,
        deposit,
        withdraw,
    };
};