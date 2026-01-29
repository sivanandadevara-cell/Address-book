/*
Name:DEVARA SIVANANDA KUMAR
Reg no:25017_071
START DATE:14/08/2025
END DATE:30/08/2025
DESCRIPTION:Address book is an application to store and query contacts.such as create,delete,update,edit,search and saving contacts.
Project tile:ADDRESS BOOK
*/

#include <stdio.h>
#include "contact.h"
/* Structure declaration */

int main()
{
    /* Variable and structre defintion */
    int option;
    struct Address_book addressbook;
    addressbook.contact_count = 0;

    
  
    load_contacts_from_file(&addressbook);
    // init_intitalization(&addressbook);

    while (1)
    {
        printf("\n\t\t\t\tAddress book menu\t\t\t\t\n"); /* Give a prompt message for a user */
        printf(BLUE"1.create contact\n2.Display contact\n3.search contact\n4.Edit contact\n5.delete contact\n6.Save contact\n7.Exit\n"RESET);
        printf("Enter the option : ");
        scanf("%d", &option);

        switch (option) /* Based on choosed option */
        {
        case 1:
        {
            create_contact(&addressbook);
            break;
        }
        case 2:
        {
            printf("List contacts \n");
            list_contacts(&addressbook);
            break;
        }
        case 3:
        {
            //printf("Search Contact menu : \n1.Name \n2.Mobile number\n3.Mail ID\n4.Exit\nEnter the option : "); /* Providing menu */
            printf("you entered the searching menu \n");
            search_contacts(&addressbook);
            break;
        }
        case 4:
        {
            //printf("edit Contact menu : \n1.Name \n2.Mobile number\n3.Mail ID\n4.Exit\nEnter the option : "); /* Providing menu */
            printf("you entered the editing menu \n");
            edit_contact(&addressbook);
            break;
        }
        case 5:
        {
           // printf("Delete Contact menu \n1.Name \n2.Mobile number\n3.Mail ID\n4. Exit\nEnter the option : "); /* Providing menu */
            printf("you entered the deleting menu \n");
            delete_contact(&addressbook);
            break;
        }

        case 6:
            printf("Saving contacts \n");
            save_contacts_to_file(&addressbook);
            break;

        case 7:
            printf("INFO : Save and Exit...\n");
            return 0;

        default:
            printf("Invalid option \n");
            break;
        }
    }
    return 0;
}