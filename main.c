/* 
   Name: T. Gopalakrishna
   Date: 12/12/2025

   Project Description:
        The Address Book Project is a C-based console application designed to manage contact information 
        such as name, phone number, and email. It provides a user-friendly interface with proper validation 
        mechanisms for ensuring accurate and reliable data entry.

   This application supports the following key functionalities:

   1. Create Contact:
        - Allows users to add new contacts with name, phone number, and email.
        - Supports adding multiple contacts in a single session.
        - Validates user input to prevent invalid or duplicate entries.

   2. List Contacts:
        - Displays all saved contacts in a clean, formatted table.
        - Automatically sorts contacts alphabetically by name for easy navigation.

   3. Search Contacts:
        - Enables searching for contacts using name, phone number, or email.
        - Displays all matching results, including cases where multiple matches are found.

   4. Edit Contact:
        - Allows modification of any field (name, phone number, email) or all fields of a contact.
        - Supports accurate selection of a contact when multiple matches exist during search.

   5. Delete Contact:
        - Removes a selected contact by name, phone number, or email.
        - Automatically shifts and updates the remaining contacts to maintain list consistency.

   6. Save Contacts:
        - Saves all contact records to an external file (contacts.txt) for persistent storage.
        - Stores the total contact count to ensure accurate loading in the next session.

   7. Load Contacts:
        - Loads previously saved contacts from the file when the program starts.
        - Restores the complete contact list for immediate use.

   Overall, this project demonstrates effective use of file handling, string manipulation, 
   structured data management, and modular programming in C.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "validate.h"

int main() 
{
    int choice;
    AddressBook addressBook;
    initialize(&addressBook); // Initialize the address book

    // User menu interface
    do 
    {
        printf(BOLD CYAN"\n-------------------------------------------------\n");
        printf("                ADDRESS BOOK MENU                       \n");
        printf("-------------------------------------------------\n"RESET);
        printf("1. Create contact\n");
        printf("2. Search contact\n");
        printf("3. Edit contact\n");
        printf("4. Delete contact\n");
        printf("5. List all contacts\n");
    	printf("6. Save contacts\n");		
        printf("7. Exit\n");
        printf(BOLD CYAN"-------------------------------------------------\n"RESET);
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) 
        {
            case 1:
                createContact(&addressBook); // Function call to create contact
                break;
            case 2:
                searchContact(&addressBook); // Function call to search contact
                break;
            case 3:
                editContact(&addressBook); // Function call to edit contact
                break;
            case 4:
                deleteContact(&addressBook); // Function call to delete contact
                break;
            case 5:
                sortContacts(&addressBook);       
                listContacts(&addressBook, 0); // Function call to list contact
                break;
            case 6:
                printf("Saving and Exiting...\n");
                sortContacts(&addressBook);
                saveContactsToFile(&addressBook);   // Function call to save contact
                break;
            default:
                printf(GREEN"Exiting the Program!\n");
                printf("Good Bye....\n"RESET);
        }
    } while (choice != 7);
    
    return 0;
}
