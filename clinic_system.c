#include <stdio.h>
#include <string.h>

/*
====================================================
CLINIC MANAGEMENT SYSTEM - CORE BACKEND FILE
====================================================

This file contains:

1. All struct definitions
2. Global variables
3. Dummy patient data
4. Empty function definitions for all modules

Team members will implement the logic inside
the functions assigned to them.

====================================================
*/


/* ==================================================
   1. PATIENT STRUCTURE
   ================================================== */

struct Patient
{
    int patientID;
    char name[50];
    int age;
    char gender[10];
    char contact[20];
};


/* 20 existing patients + space for 20 more */

struct Patient patients[40] =
{
    {1,"Alice",25,"F","0711111111"},
    {2,"Bob",30,"M","0711111112"},
    {3,"Charlie",28,"M","0711111113"},
    {4,"Diana",32,"F","0711111114"},
    {5,"Ethan",40,"M","0711111115"},
    {6,"Fiona",22,"F","0711111116"},
    {7,"George",35,"M","0711111117"},
    {8,"Hannah",29,"F","0711111118"},
    {9,"Ian",31,"M","0711111119"},
    {10,"Jane",26,"F","0711111120"},
    {11,"Kevin",38,"M","0711111121"},
    {12,"Lily",24,"F","0711111122"},
    {13,"Mike",45,"M","0711111123"},
    {14,"Nina",27,"F","0711111124"},
    {15,"Oscar",36,"M","0711111125"},
    {16,"Paula",34,"F","0711111126"},
    {17,"Quinn",33,"M","0711111127"},
    {18,"Rita",28,"F","0711111128"},
    {19,"Sam",41,"M","0711111129"},
    {20,"Tina",23,"F","0711111130"}
};

int patientCount = 20;



/* ==================================================
   2. WAITING QUEUE
   ================================================== */

int waitingQueue[50];
int front = -1;
int rear = -1;


/* ==================================================
   3. EMERGENCY STACK
   ================================================== */

int emergencyStack[50];
int top = -1;


/* ==================================================
   4. TREATMENT LINKED LIST
   ================================================== */

struct Treatment
{
    int treatmentID;
    int patientID;
    char treatmentName[50];
    float cost;
    struct Treatment *next;
};

struct Treatment *treatmentHead = NULL;



/* ==================================================
   5. DRUG INVENTORY
   ================================================== */

struct Drug
{
    int drugID;
    char name[50];
    int quantity;
    float unitPrice;
};

struct Drug inventory[100];
int drugCount = 0;



/* ==================================================
   6. PHARMACY ORDERS
   ================================================== */

struct PharmacyOrder
{
    int patientID;
    char drugName[50];
    int quantity;
    float totalPrice;
};

struct PharmacyOrder pharmacyStack[50];
int pharmacyTop = -1;



/* ==================================================
   7. BILLING STRUCTURE
   ================================================== */

struct Bill
{
    int billID;
    int patientID;
    float amount;
    char paymentStatus[20];
};

struct Bill bills[100];
int billCount = 0;



/* ==================================================
   PATIENT FUNCTIONS
   ================================================== */

/*
Function: addPatient()

Purpose:
Registers a new patient in the clinic system.

Description:
This function should collect patient details such as
name, age, gender, and contact number, then insert
the new patient into the patients array.

The function should also increase patientCount.

Important Variables:
patients[]  → array storing patient records
patientCount → number of registered patients
*/

void addPatient()
{

}



/*
Function: deletePatient()

Purpose:
Removes a patient record from the system.

Description:
The function should locate a patient using patientID
and remove that patient from the array by shifting
remaining elements.

Important Variables:
patients[]
patientCount
*/

void deletePatient()
{

}



/*
Function: searchPatient()

Purpose:
Find a patient using their patient ID.

Description:
The function should scan the patients array and
display the patient details if found.

Important Variables:
patients[]
patientCount
*/

void searchPatient()
{

}



/*
Function: updatePatient()

Purpose:
Modify patient information.

Description:
Allows updating of fields such as contact number
or patient name.

Important Variables:
patients[]
patientCount
*/

void updatePatient()
{

}



/*
Function: sortPatients()

Purpose:
Sort the patient list alphabetically.

Description:
This function should implement Selection Sort
to sort the patient array based on name.

Important Variables:
patients[]
patientCount
*/

void sortPatients()
{

}



/* ==================================================
   QUEUE FUNCTIONS
   ================================================== */

/*
Function: enqueuePatient()

Purpose:
Add a patient to the waiting queue.

Description:
The function inserts a patientID at the rear
of the queue.

Important Variables:
waitingQueue[]
front
rear
*/

void enqueuePatient()
{

}



/*
Function: dequeuePatient()

Purpose:
Remove the next patient for consultation.

Description:
Removes the patientID from the front
of the queue.

Important Variables:
waitingQueue[]
front
rear
*/

void dequeuePatient()
{

}



/*
Function: peekNextPatient()

Purpose:
View the next patient in the queue.

Description:
Displays the patientID at the front
without removing it.
*/

void peekNextPatient()
{

}



/*
Function: displayQueue()

Purpose:
Display all patients waiting in the queue.
*/

void displayQueue()
{

}



/*
Function: queueSize()

Purpose:
Return number of patients in queue.
*/

void queueSize()
{

}



/* ==================================================
   EMERGENCY STACK FUNCTIONS
   ================================================== */

void pushEmergency()
{

}

void popEmergency()
{

}

void peekEmergency()
{

}

void displayEmergencyStack()
{

}

void isEmergencyEmpty()
{

}



/* ==================================================
   TREATMENT FUNCTIONS
   ================================================== */

void addTreatment()
{

}

void deleteTreatment()
{

}

void displayTreatments()
{

}

void searchTreatment()
{

}

void sortTreatmentsByCost()
{

}



/* ==================================================
   DRUG INVENTORY FUNCTIONS
   ================================================== */

void addDrug()
{

}

void updateDrugStock()
{

}

void searchDrug()
{

}

void displayInventory()
{

}

void sortDrugsByName()
{

}



/* ==================================================
   PHARMACY ORDER FUNCTIONS
   ================================================== */

void createOrder()
{

}

void calculatePrice()
{

}

void updateInventoryAfterSale()
{

}

void displayOrders()
{

}

void cancelLastOrder()
{

}



/* ==================================================
   BILLING FUNCTIONS
   ================================================== */

void generateBill()
{

}

void updatePaymentStatus()
{

}

void searchBill()
{

}

void displayBills()
{

}

void sortBillsByAmount()
{

}