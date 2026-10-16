const formatUserData = (name, email, score) => {
    const response = `User: ${name.toUpperCase()} | Contact: ${email.trim()} | Status: ${score >= 50 ? "Pass" : "Fail"}`;
    return response;
};