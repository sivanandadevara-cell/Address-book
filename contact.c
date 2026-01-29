#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include "contact.h"

/* Function definitions */
// void init_intitalization(struct Address_book *addressbook)
// {
// }

//saving the contacts
void save_contacts_to_file(struct Address_book *addressbook)
{
    //open a file in write mode
    FILE *fptr=fopen("file.txt","w");  
    //check the address it's NULL or not
    if(fptr == NULL)
    {
        puts("file not exit\n");
        return;
    } 
    fprintf(fptr,"#%d\n",addressbook->contact_count);
    //generate the loop for upto contact count
    for(int i=0;i<addressbook->contact_count;i++)
    {
       fprintf(fptr,"%s,%s,%s\n",addressbook->contact_details[i].Name,addressbook->contact_details[i].Mobile_number,addressbook->contact_details[i].Mail_ID);
    }
    fclose(fptr);
}
//storing the contacts
void load_contacts_from_file(struct Address_book *addressbook)
{
    //open a file in read mode
    FILE * fptr = fopen("file.txt","r"); 
    //check the address it's NULL or not
    if(fptr == NULL)
    {
        puts("file not exit\n");
        return;
    }
    fscanf(fptr,"#%d\n",&addressbook->contact_count);
    //generate the loop for upto contact count
    for(int i=0;i<addressbook->contact_count;i++)
    {
        fscanf(fptr," %[^,],%[^,],%[^\n]\n",addressbook->contact_details[i].Name,addressbook->contact_details[i].Mobile_number,addressbook->contact_details[i].Mail_ID);
    }
    fclose(fptr);   
}

