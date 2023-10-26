#ifndef BIGINTEGER_H
#define BIGINTEGER_H

struct node {
    int data;
    struct node* next;
};

struct BigInteger {
    struct node *head;
};

struct node* createNode(int);
void insertInFront(struct BigInteger* , int);
struct BigInteger initialize(char*);
void removeLeadingZeros(struct BigInteger*);
int compareLists(struct BigInteger, struct BigInteger);
struct BigInteger add(struct BigInteger, struct BigInteger);
struct BigInteger sub(struct BigInteger, struct BigInteger);
struct BigInteger reverse(struct BigInteger);
struct node* addTwoLinkedList(struct node*, struct node*);
struct node* multiplyLinkedListWithDigit(struct BigInteger, int);
struct BigInteger mul(struct BigInteger, struct BigInteger);
struct BigInteger div1(struct BigInteger, struct BigInteger);
struct BigInteger mod(struct BigInteger, struct BigInteger);
void display(struct BigInteger);
#endif




