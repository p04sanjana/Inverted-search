#include "inverted_search.h"


int get_index(char *word)
{
    if (isalpha((unsigned char)word[0]))
    {
        return tolower((unsigned char)word[0]) - 'a';
    }
    else if (isdigit((unsigned char)word[0]))
    {
        return 26;
    }
    else
    {
        return 27;
    }
}


int create_database(char *argv[], MainNode *head[])
{
    FILE *fp;
    char word[50];

    for (int i = 1; argv[i] != NULL; i++)
    {
        fp = fopen(argv[i], "r");

        if (fp == NULL)
        {
            printf("ERROR: Unable to open %s\n", argv[i]);
            continue;
        }

        while (fscanf(fp, "%49s", word) == 1)
        {
            int index;

            /* Convert word to lowercase */

            for (int j = 0; word[j] != '\0'; j++)
            {
                word[j] =
                    tolower((unsigned char)word[j]);
            }

            index = get_index(word);

            MainNode *temp = head[index];

            /* Search main node */

            while (temp != NULL)
            {
                if (strcmp(temp->word, word) == 0)
                {
                    break;
                }

                temp = temp->main_link;
            }


            /* Word does not exist */

            if (temp == NULL)
            {
                MainNode *new_main =
                    malloc(sizeof(MainNode));

                if (new_main == NULL)
                {
                    fclose(fp);
                    return FAILURE;
                }

                strcpy(new_main->word, word);

                new_main->file_count = 1;

                new_main->main_link = NULL;
                new_main->sub_link = NULL;


                /* Create subnode */

                SubNode *new_sub =
                    malloc(sizeof(SubNode));

                if (new_sub == NULL)
                {
                    free(new_main);
                    fclose(fp);
                    return FAILURE;
                }

                strcpy(new_sub->filename, argv[i]);

                new_sub->word_count = 1;

                new_sub->link = NULL;


                new_main->sub_link = new_sub;


                /* Insert main node */

                if (head[index] == NULL)
                {
                    head[index] = new_main;
                }
                else
                {
                    MainNode *last = head[index];

                    while (last->main_link != NULL)
                    {
                        last = last->main_link;
                    }

                    last->main_link = new_main;
                }
            }


            /* Word already exists */

            else
            {
                SubNode *sub = temp->sub_link;


                /* Search filename */

                while (sub != NULL)
                {
                    if (strcmp(sub->filename,
                               argv[i]) == 0)
                    {
                        break;
                    }

                    sub = sub->link;
                }


                /* Same file */

                if (sub != NULL)
                {
                    sub->word_count++;
                }


                /* New file */

                else
                {
                    SubNode *new_sub =
                        malloc(sizeof(SubNode));

                    if (new_sub == NULL)
                    {
                        fclose(fp);
                        return FAILURE;
                    }

                    strcpy(new_sub->filename, argv[i]);

                    new_sub->word_count = 1;

                    new_sub->link = NULL;


                    /* Insert subnode */

                    SubNode *last =
                        temp->sub_link;

                    while (last->link != NULL)
                    {
                        last = last->link;
                    }

                    last->link = new_sub;


                    /* Increase file count */

                    temp->file_count++;
                }
            }
        }

        fclose(fp);
    }

    printf("Database created successfully\n");

    return SUCCESS;
}