//if u have a same number doesn't exit
int unique_Mobile(char* temp,struct Address_book *addressbook)
{
    for (int i = 0; i < addressbook->contact_count; i++)
    {
        if (strcmp(addressbook->contact_details[i].Mobile_number,temp) == 0)
        {
            return 0;  // Mobile already exists
        }
    }
    return 1; // Unique
}
//if u have same mail id dosn't exit
int unique_mail(char* temp,struct Address_book *addressbook)
{
    for (int i = 0; i < addressbook->contact_count; i++)
    {
        if (strcmp(addressbook->contact_details[i].Mail_ID,temp) == 0)
        {
            return 0;  // Mail ID already exists
        }
    }
    return 1; // Unique
}
//The name contain alpha letters
int valid_Name(char *name)
{
    if(strlen(name)==0)
    {
        return 0;
    }
    
    for(int i=0;i<name[i]!='\0';i++)
    {
       if(!((isalpha(name[i])) || (name[i] == ' ')))
       {
          printf("Invalid name!must be allowed only lower case\n");
          return 0;  //Invalid Name
       }
    }
    return 1;  //valid
}
// contain only digits
int valid_Mobile(char *mobile) 
{
    if (strlen(mobile) != 10) 
    return 0;

    for (int i = 0; i < 10; i++)
    {
        if (!isdigit(mobile[i]))  //only digits
        {
            return 0; // Invalid mobile
        }
    }
    return 1; // Valid mobile
}
//The mail contain name@example.com only.
int valid_mail(char *mail) 
{
    
    int i=0, at_pos = -1, dot_pos = -1, at_count = 0 , dot_count=0;
    if (strlen(mail) == 0) 
    {
        printf("Error:Mail ID is empty\n");
        return 0;
    }   
    //first character mail id  should not be digit or special character
    if(!(mail[0] >= 'a' && mail[0] <='z'))
    {
        printf(BLUE"Mail ID start with lowercase only!\n"RESET);
        return 0;
    }
    //run the while loop upto null character 
    while(mail[i]!='\0')
    {
        if(mail[i]=='@')
        {
            at_count++;
            at_pos=i;
        }
        else if(mail[i]=='.')
        {
            dot_count++;
            dot_pos=i;
        }
        else if(!((mail[i]>= 'a' && mail[i]<='z') || (mail[i]>= '0' && mail[i]<='9') || mail[i]=='@' || mail[i]=='.'))
        {
            printf(BLUE"Error:in mail id contains only lowercase,digits,'@','.'\n"RESET);
            return 0;
        }
        i++;
    }
    //only  one '@' can be allowed
    if(at_count!=1)
    {
        printf(BLUE"Error:mail id contains only one '@"RESET);
        return 0;
    }
    //only  one '.' can be allowed
    if(dot_count!=1)
    {
        printf(BLUE"Error:mail id contains only one '."RESET);
        return 0;
    }
    //mail id have one '@' and atleast one '.' it appear after '@'
    if(dot_pos < at_pos)
    {
        printf("Error:mail id should be '.' after '@'\n");
        return 0;
    }
    int letter_count=0;
    for(int j=at_pos+1;j<dot_pos;j++)
    {
        if(!(mail[j]>='a' && mail[j]<='z'))
        {
            printf("Error:only lowercase letters allowed between '@' and '.'\n");
            return 0;
        }
        letter_count++;
    }
    //After '@' two letters can be allowed
    if(letter_count<2)
    {
        printf("Error:Atleast two letters allowed between '@' and '.'\n");
        return 0;
    }
    int len=strlen(mail);
    if(len<4 || strcmp(mail+len-4,".com")!=0)
    {
        printf("Error:mail id end with only '.com'\n");
        return 0;
    }
    if(mail[(strlen(mail)-1)] == '.')
    {
        printf("Error:mail id can't end with  '.'\n");
        return 0;
    }
    return 1;
}
//checking name is valid or not
void get_valid_name(char *name)
{
    do 
    {
        printf(RED"Enter Your Name: "RESET);
        scanf(" %[^\n]", name);

        if (!valid_Name(name))
        {
            printf("Invalid Name! Only letters and after letters spaces allowed.\n");
            continue;
        }
        break;
    } while (1);
}
//checking valid mobile or not
void get_valid_mobile(char* mobile,struct Address_book *addressbook)
{
    do
    {
        printf(GREEN"Enter the mobile number:"RESET);
        scanf("%s",mobile);
        if(!valid_Mobile(mobile))
        {
            printf("Invalid mobile number must be exactly 10 digits\n");
            continue;
        }
        if(!unique_Mobile(mobile,addressbook))
        {
            printf("This number already exit!enter the correct number\n");
            continue;
        }
        break;
    }while(1);
}
//checking valid mail id or not
void get_valid_mail(char* mail,struct Address_book *addressbook)
{
    do
    {
        printf(BLUE"Enter the mail_ID:"RESET);
        scanf(" %[^\n]",mail);
        if(!valid_mail(mail))
        {
            printf(GREEN"Invalid mail id!Format should be like name@example.com\n"RESET);
            continue;
        }
        if(!unique_mail(mail,addressbook))
        {
            printf(RED"This mail id already exit!Enter another one\n"RESET);
            continue;
        }
        break;
    }while(1);
}
//contacts should be alphabetical order
void insert_contact_sorted(struct Address_book *addressbook, char *name, char *mobile, char *mail)
{
    int pos = 0;

    // Find the place where this new name should come
    while (pos < addressbook->contact_count && strcmp(addressbook->contact_details[pos].Name, name) < 0)
    {
        pos++;
    }

    // Move everything one step to the right to make space
    for (int i = addressbook->contact_count; i > pos; i--)
    {
        addressbook->contact_details[i] = addressbook->contact_details[i - 1];
    }

    //  Put the new contact in the empty space
    strcpy(addressbook->contact_details[pos].Name, name);
    strcpy(addressbook->contact_details[pos].Mobile_number, mobile);
    strcpy(addressbook->contact_details[pos].Mail_ID, mail);

    //  Increase the total count of contacts
    addressbook->contact_count++;
}

//Adding name,mobile number
int create_contact(struct Address_book *addressbook)
{
    char temp_name[50], temp_mobile[20], temp_mail[50];

    get_valid_name(temp_name);
    get_valid_mobile(temp_mobile, addressbook);
    get_valid_mail(temp_mail, addressbook);

    insert_contact_sorted(addressbook, temp_name, temp_mobile, temp_mail);

    printf("Contact added successfully!\n");
    return 1;
    
}

