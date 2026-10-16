const profileData = {
  id: 1,
  name: "Max Verstappen",
};

const notificationData = [
  { id: 1, userId: 1, message: "Notification 1" },
  { id: 2, userId: 2, message: "Notification 2" },
  { id: 3, userId: 3, message: "Notification 3" },
];

const productsData = [
  { id: 1, name: "Product 1", price: 10 },
  { id: 2, name: "Product 2", price: 20 },
  { id: 3, name: "Product 3", price: 30 },
];

const recommendationData = [
  { id: 1, userId: 1, recommendations: ["Product 1", "Product 2"] },
  { id: 2, userId: 2, recommendations: ["Product 3"] },
  { id: 3, userId: 3, recommendations: ["Product 1", "Product 3"] },
];

const fetchProfile = () => {
  return new Promise((resolve) => {
    setTimeout(() => {
      resolve(profileData);
    }, 2000);
  });
};

const fetchNotifications = () => {
  return new Promise((resolve) => {
    setTimeout(() => {
      resolve(notificationData);
    }, 2000);
  });
};

const fetchProducts = () => {
  return new Promise((resolve) => {
    setTimeout(() => {
      resolve(productsData);
    }, 2000);
  });
};

const fetchRecommendations = (userId) => {
  return new Promise((resolve) => {
    setTimeout(() => {
      const res = recommendationData.filter((item) => item.userId === userId);
      resolve(res);
    }, 2000);
  });
};

const setLoading = (isLoading) => {
  console.log(isLoading ? "Loading..." : "Done");
};

const SUCCESS = "fulfilled";

const loadDashboard = async () => {
  setLoading(true);

  try {
    const user = await fetchProfile();

    if (!user) {
      throw new Error("Profile not found");
    }

    const results = await Promise.allSettled([
      fetchNotifications(),
      fetchProducts(),
      fetchRecommendations(user.id),
    ]);

    const [notifications, products, recommendations] = results;

    console.log("Profile:", user);

    if (notifications.status === SUCCESS) {
      console.log("Notifications:", notifications.value);
    } else {
      console.log("Notifications: Error retrieving notification data");
    }

    if (products.status === SUCCESS) {
      console.log("Products:", products.value);
    } else {
      console.log("Products: Error retrieving products data");
    }
    if (recommendations.status === SUCCESS) {
      console.log("Recommendations:", recommendations.value);
    } else {
      console.log("Recommendations: Error retrieving recommendations data");
    }
  } catch {
    console.log("Please Try Again");
  } finally {
    setLoading(false);
  }
};

loadDashboard();