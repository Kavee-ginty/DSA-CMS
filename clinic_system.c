#include <stdio.h>
#include <stdlib.h>
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
   1. PATIENT STRUCTURE - Ginodh
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
   2. WAITING QUEUE - Dimanya
   ================================================== */

int waitingQueue[50];
int front = -1;
int rear = -1;


/* ==================================================
   3. EMERGENCY Queue - Dulana
   ================================================== */

struct emergencyNode
{
   int patientID;
   int emergencyScore;
   struct emergencyNode* prev;
   struct emergencyNode* next;
};

struct emergencyQueue
{
   struct emergencyNode* front;
   struct emergencyNode* rear;
};

struct emergencyQueue EMERGENCY_QUEUE;



/* ==================================================
   4. TREATMENT LINKED LIST - Dasun
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
   5. DRUG INVENTORY (DOUBLY LINKED LIST) - Neleesha
   ================================================== */

struct Drug
{
    int drugID;
    char name[50];
    int quantity;
    float unitPrice;

    struct Drug *prev;
    struct Drug *next;
};

/* Head and tail pointers for inventory list */

struct Drug *inventoryHead = NULL;
struct Drug *inventoryTail = NULL;


/* ==================================================
   6. PHARMACY ORDERS - Harsha
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
   7. BILLING STRUCTURE - Methoo
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
   PATIENT FUNCTIONS - Ginodh
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

void addPatient(char name[], int age, char gender[], char contact[])
{
      if(patientCount < 40)
      {
         patients[patientCount].patientID = patientCount + 1; // Auto ID
         strcpy(patients[patientCount].name, name);
         patients[patientCount].age = age;
         strcpy(patients[patientCount].gender, gender);
         strcpy(patients[patientCount].contact, contact);
         patientCount++;
         printf("Patient added successfully with ID: %d\n", patients[patientCount - 1].patientID);
      } else {
         printf("Patient limit reached. Cannot add more patients.\n");
      }
      for (int i = 0; i < patientCount; i++) {
         printf("Patient ID: %d, Name: %s, Age: %d, Gender: %s, Contact: %s\n",
                patients[i].patientID, patients[i].name, patients[i].age, patients[i].gender, patients[i].contact);
      }

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
   QUEUE FUNCTIONS - Dimanya
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
void enqueuePatient(int patientID)
{
   if(rear== 49){
      printf("The patient queue is full! Patient %d cannot be added to the queue.",patientID);
      return;}
    else{
        rear=rear+1;
        waitingQueue[rear]=patientID;
        printf("Patient %d added to the queue successfully \n",patientID);
    }
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
   EMERGENCY QUEUE FUNCTIONS - Dulana
   ================================================== */

void initializeEmergencyQueue(struct emergencyQueue* queue)
{
   queue->front = NULL;
   queue->rear = NULL;
}


struct emergencyNode* createEmergencyNode(int patientID, int emergencyScore)
{
   struct emergencyNode* newNode = (struct emergencyNode*)malloc(sizeof(struct emergencyNode));
   if (newNode == NULL)
   {
      return NULL;
   }
   newNode->patientID = patientID;
   newNode->emergencyScore = emergencyScore;
   newNode->prev = NULL;
   newNode->next = NULL;
   return newNode;
}

/*
Function: isEmergencyEmpty()

Purpose:
Check whether the emergency priority queue is empty.

Description:
This function checks whether any emergency
patients exist in the priority queue.

Returns 1 if the queue is empty (front == NULL),
returns 0 otherwise.

*/

int isEmergencyEmpty(struct emergencyQueue* queue)
{
   if(queue->front == NULL){
      return 1;
   }
   else{
      return 0;
   }
}

/*
Function: enqueueEmergency()

Purpose:
Add a patient to the emergency priority queue.

Description:
This function inserts a patient into the doubly linked
priority queue based on their emergency score (1-3).
Higher scores indicate higher priority and are placed
closer to the front of the queue.

Patients with the same priority are placed behind
existing patients of the same score.

Emergency Score Guide:
3 → Critical   (highest priority)
2 → Urgent
1 → Non-Urgent     (lowest priority)

*/

