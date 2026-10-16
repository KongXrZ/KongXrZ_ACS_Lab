const loadData = () => {
  return new Promise((resolve) => {
    setTimeout(() => {
      resolve("Completed");
    }, 2000);
  });
};

const processData = async () => {
  console.log("Loading...");
  await loadData();
  console.log("Data loaded");
};

processData();