//printing all contacts details
void list_contacts(struct Address_book *addressbook)
{
    //if no contacts is available.we can't anything.
    if (addressbook->contact_count == 0)
    {
        printf("No contacts available.\n");
        return ;
    }
   //generate the for loop upto to contact count
    for (int i = 0; i < addressbook->contact_count; i++) 
    {
        printf("==============================\n");
        printf("contact:%d\n",i+1);
        printf(RED"Name   : %s\n"RESET, addressbook->contact_details[i].Name);
        printf(BLUE"Mobile : %s\n"RESET, addressbook->contact_details[i].Mobile_number);
        printf(GREEN"Email  : %s\n"RESET, addressbook->contact_details[i].Mail_ID);
    }
}

//seraching the name.if not return -1,if yes return i.
int search_by_name(struct Address_book *addressbook)
{
    char str[50];          // name entered by user
    int count = 0;         // how many contacts matched
    int choice;            // user choice if multiple found
    int found_index = -1;  // index of first match

    printf(RED"Enter Name: "RESET);
    scanf(" %[^\n]", str);

    // loop through all contacts and check if name match.
    for (int i = 0; i < addressbook->contact_count; i++)
    {
        if (strcmp(addressbook->contact_details[i].Name, str) == 0)
        {
            count++;
            printf("\nContact %d:\n", count);
            
            printf(RED"Name  : %s\n"RESET, addressbook->contact_details[i].Name);
            printf(BLUE"Mobile: %s\n"RESET, addressbook->contact_details[i].Mobile_number);
            printf(GREEN"Email : %s\n"RESET, addressbook->contact_details[i].Mail_ID);
            

            if (count == 1)
            found_index = i; // store first match index
        }
    }

    // check how many contacts matched
    switch (count)
    {
        case 0: // no matches found
                printf("No contact found with the name '%s'.\n", str);
                return -1;

        case 1: // only one contact matched.
                return found_index;

        default: // more than one contact matched
                printf("\nMultiple contacts found with the name '%s'.\n", str);
                printf("Enter which contact you want (1 - %d): ", count);
                scanf("%d", &choice);

                // validate user choice
                if (choice < 1 || choice > count)
                {
                    printf("Invalid choice.\n");
                    return -1;
                }

                // find the index of chosen contact
                int current = 0,actual_index = -1;
                for (int i = 0; i < addressbook->contact_count; i++)
                {
                    if (strcmp(addressbook->contact_details[i].Name, str) == 0)
                    {
                        current++;
                        if (current == choice)
                        {
                            actual_index = i;
                            break;
                        }
                    }
                }
            printf("\nHere is the contact you selected:\n");
            printf("Contact found %d\n",count);
            printf("....................................\n");
            printf(RED"Name  : %s\n"RESET, addressbook->contact_details[actual_index].Name);
            printf(BLUE"Mobile: %s\n"RESET, addressbook->contact_details[actual_index].Mobile_number);
            printf(GREEN"Email : %s\n"RESET, addressbook->contact_details[actual_index].Mail_ID);

        return actual_index; 
    }
    return -1; // just in case, avoids compiler warning.
}
//searching mobile number.if not return -1,if yes return i.
int search_by_mobile(struct Address_book *addressbook)
{
    char Mobile[11];
    printf(BLUE"Enter the mobile number: "RESET);
    scanf("%s",Mobile);
    //generate the for loop upto contact count.
    for (int i = 0; i < addressbook->contact_count; i++) 
    {
        if (strcmp(addressbook->contact_details[i].Mobile_number,Mobile) == 0) 
        {
            printf("Contact is found\n");
            printf(RED"Name  : %s\n"RESET, addressbook->contact_details[i].Name);
            printf(BLUE"Mobile: %s\n"RESET, addressbook->contact_details[i].Mobile_number);
            printf(GREEN"Email : %s\n"RESET, addressbook->contact_details[i].Mail_ID);
            return i;
            
        }
    }
    
    printf("Error: Contact number not found. Try again.\n");
    return -1;
}

