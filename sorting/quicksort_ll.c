#include <stdlib.h>
#include <stdio.h>
#include "sort.h"

/* Insert a new node at the beginning of linked list */
void 
quicksort_ll_push( node_t ** head_ref, int new_key )
{
    node_t * new_node = (node_t *)malloc( sizeof(struct node) );
    new_node->key  = new_key;
    new_node->next = (*head_ref);
    (*head_ref)    = new_node;
}

void 
quicksort_ll_dump( node_t *head )
{
    node_t *node = head;

    while(node)
    {
        printf("%d  ", node->key);
        node = node->next;
    }
    printf("\n");
}

node_t *
getTail( node_t *cur )
{
    while (cur != NULL && cur->next != NULL)
        cur = cur->next;
    return cur;
}

// Partitions the list taking the last element as the pivot
static node_t *
partition( node_t *head, 
           node_t *endd, 
           node_t **newHead, 
           node_t **newEnd )
{
    node_t *pivot = endd;
    node_t dummy;
    dummy.next=head;
    node_t *prev = &dummy;
    node_t *curr = head;

    int temp;
    while(curr!=pivot)
    {
        if(curr->key <= pivot->key )
        {
            prev=prev->next;
            temp=curr->key;
            curr->key=prev->key;
            prev->key=temp;
        }

        curr=curr->next;
    }
    temp=prev->next->key;
    prev->next->key=pivot->key;
    pivot->key=temp;
    *newHead=head;
    *newEnd=endd;
    return (prev->next);

}

//here the sorting happens exclusive of the end node
node_t *quickSortRecur(node_t *head, node_t *endd)
{
    // base condition
    if (!head || head == endd)
        return head;

    node_t *newHead = NULL, *newEnd = NULL;

    // Partition the list, newHead and newEnd will be updated
    // by the partition function
    node_t *pivot = partition(head, endd, &newHead, &newEnd);

    // If pivot is the smallest element - no need to recur for
    // the left part.
    if (newHead != pivot)
    {
        // Set the node before the pivot node as NULL
        node_t *tmp = newHead;
        while (tmp->next != pivot)
            tmp = tmp->next;
        tmp->next = NULL;

        // Recur for the list before pivot
        newHead = quickSortRecur(newHead, tmp);

        // Change next of last node of the left half to pivot
        tmp = getTail(newHead);
        tmp->next =  pivot;
    }

    // Recur for the list after the pivot element
    pivot->next = quickSortRecur(pivot->next, newEnd);

    return newHead;
}

// The main function for quick sort. This is a wrapper over recursive
// function quickSortRecur()
void quicksort_ll(node_t **headRef)
{
    (*headRef) = quickSortRecur(*headRef, getTail(*headRef));
    return;
}

