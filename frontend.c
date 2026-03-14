#include <stdio.h>

/* Import backend system */
#include "clinic_system.c"


int main()
{

    int choice;

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


        switch(choice)
        {

            case 1: addPatient(); break;
            case 2: deletePatient(); break;
            case 3: searchPatient(); break;
            case 4: updatePatient(); break;
            case 5: sortPatients(); break;

            case 6: enqueuePatient(); break;
            case 7: dequeuePatient(); break;

            case 8: pushEmergency(); break;

            case 9: addTreatment(); break;

            case 10: createOrder(); break;

            case 11: generateBill(); break;

            case 0: return 0;

            default: printf("Invalid option\n");
        }

    }

}