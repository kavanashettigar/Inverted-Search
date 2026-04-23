/*
Name : Kavana
Project Name : Inverted Search
Description : The Inverted Search Project is a file indexing system that stores and organizes words from 
multiple text files for fast searching. It uses a hash table where each unique word is stored in a main 
node, and the files containing that word along with their frequency are stored in sub-nodes using linked 
lists.
The project supports creating the database from files, searching for a word, displaying the indexed data, 
saving the database to a file, and updating the database from a saved file. By avoiding repeated file 
scanning, it reduces search time and improves efficiency.
*/

#include "inverted.h"


int main(int argc,char *argv[])
{
    if(argc<2)//checking atleast 2 argument passed or not
    {
        printf("Invalid arguments\n");
        return 0;
    }
    int db_created=0;//flag variables to create and update funtions
    int db_updated=0;
    Slist *head=NULL;

    hash_t arr[27];
    //initializing hash table index and link
    for(int i=0;i<27;i++)
    {
        arr[i].index=i;
        arr[i].link=NULL;
    }
    int i=1;
    while(argv[i]!=NULL)//validating all files passed through command line
    {
        if(validate_files(argv[i])==SUCCESS)
        {
            if(find_node(head,argv[i])==SUCCESS)
            {
                printf("INFO: %s duplicate found\n",argv[i]);
            }
            else
            {
                insert_at_last(&head,argv[i]);//inserting valid file in linked list
            }
        }
        i++;
    }
    printf("INFO: Valid files are: ");
    print_list(head);

    int opt;

    while(1)
    {
        //printing inverted search menu
        printf("\n:::MENU:::\n");
        printf("\n1.Create database\n2.Display database\n3.Search database\n4.update database\n5.Save\n6.Exit\n\n");
        printf("Enter the option: ");
        scanf("%d",&opt);
        getchar();

        switch(opt)//performing operation based on option
        {
            case 1:
            if(db_created==1)//checking already database created
            {
                printf("INFO: database already created\n");
                break;
            }
            db_created=1;
            create_database(head,arr);//if not created call create function
            printf("INFO: Database created successfully\n");
            break;

            case 2:
            if(db_created==0 && db_updated==0)//if create and update both not done
            printf("INFO: Database is empty\n");//database is empty

            else
            display_database(arr);//call display function
            break;

            case 3:
            search_data(arr);//call search function to search data
            break;

            case 4:
            if(db_updated==1)//checking already database updated or not
            {
                printf("INFO: Database already updated\n");
                break;
            }
    
            if(update_database(arr)==SUCCESS)//if not updated calling update function
            db_updated=1;

            else
            printf("ERROR: Update database failed\n");
            break;

            case 5:
            save_database(arr);//call save function to store database in file
            break;

            case 6:
            return 0;//terminating program

            default:
            printf("ERROR: Invalid Option\n");
        }
    }
}

//funtion definition for validating files
int validate_files(char *file)
{
    char *ch=strchr(file,'.');
    if(ch==NULL || strcmp(ch,".txt")!=0)//checking file has .txt extension
    {
        printf("INFO: %s has invalid extesion\n",file);
        return FAILURE;
    }

    FILE *fptr=fopen(file,"r");//open file in read mode
    if(fptr==NULL)//checking file exist or not
    {
        printf("INFO: %s file does not exist\n",file);
        return FAILURE;
    }
    fseek(fptr,0,SEEK_END);
    if(ftell(fptr)==0)//checking file is empty
    {
        printf("INFO: %s is empty\n",file);
        fclose(fptr);
        return FAILURE;
    }
    fclose(fptr);
    return SUCCESS;
    
   
}
