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
        {1, "Alice", 25, "F", "0711111111"},
        {2, "Bob", 30, "M", "0711111112"},
        {3, "Charlie", 28, "M", "0711111113"},
        {4, "Diana", 32, "F", "0711111114"},
        {5, "Ethan", 40, "M", "0711111115"},
        {6, "Fiona", 22, "F", "0711111116"},
        {7, "George", 35, "M", "0711111117"},
        {8, "Hannah", 29, "F", "0711111118"},
        {9, "Ian", 31, "M", "0711111119"},
        {10, "Jane", 26, "F", "0711111120"},
        {11, "Kevin", 38, "M", "0711111121"},
        {12, "Lily", 24, "F", "0711111122"},
        {13, "Mike", 45, "M", "0711111123"},
        {14, "Nina", 27, "F", "0711111124"},
        {15, "Oscar", 36, "M", "0711111125"},
        {16, "Paula", 34, "F", "0711111126"},
        {17, "Quinn", 33, "M", "0711111127"},
        {18, "Rita", 28, "F", "0711111128"},
        {19, "Sam", 41, "M", "0711111129"},
        {20, "Tina", 23, "F", "0711111130"}};

int patientCount = 20;

/* ==================================================
   2. WAITING QUEUE - Dimanya
   ================================================== */

#define MAX_QUEUE_SIZE 50

struct waitingNode {
    int patientID;
    char name[50];
    struct waitingNode* prev;
    struct waitingNode* next;
};

struct Queue {
    struct waitingNode* front;
    struct waitingNode* rear;
    int size; // optional
};

struct Queue clinicQueue;

/* ==================================================
   3. EMERGENCY Queue - Dulana
   ================================================== */

struct emergencyNode
{
   int patientID;
   int emergencyScore;
   struct emergencyNode *prev;
   struct emergencyNode *next;
};

