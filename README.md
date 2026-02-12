# 🚗 Car Rental System

<p align="center">
  <img src="https://img.shields.io/badge/Language-C%2B%2B-blue.svg" />
  <img src="https://img.shields.io/badge/Data%20Structures-AVL%20%7C%20Hash%20%7C%20Heap-green.svg" />
  <img src="https://img.shields.io/badge/Type-Console%20Application-orange.svg" />
  <img src="https://img.shields.io/badge/Status-Academic%20Project-success.svg" />
</p>

## 📚 Final Project – Data Structures Course

**Instructor:** Dr. Mojtaba Khalili  
**Developer:** Kourosh Jamshidi  
**Faculty:** Electrical & Computer Engineering  
**Academic Year:** 2024–2025  

---

## 📌 Table of Contents

- [🎯 Project Overview](#-project-overview)
- [👥 System Roles](#-system-roles)
- [🧠 Data Structures Used](#-data-structures-used)
- [⚙️ Technical Requirements](#️-technical-requirements)
- [🚀 Key Features](#-key-features)
- [🏗 System Architecture](#-system-architecture)
- [▶️ How to Run](#️-how-to-run)
- [📊 Learning Outcomes](#-learning-outcomes)

---

## 🎯 Project Overview

This project implements a **Console-Based Car Rental Management System** with a strong focus on efficient usage of fundamental **Data Structures**.

The system supports:

- 🔎 Vehicle searching  
- 📅 Reservation management  
- 🔄 Rental processing  
- 💰 Late penalty calculation  
- 📊 Performance reporting  

The primary objective is to practice selecting appropriate data structures and designing scalable systems under realistic constraints.

---

## 👥 System Roles

### 🧑 Guest
- Register a new account  
- Browse vehicles (filter by brand / price / type)  
- View car details and availability status  

### 👤 Customer
- Secure login (hashed password)  
- Create reservation with time validation  
- View active reservations and rentals  
- Extend rental (if no conflict exists)  
- Pay rental fees or penalties  

### 🛠 Staff
- Convert reservation → active rental  
- Process car return  
- Automatically calculate late fines  
- Manage reservation waiting queue  
- Add / Edit vehicles  

### 🔧 Maintenance
- Record repair details (date, cost, description)  
- Mark vehicle as `Maintenance`  
- Track maintenance history  

### 👨‍💼 Manager
- Generate revenue & performance reports  
- Export CSV reports  
- Block users with unpaid debts  
- Backup & restore system data  

---

## 🧠 Data Structures Used

| Data Structure | Purpose |
|----------------|----------|
| Doubly Linked List | Manage vehicle list |
| Linked List | Store users |
| AVL Tree | Fast car search by name |
| Hash Table | Username → User pointer mapping |
| Priority Queue (Heap) | Reservation queue management |

---

## ⚙️ Technical Requirements

- Language: **C / C++**
- Only standard `string` library allowed
- Object-Oriented Programming principles applied
- No double booking allowed
- Passwords stored using hashing
- Configurable system parameters:
  - Rental duration
  - Late penalty rate
  - Maximum concurrent reservations

---

## 🚀 Key Features

- ⚡ Fast indexed search using AVL Tree  
- 🔍 O(1) average login using Hash Table  
- 🛡 Conflict-free reservation handling  
- 📈 Designed to handle hundreds of users & vehicles  
- 🔄 Automatic fine calculation system  

---

## 🏗 System Architecture

