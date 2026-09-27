const checkAge = (age) => {
  return new Promise((resolve, reject) => {
    if (age >= 18) {
      resolve("Allowed");
    } else {
      reject("Not allowed");
    }
  });
};

checkAge(20)
  .then((result) => {
    console.log(result);
  })
  .catch((error) => {
    console.log(error);
  });