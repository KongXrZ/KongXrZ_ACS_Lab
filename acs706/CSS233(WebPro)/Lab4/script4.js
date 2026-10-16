const createItemManager = () => {
    let items = [];

    const addItem = (item) => {
        if (items.includes(item)) {
            console.log(`Item "${item}" already exists.`);
            return;
        }
        items.push(item);
        console.log(`Item "${item}" added successfully.`);
    };

    const removeItem = (item) => {
        const index = items.indexOf(item);
        if (index === -1) {
            console.log(`Item "${item}" not found.`);
            return;
        }
        items.splice(index, 1);
        console.log(`Item "${item}" removed successfully.`);
    };

    const listItems = () => {
        return items;
    };

    return {
        addItem,
        removeItem,
        listItems,
    };
};
    
