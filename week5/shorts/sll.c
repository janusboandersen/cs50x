#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int val;
    struct node* next;
}
node;

//pointer to the first element in the SLL
node* head = NULL;

//prototypes
void print_last();
void insert_after_third(int to_insert);


int main(void)
{
    
}


//Implementations

void print_last()
{
    //if the list is empty
    if (head == NULL)
    {
        printf("List is empty. No last element.\n");
    }
    
    else
    {
        //traversal pointer
        node* crawler = head;
        
        //until the end of the list
        while (crawler->next != NULL)
        {
            crawler = crawler->next;
        }
        
        //print the last integer
        printf("The last integer is %d\n", crawler->val);
        
    }
    
}

void insert_after_third(int to_insert)
{
    //if the list is empty
    if (head == NULL)
    {
        printf("List is empty. No third position exists.\n");
    }
    
    else
    {
        //traversal pointer
        node* crawler = head;
        
        //set crawler to the third position in the list
        for (int i = 1; i < 3; i++)
        {
            //if already at the end of the list, return
            if (crawler->next == NULL)
            {
                printf("List not long enough.\n");
                return;
            }
            
            //Else keep traversing the list
            else
                crawler = crawler->next;
                
        }
        
        //Initialize a new node to be inserted
        node* new_node = malloc(sizeof(node));
        if (new_node == NULL)
        {
            printf("Out of memory error.\n");
            return;
        }
        
        // Initialize the new node values
        new_node->val = to_insert;
        new_node->next = NULL;
        
        
        // Fix Pointers: new_node next field points to previous fourth
        new_node->next = crawler->next;
        
        //Pointers: previous third now points to new_node
        crawler->next = new_node;
    }
}