void enqueueEmergency(struct emergencyQueue* queue, int patientID, int emergencyScore)
{
   if (emergencyScore > 3 || emergencyScore < 1) {
      printf("Invalid Emeregency Condition");
      return;
   }

   struct emergencyNode* newNode;
   newNode = createEmergencyNode(patientID, emergencyScore);
   //empty queue
   if (isEmergencyEmpty(queue) == 1){
      queue->front = newNode;
      queue->rear = newNode;
      return;
   }

   //non emepty queue
   struct emergencyNode* temp;
   temp = queue->rear;
   int enqueued = 0;
   while(!enqueued){
      if(emergencyScore > temp->emergencyScore){
         // if temp has reached to front and want to add node to the front
         if(temp == queue->front){
            temp->prev = newNode;
            newNode->next = temp;
            queue->front = newNode;
            enqueued = 1;
         }
         else{
             temp = temp->prev;
         }
      }
      else{
         //if new node is going to be attached to the rear
         if(temp == queue->rear){
            newNode->prev = temp;
            temp->next = newNode;
            queue->rear = newNode;
            enqueued = 1;
         }
         else{
            newNode->next = temp->next;
            newNode->prev = temp;
            temp->next->prev = newNode;
            temp->next = newNode;
            enqueued = 1;
         }
      }
   }
}

/*
Function: dequeueEmergency()

Purpose:
Remove and return the highest priority emergency patient.

Description:
This function removes the patient at the front of the
emergency priority queue, which is always the patient
with the highest emergency score.

The front pointer is updated to the next node after
removal. Memory of the removed node is freed.

Important Variables:
queue->front
queue->rear
*/

void dequeueEmergency()
{

}

/*
Function: peekEmergency()

Purpose:
View the highest priority emergency patient.

Description:
Displays the patientID and emergency score of the
patient currently at the front of the priority queue
without removing them.

The front of the queue always holds the patient
with the highest emergency score.

Important Variables:
queue->front
*/

void peekEmergency()
{

}

/*
Function: displayEmergencyQueue()

Purpose:
Display all patients in the emergency priority queue.

Description:
Traverses the doubly linked priority queue from
front to rear and prints each patient's ID
in priority order.

The front holds the highest priority patient
and the rear holds the lowest priority patient.

Important Variables:
queue->front
queue->rear
*/

void displayEmergencyQueue(struct emergencyQueue* queue)
{
   if(isEmergencyEmpty(queue) == 1){
      printf("Emergency Queue is empty.\n");
   }
   else{
      struct emergencyNode* temp = queue->front;
      while(temp != NULL){
         printf("Emergency Patient ID: %d\n", temp->patientID);
         temp = temp->next;
      }
   }
}





/* ==================================================
   TREATMENT FUNCTIONS - Dasun
   ================================================== */

/*
Function: addTreatment()

Purpose:
Add a treatment record.

Description:
Creates a new treatment node containing
treatmentID, patientID, treatment name,
and cost.

The node should be inserted into the
treatment linked list.

Important Variables:
treatmentHead → start of treatment list
*/

void addTreatment()
{

}

/*
Function: deleteTreatment()

Purpose:
Remove a treatment record.

Description:
Searches for a treatment using treatmentID
and removes the corresponding node from
the linked list.

The links between nodes must be updated
to maintain list integrity.

Important Variables:
treatmentHead
*/

void deleteTreatment()
{

}

/*
Function: displayTreatments()

Purpose:
Display all treatment records.

Description:
Traverses the linked list starting from
treatmentHead and prints all treatment
details.

Important Variables:
treatmentHead
*/

void displayTreatments()
{

}

/*
Function: searchTreatment()

Purpose:
Find a treatment record.

Description:
Searches the linked list for a treatment
using treatmentID and displays the record
if found.

Important Variables:
treatmentHead
*/

void searchTreatment()
{

}

