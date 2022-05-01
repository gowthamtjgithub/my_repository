#include <stdio.h>
#include <stdlib.h>

 struct Node{
    int data;
    int empty;
    struct Node* next;
};
//Three pointers are used in the buffer
//buff_start pointer marks the actual starting point of the buffer, it reamains constant throughout the read/write operations
//start pointer marks the node where the latest data has to be added in the buffer
//end pointer marks the node where the least latest data to be read from the buffer
struct ring_buffer{
    struct Node *buff_start;
    struct Node *start;
    struct Node *end;
};

//Creating an empty linked list of given length
struct ring_buffer create_buffer(int size)
{
    struct ring_buffer b;//instance of ring_buffer
    //Creating a new node which acts as starting node for the buffer
    b.start = (struct Node *) malloc(sizeof(struct Node));
    b.start->empty = 1;
    b.start->next = NULL;

    //copying the address of the new node to a pointer
    struct Node *ptr = b.start;

    //creating the buffer of given size
    for(int i=0; i<size-1; i++){
        struct Node *newNode = (struct Node *) malloc(sizeof(struct Node));
        newNode->empty = 1;
        newNode->next = NULL;

        //linking the new node to the starting node
        ptr->next = newNode;

        //shifting the address of the starting node to the new node using the pointer
        ptr = ptr->next;
    }

    //Linking the last node of the buffer to the first node
    ptr->next = b.start;

    //Expression for making the  buffer as circular linked list
    //Making the staring and ending of the buffer as the same node
    b.end = b.start;

    //setting the buffer start pointer to the start pointer
    b.buff_start = b.start;

    return b;
}

void display(struct ring_buffer b)
{

    struct Node* ptr = b.buff_start;
    do{
        if(ptr->empty == 1)
            printf("NULL -> ");
        else
            printf("%d -> ", ptr->data);
        //traversing through the nodes
        ptr = ptr->next;
    }while(ptr != b.buff_start);//stop condition at the buffer start pointer of the buffer
                                //buffer start pointer remains the same
                                // start and end pointers shift with read and write data
    printf("\b\b\b\b   \b\b\b\n");
}

struct ring_buffer write_data(struct ring_buffer b, int data)
{
    //writing the data to the buffer from rear
    b.end->data = data;
    //Assigning the node property 'empty = 0' to indicate that the node has been written some data
    b.end->empty = 0;
    //Shifting the end of the buffer to the next node for the new data to be added
    b.end = b.end->next;

    return b;
}

struct ring_buffer consume_data(struct ring_buffer b)
{
    //Reading or consuming the data from front end
    //condition for data read from a node is 'empty=1'
    b.start->empty = 1;
    //shifting the starting from current node to the next node in buffer
    b.start = b.start->next;

    return b;
}

int main()
{

    struct ring_buffer b = {NULL, NULL};
    int size;
    printf("Enter the fixed size of the buffer: ");
    scanf("%d", &size);

    b = create_buffer(size);

    //writing a value in the buffer
    b = write_data(b, 1);
    display(b);
     b = consume_data(b);
    display(b);
    b = write_data(b, 2);
    display(b);
     b = consume_data(b);
    display(b);
    b = write_data(b, 3);
    display(b);
    b = write_data(b, 4);
    display(b);
    b = write_data(b, 5);
    display(b);
    b = write_data(b, 6);
    display(b);
    b = write_data(b, 7);
    display(b);
    b = write_data(b, 8);
    display(b);

    b = consume_data(b);
    display(b);
    b = write_data(b, 9);
    display(b);
    b = write_data(b, 10);
    display(b);
    b = write_data(b, 11);
    display(b);

    b = consume_data(b);   display(b);
    b = consume_data(b);   display(b);
    b = consume_data(b);   display(b);

    b = write_data(b, 12);  display(b);
    b = write_data(b, 13);  display(b);
    b = consume_data(b);   display(b);


    return 0;
}
