#include <stdio.h>
#include "file.h"
#include <string.h>
#include "contact.h"

#define RESET   "\x1b[0m"
#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
//function to save all contacts into contacts.txt
void saveContactsToFile(AddressBook *addressBook) {
    FILE *fptr = fopen("contacts.csv","w");  //open file in write mode

    if(fptr == NULL)                         //check for file for failure
    {
        printf(RED"Error !: cannot open file: contact.csv for writing.\n"RESET);
        return ;
    }
    fprintf(fptr,"%d\n",addressBook->contactCount);
    //write each contact as a CSV line : name ,phone, email
    for(int i = 0; i < addressBook->contactCount;i++)
    {
        fprintf(fptr, "%s,%s,%s\n",
                addressBook->contacts[i].name,    //write name
                addressBook->contacts[i].phone,   //write phone
                addressBook->contacts[i].email);  //write email
    }
    fclose(fptr);   //close file
    printf(GREEN"All contacts save to file successfully : contact.csv\n"RESET);
  
}
// Function to load contacts from contacts.txt
void loadContactsFromFile(AddressBook *addressBook) {
    FILE *fptr = fopen("contacts.csv","r");  //open file in read mode
    if(fptr == NULL)                         //if file does not exit
    {
        printf(RED"No contact file found(contact.csv).starting with an empty address book.\n"RESET);
        addressBook->contactCount = 0;     // set contact count = 0;
        return ;
    }
    fscanf(fptr,"%d\n",&addressBook->contactCount);
    int i = 0;     //index for conacts array
    //Read each line until EOF or max contacts reached
    while(i < MAX_CONTACTS &&
    
        fscanf(fptr, " %[^,],%[^,],%[^\n]\n",
                addressBook->contacts[i].name,         //Read name
                addressBook->contacts[i].phone,        //Read phone
                addressBook->contacts[i].email) == 3) //Read phone and Ensure all 3 fields are read
    {
        i++;  //move to the next contact
    }
    addressBook->contactCount = i; //update total contacts
    fclose(fptr);
    printf(GREEN"Loaded %d conacts from file : contact.csv\n"RESET,addressBook->contactCount);
    
}
