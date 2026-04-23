#include "inverted.h"

//function definition for create database
void create_database(Slist *head,hash_t *arr)
{

    Slist *temp=head;
    char word_buffer[50];
    int found=0;

    while(temp!=NULL)//traversing the list till last node
    {
        if(file_exists(arr,temp->filename)==1)//checking already file data updated in hash table while update function
        {
            temp=temp->link;//if updated then updating temp
            continue;
        }
        FILE *fptr=fopen(temp->filename,"r");//open file in read mode
        if(fptr==NULL)
        {
            temp=temp->link;
            continue;
        }
        while(fscanf(fptr,"%s",word_buffer)!=EOF)//reading file data word by word
        {
            int ind;
            //finding index of each word
            if(word_buffer[0]>='A' && word_buffer[0]<='Z')
            ind=word_buffer[0]-'A';

            else if(word_buffer[0]>='a' && word_buffer[0]<='z')
            ind=word_buffer[0]-'a';

            else
            ind=26;
        
            if(arr[ind].link==NULL)//checking hash table index link null
            {
                //if null create main node and sub node
                arr[ind].link=create_main_node(word_buffer,temp->filename);//update hash index link with main node
                
            }
            else
            {
                //if not null
                main_node *main=arr[ind].link;
                main_node *prev_main=NULL;
                while(main!=NULL)//traverse main node till last
                {
                    if(strcmp(main->word,word_buffer)==0)//compare word with main node word
                    {
                        //if word found
                        found=1;
                        sub_node *sub=main->sub_link;
                        sub_node *prev_sub=NULL;
                        while(sub!=NULL)//traverse sub nodes till last
                        {
                            if(strcmp(temp->filename,sub->f_name)==0)//check file name same or not
                            {
                                //if file same
                                (sub->word_count)++;//update word count
                                break;
                            }
        
                            prev_sub=sub;//update previous sub node
                            sub=sub->link;//update sub node

                        }

                        if(sub==NULL)//if sub null then file not exist
                        {
                            //create subnode and update previous sub link
                            prev_sub->link=create_sub_node(temp->filename);
                            (main->file_count)++;
                        }
                        else
                        break;

                    }

                    prev_main=main;//update previous main
                    main=main->link;//update main
                }

                if(found==0)//if word not found
                {
                    //create main node and update previous main link
                    prev_main->link=create_main_node(word_buffer,temp->filename);
                }

            }
        }
        fclose(fptr);//close file
        temp=temp->link;//update temp
    }
}

//function definition for create main node
main_node *create_main_node(char *word,char *filename)
{
    main_node *main_new=malloc(sizeof(main_node));//create main node

    if(main_new==NULL)//cheking node created or not
    return NULL;

    //updating main node file count,word,sub link and link
    main_new->file_count=1;
    strcpy(main_new->word,word);
    main_new->link=NULL;
    main_new->sub_link=create_sub_node(filename);
    if(main_new->sub_link==NULL)
    {
        free(main_new);
        return NULL;
    }
    return main_new;
}
//function definition for create sub node
sub_node *create_sub_node(char *filename)
{

    sub_node *sub_new=malloc(sizeof(sub_node));//create sub node

    if(sub_new==NULL)//checking node created or not
    return NULL;

    //updating sub node word count,filename and link 
    sub_new->word_count=1;
    strcpy(sub_new->f_name,filename);
    sub_new->link=NULL;
    
    return sub_new;
}

//function definition to check file exist in hash table 
int file_exists(hash_t *arr, char *filename)
{
    for(int i=0;i<27;i++)//traversing hash table
    {
        main_node *main = arr[i].link;
        while(main)//traversing main node
        {
            sub_node *sub = main->sub_link;
            while(sub)//traversing sub node
            {
                if(strcmp(sub->f_name, filename) == 0)//checking file name with sub node file name
                return 1;//if equal return 1
                sub = sub->link;//update sub 
            }
            main = main->link;//update main
        }
    }
    return 0;
}

