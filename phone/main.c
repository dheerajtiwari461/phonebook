#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char name[50];
    char phoneNumber[15];
} Contact;

void addContact();
void searchContact();
void deleteContact();
void listContacts();
void readFromFile();
void writeToFile();


void addContact() {
    Contact c;
    FILE *file = fopen("phonebook.dat", "ab"); // Open the file in append mode

    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    printf("Enter name: ");
    scanf("%49s", c.name); // Read the name
    printf("Enter phone number: ");
    scanf("%14s", c.phoneNumber); // Read the phone number

    fwrite(&c, sizeof(Contact), 1, file); // Write the contact to file
    fclose(file); // Close the file

    printf("Contact added successfully.\n");
}

// Call this function at the start of your program to read existing contacts from file
void readFromFile() {
    FILE *file = fopen("phonebook.dat", "rb");
    Contact c;

    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    while(fread(&c, sizeof(Contact), 1, file)) {
        // Add the contact to your in-memory data structure, e.g. a linked list
        // ...
    }

    fclose(file);
}


void searchContact() {
    char name[50];
    Contact c;
    FILE *file = fopen("phonebook.dat", "rb");
    int found = 0;

    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    printf("Enter the name to search: ");
    scanf("%49s", name);

    while(fread(&c, sizeof(Contact), 1, file)) {
        if (strcmp(c.name, name) == 0) {
            printf("Name: %s, Phone Number: %s\n", c.name, c.phoneNumber);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("No contact found with the name %s.\n", name);
    }

    fclose(file);
}


void deleteContact() {
    char name[50];
    Contact c;
    FILE *file = fopen("phonebook.dat", "rb");
    FILE *tempFile = fopen("temp.dat", "wb");
    int found = 0;

    if (file == NULL || tempFile == NULL) {
        perror("Error opening file");
        return;
    }

    printf("Enter the name to delete: ");
    scanf("%49s", name);

    while(fread(&c, sizeof(Contact), 1, file)) {
        if (strcmp(c.name, name) == 0) {
            found = 1;
        } else {
            fwrite(&c, sizeof(Contact), 1, tempFile);
        }
    }

    fclose(file);
    fclose(tempFile);

    remove("phonebook.dat");
    rename("temp.dat", "phonebook.dat");

    if (found) {
        printf("Contact deleted successfully.\n");
    } else {
        printf("No contact found with the name %s.\n", name);
    }
}


void listContacts() {
    Contact c;
    FILE *file = fopen("phonebook.dat", "rb");

    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    while(fread(&c, sizeof(Contact), 1, file)) {
        printf("Name: %s, Phone Number: %s\n", c.name, c.phoneNumber);
    }

    fclose(file);
}


int main() {
    int choice;
    

    readFromFile(); // Load existing contacts into memory

    do {
        printf("Phonebook Application\n");
        printf("1. Add Contact\n");
        printf("2. Search Contact\n");
        printf("3. Delete Contact\n");
        printf("4. List Contacts\n");
        printf("5. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addContact();
                break;
            case 2:
                searchContact();
                break;
            case 3:
                deleteContact();
                break;
            case 4:
                listContacts();
                break;
            case 5:
                printf("Exiting application.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 5);

    return 0;
}