/*
Function: sortTreatmentsByCost()

Purpose:
Sort treatments based on cost.

Description:
This function should implement Bubble Sort
or another sorting method to arrange
treatments in ascending order of cost.

Important Variables:
treatmentHead
*/

void sortTreatmentsByCost()
{

}



/* ==================================================
   DRUG INVENTORY FUNCTIONS - Neleesha
   ================================================== */

/*
Function: addDrug()

Purpose:
Insert a new drug into the inventory.

Description:
Creates a new Drug node containing drugID,
name, quantity, and unit price.

The node should be inserted into the
doubly linked list while updating
prev and next pointers.

Important Variables:
inventoryHead
inventoryTail
*/

void addDrug()
{

}

/*
Function: updateDrugStock()

Purpose:
Update quantity of a drug.

Description:
Searches the inventory list using drugID
and updates the available quantity after
restocking or corrections.

Important Variables:
inventoryHead
*/

void updateDrugStock()
{

}

/*
Function: searchDrug()

Purpose:
Find a drug in the inventory.

Description:
Traverses the doubly linked list to locate
a drug using drugID or name and displays
its details.

Important Variables:
inventoryHead
*/

void searchDrug()
{

}

/*
Function: displayInventory()

Purpose:
Display all medicines in inventory.

Description:
Traverses the doubly linked list from
inventoryHead to inventoryTail and
prints all drug information.

Important Variables:
inventoryHead
inventoryTail
*/

void displayInventory()
{

}

/*
Function: sortDrugsByName()

Purpose:
Sort drugs alphabetically.

Description:
Sorts the inventory list based on drug name.
Nodes may be rearranged or data swapped
to maintain sorted order.

Important Variables:
inventoryHead
*/

void sortDrugsByName()
{

}



/* ==================================================
   PHARMACY ORDER FUNCTIONS - Harsha
   ================================================== */

/*
Function: createOrder()

Purpose:
Record a medicine purchase.

Description:
Creates a pharmacy order for a patient
including drug name and quantity.

The order is pushed onto the pharmacyStack.

Important Variables:
pharmacyStack[]
pharmacyTop
*/

void createOrder()
{
   int 

}

/*
Function: calculatePrice()

Purpose:
Calculate total order cost.

Description:
This function retrieves the unit price
from the inventory and multiplies it
by the quantity purchased to determine
the total price.

Important Variables:
pharmacyStack[]
inventoryHead
*/

void calculatePrice()
{

}

/*
Function: updateInventoryAfterSale()

Purpose:
Reduce inventory after medicine sale.

Description:
After an order is confirmed, this function
reduces the quantity of the corresponding
drug in the inventory list.

Important Variables:
inventoryHead
*/

void updateInventoryAfterSale()
{

}

/*
Function: displayOrders()

Purpose:
Display pharmacy order history.

Description:
Prints all pharmacy orders currently
stored in the pharmacy stack.

Important Variables:
pharmacyStack[]
pharmacyTop
*/

void displayOrders()
{

}

/*
Function: cancelLastOrder()

Purpose:
Undo the most recent pharmacy order.

Description:
Removes the top element from the
pharmacy stack and restores inventory
if necessary.

Important Variables:
pharmacyStack[]
pharmacyTop
*/

void cancelLastOrder()
{

}


/* ==================================================
   BILLING FUNCTIONS  - Methoo
   ================================================== */

/*
Function: generateBill()

Purpose:
Create a billing record.

Description:
Generates a bill for a patient including
treatment costs and pharmacy purchases.

The bill is stored in the bills array.

Important Variables:
bills[]
billCount
*/

void generateBill()
{

}

/*
Function: updatePaymentStatus()

Purpose:
Update payment information.

Description:
Allows the payment status of a bill
to be updated (for example Paid,
Pending, or Cancelled).

Important Variables:
bills[]
billCount
*/

void updatePaymentStatus()
{

}

/*
Function: searchBill()

Purpose:
Find a specific bill.

Description:
Searches the bills array using billID
and displays billing information.

Important Variables:
bills[]
billCount
*/

