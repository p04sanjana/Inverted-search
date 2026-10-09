#include "inverted_search.h"

int save_database(MainNode *head[], char *backup_file)
{
    FILE *fp;

    fp = fopen(backup_file, "w");

    if (fp == NULL)
    {
        printf("ERROR: Unable to create backup file\n");
        return FAILURE;
    }


    for (int i = 0; i < SIZE; i++)
    {
        MainNode *temp = head[i];

        while (temp != NULL)
        {
            fprintf(fp, "#%d;%s;%d;",
                    i,
                    temp->word,
                    temp->file_count);


            SubNode *sub = temp->sub_link;

            while (sub != NULL)
            {
                fprintf(fp, "%s;%d;",
                        sub->filename,
                        sub->word_count);

                sub = sub->link;
            }

            fprintf(fp, "#\n");

            temp = temp->main_link;
        }
    }

    fclose(fp);

    printf("Database saved successfully in %s\n",
           backup_file);

    return SUCCESS;
}