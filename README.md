(existing code...)
# Clinic Management System (C – Data Structures Project)

## Project Overview

This project implements a **Clinic Management System** using fundamental **data structures and sorting algorithms in C**.

The system simulates the workflow of a small clinic, including:

- Patient registration - Ginodh
- Waiting queue management - Dimanya
- Emergency case handling - Dulana
- Treatment record management - Dasun
- Pharmacy inventory management - Neleesha
- Medicine purchase tracking - Harsha
- Billing and payment records - Methoo

The main objective is to demonstrate how **different data structures can model real-world systems** efficiently.

---

## System Workflow

1. Patients are **registered** and stored in the **Patient Records array**.
2. When they arrive at the clinic, they are added to the **Waiting Queue**.
3. If a patient has an emergency, they are pushed into the **Emergency Stack** and treated first.
4. The doctor records treatments in the **Treatment Linked List**.
5. If medicines are prescribed, a **Pharmacy Order** is created.
6. The system checks the **Drug Inventory (Doubly Linked List)** to get price and update stock.
7. A **Bill** is generated including treatment and medicine costs.

---

## Data Structures Used

| Module            | Data Structure        | Reason                                 |
|-------------------|----------------------|-----------------------------------------|
| Patient Records   | Array                | Fast access and fixed capacity          |
| Waiting Queue     | Queue                | First-Come-First-Serve patient handling |
| Emergency Cases   | Stack                | Immediate handling of urgent cases      |
| Treatment Records | Singly Linked List   | Dynamic number of treatments            |
| Drug Inventory    | Doubly Linked List   | Efficient insertion, deletion, traversal|
| Pharmacy Orders   | Stack                | Track most recent transactions          |
| Billing Records   | Array                | Simple storage and easy sorting         |

---

## Project Structure

```
clinic-management-system/
│
├── clinic_system.c   # Backend system: struct definitions, global variables, dummy patient data, function definitions (to implement)
├── frontend.c        # Simple console-based interface that calls backend functions
└── README.md         # Project documentation
```

---

## Modules and Responsibilities

Each team member is responsible for implementing **one data structure module**.

### Patient Management
Functions:
- addPatient()
- deletePatient()
- searchPatient()
- updatePatient()
- sortPatients()

### Waiting Queue
Functions:
- enqueuePatient()
- dequeuePatient()
- peekNextPatient()
- displayQueue()
- queueSize()

### Emergency Stack
Functions:
- pushEmergency()
- popEmergency()
- peekEmergency()
- displayEmergencyStack()
- isEmergencyEmpty()

### Treatment Records
Functions:
- addTreatment()
- deleteTreatment()
- displayTreatments()
- searchTreatment()
- sortTreatmentsByCost()

### Drug Inventory
Functions:
- addDrug()
- updateDrugStock()
- searchDrug()
- displayInventory()
- sortDrugsByName()

### Pharmacy Orders
Functions:
- createOrder()
- calculatePrice()
- updateInventoryAfterSale()
- displayOrders()
- cancelLastOrder()

### Billing System
Functions:
- generateBill()
- updatePaymentStatus()
- searchBill()
- displayBills()
- sortBillsByAmount()

---

## Sorting Algorithms Used

The following sorting algorithms are implemented across modules:
- **Bubble Sort**
- **Selection Sort**
- **Insertion Sort**

These are used to sort:
- Patients
- Treatments
- Drug inventory
- Billing records

---

## Dummy Data

The system initializes with **20 preloaded patient records** and space for **20 additional patients**.

This allows immediate testing of the system without entering data manually.

---

## Compilation

Compile the backend and frontend files together:

```bash
gcc clinic_system.c frontend.c -o clinic
(existing code...)
The system initializes with \*\*20 preloaded patient records\*\* and space for \*\*20 additional patients\*\*.

This allows immediate testing of the system without entering data manually.

\---

\# Compilation

Compile the backend and frontend files together:

\`\`\`bash

gcc clinic\_system.c frontend.c -o clinic
