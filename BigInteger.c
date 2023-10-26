#include <stdio.h>
#include <stdlib.h>
#include "BigInteger.h"

struct node* createNode(int data) {
    struct node* newNode = (struct node*)malloc(sizeof(struct node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void insertInFront(struct BigInteger* a, int val) {
    struct node *temp = createNode(val);
    if (a->head == NULL)
        a->head = temp;
    else {
        temp->next = a->head;
        a->head = temp;
    }
}


struct BigInteger initialize(char* s) {
    struct BigInteger a;
    a.head = NULL;
    for (int i = 0; s[i] != '\0'; i++) {
        insertInFront(&a, s[i] - '0');
    }
    return a;
}

void removeLeadingZeros(struct BigInteger* a) {
    struct node *num=a->head;
    while (num != NULL && num->data == 0) {
        struct node* temp = num;
        num = num->next;
        free(temp);
    }
}

int compareLists(struct BigInteger a, struct BigInteger b) {
    struct node *num1=a.head;
    struct node *num2=b.head;
    while (num1 != NULL && num2 != NULL) {
        if (num1->data > num2->data) return 1;
        if (num1->data < num2->data) return -1;
        num1 = num1->next;
        num2 = num2->next;
    }

    
    if (num1 == NULL && num2 == NULL)
    return 0;

    if (num1 != NULL)
    return 1;

    
    return -1;
}


struct BigInteger add(struct BigInteger a, struct BigInteger b) {
    struct BigInteger result;
    result.head = NULL;
    int carry = 0;
    struct node* num1 = a.head;
    struct node* num2 = b.head;

    while (num1 != NULL || num2 != NULL || carry) {
        int sum = carry;
        if (num1 != NULL) {
            sum += num1->data;
            num1 = num1->next;
        }
        if (num2 != NULL) {
            sum += num2->data;
            num2 = num2->next;
        }

        carry = sum / 10;
        sum = sum % 10;

        insertInFront(&result, sum);
    }

    return result;
}

struct BigInteger sub(struct BigInteger a, struct BigInteger b) {
    struct BigInteger result;
    result.head = NULL;
    int borrow = 0;
    struct node* num1 = a.head;
    struct node* num2 = b.head;
    int d=0;

    while (num1 != NULL || num2 != NULL) {

        d=borrow;
        
        if (num1 != NULL) {
            d+= num1->data;
            num1 = num1->next;
        }
        if (num2 != NULL) {
            d-= num2->data;
            num2 = num2->next;
        }
        

        if(d<0)
        {
            borrow=-1;
            d+=10;
        }
        else
        borrow=0;


        insertInFront(&result, d);
    }

    return result;
}


struct BigInteger reverse(struct BigInteger a)
{
    struct node *prev = NULL, *current = a.head, *next;
    while (current != NULL)
    {
        next  = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    a.head=prev;
    return a;
}

struct node* addTwoLinkedList(struct node* l1, struct node* l2) {
    struct node *prev = l1;
    int carry = 0;
    while (l2 != NULL || carry != 0) {
        int sum = carry 
        + (prev->next != NULL ? prev->next->data : 0) 
        + (l2 != NULL ? l2->data : 0);
        carry = sum / 10;
        sum = sum % 10;
        if (prev->next != NULL)
            prev->next->data = sum;
        else
            prev->next = createNode(sum);
        if (l2 != NULL)
            l2 = l2->next;
        prev = prev->next;
    }
    return l1;
}

struct node* multiplyLinkedListWithDigit(struct BigInteger a, int digit) {
    struct node* ans = createNode(-1); 
    struct node* curr = ans;
    int carry = 0;
    struct node *l1=a.head;
    while (l1 != NULL || carry != 0) {
        int sum = carry + (l1 != NULL ? (l1->data * digit) : 0);
        carry = sum / 10;
        sum = sum % 10;
        curr->next = createNode(sum);
        if (l1 != NULL)
            l1 = l1->next;
        curr = curr->next;
    }
    return ans->next;
}

struct BigInteger mul(struct BigInteger a, struct BigInteger b) {

    struct node* ans = createNode(-1); 
    struct node* ans_itr = ans;
    struct node* b_itr = b.head;
    struct BigInteger result;
    result.head=NULL;
    while (b_itr != NULL) {
        struct node* head = multiplyLinkedListWithDigit(a, b_itr->data);
        b_itr = b_itr->next;
        ans_itr = addTwoLinkedList(ans_itr,head);
        ans_itr = ans_itr->next;
    }
    
    ans = ans->next;
    result.head=ans;
    return reverse(result);
}

struct BigInteger div1(struct BigInteger num1, struct BigInteger num2) {
    
    if (num2.head == NULL) {
        printf("Division by zero is not allowed.\n");
        return num2;
    }
    struct BigInteger result,dividend;
    result.head=NULL;
    dividend.head=NULL;
    struct node* current = num1.head;
    

    while (current != NULL) {
        insertInFront(&dividend, current->data);
        removeLeadingZeros(&dividend);

        int quotient = 0;
        while (compareLists(dividend, num2) >= 0) {
            dividend = sub(dividend, num2);
            quotient++;
        }

        insertInFront(&result, quotient);

        current = current->next;
    }

    
    removeLeadingZeros(&result);

    

    
    if (result.head == NULL) {
        insertInFront(&result, 0);
    }

    return result;
}   



struct BigInteger mod(struct BigInteger a, struct BigInteger b) {
    struct BigInteger result;
    result.head=NULL;
    struct BigInteger temp;
    temp.head=NULL;
    struct node *t=temp.head;
    struct node *num1=a.head;
    struct node *num2=b.head;


    
    while (num1 != NULL) {
        
        insertInFront(&temp, num1->data);
        while (t != NULL && num1 != NULL && num1->data >= num2->data) {
            int quotient = num1->data / num2->data;
            int remainder = num1->data % num2->data;
            num1->data = remainder;
            num1 = num1->next;
        }
        
       
        if (num1 != NULL) {
            num1 = num1->next;
        }
    }

    while (t != NULL) {
        insertInFront(&result, t->data);
        t = t->next;
    }

    return result;
}




void display(struct BigInteger a) {
    struct node* temp = a.head;
    while (temp != NULL) {
        printf("%d", temp->data);
        temp = temp->next;
    }
}