//function definition for display function
void display_database(hash_t *arr)
{
    printf("\n%-6s %-8s %-15s %-10s %-15s\n","Index", "FCount", "Word", "WCount", "FileName");
    for(int i=0;i<27;i++)//traversing hash table
    {
        if(arr[i].link!=NULL)//checking link not null
        {
            main_node *main_temp=arr[i].link;
            while(main_temp!=NULL)//traversing main node
            {
                printf("%-6d ",i);//printing index
                printf("%-8d %-15s ",main_temp->file_count,main_temp->word);//printing filecount and word
                sub_node *sub_temp=main_temp->sub_link;
                while(sub_temp!=NULL)//traversing sub node
                {
                    printf("%-10d %-15s ",sub_temp->word_count,sub_temp->f_name);//printing word count and file name
                    sub_temp=sub_temp->link;//updating sub
                }
                main_temp=main_temp->link;//updating main
                printf("\n");
            }
            
        }
    }

}
//function definition for save database
void save_database(hash_t *arr)
{
    char filename[25];
    printf("Enter file name to save database: ");
    scanf(" %s",filename);//reading filename from user
    char *dot=strchr(filename,'.');
    if(dot==NULL || strcmp(dot,".txt")!=0)//checking file has .txt extension
    {
        printf("ERROR: Invalid file extension.File extension should be .txt\n");
        return;
    }
    FILE *fptr=fopen(filename,"w");//open file in read mode
    if(fptr==NULL)//checking file exist or not
    {
        printf("ERROR: Unable to open %s file\n",filename);
        return;
    }
    for(int i=0;i<27;i++)//traversing hash table
    {
        if(arr[i].link!=NULL)
        {
            main_node *main_temp=arr[i].link;
            while(main_temp!=NULL)//traversing main nodes
            {
                //printing all datas in file
                fprintf(fptr,"#%d;",i);
                fprintf(fptr,"%d;%s;",main_temp->file_count,main_temp->word);
                sub_node *sub_temp=main_temp->sub_link;
                while(sub_temp!=NULL)//traversing sub nodes
                {
                    fprintf(fptr,"%d;%s;",sub_temp->word_count,sub_temp->f_name);
                    sub_temp=sub_temp->link;
                }
                main_temp=main_temp->link;
                fprintf(fptr,"#\n");
            }
            
        }
    }
    fclose(fptr);//close file
    printf("INFO: Database saved Successfully\n");
}
//function definition to search data
void search_data(hash_t *arr)
{
    char word[25];
    printf("Enter the word for search: ");
    scanf(" %s",word);//reading word from user
    int ind;

    //finding index
    if(word[0]>='A' && word[0]<='Z')
    ind=word[0]-'A';

    else if(word[0]>='a' && word[0]<='z')
    ind=word[0]-'a';

    else
    ind=26;

    if(arr[ind].link!=NULL)//checking hash index null or not
    {
        main_node *main_temp=arr[ind].link;
        while(main_temp!=NULL)//traversing main nodes
        {
            if(strcmp(main_temp->word,word)==0)//comparing word with main node word
            {
                //if found print details of word present file
                printf("%s is present in %d file(s)\n",word,main_temp->file_count);
                sub_node *sub_temp=main_temp->sub_link;
                while(sub_temp!=NULL)
                {
                    printf("In file %s ,%d time(s)\n",sub_temp->f_name,sub_temp->word_count);
                    sub_temp=sub_temp->link;
                }
                return;
            }
            main_temp=main_temp->link;
        }
    }
    printf("INFO: %s is not found in database\n",word);

}
//function definition for update database
int update_database(hash_t *arr)
{
    char filename[25],line[50];
    printf("Enter the saved file name: ");
    scanf("%s",filename);//read filename from user

    if(validate_files(filename)==FAILURE)//validating file
    return FAILURE;

    FILE *fptr=fopen(filename,"r");//open file in read mode
    while(fscanf(fptr,"%s",line)!=EOF)//reading file line by line
    {
        int len=strlen(line);
        if(line[0]!='#' || line[len-1]!='#')//validating line star with # and end with #
        {
            printf("ERROR: Invalid %s file format\n",filename);
            fclose(fptr);
            return FAILURE;
        }
            main_node *main_new=malloc(sizeof(main_node));//creating main node
            if(main_new==NULL)
            {
                printf("ERROR: main node creation failed\n");
                fclose(fptr);
                return FAILURE;
            }
            //updatng main node data from file
            char *token=strtok(&line[1],";");
            int index=atoi(token);
            main_new->file_count=atoi(strtok(NULL,";"));
            strcpy(main_new->word,strtok(NULL,";"));
            main_new->sub_link=NULL;
            main_new->link=NULL;
            for(int i=0;i<main_new->file_count;i++)//generating loop file count time
            {
                sub_node *sub_new=malloc(sizeof(sub_node));//creating sub node
                //updating sub node data from file
                sub_new->word_count=atoi(strtok(NULL,";"));
                strcpy(sub_new->f_name,strtok(NULL,";"));
                sub_new->link=NULL;

                if(main_new->sub_link==NULL)
                main_new->sub_link=sub_new;

                else
                {
                    sub_node *sub_temp=main_new->sub_link;
                    while(sub_temp->link!=NULL)
                    sub_temp=sub_temp->link;

                    sub_temp->link=sub_new;

                }

            }
        
            main_node *main=arr[index].link;// Get the first main node from the hash table index
            main_node *prev_main=NULL;
            int w_found=0,f_found=0;// Flags to check word and file presence
            while(main!=NULL)// Traverse main node list to check if word already exists
            {
                if(strcmp(main->word,main_new->word)==0)// If word matches
                {
                    w_found=1;//update word found
                    sub_node *sub=main_new->sub_link;
                    
                    // Traverse all sub nodes 
                    while(sub!=NULL)
                        {
                            int f_found=0;
                            sub_node *temp=main->sub_link;
                            sub_node *prev_temp=NULL;
                            while(temp!=NULL)// Traverse existing sub list to check file name
                            {
                                if(strcmp(sub->f_name,temp->f_name)==0)// File already exists
                                {
                                    f_found=1;
                                    break;
                                }
                                prev_temp=temp;
                                temp=temp->link;
                            }
                            if(f_found==0)// If file not found, create new sub node and attach
                            {
                                sub_node *copy=malloc(sizeof(sub_node));
                                // Copy data
                                copy->word_count = sub->word_count;
                                strcpy(copy->f_name, sub->f_name);
                                copy->link = NULL;
                                prev_temp->link = copy;
                                (main->file_count)++;//Increment file count
                            }
                            sub=sub->link;

                        }
                        break;

                }

                prev_main=main;
                main=main->link;
            }
        if(w_found==0)// If word not found in entire main list
        {
            if(arr[index].link==NULL)//if hash index null
            arr[index].link=main_new;// update new main node

            else
            {
                main_node *main_temp=arr[index].link;
                while(main_temp->link!=NULL)// Traverse to end of main list
                main_temp=main_temp->link;

                main_temp->link=main_new;// update new main node at end
            }
        }
        else
        {
            // Word already existed, so free newly created duplicate main node
            sub_node *tmp = main_new->sub_link;
            while(tmp != NULL)// Free all sub nodes
            {
                sub_node *next = tmp->link;
                free(tmp);
                tmp = next;
            }
            free(main_new);//free main node
        }
    }
    fclose(fptr);//close file
    printf("INFO: Updated database successfully\n");
    return SUCCESS;

}