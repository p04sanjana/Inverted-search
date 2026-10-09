#include "inverted_search.h"

int display_database(MainNode *head[])
{
    int empty = 1;

    printf("\n------------------------------------------------------------\n");
    printf("INDEX\tWORD\t\tFILE COUNT\tFILE DETAILS\n");
    printf("------------------------------------------------------------\n");

    for (int i = 0; i < SIZE; i++)
    {
        MainNode *temp = head[i];

        while (temp != NULL)
        {
            empty = 0;

            printf("%d\t%-15s\t%d\t\t",
                   i,
                   temp->word,
                   temp->file_count);

            SubNode *sub = temp->sub_link;

            while (sub != NULL)
            {
                printf("%s(%d) ",
                       sub->filename,
                       sub->word_count);

                sub = sub->link;
            }

            printf("\n");

            temp = temp->main_link;
        }
    }

    printf("------------------------------------------------------------\n");

    if (empty)
    {
        printf("Database is empty\n");
        return FAILURE;
    }

    return SUCCESS;
}