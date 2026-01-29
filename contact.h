#ifndef CONTACT_H
#define CONTACT_H

#define RESET "\033[0m"
#define RED  "\033[1;31m"
#define GREEN "\033[1;32m"
#define BLUE "\033[1;34m"

struct Contact_data
{
    char Name[32];
    char Mobile_number[11];
    char Mail_ID[35];
};


struct Address_book
{
    struct Contact_data contact_details[100];
    int contact_count;
};

/* Function declarations */
void init_intitalization(struct Address_book *addressbook);
int create_contact(struct Address_book *addressbook);
void list_contacts(struct Address_book *addressbook);
int search_contacts(struct Address_book *addressbook);
void edit_contact(struct Address_book *addressbook);
int delete_contact(struct Address_book *addressbook);
void save_contacts_to_file(struct Address_book *addressbook);
void load_contacts_from_file(struct Address_book *addressbook);

#endif // CONTACT_H
// CONTACT_H        