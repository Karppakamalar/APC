// header files
// validation of input
// calling of func

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "apc.h"

void print_help()
{
    printf("Usage: ./a.exe <number1> <operator> <number2>\n");
    printf("\n");
    printf("Operators:\n");
    printf("+ : Addition\n");
    printf("- : Subtraction\n");
    printf("x : Multiplication\n");
    printf("/ : Division\n");
}

int main(int argc,char *argv[]){

    if(argc<4 || argc>4)
    {
        printf("Invalid number of arguments.\n");
        print_help();
        return 0;
    }

    if((strcmp(argv[2],"+")!=0 ) && (strcmp(argv[2],"-")!= 0) && (strcmp(argv[2],"x")!=0) && 
       (strcmp(argv[2],"/")!=0)){
        printf("Invalid argument. Enter a valid operator\n");
        print_help();
        return 0;
    }

    int sign1 = 1;
    int sign2 = 1;

    char *num1 = argv[1];
    char *num2 = argv[3];

    if(num1[0] == '-')
    {
        sign1 = -1;
        num1++;
    }

    if(num2[0] == '-')
    {
        sign2 = -1;
        num2++;
    }

    Dlist *head1=NULL;
    Dlist *head2=NULL;

    Dlist *tail1=NULL;
    Dlist *tail2=NULL;

    Dlist *reshead=NULL;
    Dlist *restail=NULL;

    create_list(num1,&head1,&tail1);
    create_list(num2,&head2,&tail2);

    if(is_zero(head1))
    {
        sign1 = 1;
    }

    if(is_zero(head2))
    {
        sign2 = 1;
    }

    //add func
    if(strcmp(argv[2],"+")==0)
    {
        int result;

        if(sign1 == sign2)
        {
            add_func(&head1,&tail1,
                     &head2,&tail2,
                     &reshead,&restail);

            if(sign1 == -1 && !is_zero(reshead))
            {
                printf("-");
            }
        }
        else
        {
            result = list_comp(head1,head2);

            if(result == 0)
            {
                insert_at_first(&reshead,&restail,0);
            }
            else if(result > 0)
            {
                sub_func(&head1,&tail1,&head2,&tail2,&reshead,&restail);

                if(sign1 == -1)
                {
                    printf("-");
                }
            }
            else
            {
                sub_func(&head2,&tail2,&head1,&tail1,&reshead,&restail);

                if(sign2 == -1)
                {
                    printf("-");
                }
            }

            rem_leading_zeros(&reshead,&restail);
        }

        Dlist *temp = reshead;

        while(temp != NULL)
        {
            printf("%d",temp->data);
            temp = temp->next;
        }

        printf("\n");
    }
    
    //sub func
    if(strcmp(argv[2],"-")==0)
    {
        int result;

        if(sign1 == 1 && sign2 == 1)
        {
            result = list_comp(head1,head2);

            if(result == 0)
            {
                insert_at_first(&reshead,&restail,0);
            }
            else if(result > 0)
            {
                sub_func(&head1,&tail1,&head2,&tail2,&reshead,&restail);
            }
            else
            {
                printf("-");

                sub_func(&head2,&tail2,&head1,&tail1,&reshead,&restail);
            }
        }

        else if(sign1 == 1 && sign2 == -1)
        {
            add_func(&head1,&tail1,&head2,&tail2,&reshead,&restail);
        }

        else if(sign1 == -1 && sign2 == 1)
        {
            printf("-");

            add_func(&head1,&tail1,&head2,&tail2,&reshead,&restail);
        }
        else
        {
            result = list_comp(head1,head2);

            if(result == 0)
            {
                insert_at_first(&reshead,&restail,0);
            }
            else if(result > 0)
            {
                printf("-");

                sub_func(&head1,&tail1,&head2,&tail2,&reshead,&restail);
            }
            else
            {
                sub_func(&head2,&tail2,&head1,&tail1,&reshead,&restail);
            }
        }

        rem_leading_zeros(&reshead,&restail);

        Dlist *temp = reshead;

        while(temp != NULL)
        {
            printf("%d",temp->data);
            temp = temp->next;
        }

        printf("\n");
    }

    //mul func
    if(strcmp(argv[2],"x")==0)
    {
        mul_func(&head1,&tail1,&head2,&tail2,&reshead,&restail);

        rem_leading_zeros(&reshead,&restail);
        if(sign1 != sign2 && !is_zero(reshead))
        {
            printf("-");
        }

        Dlist *temp = reshead;

        while(temp != NULL)
        {
            printf("%d",temp->data);
            temp = temp->next;
        }

        printf("\n");
    }


    //div func
    if(strcmp(argv[2],"/")==0)
    {
        if(is_zero(head2))
        {
            printf("Error: Division by zero\n");
            free_list(&head1,&tail1);
            free_list(&head2,&tail2);
            return 0;
        }

        div_func(&head1,&tail1,&head2,&tail2,&reshead,&restail);

        rem_leading_zeros(&reshead,&restail);

        if(sign1 != sign2 && !is_zero(reshead))
        {
            printf("-");
        }

        Dlist *temp = reshead;

        while(temp != NULL)
        {
            printf("%d",temp->data);
            temp = temp->next;
        }

        printf("\n");
    }

    free_list(&head1,&tail1);
    free_list(&head2,&tail2);
    free_list(&reshead,&restail);
    return 0;
}