struct emergencyQueue
{
   struct emergencyNode *front;
   struct emergencyNode *rear;
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

void initializeDummyDrugs() {
    // Array of dummy data
    struct Drug dummyDrugs[10] = {
        {1, "Paracetamol", 100, 2.50, NULL, NULL},
        {2, "Amoxicillin", 50, 5.00, NULL, NULL},
        {3, "Ibuprofen", 200, 3.20, NULL, NULL},
        {4, "Cetirizine", 150, 1.50, NULL, NULL},
        {5, "Omeprazole", 80, 4.75, NULL, NULL},
        {6, "Aspirin", 300, 1.80, NULL, NULL},
        {7, "Loratadine", 120, 2.00, NULL, NULL},
        {8, "Metformin", 90, 5.50, NULL, NULL},
        {9, "Azithromycin", 60, 8.00, NULL, NULL},
        {10, "Diclofenac", 110, 3.50, NULL, NULL}
    };

    // Insert them into linked list 
    for(int i = 0; i < 10; i++) {
        struct Drug* newDrug = (struct Drug*)malloc(sizeof(struct Drug));
        *newDrug = dummyDrugs[i];
        
        if (inventoryHead == NULL) {
            inventoryHead = newDrug;
            inventoryTail = newDrug;
        } else {
            inventoryTail->next = newDrug;
            newDrug->prev = inventoryTail;
            inventoryTail = newDrug;
        }
    }
}


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
   if (patientCount < 40)
   {
      patients[patientCount].patientID = patientCount + 1; // Auto ID
      strcpy(patients[patientCount].name, name);
      patients[patientCount].age = age;
      strcpy(patients[patientCount].gender, gender);
      strcpy(patients[patientCount].contact, contact);
      patientCount++;
      printf("Patient added successfully with ID: %d\n", patients[patientCount - 1].patientID);
   }
   else
   {
      printf("Patient limit reached. Cannot add more patients.\n");
   }
   for (int i = 0; i < patientCount; i++)
   {
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

void deletePatient(int patientID)
{
   for (int i = 0; i < patientCount; i++)
   {
      if (patients[i].patientID == patientID)
      {
         for (int j = i; j < patientCount - 1; j++)
         {
            patients[j] = patients[j + 1];
         }
         patientCount--;
         printf("Patient with ID %d deleted successfully.\n", patientID);
         return;
      }
   }
   printf("Patient with ID %d not found.\n", patientID);

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

void searchPatient(int patientID)
{
   for (int i = 0; i < patientCount; i++)
   {
      if (patients[i].patientID == patientID)
      {
         printf("Patient ID: %d, Name: %s, Age: %d, Gender: %s, Contact: %s\n",
                patients[i].patientID, patients[i].name, patients[i].age, patients[i].gender, patients[i].contact);
         return;
      }
   }
   printf("Patient with ID %d not found.\n", patientID);
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

void updatePatient(int patientID, char newName[], char newContact[])
{
   for (int i = 0; i < patientCount; i++)
   {
      if (patients[i].patientID == patientID)
      {
         if (strlen(newName) > 0) {
             strcpy(patients[i].name, newName);
         } if (strlen(newContact) > 0) {
             strcpy(patients[i].contact, newContact);
         }
         printf("Patient with ID %d updated successfully.\n", patientID);
         return;
      }
   }
   printf("Patient with ID %d not found.\n", patientID);
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

void sortPatients(struct Patient patients[], int patientCount)
{
   for (int i = 0; i < patientCount - 1; i++)
   {
      int minIndex = i;
      for (int j = i + 1; j < patientCount; j++)
      {
         if (strcmp(patients[j].name, patients[minIndex].name) < 0)
         {
            minIndex = j;
         }
      }
      if (minIndex != i)
      {
         struct Patient temp = patients[i];
         patients[i] = patients[minIndex];
         patients[minIndex] = temp;
      }
   }
   printf("Patients sorted alphabetically by name.\n");
}

void printPratients()
{
   for (int i = 0; i < patientCount; i++)
   {
      printf("Patient ID: %d, Name: %s, Age: %d, Gender: %s, Contact: %s\n",
             patients[i].patientID, patients[i].name, patients[i].age, patients[i].gender , patients[i].contact);
   } 
}

/* ==================================================
   QUEUE FUNCTIONS - Dimanya
   ================================================== */
void initializeWaitingQueue(struct Queue* queue) {
    queue->front = NULL;
    queue->rear = NULL;
    queue->size = 0;
}

struct waitingNode* createWaitingPatientNode(int patientID, char name[]) {
    struct waitingNode* newNode = (struct waitingNode*)malloc(sizeof(struct waitingNode));
    if (newNode == NULL) {
        return NULL;
    }
    newNode->patientID = patientID;
    strcpy(newNode->name, name);
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}
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
void enqueuePatient(struct Queue* queue, int patientID) {
    int exists = 0;
    for (int i = 0; i < patientCount; i++) {
        if (patients[i].patientID == patientID) {
            exists = 1;
            break;
        }
    }
    if (!exists) {
        printf("Patient ID %d is not registered. Cannot add to the queue.\n", patientID);
        return;
    }
    if (queue->size >= MAX_QUEUE_SIZE) {
        printf("The patient queue is full! Patient %d cannot be added.\n", patientID);
        return;
    }

    struct waitingNode* newNode = createWaitingPatientNode(patientID, patients[patientID - 1].name);
    if (newNode == NULL) {
        printf("Memory allocation failed for patient %d\n", patientID);
        return;
    }

    if (queue->front == NULL) {  // empty queue
        queue->front = newNode;
        queue->rear = newNode;
    } else {  // add to rear
        queue->rear->next = newNode;
        newNode->prev = queue->rear;
        queue->rear = newNode;
    }

    queue->size++;
    printf("Patient %d - %s added to the queue successfully.\n", patientID, newNode->name);
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

void dequeuePatient(struct Queue* queue)
{
    if (queue->front == NULL) {
        printf("Queue is empty. No patient to remove.\n");
        return;
    }

    struct waitingNode* temp = queue->front;

    printf("Patient %d - %s removed from the queue.\n", temp->patientID, temp->name);

    // Move front to next node
    queue->front = queue->front->next;

    // If queue is not empty, update prev pointer
    if (queue->front != NULL) {
        queue->front->prev = NULL;
    } else {
        // If queue becomes empty, rear should also be NULL
        queue->rear = NULL;
    }

    free(temp); // free memory
    queue->size--;
}

/*
Function: peekNextPatient()

Purpose:
View the next patient in the queue.

Description:
Displays the patientID at the front
without removing it.
*/

int peekNextPatient(struct Queue* queue)
{
    if (queue->front == NULL) {
        printf("Queue is empty\n");
        return '\0';
    } else {
        printf("Next patient in queue: ID %d - %s\n", queue->front->patientID, queue->front->name);
         return queue->front->patientID;
    }
}

/*
Function: displayQueue()

Purpose:
Display all patients waiting in the queue.
*/

void displayQueue(struct Queue* queue) {
    if(queue->front == NULL){
        printf("The waiting queue is empty.\n");
        return;
    }

    printf("Patients in the waiting queue:\n");
    struct waitingNode* temp = queue->front;
    while(temp != NULL){
        printf("Patient ID: %d , Name: %s\n", temp->patientID, temp->name);
        temp = temp->next;
    }
}

/*
Function: queueSize()

Purpose:
Return number of patients in queue.
*/

int queueSize(struct Queue* queue)
{
    int count = 0;
    struct waitingNode* temp = queue->front;
    while(temp != NULL) {
        count++;
        temp = temp->next;
    }
    return count;
}

/* ==================================================
   EMERGENCY QUEUE FUNCTIONS - Dulana
   ================================================== */

void initializeEmergencyQueue(struct emergencyQueue *queue)
{
   queue->front = NULL;
   queue->rear = NULL;
}

struct emergencyNode *createEmergencyNode(int patientID, int emergencyScore)
{
   struct emergencyNode *newNode = (struct emergencyNode *)malloc(sizeof(struct emergencyNode));
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

int isEmergencyEmpty(struct emergencyQueue *queue)
{
   if (queue->front == NULL)
   {
      return 1;
   }
   else
   {
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

void enqueueEmergency(struct emergencyQueue *queue, int patientID, int emergencyScore)
{
   if (emergencyScore > 3 || emergencyScore < 1)
   {
      printf("Invalid Emeregency Condition");
      return;
   }

   struct emergencyNode *newNode;
   newNode = createEmergencyNode(patientID, emergencyScore);
   // empty queue
   if (isEmergencyEmpty(queue) == 1)
   {
      queue->front = newNode;
      queue->rear = newNode;
      return;
   }

   // non emepty queue
   struct emergencyNode *temp;
   temp = queue->rear;
   int enqueued = 0;
   while (!enqueued)
   {
      if (emergencyScore > temp->emergencyScore)
      {
         // if temp has reached to front and want to add node to the front
         if (temp == queue->front)
         {
            temp->prev = newNode;
            newNode->next = temp;
            queue->front = newNode;
            enqueued = 1;
         }
         else
         {
            temp = temp->prev;
         }
      }
      else
      {
         // if new node is going to be attached to the rear
         if (temp == queue->rear)
         {
            newNode->prev = temp;
            temp->next = newNode;
            queue->rear = newNode;
            enqueued = 1;
         }
         else
         {
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

void displayEmergencyQueue(struct emergencyQueue *queue)
{
   if (isEmergencyEmpty(queue) == 1)
   {
      printf("Emergency Queue is empty.\n");
   }
   else
   {
      struct emergencyNode *temp = queue->front;
      while (temp != NULL)
      {
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
    
    struct Drug* newDrug = (struct Drug*)malloc(sizeof(struct Drug));

    printf("Enter Drug ID: ");
    scanf("%d", &newDrug->drugID);

    printf("Enter Drug Name (no spaces): ");
    scanf("%s", newDrug->name); 

    printf("Enter Quantity: ");
    scanf("%d", &newDrug->quantity);

    printf("Enter Unit Price: ");
    scanf("%f", &newDrug->unitPrice);

    newDrug->next = NULL;
    newDrug->prev = NULL;

    if (inventoryHead == NULL) {
        inventoryHead = inventoryTail = newDrug;
    } else {
        inventoryTail->next = newDrug;
        newDrug->prev = inventoryTail;
        inventoryTail = newDrug;
    }

    printf("Drug added successfully!\n");
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
    int id, newQty;
    printf("Enter Drug ID: ");
    scanf("%d", &id);

    struct Drug* temp = inventoryHead;

    while (temp != NULL) {
        if (temp->drugID == id) {
            printf("Enter new quantity: ");
            scanf("%d", &newQty);
            if(newQty < 0) {
                printf("Invalid quantity!\n"); 
                return; }
            else{
            temp->quantity = newQty;

            printf("Stock updated!\n");
            return; }
        }
        temp = temp->next;
    }

    printf("Drug not found!\n");
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
    int id;
    printf("Enter Drug ID to search: ");
    scanf("%d", &id);

    struct Drug* temp = inventoryHead;

    while (temp != NULL) {
        if (temp->drugID == id) {
            printf("Found: %s | Qty: %d | Price: %.2f\n",
                   temp->name, temp->quantity, temp->unitPrice);
            return;
        }
        temp = temp->next;
    }

    printf("Drug not found!\n");
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
    struct Drug* temp = inventoryHead;

    if (temp == NULL) {
        printf("Inventory is empty!\n");
        return;
    }

    printf("\n--- Drug Inventory ---\n");

    while (temp != NULL) {
        printf("ID: %d | Name: %s | Qty: %d | Price: %.2f\n",
               temp->drugID, temp->name, temp->quantity, temp->unitPrice);
        temp = temp->next;
    }
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
    if (inventoryHead == NULL) {
        printf("Inventory is empty!\n");
        return;
    }

    int swapped;
    struct Drug* ptr;

    do {
        swapped = 0;
        ptr = inventoryHead;

        while (ptr->next != NULL) {

            if (strcmp(ptr->name, ptr->next->name) > 0) {

                // Swap ONLY data (not pointers)
                int tempID = ptr->drugID;
                char tempName[50];
                int tempQty = ptr->quantity;
                float tempPrice = ptr->unitPrice;

                strcpy(tempName, ptr->name);

                ptr->drugID = ptr->next->drugID;
                strcpy(ptr->name, ptr->next->name);
                ptr->quantity = ptr->next->quantity;
                ptr->unitPrice = ptr->next->unitPrice;

                ptr->next->drugID = tempID;
                strcpy(ptr->next->name, tempName);
                ptr->next->quantity = tempQty;
                ptr->next->unitPrice = tempPrice;

                swapped = 1;
            }

            ptr = ptr->next;
        }

    } while (swapped);

    printf("Drugs sorted by name (A-Z)!\n");
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
   printf("\n--- Available Drugs ---\n");
   struct Drug *temp = inventoryHead;
   if (temp == NULL)
   {
      printf("No drugs available in inventory.\n");
      return; // Exit early since user can't order anything
   }
   else{
   
      while (temp != NULL)
      {
         printf("ID: %d | Name: %s | Qty: %d | Price: %.2f\n", 
                temp->drugID, temp->name, temp->quantity, temp->unitPrice);
         temp = temp->next;
      }
   }
   printf("-----------------------\n");

   int pID;
   printf("\nEnter Patient ID: ");
   scanf("%d", &pID);
   getchar(); // Consume trailing newline

   char addMore;
   do {
      if (pharmacyTop >= 49)
      {
         printf("Pharmacy stack is full! Cannot add more orders.\n");
         break;
      }

      int dID, qty;
      printf("\nEnter Drug ID: ");
      scanf("%d", &dID);

      // Validation: Find the drug name string by ID
      char dName[50] = "";
      temp = inventoryHead;
      int found = 0;
      while(temp != NULL) {
         if (temp->drugID == dID) {
            strcpy(dName, temp->name);
            found = 1;
            break;
         }
         temp = temp->next;
      }

      if (!found) {
         printf("Invalid Drug ID! Order for this ID cancelled.\n");
         getchar(); 
      } else {
         printf("Enter Quantity: ");
         scanf("%d", &qty);
         getchar(); // Consume trailing newline

         pharmacyTop++;
         pharmacyStack[pharmacyTop].patientID = pID; // Assigned patient ID
         strcpy(pharmacyStack[pharmacyTop].drugName, dName); // Still storing Name in order struct
         pharmacyStack[pharmacyTop].quantity = qty;
         pharmacyStack[pharmacyTop].totalPrice = 0.0;

         printf("Pharmacy order for '%s' created successfully for Patient %d.\n", dName, pID);
      }

      printf("\nDo you want to add another drug? (Y/N): ");
      scanf(" %c", &addMore);
      getchar(); // Consume trailing newline
   } while (addMore == 'Y' || addMore == 'y');
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
   if (pharmacyTop == -1)
   {
      printf("No orders to calculate price for.\n");
      return;
   }

   float grandTotal = 0.0;
   printf("\n--- Calculated Prices ---\n");

   for (int i = 0; i <= pharmacyTop; i++) 
   {
      struct PharmacyOrder *order = &pharmacyStack[i];
      struct Drug *temp = inventoryHead;
      int found = 0;

      while (temp != NULL)
      {
         if (strcmp(temp->name, order->drugName) == 0)
         {
            order->totalPrice = temp->unitPrice * order->quantity;
            printf(" - %d x %s: %.2f\n", order->quantity, order->drugName, order->totalPrice);
            grandTotal += order->totalPrice;
            found = 1;
            break;
         }
         temp = temp->next;
      }

      if (!found)
      {
         printf(" - Error: Drug '%s' not found in inventory.\n", order->drugName);
      }
   }

   printf("-------------------------\n");
   printf("GRAND TOTAL FOR ALL ORDERS: %.2f\n", grandTotal);
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
   if (pharmacyTop == -1)
   {
      printf("No orders to process.\n");
      return;
   }

   printf("\n--- Updating Inventory ---\n");
   for (int i = 0; i <= pharmacyTop; i++)
   {
      struct PharmacyOrder *order = &pharmacyStack[i];
      struct Drug *temp = inventoryHead;
      int found = 0;

      while (temp != NULL)
      {
         if (strcmp(temp->name, order->drugName) == 0)
         {
            if (temp->quantity >= order->quantity)
            {
               temp->quantity -= order->quantity;
               printf("Updated %s: %d remaining.\n", temp->name, temp->quantity);
            }
            else
            {
               printf("Warning: Insufficient stock for %s! Have %d, order requires %d.\n", 
                      temp->name, temp->quantity, order->quantity);
            }
            found = 1;
            break;
         }
         temp = temp->next;
      }

      if (!found)
      {
         printf("Error: Drug '%s' not found in inventory to update.\n", order->drugName);
      }
   }
   printf("--------------------------\n");
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
   if (pharmacyTop == -1)
   {
      printf("No pharmacy orders in the history yet.\n");
      return;
   }

   printf("\n====== PHARMACY ORDER HISTORY ======\n");
   for (int i = pharmacyTop; i >= 0; i--) // Displaying from most recent to oldest
   {
      printf("Patient ID: %d | Drug: %s | Qty: %d | Total: %.2f\n",
             pharmacyStack[i].patientID,
             pharmacyStack[i].drugName,
             pharmacyStack[i].quantity,
             pharmacyStack[i].totalPrice);
   }
   printf("====================================\n\n");
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
   if (pharmacyTop == -1)
   {
      printf("No orders to cancel.\n");
      return;
   }

   struct PharmacyOrder *lastOrder = &pharmacyStack[pharmacyTop];

   // Optional: Provide a feature to add stock back to inventory if this order already deducted it.
   // But since it's just canceling from the stack:
   
   printf("Cancelled the last order for Patient %d (Drug: %s, Qty: %d).\n", 
          lastOrder->patientID, lastOrder->drugName, lastOrder->quantity);
          
   // Reduce the top counter to remove the order
   pharmacyTop--;
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
   int patientID;
   char name[50];
   int age;
   char gender[10];
   char contact[20];
   int choice, workflow;
   initializeEmergencyQueue(&EMERGENCY_QUEUE);
   initializeDummyDrugs();

   //  while(1)
   // {
   //    printf("\n==== CLINIC MANAGEMENT SYSTEM ====\n");

   //    printf("1 Add Patient\n");
   //    printf("2 Delete Patient\n");
   //    printf("3 Search Patient\n");
   //    printf("4 Update Patient\n");
   //    printf("5 Sort Patients\n");

   //    printf("6 Add to Waiting Queue\n");
   //    printf("7 Treat Next Patient\n");

   //    printf("8 Emergency Patient\n");

   //    printf("9 Add Treatment\n");

   //    printf("10 Pharmacy Order\n");

   //    printf("11 Generate Bill\n");

   //    printf("0 Exit\n");

   //    printf("Enter choice: ");
   //    scanf("%d", &choice);
   //    getchar();

   //    switch (choice)
   //    {

   //    case 1:
   //       printf("Adding new patient...\n");
   //       printf("Enter patient details:\n");
   //       printf("Patient Name: ");
   //       fflush(stdin);
   //       fgets(name, sizeof(name), stdin);
   //       size_t len = strlen(name);
   //       if (len > 0 && name[len - 1] == '\n')
   //       {
   //          name[len - 1] = '\0';
   //       }
   //       printf("Patient Age: ");
   //       scanf("%d", &age);
   //       getchar();
   //       printf("Patient Gender [M/F]: ");
   //       fgets(gender, sizeof(gender), stdin);
   //       len = strlen(gender);
   //       if (len > 0 && gender[len - 1] == '\n')
   //       {
   //          gender[len - 1] = '\0';
   //       }
   //       printf("Patient Contact: ");
   //       fgets(contact, sizeof(contact), stdin);
   //       len = strlen(contact);
   //       if (len > 0 && contact[len - 1] == '\n')
   //       {
   //          contact[len - 1] = '\0';
   //       }
   //       addPatient(name, age, gender, contact);
   //       break;
   //    case 2:
   //       deletePatient();
   //       break;
   //    case 3:
   //       searchPatient();
   //       break;
   //    case 4:
   //       updatePatient();
   //       break;
   //    case 5:
   //       sortPatients();
   //       break;

   //    case 6:
   //       printf("Enter Patient ID to add to waiting queue: ");
   //       scanf("%d", &patientID);
   //       enqueuePatient(patientID);
   //       break;
   //    case 7:
   //       dequeuePatient();
   //       break;

   //    case 8:
   //       printf("--INSERT PATIENT TO EMERGENCY PRIORITY QUEUE--\n");
   //       printf("Enter Emergency Patient ID: ");
   //       int emergencyPatientID;
   //       scanf(" %d", &emergencyPatientID);
   //       if (emergencyPatientID < 1 || emergencyPatientID > patientCount)
   //       {
   //          printf("Invalid ID\n");
   //          break;
   //       }
   //       printf("Enter Emergency condition:\nCritical: 3\nUrgent: 2\nNon-Urgent: 1\n");
   //       int emergencyScore;
   //       if (scanf(" %d", &emergencyScore) != 1)
   //       {
   //          printf("Invalid emergency condition input\n");
   //          break;
   //       }
   //       if (emergencyScore < 1 || emergencyScore > 3)
   //       {
   //          printf("Invalid emergency condition score. Please enter 1, 2, or 3.\n");
   //          break;
   //       }
   //       printf("Inserting...\n");
   //       enqueueEmergency(&EMERGENCY_QUEUE, emergencyPatientID, emergencyScore);
   //       printf("Inserted.\nCurrent Queue:\n");
   //       displayEmergencyQueue(&EMERGENCY_QUEUE);
   //       break;

   //    case 9:
   //       addTreatment();
   //       break;

   //    case 10:
   //       createOrder();
   //       break;

   //    case 11:
   //       generateBill();
   //       break;

   //    case 0:
   //       return 0;

   //    default:
   //       printf("Invalid option\n");
   //    }
   // }

   while (1)
   {
      printf("\nSelect workflow:\n");
      printf("1. Patient Registration\n");
      printf("2. Waiting queue management\n");
      printf("3. Emergency case handling\n");
      printf("4. Treatment record management\n");
      printf("5. Pharmacy inventory management\n");
      printf("6. Medicine Purchase Tracking\n");
      printf("7. Billing and payment processing\n");
      printf("Enter choice: ");
      scanf("%d", &workflow);
      switch (workflow)
      {
      case 1:
         while (1)
         {
            printf("\nPatient Registration Workflow\n");
            printf("1: Add Patient\n");
            printf("2: Delete Patient\n");
            printf("3: Search Patient\n");
            printf("4: Update Patient\n");
            printf("5: Sort Patients\n");
            printf("6: Print Patients\n");
            printf("0: Exit Patient Registration Workflow\n");
            printf("Enter choice: ");
            scanf("%d", &choice);
            switch (choice)
            {
            case 1:
               printf("Adding new patient...\n");
               printf("Enter patient details:\n");
               printf("Patient Name: ");
               getchar();
               fflush(stdin);
               fgets(name, sizeof(name), stdin);
               size_t len = strlen(name);
               if (len > 0 && name[len - 1] == '\n')
               {
                  name[len - 1] = '\0';
               }
               printf("Patient Age: ");
               scanf("%d", &age);
               getchar();
               printf("Patient Gender [M/F]: ");
               fgets(gender, sizeof(gender), stdin);
               len = strlen(gender);
               if (len > 0 && gender[len - 1] == '\n')
               {
                  gender[len - 1] = '\0';
               }
               printf("Patient Contact: ");
               fgets(contact, sizeof(contact), stdin);
               len = strlen(contact);
               if (len > 0 && contact[len - 1] == '\n')
               {
                  contact[len - 1] = '\0';
               }
               addPatient(name, age, gender, contact);
               break;
            case 2:
               printf("Enter Patient ID to delete: ");
               scanf("%d", &patientID);
               deletePatient(patientID);
               break;
            case 3:
               printf("Enter Patient ID to search: ");
               scanf("%d", &patientID);
               searchPatient(patientID);
               break;
            case 4:
               printf("Enter Patient ID to update: ");
               scanf("%d", &patientID);
               char newName[50];
               char newContact[20];
               printf("Enter new name: ");
               getchar();
               fflush(stdin);
               fgets(newName, sizeof(newName), stdin);
               size_t newLen = strlen(newName);
               if (newLen > 0 && newName[newLen - 1] == '\n')
               {
                  newName[newLen - 1] = '\0';
               }
               printf("Enter new contact: ");
               fgets(newContact, sizeof(newContact), stdin);
               size_t newContactLen = strlen(newContact);
               if (newContactLen > 0 && newContact[newContactLen - 1] == '\n')
               {
                  newContact[newContactLen - 1] = '\0';
               }
               updatePatient(patientID, newName, newContact);
               break;
            case 5:
               sortPatients(patients, patientCount);
               break;
            case 6:
               printf("Print patients list");
               printPratients();
               break;
            case 0:
               printf("Returning to Main Menu...\n");
               break;
            default:
               printf("Invalid option\n");
            }
            if (choice == 0)
               break;
         }
         break;
      case 2:
         while (1)
         {
            printf("\nWaiting Queue Management Workflow\n");
            printf("1: Add to Waiting Queue\n");
            printf("2: Treat Next Patient\n");
            printf("3: View Next Patient\n");
            printf("4: Display Waiting Queue\n");
            printf("5: Get Queue Size\n");
            printf("0: Exit Waiting Queue Management Workflow\n");
            printf("Enter choice: ");
            scanf("%d", &choice);
            switch (choice)
            {
            case 1:
            {
               printf("Enter Patient ID to add to waiting queue: ");
               int patientID;
               scanf("%d", &patientID);
               enqueuePatient(&clinicQueue, patientID);
               break;
            }
            case 2:
               dequeuePatient(&clinicQueue);
               break;
            case 3:
            {
               peekNextPatient(&clinicQueue);
               break;
            }
            case 4:
               displayQueue(&clinicQueue);
               break;
            case 5:
            {
               int queuecount = queueSize(&clinicQueue);
               printf("Number of patients in queue: %d\n", queuecount);
               break;
            }
            case 0:
               printf("Returning to Main Menu...\n");
                break;;
            default:
               printf("Invalid option\n");
            }
            if (choice == 0)
               break;
         }
         break;
      case 3:
         while (1)
         {
            printf("\nEmergency Case Handling Workflow\n");
            printf("1: Check queue is empty\n");
            printf("2: Add Emergency Patient\n");
            printf("3: Treat Next Emergency Patient\n");
            printf("4: View Highest Priority Emergency Patient\n");
            printf("5: Display Emergency Queue\n");
            printf("0: Exit Emergency Case Handling Workflow\n");
            printf("Enter choice: ");
            scanf("%d", &choice);
            switch (choice)
            {
            case 1:
               isEmergencyEmpty(&EMERGENCY_QUEUE);
               break;
            case 2:
               printf("--INSERT PATIENT TO EMERGENCY PRIORITY QUEUE--\n");
               printf("Enter Emergency Patient ID: ");
               int emergencyPatientID;
               scanf(" %d", &emergencyPatientID);
               if (emergencyPatientID < 1 || emergencyPatientID > patientCount)
               {
                  printf("Invalid ID\n");
                  break;
               }
               printf("Enter Emergency condition:\nCritical: 3\nUrgent: 2\nNon-Urgent: 1\n");
               int emergencyScore;
               if (scanf(" %d", &emergencyScore) != 1)
               {
                  printf("Invalid emergency condition input\n");
                  break;
               }
               if (emergencyScore < 1 || emergencyScore > 3)
               {
                  printf("Invalid emergency condition score. Please enter 1, 2, or 3.\n");
                  break;
               }
               printf("Inserting...\n");
               enqueueEmergency(&EMERGENCY_QUEUE, emergencyPatientID, emergencyScore);
               printf("Inserted.\nCurrent Queue:\n");
               displayEmergencyQueue(&EMERGENCY_QUEUE);
               break;
            case 3:
               dequeueEmergency();
               break;
            case 4:
               peekEmergency();
               break;
            case 5:
               displayEmergencyQueue(&EMERGENCY_QUEUE);
               break;
            case 0:
               printf("Returning to Main Menu...\n");
                break;;
            default:
               printf("Invalid option\n");
            }
            if (choice == 0)
               break;
         }

         break;
      case 4:
         while (1)
         {
            printf("\nTreatment Record Management Workflow\n");
            printf("1: Add Treatment\n");
            printf("2: Delete Treatment\n");
            printf("3: Display Treatments\n");
            printf("4: Search Treatment\n");
            printf("5: Sort Treatments by Cost\n");
            printf("0: Exit Treatment Record Management Workflow\n");
            printf("Enter choice: ");
            scanf("%d", &choice);
            switch (choice)
            {
            case 1:
               addTreatment();
               break;
            case 2:
               deleteTreatment();
               break;
            case 3:
               displayTreatments();
               break;
            case 4:
               searchTreatment();
               break;
            case 5:
               sortTreatmentsByCost();
               break;
            case 0:
               printf("Returning to Main Menu...\n");
                break;;
            default:
               printf("Invalid option\n");
            }
            if (choice == 0)
               break;
         }
         break;
      case 5:
         while (1)
         {
            printf("\nPharmacy Inventory Management Workflow\n");
            printf("1: Add Drug\n");
            printf("2: Update Drug Stock\n");
            printf("3: Search Drug\n");
            printf("4: Display Inventory\n");
            printf("5: Sort Drugs by Name\n");
            printf("0: Exit Pharmacy Inventory Management Workflow\n");
            printf("Enter choice: ");
            scanf("%d", &choice);
            switch (choice)
            {
            case 1:
               addDrug();
               break;
            case 2:
               updateDrugStock();
               break;
            case 3:
               searchDrug();
               break;
            case 4:
               displayInventory();
               break;
            case 5:
               sortDrugsByName();
               break;
            case 0:
               printf("Returning to Main Menu...\n");
                break;;
            default:
               printf("Invalid option\n");
            }
            if (choice == 0)
               break;
         }
         break;
      case 6:
         while (1)
         {
            printf("\nMedicine Purchase Workflow\n");
            printf("1: Create Pharmacy Order\n");
            printf("2: Calculate Order Price\n");
            printf("3: Update Inventory After Sale\n");
            printf("4: Display Orders\n");
            printf("5: Cancel Last Order\n");
            printf("0: Exit Medicine Purchase Workflow\n");
            printf("Enter choice: ");
            scanf("%d", &choice);
            switch (choice)
            {
            case 1:
               createOrder();
               break;
            case 2:
               calculatePrice();
               break;
            case 3:
               updateInventoryAfterSale();
               break;
            case 4:
               displayOrders();
               break;
            case 5:
               cancelLastOrder();
               break;
            case 0:
               printf("Returning to Main Menu...\n");
                break;;
            default:
               printf("Invalid option\n");
            }
            if (choice == 0)
               break;
         }

         break;
      case 7:
         while (1)
         {
            printf("\nBilling and Payment Processing Workflow\n");
            printf("1: Generate Bill\n");
            printf("2: Update Payment Status\n");
            printf("3: Search Bill\n");
            printf("4: Display Bills\n");
            printf("5: Sort Bills by Amount\n");
            printf("0: Exit Billing and Payment Processing Workflow\n");
            printf("Enter choice: ");
            scanf("%d", &choice);
            switch (choice)
            {
            case 1:
               generateBill();
               break;
            case 2:
               updatePaymentStatus();
               break;
            case 3:
               searchBill();
               break;
            case 4:
               displayBills();
               break;
            case 5:
               sortBillsByAmount();
               break;
            case 0:
               printf("Returning to Main Menu...\n");
                break;;
            default:
               printf("Invalid option.\n");
            }
            if (choice == 0)
               break;
         }
         break;
      default:
         printf("Invalid workflow selection.\n");
      }
   }
   return 0;
}