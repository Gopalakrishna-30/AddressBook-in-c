# 📒 Address Book Management System (CLI) – C

A **menu-driven Command-Line Interface (CLI) Address Book Management System** developed in **C** as part of an **Embedded Systems internship project**.
This application demonstrates **modular programming, strong input validation, file handling, and structured data management** in C.

---

## 🚀 Features

* **Create Contact**
  Add new contacts with name, mobile number, and email ID.

* **Search Contact**
  Search contacts using name, mobile number, or email.

* **Edit Contact**
  Update existing contact details with proper validation.

* **Delete Contact**
  Remove contacts while maintaining clean indexing.

* **List Contacts**
  Display all contacts in a formatted table.

* **Save & Exit**
  Ensures **data persistence** using file handling.

---

## ✅ Input Validations

* **Name** → First letter must be capital and Alphabets and spaces only
* **Mobile Number** → Exactly 10 digits
* **Email ID** → Must contain `@gmail.com`
* **Duplicate Check** → Prevents repeated mobile numbers and email IDs

---

## 🛠️ Technical Highlights

* Modular and reusable function design
* Efficient partial search logic
* Robust validation for all user inputs
* File handling for persistent storage
* Clean and user-friendly CLI menu system

---

## 📚 Key Learnings

* Practical use of **structures** for data organization
* **File I/O operations** for saving and loading data
* **Pointers and string manipulation** in real-world scenarios
* Importance of **modular design and debugging**
* Experience building **scalable menu-driven applications**

---

## ⚙️ Technologies Used

* **Language:** C
* **Concepts:** Structures, Pointers, File Handling, String Operations
* **Platform:** GCC / Linux / Windows (CLI-based)

---

## ▶️ How to Run

```bash
gcc *.c -o address_book
./address_book
```

---

## 📌 Future Enhancements

* Sorting contacts (A–Z)
* Import/Export contacts (CSV)
* Password-protected access
* Enhanced search filters

---
