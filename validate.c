#include<string.h>
#include<stdio.h>
#include "validate.h"
#include "contact.h"

/*Function to validate name*/
int validate_name(char name[])
{
    int i = 0;
    int flag = 0;
    while(name[i] != '\0') //loop runs untill reach the null character
    {
        // check the name in between the character or not

        if(!(name[0] >='A' && name[0] <= 'Z'))
        {
            printf(RED"First character must be uppercase only\n"RESET);
            flag=0;
            break;
        }
        
        if(name[i] >='A' && name[i] <='Z'  || name[i] >='a'  && name[i] <='z' || name[i] == ' ')
        {
            flag  = 1;
            i++;
        }
        else
        {
            flag = 0;
            break;
        }
        
    }
    return flag;    
}

/*Function to validate phone number*/
int validate_phone_no(char phone_no[20])
{
    int i= 0;
    int len = 0; 
    //check length = 10
    while(phone_no[len] != '\0') //loop runs the untill reach the null character
        len++;
    if(len != 10)
        return 0; // if number is invalid

    // check the all characters are digits 
    while(phone_no[i] != '\0')
    {
        //check the phone number in between the digits or not
        if(phone_no[i] >='0' && phone_no[i] <= '9')
        {
            i++;
        }
        else{
            return 0; // if number is invalid
        }
    }
    return 1; //if number is valid       
}

/*Function to validate email*/
int validate_mail(char mail[])
{
    int i = 0;
    // Spaces are not allowed
    while(mail[i] != '\0')
    {
        if(mail[i] == ' ')
        {
            printf("In mail id should not contain space\n");
            return 0;
        }
        i++;
    }    
    // Must end with @gmail.com
    char *pos =strstr(mail,"@gmail.com");
    if(pos == NULL || strcmp(pos,"@gmail.com") != 0)
    {
        printf("Mail id must end with @gmail.com\n");
        return 0;
    }
    //username part(before @ )
    int username_len = pos -mail;
    //username cannot be empty
    if(username_len == 0)
    {
        printf("mail id must start with a lowercase alphabet\n");
        return 0;
    }
    //username must start with lowercase alphabet
    if(!(mail[0] >= 'a' && mail[0] <= 'z'))
    {
        printf("mail id must start with a lowercase alphabet\n");
        return 0;
    }
    // check username characters
    for(i = 0; i < username_len; i++)
    {
        if(!(mail[i] >= 'a' && mail[i] <= 'z') &&    // lowercase letters
           !(mail[i] >= '0' && mail[i] <= '9') &&    // digits
           !(mail[i] == '_'))                        // underscore
        {
            printf("Invalid character in username. Only lowercase, digits, _ allowed\n");
            return 0;
        }
    }
    return 1;  // valid maid id
}