void searchBill()
{

}

/*
Function: displayBills()

Purpose:
Display all billing records.

Description:
Prints all bills stored in the bills array.

Important Variables:
bills[]
billCount
*/

void displayBills()
{

}

/*
Function: sortBillsByAmount()

Purpose:
Sort billing records.

Description:
Uses Bubble Sort to arrange bills
in ascending order based on amount.

Important Variables:
bills[]
billCount
*/

void sortBillsByAmount()
{

}


int main()
{

    int choice;
    initializeEmergencyQueue(&EMERGENCY_QUEUE);

    while(1)
    {
        printf("\n==== CLINIC MANAGEMENT SYSTEM ====\n");

        printf("1 Add Patient\n");
        printf("2 Delete Patient\n");
        printf("3 Search Patient\n");
        printf("4 Update Patient\n");
        printf("5 Sort Patients\n");

        printf("6 Add to Waiting Queue\n");
        printf("7 Treat Next Patient\n");

        printf("8 Emergency Patient\n");

        printf("9 Add Treatment\n");

        printf("10 Pharmacy Order\n");

        printf("11 Generate Bill\n");

        printf("0 Exit\n");

        printf("Enter choice: ");
        scanf("%d",&choice);
        getchar();

        
        int patientID;
        char name[50];
        int age;
        char gender[10];
        char contact[20];


        switch(choice)
        {
            
            case 1:
                printf("Adding new patient...\n");
                printf("Enter patient details:\n");
                printf("Patient Name: ");
                fflush(stdin);
                fgets(name, sizeof(name), stdin);
                size_t len = strlen(name);
                if (len > 0 && name[len - 1] == '\n') {
                    name[len - 1] = '\0';
                }
                printf("Patient Age: ");
                scanf("%d", &age);
                getchar(); 
                printf("Patient Gender [M/F]: ");
                fgets(gender, sizeof(gender), stdin);
                len = strlen(gender);
                if (len > 0 && gender[len - 1] == '\n') {
                    gender[len - 1] = '\0';
                }
                printf("Patient Contact: ");
                fgets(contact, sizeof(contact), stdin);
                len = strlen(contact);
                if (len > 0 && contact[len - 1] == '\n') {
                    contact[len - 1] = '\0';
                }
                addPatient(name, age, gender, contact);
                break;
            case 2: deletePatient(); break;
            case 3: searchPatient(); break;
            case 4: updatePatient(); break;
            case 5: sortPatients(); break;

            case 6: 
               printf("Enter Patient ID to add to waiting queue: ");
               scanf("%d", &patientID);
               enqueuePatient(patientID);
               break;
            case 7: dequeuePatient(); break;

            case 8: 
                printf("--INSERT PATIENT TO EMERGENCY PRIORITY QUEUE--\n");
                printf("Enter Emergency Patient ID: ");
                int emergencyPatientID;
                scanf(" %d", &emergencyPatientID);
                if(emergencyPatientID < 1 || emergencyPatientID > patientCount){
                    printf("Invalid ID\n");
                    break;
                }
                printf("Enter Emergency condition:\nCritical: 3\nUrgent: 2\nNon-Urgent: 1\n");
                int emergencyScore;
                if (scanf(" %d", &emergencyScore) != 1) {
                    printf("Invalid emergency condition input\n");
                    break;
                }
                if (emergencyScore < 1 || emergencyScore > 3) {
                    printf("Invalid emergency condition score. Please enter 1, 2, or 3.\n");
                    break;
                }
                printf("Inserting...\n");
                enqueueEmergency(&EMERGENCY_QUEUE, emergencyPatientID, emergencyScore); 
                printf("Inserted.\nCurrent Queue:\n");
                displayEmergencyQueue(&EMERGENCY_QUEUE);
                break;

            case 9: addTreatment(); break;

            case 10: createOrder(); break;

            case 11: generateBill(); break;

            case 0: return 0;

            default: printf("Invalid option\n");
        }

    }

}
