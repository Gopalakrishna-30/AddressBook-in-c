#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"
#include "validate.h"



void listContacts(AddressBook *addressBook, int sortCriteria) 
{
    // Sort contacts based on the chosen criteria
    getchar();
    // If no contacts available   
    if(addressBook->contactCount == 0)
    {
        printf(RED"No contacts available to display.\n"RESET); //
        return;
    }
    printf(BOLD CYAN"\n--------------------------------------------------------------------------------\n");
    printf("|%-5s  | %-25s |%-15s  | %-30s\n","S.NO ", "NAMES","PHONE NUMBERS","EMAIL ID'S");
    printf("--------------------------------------------------------------------------------\n"RESET);
    //printf(BLUE"------%d Member Details ------\n"RESET,(*addressBook).contactCount);

    for (int i=0 ;i<addressBook->contactCount;i++)
    {
        //printf(GREEN"Name : %3s "RESET,addressBook->contacts[i].name);
        //printf(CYAN"phone : %3s "RESET,addressBook->contacts[i].phone);
        //printf(YELLOW"Email : %3s "RESET,addressBook->contacts[i].email);
        //printf("\n");
        printf("| %-5d | %-25s | %-15s | %-30s\n",i+1,addressBook->contacts[i].name,
                    addressBook->contacts[i].phone,addressBook->contacts[i].email);
    }
    printf(BOLD CYAN"--------------------------------------------------------------------------------\n"RESET);
}

void initialize(AddressBook *addressBook) {
    addressBook->contactCount = 0;
  //  populateAddressBook(addressBook);
    
    // Load contacts from file during initialization (After files)
    loadContactsFromFile(addressBook);
}

void saveAndExit(AddressBook *addressBook) {
    saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS); // Exit the program
}


void createContact(AddressBook *addressBook)
{
	/* Define the logic to create a Contacts */
    char name[30];                      //character array name declaration
    int res;                           //Variable declaration
    printf("Enter the name: ");       //Ask to user name
    scanf(" %[^\n]",name);           //Read the name with spaces also
    //validation of name 
    do{
        res = validate_name(name);   //function call of validate name
        if(res == 0)                // If invalid name
        {
            printf(RED"Invalid name! only alphabets are allowed.\n"RESET);  //Error maessage
            printf("Enter the name again: ");                              //Ask to user to enter name again
            scanf(" %[^\n]",name);                                        //Read name again
        }
    }while(res == 0); //loop runs untill the valid and unique name
    
    //Read the number from the user
    char phone[20];                                                       //character array phone number declaration
    int phone_no = 0;                                                    //flag for phone number validation
    printf("Enter the phone number: ");                                 //ask to user phone number
    scanf("%s",phone);                                                 //Read the phone number
    do{
        phone_no = validate_phone_no(phone); //function call of validate phone number
        if(phone_no == 0)                   //if invaild phone number
        {
            printf(RED"Invalid phone number! Enter 10 digits only.\n"RESET); //error message
            printf("Enter the phone number again: ");                       //Ask to user again enter the phone number
            scanf("%s",phone);                                             //Read the phone number again
            continue;                                                     //recheck again from loop 
        }
        //Duplicate check in phone number
        int duplicate_phone = 0;  //flag for duplicate phone number
        for(int i = 0; i < addressBook->contactCount; i++)            //loop run through all contacts
        {
            if(strcmp(addressBook ->contacts[i].phone,phone) == 0)  //check the duplicates
            {
                duplicate_phone = 1;                              //if duplicates is found
                break;                                           // stop checking
            }    
        }
        if(duplicate_phone) //if duplicate number is found
        {
            printf(RED"This number already exits\n"RESET);  //Show the message to user 
            printf("Enter the number again: ");            //Ask phone number again to user 
            scanf("%s",phone);                            //Read again the phone number
            phone_no = 0;                                // force loop to continue
            continue;                                   //continue loop
        }
    }while(phone_no == 0); //loop runs untill vaild and unique phone number
    
    //Read the Email from the user
    char mail[50];                        //character array mail declaration
    int email = 0;                       //flag for email validation 
    printf("Enter the Email Id: ");     //ask to user for mail
    scanf("%s",mail);                  //Read the mail
    do{
        email = validate_mail(mail); // function call of validate_mail
        if(email == 0)              //if invalid email
        {
            printf(RED"Error: Invalid mail!\n"RESET);                //Error message
            printf("Enter the mail id again: ");                    //ask to user again
            scanf("%s",mail);                                      //Read the mail again
        }
        //duplicates checks in email
        int duplicate_mail = 0; //flag for duplicate mail
        for(int i = 0; i < addressBook->contactCount; i++)           //loop all the contacts
        {
            if(strcmp(addressBook ->contacts[i].email,mail) == 0)  //check the duplicates
            {
                duplicate_mail = 1;                              //if duplicate is found
                break;                                          //stop the checking
            }    
        }
        if(duplicate_mail) //if duplicate found
        {
            printf(RED"This mail already exits\n"RESET);      //show message to user
            printf("Enter the mail again: ");                //ask to user again
            scanf("%s",mail);                               //read mail agin
            email = 0;                                     // force loop to continue
            continue;                                     //continue the loop
        }
    }while(email == 0); //loop runs untiil vaid mail and unique mail
    
    strcpy(addressBook->contacts[addressBook->contactCount].name,name);     //store name
    strcpy(addressBook->contacts[addressBook->contactCount].phone,phone);  //store phone
    strcpy(addressBook->contacts[addressBook->contactCount].email,mail);  //store email
    addressBook->contactCount++;                                         //incrementing the contact count after adding the contact
    printf(GREEN"contact added successfully\n"RESET);                   //success message

    
}

