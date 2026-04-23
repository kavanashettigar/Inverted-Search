#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//macro for success and failure
#define SUCCESS 1
#define FAILURE 0

//structure to store valid file names in list
typedef struct node
{
    char filename[25];
    struct node *link;
}Slist;

//structure to store sub nodes
typedef struct node1
{
    int word_count;
    char f_name[25];
    struct node1 *link;
}sub_node;

//structure to store main nodes
typedef struct node2
{
    int file_count;
    char word[25];
    struct node2 *link;
    sub_node *sub_link;
}main_node;

//structure for hash table
typedef struct node3
{
    int index;
    main_node *link;
}hash_t;

//function prototypes
int validate_files(char *file);
main_node *create_main_node(char *word,char *filename);
sub_node *create_sub_node(char *filename);
int file_exists(hash_t *arr, char *filename);

void create_database(Slist *head,hash_t *arr);
void display_database(hash_t *arr);
void search_data(hash_t *arr);
void save_database(hash_t *arr);
int update_database(hash_t *arr);

int insert_at_last(Slist **head, char *data);
int find_node(Slist *head, char *data);
void print_list(Slist *head);