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