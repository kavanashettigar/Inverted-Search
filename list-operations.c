#include "inverted.h"

int find_node(Slist *head, char *data)
{
    if(head==NULL)//checking list is empty
    return FAILURE;
    Slist *t=head;
    while(t!=NULL) //traverse till last node
    {
        if(strcmp(t->filename,data)==0) //checking given data with node data
        return SUCCESS; //if found return failure
        else
        {
            //update node address 
            t=t->link;
        }
    }
    return FAILURE;
    	
}

int insert_at_last(Slist **head, char *data)
{
    //create a node
    Slist *new=malloc(sizeof(Slist));
    //check node is created or not
    if(new==NULL)
    return FAILURE;
    
    //update value to node
    strcpy(new->filename,data);
    new->link=NULL;
    
    //check node is empty
    if(*head==NULL)
    {
        //update the last node
        *head=new;
        return SUCCESS;
    }
    else
    {
        //node is not empty
        Slist *temp=*head;
        //traverse till last node
        while(temp->link != NULL)
        temp=temp->link;
        //update the last node
        temp->link=new;
        return SUCCESS;
        
    }

}

void print_list(Slist *head)
{
	if (head == NULL)//checking head is null
	{
		printf("INFO : List is empty\n");
	}
    else
    {
	    while (head) //traversing list till last		
	    {
		    printf("%s -> ", head -> filename);//printing data
		    head = head -> link;//updating head
	    }

	    printf("NULL\n");
    }
}


