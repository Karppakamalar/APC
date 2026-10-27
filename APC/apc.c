//create func for creating of list to be called from the main func
#include<stdio.h>
#include<stdlib.h>
#include "apc.h"

void create_list(char *str,Dlist **head,Dlist **tail){

    int i=0;
    int data;

    while(str[i]!='\0'){
        data=str[i]-'0'; 
        insert_at_last(head,tail,data);
        i++;
    }
}

int insert_at_last(Dlist **head,Dlist **tail,int data){

    Dlist *new=malloc(sizeof(Dlist));

    if(new==NULL){
        return -1;
    }

    new->data=data;
    new->prev=NULL;
    new->next=NULL;

    if(*head==NULL){
        *head=*tail=new;
        return 1;
    }
   
    new->prev=*tail;
    (*tail)->next=new;
    new->next=NULL;
    *tail=new;

    return 1;

}

int insert_at_first(Dlist **head, Dlist **tail, int data)
{
    Dlist *new = malloc(sizeof(Dlist));

    if(new == NULL)
    {
        return -1;
    }

    new->data = data;
    new->prev = NULL;
    new->next = NULL;

    if(*head == NULL)
    {
        *head =*tail = new;
        return 1;
    }

    new->next = *head;
    (*head)->prev = new;
    *head = new;

    return 1;
}

int add_func(Dlist **head1, Dlist **tail1,Dlist **head2, Dlist **tail2,Dlist **reshead, Dlist **restail){
    Dlist *t1 = *tail1;
    Dlist *t2 = *tail2;

    int carry = 0;
    int res;

    while(t1 != NULL || t2 != NULL)
    {
        if(t1 != NULL && t2 != NULL)
        {
            res = t1->data + t2->data + carry;

            t1 = t1->prev;
            t2 = t2->prev;
        }
        else if(t1 != NULL)
        {
            res = t1->data + 0 + carry;

            t1 = t1->prev;
        }
        else
        {
            res = 0 + t2->data + carry;

            t2 = t2->prev;
        }

        if(res > 9)
        {
            res = res % 10;
            carry = 1;
        }
        else
        {
            carry = 0;
        }

        insert_at_first(reshead, restail, res);
    }

    if(carry)
    {
        insert_at_first(reshead, restail, carry);
    }

    return 1;
}

int list_comp(Dlist *head1, Dlist *head2)
{
    int count1 = 0;
    int count2 = 0;

    Dlist *temp1 = head1;
    Dlist *temp2 = head2;

    while(temp1 != NULL)
    {
        count1++;
        temp1 = temp1->next;
    }

    while(temp2 != NULL)
    {
        count2++;
        temp2 = temp2->next;
    }

    if(count1 > count2)
    {
        return 1;
    }
    else if(count1 < count2)
    {
        return -1;
    }

    temp1 = head1;
    temp2 = head2;

    while(temp1 != NULL)
    {
        if(temp1->data > temp2->data)
        {
            return 1;
        }
        else if(temp1->data < temp2->data)
        {
            return -1;
        }

        temp1 = temp1->next;
        temp2 = temp2->next;
    }

    return 0;
}

int sub_func(Dlist **head1, Dlist **tail1,Dlist **head2, Dlist **tail2,Dlist **reshead, Dlist **restail){
    Dlist *t1 = *tail1;
    Dlist *t2 = *tail2;

    int borrow = 0;
    int res;

    while(t1 != NULL || t2 != NULL)
    {
        if(t1 != NULL && t2 != NULL)
        {
            res = t1->data - t2->data - borrow;

            t1 = t1->prev;
            t2 = t2->prev;
        }
        else if(t1 != NULL)
        {
            res = t1->data - 0 - borrow;

            t1 = t1->prev;
        }
        else
        {
            res = 0 - t2->data - borrow;

            t2 = t2->prev;
        }

        if(res < 0)
        {
            res = res + 10;
            borrow = 1;
        }
        else
        {
            borrow = 0;
        }

        insert_at_first(reshead, restail, res);
    }

    return 1;
}

