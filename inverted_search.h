#ifndef INVERTED_SEARCH_H
#define INVERTED_SEARCH_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define SIZE 28

#define SUCCESS 0
#define FAILURE -1

typedef struct subnode
{
    char filename[50];
    int word_count;
    struct subnode *link;

} SubNode;


typedef struct node
{
    char word[50];
    int file_count;

    SubNode *sub_link;
    struct node *main_link;

} MainNode;


/* Validation */
int read_and_validate_args(int argc, char *argv[]);


/* Create database */
int create_database(char *argv[], MainNode *head[]);


/* Display database */
int display_database(MainNode *head[]);


/* Search database */
int search_database(MainNode *head[], char *word);


/* Save database */
int save_database(MainNode *head[], char *backup_file);


/* Update database */
int update_database(MainNode *head[], char *backup_file);


/* Hash function */
int get_index(char *word);

#endif