#include "inverted_search.h"

int update_database(MainNode *head[], char *backup_file)
{
    FILE *fp;

    char buffer[500];

    fp = fopen(backup_file, "r");

    if (fp == NULL)
    {
        printf("ERROR: Backup file not found\n");
        return FAILURE;
    }


    while (fscanf(fp, " %[^\n]", buffer) == 1)
    {
        char *token;

        int index;
        int file_count;


        /* Remove # from beginning */

        token = strtok(buffer, "#");

        if (token == NULL)
            continue;


        /* Index */

        token = strtok(token, ";");

        if (token == NULL)
            continue;

        index = atoi(token);


        /* Word */

        token = strtok(NULL, ";");

        if (token == NULL)
            continue;

        char word[50];

        strcpy(word, token);


        /* File count */

        token = strtok(NULL, ";");

        if (token == NULL)
            continue;

        file_count = atoi(token);


        /* Create main node */

        MainNode *new_main =
            malloc(sizeof(MainNode));

        if (new_main == NULL)
        {
            fclose(fp);
            return FAILURE;
        }

        strcpy(new_main->word, word);

        new_main->file_count = file_count;

        new_main->sub_link = NULL;
        new_main->main_link = NULL;


        /* Create subnodes */

        SubNode *sub_tail = NULL;

        for (int i = 0; i < file_count; i++)
        {
            char *filename;
            char *count;


            filename = strtok(NULL, ";");

            if (filename == NULL)
                break;


            count = strtok(NULL, ";");

            if (count == NULL)
                break;


            SubNode *new_sub =
                malloc(sizeof(SubNode));

            if (new_sub == NULL)
            {
                fclose(fp);
                return FAILURE;
            }

            strcpy(new_sub->filename, filename);

            new_sub->word_count =
                atoi(count);

            new_sub->link = NULL;


            if (new_main->sub_link == NULL)
            {
                new_main->sub_link = new_sub;
            }
            else
            {
                sub_tail->link = new_sub;
            }

            sub_tail = new_sub;
        }


        /* Insert main node */

        if (head[index] == NULL)
        {
            head[index] = new_main;
        }
        else
        {
            MainNode *temp = head[index];

            while (temp->main_link != NULL)
            {
                temp = temp->main_link;
            }

            temp->main_link = new_main;
        }
    }

    fclose(fp);

    printf("Database updated successfully\n");

    return SUCCESS;
}