int mul_func(Dlist **head1, Dlist **tail1,Dlist **head2, Dlist **tail2,Dlist **reshead, Dlist **restail){
    Dlist *t1;
    Dlist *t2 = *tail2;

    Dlist *temphead = NULL;
    Dlist *temptail = NULL;

    Dlist *newhead = NULL;
    Dlist *newtail = NULL;

    int carry;
    int res;
    int zero = 0;
    int i;

    *reshead = NULL;
    *restail = NULL;

    while(t2 != NULL)
    {
        t1 = *tail1;
        carry = 0;

        while(t1 != NULL)
        {
            res = (t1->data * t2->data) + carry;

            insert_at_first(&temphead, &temptail, res % 10);

            carry = res / 10;

            t1 = t1->prev;
        }

        if(carry != 0)
        {
            insert_at_first(&temphead, &temptail, carry);
        }

        for(i = 0; i < zero; i++)
        {
            insert_at_last(&temphead, &temptail, 0);
        }

        add_func(reshead, restail,&temphead, &temptail,&newhead, &newtail);
        free_list(reshead, restail);


        *reshead = newhead;
        *restail = newtail;
        free_list(&temphead, &temptail);


        t2 = t2->prev;
        zero++;

        newhead = NULL;
        newtail = NULL;
    }

    return 1;
}

void free_list(Dlist **head, Dlist **tail)
{
    Dlist *temp;

    while(*head != NULL)
    {
        temp = *head;
        *head = (*head)->next;
        free(temp);
    }

    *tail = NULL;
}

void rem_leading_zeros(Dlist **head, Dlist **tail)
{
    Dlist *temp = *head;

    while(temp != NULL && temp->data == 0 && temp->next != NULL)
    {
        *head = temp->next;
        (*head)->prev = NULL;

        free(temp);

        temp = *head;
    }

    if(*head == NULL)
    {
        *tail = NULL;
    }
    else
    {
        *tail = *head;

        while((*tail)->next != NULL)
        {
            *tail = (*tail)->next;
        }
    }
}

int is_zero(Dlist *head)
{
    while(head != NULL)
    {
        if(head->data != 0)
        {
            return 0;
        }

        head = head->next;
    }

    return 1;
}

int incr_list(Dlist **head, Dlist **tail)
{
    Dlist *temp = *tail;
    int carry = 1;
    int res;

    if(*head == NULL)
    {
        insert_at_first(head, tail, 1);
        return 1;
    }

    while(temp != NULL && carry)
    {
        res = temp->data + carry;

        if(res > 9)
        {
            temp->data = 0;
            carry = 1;
        }
        else
        {
            temp->data = res;
            carry = 0;
        }

        temp = temp->prev;
    }

    if(carry)
    {
        insert_at_first(head, tail, carry);
    }

    return 1;
}

int div_func(Dlist **head1, Dlist **tail1,Dlist **head2, Dlist **tail2,Dlist **reshead, Dlist **restail)
{
    Dlist *remhead = *head1;
    Dlist *remtail = *tail1;

    Dlist *temphead = NULL;
    Dlist *temptail = NULL;

    int cmp;

    *reshead = NULL;
    *restail = NULL;

    if(is_zero(*head2))
    {
        printf("Error: Division by zero\n");
        return -1;
    }

    if(is_zero(*head1))
    {
        insert_at_first(reshead, restail, 0);
        return 1;
    }

    cmp = list_comp(remhead, *head2);

    if(cmp < 0)
    {
        insert_at_first(reshead, restail, 0);
        return 1;
    }

    while(list_comp(remhead, *head2) >= 0)
    {
        sub_func(&remhead, &remtail,head2, tail2,&temphead, &temptail);
        rem_leading_zeros(&temphead, &temptail);

        if(remhead != *head1)
        {
            free_list(&remhead, &remtail);
        }

        remhead = temphead;
        remtail = temptail;

        temphead = NULL;
        temptail = NULL;

        incr_list(reshead, restail);
    }

    if(*reshead == NULL)
    {
        insert_at_first(reshead, restail, 0);
    }

    if(remhead != *head1)
    {
        free_list(&remhead, &remtail);
    }

    return 1;
}