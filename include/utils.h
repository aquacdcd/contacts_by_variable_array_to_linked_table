#ifndef UTILS_H
#define UTILS_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>   

typedef struct{
    char name[50];
    char phone[20];
    char email[50];
} contact;

contact *creat_contact();
void safe_free(contact** p);
void ensure_capacity(int *num_ptr,int *capacity_ptr,contact ***contacts_ptr);
void delete_contact(int *num_ptr,contact **contacts);
void print_all_contact(contact **contacts,int num);
void cleanup(contact **contacts,int num);
void sort_contact(contact **contacts,int num);
void save_contacts(contact **contacts,int num);
void load_contacts(int* num,int *capacity,contact ***contacts_ptr);
void add_contact_to_list(contact **contacts,int *num,contact *new_key);
void find_contact(int num,contact **contact);

int add(int a, int b);

#endif