//searching mail id.if not return 0,if yes return i.
int search_by_mail(struct Address_book *addressbook)
{
    char Mail[35];
    // int found;
    printf(GREEN"Enter the mail id: "RESET);
    scanf("%s",Mail);
    //generate the for loop upto contact count.
    for (int i = 0; i < addressbook->contact_count; i++) 
    {
        if (strcmp(addressbook->contact_details[i].Mail_ID,Mail) == 0) 
        {
            printf("Contact is found\n");
            printf(RED"Name  : %s\n"RESET, addressbook->contact_details[i].Name);
            printf(BLUE"Mobile: %s\n"RESET, addressbook->contact_details[i].Mobile_number);
            printf(GREEN"Email : %s\n"RESET, addressbook->contact_details[i].Mail_ID);
            return i;
            
        }
    }
    
    printf("Error: Mail ID  not found. Try again.\n");
    return -1;
}

//seraching each contact details.
int search_contacts(struct Address_book *addressbook)
{
    int opt;
    while(1)
    {
        //how to search
        printf(GREEN"1.Name\n2.Mobile number\n3.Email id\n4.exit\n"RESET);
        printf("select one option from above menu: ");
        scanf("%d",&opt);

        switch(opt)
        {
            case 1:
                    search_by_name(addressbook);
                    break;
            case 2:
                    search_by_mobile(addressbook);
                    break;
            case 3:
                    search_by_mail(addressbook);
                    break;
            case 4:
                    printf("Exit\n");
                    return 0;
            default:
                    printf("invalid option\n");
                    continue;

        }
    }
}

