#ifndef DLL_H
#define DLL_H

typedef struct node{
    int data;
    struct node *prev;
    struct node *next;
}Dlist;

void create_list(char *str,Dlist **head,Dlist **tail);
int insert_at_last(Dlist **head,Dlist **tail,int data);
int insert_at_first(Dlist **head, Dlist **tail, int data);
int add_func(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **reshead, Dlist **restail);
int list_comp(Dlist *head1, Dlist *head2);
int sub_func(Dlist **head1, Dlist **tail1,Dlist **head2, Dlist **tail2,Dlist **reshead, Dlist **restail);
int mul_func(Dlist **head1, Dlist **tail1,Dlist **head2, Dlist **tail2,Dlist **reshead, Dlist **restail);
void free_list(Dlist **head, Dlist **tail);
int div_func(Dlist **head1, Dlist **tail1,Dlist **head2, Dlist **tail2,Dlist **reshead, Dlist **restail);
int incr_list(Dlist **head, Dlist **tail);
void rem_leading_zeros(Dlist **head, Dlist **tail);
int is_zero(Dlist *head);

#endif