void searchContact(AddressBook *addressBook)  // function to search contacts in the address book
{
    /* Define the logic for search */
    char opinion = 'y';                    // variable to control repeat of search loop
    int choice,flag=0,index,res,valid;    // variables for menu choice, flags, index, validation
    char name[30],phone[20],email[50];   // buffers for name, phone, and email input
    do{                                 // outer loop to repeat whole search until user exits
        do{                            // loop to validate menu choice
            flag = 0;                  // reset flag for invalid menu choice
            printf(BLUE"-----Search Contacts -----\n"RESET);                   // print search menu header
            printf("1.Name : \n2.phoneno : \n3.Mail id : \n4.Exit: \n");      // options for search type
            printf("Enter the choice you want: ");                           // ask for user input 
            scanf("%d",&choice);                                            // read user choice
            if(choice == 0 || choice > 4)                                  // check invalid input
            {
                printf(YELLOW"Select the valid option to search(1-4).\n"RESET);  // invalid choice message
                flag =1;     // mark choice as invalid
            }
        }while (flag==1);   // repeat until valid menu choice

        switch(choice)    // start processing based on user choice
        { 
            case 1:     // option 1: search by name
            {
                printf("Entered the name: \n");  // prompt user to enter name
                do{
                    scanf(" %[^\n]",name);        // read full name (including spaces)
                    res = validate_name(name);   // function call validate entered name
                    if(res)                     // if name valid
                    { 
                        for(int i = 0; i < addressBook->contactCount;i++)           // loop through contacts
                        {
                            if(strcmp(name,addressBook->contacts[i].name)== 0)    //check the entered name is there are not
                            {
                                flag++;                                         //make us to know contacts are present with that name
                                index = i;                                     //store the index that name
                            }  
                        }
                        if(flag == 0) //if no contact
                            printf(YELLOW"No contact found with this name\n"RESET);
                        else if(flag == 1) //if single contact
                        {
                            printf(BLUE"--contact found--\n"RESET);
                            printf("Name = %s\n",addressBook->contacts[index].name);       //display the name
                            printf("Phone = %s\n",addressBook->contacts[index].phone);    //display the phone number
                            printf("Email = %s\n",addressBook->contacts[index].email);   //display the mail id
                        }
                        else //if multiple conacts are same name
                        {
                            printf(YELLOW"Found %d conacts with the same name \n",flag);  //To display how many contacts are same
                            printf("please enter the phone number: ");                   //number is unique for every one
                            do{
                                scanf("%s",phone);
                                res = validate_phone_no(phone);    //again validation of phone number
                                if(res)                           //if valid
                                {
                                    for(int i =0;i<addressBook->contactCount;i++)              //loop runs through all contacts
                                    {
                                        if(strcmp(phone,addressBook->contacts[i].phone) == 0) //find the user with the help of number
                                        {
                                            printf(BLUE"--contact found--\n"RESET);
                                            printf("Name = %s\n",addressBook->contacts[i].name);     //display name
                                            printf("Phone = %s\n",addressBook->contacts[i].phone);  //display phone number
                                            printf("Email = %s\n",addressBook->contacts[i].email); //display email id
                                        }
                                    }
                                }
                                else  //if not valid number
                                {
                                    printf(RED"Error!:Entered number is not valid\n"RESET); //Error message
                                    printf("Enter the valid number");                      // Again ask to user
                                }
                            }while(res == 0); // loop runs untill valid  number
                        }
                    }
                    else{ //if name is not valid
                        printf(RED"Error: Entered name is not valid\n"RESET);  //Error message to show to user
                        printf("please enter the valid name: ");              //Ask to user again enter the name
                    }        
                }while(res == 0); // repeat until valid name
                break; //Avoid all fallthrough (go to next acse)
            }
            case 2:        // option 2: search by phone number
            {
                flag = 0;  // reset flag for found contacts
                printf("Enter the number : ");   // ask for phone number
                do{
                    scanf("%s",phone);            // read phone number
                    res = validate_phone_no(phone);  // function call validate phone
                    if(res)      // phone is valid
                    {
                        for (int i=0; i<addressBook->contactCount; i++)      // loop through contacts
                        {
                            if(strcmp(phone, addressBook->contacts[i].phone) == 0) //check match
                            {     //check the entered number is there or not
                                printf(BLUE"---Contact Found--\n"RESET);
                                printf("Name  = %s\n", addressBook->contacts[i].name);   //Display name
                                printf("Phone = %s\n", addressBook->contacts[i].phone);  //Display phone number
                                printf("Email = %s\n", addressBook->contacts[i].email);  //Display Email id
                                flag = 1;   // mark as found
                            }
                        }
                        if (flag == 0)                       //No contact found 
                        printf(RED"No contact found ?\n"RESET);
                }
                else //if not a valid number
                {    
                        printf(RED"Error : Entered name not correct!"RESET"\nEnter the valid name: \n");
                }
                } while (res == 0);    // repeat until valid phone
                break;               //avoids the fall through (step into next case)
            }
            case 3:   // option 3: search by email
            {
                flag = 0;  //reset flag
                printf("Enter the email : ");  //ask for email
                do{
                scanf("%s",email);   //read mail
                res=validate_mail(email);     //check for valid email
                if (res)                    //if valid excute the next steps
                {
                        for (int i=0; i<addressBook->contactCount; i++)  // loop through contacts   
                        {
                            if(strcmp(email, addressBook->contacts[i].email) == 0){     //check the entered email is match found
                                printf(BLUE"Contact Found...\n"RESET);
                                printf("Name  = %s\n", addressBook->contacts[i].name);  //Display name
                                printf("Phone = %s\n", addressBook->contacts[i].phone);  //Display phone number
                                printf("Email = %s\n", addressBook->contacts[i].email);  //Display Email id
                                flag=1;  // mark as found
                            }
                        }
                        if (flag == 0)                       //No contact 
                        printf(RED"No contact found ?\n"RESET);
                }
                else     //if not a valid email
                {
                        printf(RED"Error : Entered name is not correct!"RESET"\nEnter the valid name: \n");
                }    
                } while (res == 0);
                break;               //avoids the fall through (step into next case)
            }
            default:  // option 4: exit search
            {
                printf(YELLOW"Exiting the search..."RESET);  // print exit message
                break;    // exit switch
            }
        }
        printf(RED"Are you want to really exit from search contact ?(y/n): "RESET);   // ask user whether to exit
        getchar();    // clear input buffer
        scanf("%c",&opinion);       // read user choice      
    }
    while(opinion == 'n');   // repeat search until user chooses 'y'
}

