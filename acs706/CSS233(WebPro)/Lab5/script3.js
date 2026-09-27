const userData = [
  { id: 1, name: "BatMan" },
  { id: 2, name: "NightWing" },
  { id: 3, name: "RedHood" },
];

const orderData = [
  { id: 1, userId: 1, items: ["Order 1", "Order 2"] },
  { id: 2, userId: 2, items: ["Order 3", "Order 4"] },
  { id: 3, userId: 3, items: ["Order 5", "Order 6"] },
];

const getUser = () => {
  return new Promise((resolve) => {
    setTimeout(() => {
      resolve(userData);
    }, 2000);
  });
};

const getOrders = (userId) => {
  return new Promise((resolve) => {
    setTimeout(() => {
      const res = orderData.filter((item) => item.userId === userId);
      resolve(res);
    }, 2000);
  });
};

const getOrderDetails = (orderId) => {
  return new Promise((resolve) => {
    setTimeout(() => {
      const res = orderData.find((item) => item.id === orderId);
      resolve(res);
    }, 2000);
  });
};

const setLoading = (isLoading) => {
  console.log(isLoading ? "Loading..." : "Processing Done");
};

async function fetchData() {
  try {
    setLoading(true);
    const users = await getUser();
    const orders = await getOrders(users[0].id);
    const orderDetails = await getOrderDetails(orders[0].id);

    console.log("Users:", users);
    console.log("Orders for user 1:", orders);
    console.log("Order details for order 1:", orderDetails);
  } catch {
    console.log("Error occurred while fetching data, please try again later.");
  } finally {
    setLoading(false);
  }
}

fetchData();