//if not -1
void edit_contact(struct Address_book *addressbook)
{
    //if no contacts is available.we can't do anything.
    if (addressbook->contact_count == 0) 
    {
        printf("No contacts available to edit.\n");
        return ;
    }

    int choice, found = -1;

    // how to search
    printf("\nHow do you want to search the contact to edit?\n");
    printf(RED"1. By Name\n"RESET);
    printf(BLUE"2. By Mobile Number\n"RESET);
    printf(GREEN"3. By Mail ID\n"RESET);
    printf(BLUE"4. Back to Main Menu\n"RESET);
    printf(RED"Enter your choice: "RESET);
    scanf("%d", &choice);

    switch (choice) 
    {
        case 1: 
                found = search_by_name(addressbook);
                break;
        case 2: 
                found = search_by_mobile(addressbook); 
                break;
        case 3: 
                found = search_by_mail(addressbook); 
                break;
        case 4: 
                return;
        default:
                printf("Invalid choice.\n");
                return;
    }

    if (found == -1) 
    {
        printf("Contact not found.\n");
        return;
    }

    printf("\nHere is the contact you selected:\n");
   
    //if contact is found .which option you want to edit.
    choice;
    do 
    {
        //how to search
        printf("\nWhat do you want to edit?\n");
        printf("1. Name\n");
        printf("2. Mobile Number\n");
        printf("3. Mail ID\n");
        printf("4. All details (Name, Mobile, Mail)\n");
        printf("5. Finish editing\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) 
        {
            case 1: 
            {
                char new_name[50];
                do 
                {
                    printf(RED"Enter new Name: "RESET);
                    scanf(" %[^\n]", new_name);
                } while (!valid_Name(new_name));
                strcpy(addressbook->contact_details[found].Name, new_name);
                printf("Contact Name updated successfully.\n");
                break;
            }
            case 2: 
            {
                char new_mobile[15];
                do 
                {
                    printf(BLUE"Enter new Mobile Number (10 digits): "RESET);
                    scanf(" %s", new_mobile);
                    if (!valid_Mobile(new_mobile))
                        printf("Invalid Mobile!\n");
                    else if (!unique_Mobile(new_mobile, addressbook))
                        printf("This number already exists! Enter another.\n");
                    else 
                    break;
                } while (1);
                strcpy(addressbook->contact_details[found].Mobile_number, new_mobile);
                printf("Mobile Number updated successfully.\n");
                break;
            }
            case 3: 
            {
                char new_mail[50];
                do 
                {
                    printf(GREEN"Enter new Mail ID: "RESET);
                    scanf(" %s", new_mail);
                    if (!valid_mail(new_mail))
                        printf("Invalid Mail format!\n");
                    else if (!unique_mail(new_mail, addressbook))
                        printf("This Mail ID already exists! Enter another.\n");
                    else 
                    break;
                } while (1);
                strcpy(addressbook->contact_details[found].Mail_ID, new_mail);
                printf("Mail ID updated successfully.\n");
                break;
            }
            
            case 4: 
            {
                char new_name[50], new_mobile[15],new_mail[50];

                // Name
                do 
                {
                    printf(RED"Enter new Name: "RESET);
                    scanf(" %[^\n]", new_name);
                } while (!valid_Name(new_name));

                // Mobile
                do 
                {
                    printf(BLUE"Enter new Mobile Number (10 digits): "RESET);
                    scanf(" %s", new_mobile);
                    if (!valid_Mobile(new_mobile))
                        printf("Invalid Mobile!\n");
                    else if (!unique_Mobile(new_mobile, addressbook))
                        printf("This number already exists! Enter another.\n");
                    else break;
                } while (1);
            
                strcpy(addressbook->contact_details[found].Name, new_name);
                strcpy(addressbook->contact_details[found].Mobile_number, new_mobile);
                strcpy(addressbook->contact_details[found].Mail_ID, new_mail);

                // Mail
                do 
                {
                    printf(GREEN"Enter new Mail ID: "RESET);
                    scanf(" %s", new_mail);
                    if (!valid_mail(new_mail))
                        printf("Invalid Mail format!\n");
                    else if (!unique_mail(new_mail, addressbook))
                        printf("This Mail ID already exists! Enter another.\n");
                    else 
                    break;
                } while (1);

                strcpy(addressbook->contact_details[found].Name, new_name);
                strcpy(addressbook->contact_details[found].Mobile_number, new_mobile);
                strcpy(addressbook->contact_details[found].Mail_ID, new_mail);

                printf(RED"All contact details updated successfully.\n"RESET);
                break;
            }
            
            case 5:
                printf(BLUE"Finished editing contact.\n"RESET);
                break;
            default:
                printf("Invalid choice. Try again.\n");
            }
    } while (choice != 5);
}
//whatever you want you can delete it.
int delete_contact(struct Address_book *addressbook)
{
    // If no contacts, we can’t delete anything
    if (addressbook->contact_count == 0) 
    {
        printf("No contacts available to delete.\n");
        return 0;
    }

    int choice, found = -1;

    // Ask user how they want to search the contact
    printf("\nHow do you want to search the contact to delete?\n");
    printf(RED"1. By Name\n"RESET);
    printf(GREEN"2. By Mobile Number\n"RESET);
    printf(BLUE"3. By Mail ID\n"RESET);
    printf(GREEN"4. Back to Main Menu\n"RESET);
    printf("Enter your choice: ");
    scanf("%d", &choice);

    // Call respective search function based on user choice
    switch (choice)
    {
        case 1: 
                found = search_by_name(addressbook);
                break;
        case 2: 
                found = search_by_mobile(addressbook); 
                break;
        case 3: 
                found = search_by_mail(addressbook); 
                break;
        case 4: 
                return 0; // Go back to main menu
        default:
                printf("Invalid choice.\n");
                return 0;
    }

    // If not found, show message and return
    if (found == -1)
    {
        printf("Contact not found.\n");
        return 0;
    }

    // Show the contact before deleting
    printf("\nHere is the contact you selected for deletion:\n");
    printf(RED"Name  : %s\n"RESET, addressbook->contact_details[found].Name);
    printf(GREEN"Mobile: %s\n"RESET, addressbook->contact_details[found].Mobile_number);
    printf(BLUE"Email : %s\n"RESET, addressbook->contact_details[found].Mail_ID);


    // Confirm from user before deleting
    char confirm;
    printf(GREEN"Are you sure you want to delete this contact? (y/n): "RESET);
    scanf(" %c", &confirm);

    // If user confirms, shift all contacts up to remove this one
    if (confirm == 'y' || confirm == 'Y')
    {
        for (int i = found; i < addressbook->contact_count - 1; i++) {
            addressbook->contact_details[i] = addressbook->contact_details[i + 1];
        }
        addressbook->contact_count--;  // reduce count after deletion
        printf(RED"Contact deleted successfully!\n"RESET);
        return 1;
    }
    else 
    {
        printf(BLUE"Deletion cancelled.\n"RESET);
        return 0;
    }
}