void editContact(AddressBook *addressBook)    //function to edit a contact in the Address book
{
	/* Define the logic for Editcontact */
    char name[50],newname[50];              //arrays for current and new name
    char phone[20],newphone[20];           //arrays for current and new phone
    char email[50],newemail[50];          //arrays for current and new email
    int choice,res,found=0,index;        //variables for user choice, validation, search flag, index
    char opinion = 'y';                 //variable to repeat edit loop
    do{
        do{                  //main edit loop   
            res = 0;        //loop to validate menu option
            printf(BLUE"----Edit by contact--\n"RESET);   // print menu header
            printf("1.Name: \n");                        // option to edit name
            printf("2.Phone: \n");                      // option to edit phone number
            printf("3.Email: \n");                     // option to edit email id
            printf("4.Exits: \n");                    // option to exit
            printf("Enter your choice: ");           // prompting message for input
            scanf("%d",&choice);                    // Read user choice
            if(choice == 0 || choice > 4)          // check valid input or not
            {
                printf(YELLOW"Select the valid search option(1-4): \n"RESET); // show error message
                res = 1;                                                     // flag invalid status
            }

        }while(res == 1);  // Repeat loop until valid choice
        switch(choice)    //switch based on menu
        {
            case 1: //edit by the name
            {
                printf("Enter the name to edit: ");     // prompting message for name to edit
                do{
                    scanf(" %[^\n]",name);            // Read the full name with spaces input
                    res = validate_name(name);       // function call for validate enter name
                    if(res == 0)                    // if name invalid
                    {
                        printf(RED"Error! : Entered the name Invalid"RESET"\nEnter the valid name again: ");  // Eorror message
                    }
                }while(res == 0);   //Repeat the loop until valid name
                //Matching contacts are there
                for(int i = 0; i<addressBook->contactCount;i++)           // Loop through contact list
                {
                    if(strcmp(name,addressBook->contacts[i].name) == 0)  // check for name match
                    {
                        printf("index %d -> Name : %s phone : %s Email : %s\n",i,
                        addressBook->contacts[i].name,      // print the match name
                        addressBook->contacts[i].phone,    // print the match phone number
                        addressBook->contacts[i].email);  // print the match email
                        found++;
                    }
                }
                if(found == 0)   // if no contact found
                {
                    printf(RED"No contact found ?\n"RESET);  // print error message
                }
                else{
                    printf(BLUE"..contact found..\n"RESET); // show success message
                    choice =0;                             // Reset choice for index validation
                    do{
                        printf("Enter the index you want to edit: ");  // prompt for index ask to user
                        scanf("%d",&index);                           // Read index
                        if (index < 0 || index >= addressBook->contactCount) // if choose invalid choice
                        {
                            printf(RED"Error: Enter the valid index number to edit name!\n"RESET);  // Error message
                            choice=1; // force to repeat
                        }
                    }while (choice == 1);  // Repeat loop until idex
                    printf("Enter the new name: "); // Ask to user to enter for new name
                    do{
                        scanf(" %[^\n]",newname);    // Read new name
                        res=validate_name(newname); // function call validate new name
                        if (res == 0)              // if name invalid
                        {
                            printf(RED"Error : Enter th valid name again !\n"RESET);  // Error message
                        }    
                    }while (res == 0);      //Repeat until valid name
                    strcpy(addressBook->contacts[index].name,newname);   // update name
                    printf(GREEN"Name updated successfully...\n"RESET); // success message
                }
                break;   // exit case 1
            }
            // Edit phone number
            case 2:
            {
                printf("Enter the phone number to Edit: ");   // Ask to user for phone number to edit
                do{
                    scanf("%s",phone);                      // Read phone number
                    res = validate_phone_no(phone); // function call for validate phone number    
                    if(res == 0)                   // if invalid phone number
                    {
                        printf(RED"Error: Entered the phone number is not valid.\n"RESET);  // Error message
                        printf("Enter the phone number again: ");                          // Again ask to user enter phone number
                    }
                }while(res == 0);        // Repeat until valid
                for(int i =0; i <addressBook->contactCount;i++)  // loop through contacts
                {
                    if(strcmp(phone,addressBook->contacts[i].phone) == 0)  //phone number match
                    {
                        printf(BLUE" ..Contact Found..\n"RESET);   // success message
                        printf("Enter the new number: "RESET);    // Ask to user for new name
                        do{
                            scanf("%s",newphone);               //Read new phone number
                            res  = validate_phone_no(newphone);//function call for new phone number
                            if(res == 0)   // if invalid new phone number
                            {
                                printf(RED"Error : Invalid number!Enter number again: "RESET);  //Error message
                                continue;  //retry
                            }
                            int duplicate = 0;                                  // flag for duplicate number
                            for(int j = 0; j < addressBook->contactCount;j++)  // check the duplicates
                            {
                                if(j != i && strcmp(addressBook->contacts[j].phone,newphone) == 0)
                                {
                                    duplicate = 1;  // duplicate found
                                    break;         // exit the loop
                                }
                            }
                            if(duplicate)       // if duplicate exists 
                            {
                                printf(RED"This number already exists."RESET"CYAN\nEnter the another number: "); //Error message and ask again enter number
                                res = 0;       // force to retry
                            }
                        }while(res == 0);    // Repeat until valid new phone number    
                        strcpy(addressBook->contacts[i].phone,newphone);                // update phone number
                        printf(GREEN"phone number is updated successfully..\n"RESET);  // success message
                        found++;    // mark as found
                        break;     // exit loop
                    }
                }
                if(found == 0)  // No match found
                {
                    printf(RED"Entered contact is not found\n"RESET); // Error message
                }
                break;      // exit case 2                    
            }
            // Edit email                            
            case 3:
            {
                printf("Enter the email to edit: "); //Ask to user enter mail id
                do{

                    scanf("%s",email);            // Read input email
                    res = validate_mail(email);  // function call validate email
                    if(res == 0) // if invalid email
                    {
                        printf(RED"Entered email is not valid.\n"RESET);  // Error message
                        printf("Enter the email again: ");               // Ask to user retry the email
                    }
                }while(res ==0);     // Repeat until valid email    
                for(int i =0; i< addressBook->contactCount;i++)             // loop through contacts
                {
                    if(strcmp(email,addressBook->contacts[i].email) == 0) // match found
                    {
                        printf(BLUE"Email found...\n"RESET);         //success message
                        printf("Enter the new email you want: ") ;  //ask for new email
                        do{
                            scanf("%s",newemail);            // read new email
                            res = validate_mail(newemail);  // validate new email
                            if(res == 0)  // if invalid
                            {
                                printf(RED"Error : Invalid Email!."RESET"\nEnter the valid email again: "); //error message and ask again enter mail
                                continue; //retry
                            }
                            int duplicate = 0;                                   // duplicate flag
                            for(int j = 0; j < addressBook->contactCount; j++)  // check for duplicates
                            {
                                if(j != i && strcmp(addressBook->contacts[j].email, newemail) == 0)
                                {
                                    duplicate = 1;  // duplicate found
                                    break;         // exit duplicate loop
                                }
                            }

                            if(duplicate)  // if email exists
                            {
                                printf(RED"This email already exists."RESET"\nEnter the another Email: ");  // Error message ask again
                                res = 0;     // retry
                            }
                        }while(res == 0);  // repeat until valid email
                        strcpy(addressBook->contacts[i].email,newemail);           // update email
                        printf(GREEN"Entered the updated successfully..\n"RESET); // success message
                        found++;   // mark as found
                        break;    // stop searching
                    }
                }
                if(found == 0)  // if not found
                {
                    printf(RED"Entered email is not found.\n"RESET);  // Error message
                    break;  // exit email case
                }
            }
            default: // option 4 or invalid
            {
                printf(YELLOW"Exiting the Edit.\n"RESET);  // print exit message
                break;                                    // exit switch
            }
        }
        printf(RED"Are you want to really exit from search contact ?(y/n): "RESET); //ask user to continue
        getchar();             // clear buffer
        scanf("%c",&opinion); // Raed user choice  
    }
    while(opinion == 'n');   // repeat edit until user says yes
} 
void deleteContact(AddressBook *addressBook)
{
	/* Define the logic for deletecontact */  
    char name[50],phone[20],email[50];
    int choice,res,found = 0,firstindex = -1,delindex = -1;
    char opinion = 'y';
    do{       // repeat delete menu until user exits
        do{   // validate menu choice
            res = 0;
            printf(BLUE"---Deleted by contact---\n"RESET);
            printf("1.Name: \n");
            printf("2.Phone: \n");
            printf("3.Email: \n");
            printf("4.Exits: \n");
            printf("Enter your choice: ");
            scanf("%d",&choice);
            if(choice == 0 || choice > 4)  // invalid menu option condition
            {
                printf(YELLOW"Select the valid option to search(1-4): \n"RESET);
                res = 1;
            }
        }while(res == 1);    // repeat until valid menu choice
        switch(choice)
        {
            case 1: //Deleted by name
            {
                int i;
                printf("Enter the name to delete you want: ");
                do{
                    scanf("%s",name);
                    res = validate_name(name);
                    if(res == 0)   // invalid name condition
                    {
                        printf(RED"Error! : Entered the name Invalid.\n"RESET);
                        printf("Enter the valid name again: ");
                    }
                }while(res == 0);    // repeat until valid name
                // if Matching contacts with that name
                for(int i = 0 ;i < addressBook->contactCount;i++)   // search all contacts
                {
                    if(strcmp(name,addressBook->contacts[i].name) == 0)  // name match condition
                    {
                        printf("index %d -> Name : %s phone : %s Email : %s\n",i,
                        addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
                        found++;          // count how many contacts have this name
                        firstindex = i;  // store first match index
                    }
                }
                if(found == 0)   // no contacts found with name
                {
                    printf(RED"No contact found ?\n"RESET);
                    return;
                }
                if(found == 1) // // only one contact → delete directly
                {
                    delindex = firstindex;
                }
                else if(found > 1)  // multiple contacts with same name
                {
                    printf(RED"More than one contact found has this name.\n"RESET);
                    printf("Enter the number of the contact to delete : ");
                    do{       // validate phone number
                        scanf("%s",phone);
                        res = validate_phone_no(phone);
                        if(res == 0)   // invalid phone number
                        {
                            printf(RED"Error: Entered number is Invalid.\n"RESET);
                            printf("Enter the valid number again: ");
                        }
                    }while(res == 0);
                    //find the same name and phone number
                    for(int i = 0; i<addressBook->contactCount;i++)  // find exact name+phone match
                    {
                        if(((strcmp(name,addressBook->contacts[i].name)==0) && strcmp(phone,addressBook->contacts[i].phone)==0))  // match both name & phone number
                        {
                            delindex = i;
                            break;
                        }
                    }
                    if(delindex == -1)  // no exact match found
                    {
                        printf(RED"No contact matches this name and number.\n"RED);
                        return;
                    }
                }
                for(int i= delindex; i <addressBook->contactCount -1;i++)  // shift contacts to left
                addressBook->contacts[i] = addressBook->contacts[i+1];
                addressBook->contactCount--;   // reduce total count
                printf(GREEN"contact Deleted successfully.\n"RESET);
                break;
            }
            case 2:
            {
                printf("Enter the phone number deleted you want: ");
                do   // validate phone number
                {
                    scanf("%s",phone);
                    res = validate_phone_no(phone);
                    if(res == 0)   // invalid phone condition
                    {
                        printf(RED"Error: Entered phone number is not valid.\n"RESET);
                        printf("Enter the phone number again: ");
                    }
                } while (res == 0);
                for(int i =0; i<addressBook->contactCount;i++)   // search by phone number
                {
                    if(strcmp(phone,addressBook->contacts[i].phone) == 0)   // match found
                    {
                        delindex = i;
                        break;
                    }
                }
                if(delindex == -1)   // no contact with that phone number
                {
                    printf(RED"No contact found with this number.\n"RESET);
                    return;
                }
                for(int i= delindex; i <addressBook->contactCount -1;i++)
                { // shift left
                    addressBook->contacts[i] = addressBook->contacts[i+1];
                    addressBook->contactCount--;   // decrement count
                }
                printf(GREEN"contact Deleted successfully.\n"RESET);
                break;  
            }
            case 3:
            {
                printf("Enter the email deleted you want: ");
                do     // validate email
                {
                    scanf("%s",email);
                    res = validate_mail(email);
                    if(res == 0)  // invalid email
                    {
                        printf(RED"Error: Entered email is not valid.\n"RESET);
                        printf("Enter the email again: ");
                    }
                } while (res == 0);
                for(int i =0; i<addressBook->contactCount;i++)   // search by email
                {
                    if(strcmp(email,addressBook->contacts[i].email) == 0)  // match found
                    {
                        delindex = i;
                        break;
                    }
                }
                if(delindex == -1)  // not found
                {
                    printf(RED"No contact found with this email.\n"RESET);
                    return;
                }
                for(int i= delindex; i <addressBook->contactCount -1;i++)  // shift left
                addressBook->contacts[i] = addressBook->contacts[i+1];
                addressBook->contactCount--;  // reduce count
                printf(GREEN"contact Deleted successfully.\n"RESET);
                break;  
            }
            default:   // choice == 4 → exit
                printf(YELLOW"Exiting the Deleted.\n"RESET);
                break;
        }
        printf(RED"Are you want to really exit from search contact ?(y/n): "RESET); // ask to exit delete menu
        getchar();
        scanf("%c",&opinion);       
    }
    while(opinion == 'n');   // repeat until user chooses yes
}


// Sort contacts alphabetically by name
void sortContacts(AddressBook *addressBook)
{
    // Using Bubble sort algorithm
    for (int i = 0; i < addressBook->contactCount - 1; i++)
    {
        for (int j = 0; j < addressBook->contactCount - 1 - i; j++)
        {
            if (strcmp(addressBook->contacts[j].name, addressBook->contacts[j + 1].name) > 0)
            {
                Contact temp = addressBook->contacts[j];
                addressBook->contacts[j] = addressBook->contacts[j + 1];
                addressBook->contacts[j + 1] = temp;
            }
        }
    }
}
