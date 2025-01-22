
# Inventory Management System

## Overview

The **Inventory Management System** is a C-based project designed to efficiently manage inventory in a store. It allows users to perform operations like adding, editing, viewing, deleting items, and generating bills for purchased items. The system uses a file-based approach to store and retrieve inventory data.

---

## Features

- **Add New Products**: Add details of new products, including name, brand, cost, ID, and quantity.
- **View Inventory**: Display a list of all products in the inventory.
- **Edit Products**: Update product details using their unique ID.
- **Delete Products**: Remove products from the inventory by their ID.
- **Calculate Total Bill**: Compute the bill for purchased items based on quantity and cost.
- **Persistent Storage**: Data is stored in a file (`NextFile.dat`) for long-term use.

---

## Project Structure

- **Source Code**: The main program includes functions for all operations.
- **Data File**: The file `NextFile.dat` is used to store inventory details.

### Files in the Project
- `inventory_management.c`: Main source code file.
- `NextFile.dat`: Data file storing product information.
- `TempFile.dat`: Temporary file used during operations like editing and deleting products.

---

## How to Use

### Prerequisites
- A C compiler (e.g., GCC).
- Basic knowledge of terminal/command-line operations.

### Steps to Run
1. Clone or download the repository to your local machine.
2. Compile the code using a C compiler:
   ```bash
   gcc inventory_management.c -o inventory
   ```
3. Run the compiled program:
   ```bash
   ./inventory
   ```
4. Follow the on-screen menu to perform desired operations.

---

## Menu Options

1. **Add Goods**: Add a new product to the inventory by entering the required details.
2. **Read Goods**: View all available products in the inventory.
3. **Edit Goods**: Modify details of a product using its unique ID.
4. **Delete Goods**: Remove a product by its ID.
5. **Total Bill**: Calculate the total bill for a specific product and quantity.
6. **Exit**: Close the application.

---

## Sample Data

Here is an example of the data format in `NextFile.dat`:
```
item_name brand_name cost item_id quantity
Laptop    Dell       55000 101      10
Mobile    Samsung    15000 102      25
Headset   Sony        2000 103      50
```

---

## Future Enhancements

- Implement user authentication for secure access.
- Add support for graphical user interfaces (GUI).
- Enable real-time inventory tracking.
- Extend the system to support multiple users and roles.

---

## Contributing

Contributions are welcome! Please create an issue or submit a pull request for any enhancements or bug fixes.

---

## License

This project is open-source and available under the [MIT License](LICENSE).

---
