#include "inverted_search.h"

int search_database(MainNode *head[], char *word)
{
    int index;

    /* Convert to lowercase */

    for (int i = 0; word[i] != '\0'; i++)
    {
        word[i] =
            tolower((unsigned char)word[i]);
    }

    index = get_index(word);

    MainNode *temp = head[index];


    /* Search main node */

    while (temp != NULL)
    {
        if (strcmp(temp->word, word) == 0)
        {
            printf("\nWord found: %s\n",
                   temp->word);

            printf("File count: %d\n",
                   temp->file_count);


            SubNode *sub = temp->sub_link;

            while (sub != NULL)
            {
                printf("%s -> %d\n",
                       sub->filename,
                       sub->word_count);

                sub = sub->link;
            }

            return SUCCESS;
        }

        temp = temp->main_link;
    }

    printf("Word %s not found\n", word);

    return FAILURE;
}