# ATM Simulation System

## 📌 Description

This is a **C++ console-based ATM simulation** that allows users to perform various banking operations such as withdrawals, deposits, and balance inquiries. The system validates users through their **account number and PIN** and retrieves their data from a text file (`Clients.txt`). The program is built using functional/procedural programming.

This project does **not** include a **graphical UI** or any external **frameworks**. It relies on **standard input/output (cin/cout)** for interaction and uses **file handling** to manage client data.

## ✨ Features

- 🔐 **User authentication** via **Account Number & PIN**.
- 💰 **Quick Withdraw options** for predefined amounts.
- 🏧 **Normal Withdraw option** where users specify the amount.
- 💵 **Deposit feature** to add funds to the account.
- 📊 **Balance inquiry** to check the current account balance.
- 📂 **Client data stored in `Clients.txt`**, making it **persistent**.
- 🔄 **Looped menu** for multiple transactions until logout.

## 🛠️ How to Compile and Run

### 🔹 Compilation

Ensure you have a **C++ compiler** installed (e.g., `g++`).


## 🎮 Usage Instructions

1️⃣ **Login with Account Number & PIN.**
2️⃣ Select an option from the **main menu:**
   - `1`: 💸 Quick Withdraw (predefined amounts)
   - `2`: 🏧 Normal Withdraw (user-specified amount)
   - `3`: 💵 Deposit funds
   - `4`: 📊 Check balance
   - `5`: 🔐 Logout
3️⃣ **Perform the chosen transaction.**
4️⃣ The system updates **your balance** and **saves it** in `Clients.txt`.
5️⃣ Repeat until you choose to **logout**.

## 📂 File Structure
- `Clients.txt` **(Database File)**:
  - Stores client account details.
  - Format: `AccountNumber#//#PinCode#//#Name#//#Phone#//#Balance`
  - Example Entry:
    ```
    A1234#//#3214#//#Adel Amir#//#077777777#//#13980.00
    ```
- `atm_simulator.cpp` **(Main Source Code)**:
  - Handles login, transactions, and file operations.

## ⚠️ Known Issues
- ⚠️ No **encryption** for stored PINs (plaintext storage).
- ⚠️ No **error handling** for corrupt/missing `Clients.txt`.
- ⚠️ Withdrawals do not verify ATM **denominations**.

## 🚀 Future Improvements
- 🔒 Implement **PIN encryption** for better security.
- 🖥️ Add **GUI support** using **Qt/SFML**.
- 🔄 Improve **error handling** for file operations.
- 🏦 Add **multi-user session handling**.

## 📜 License
This project is licensed under the **MIT License**.

## 👤 Author
Ossama A.

