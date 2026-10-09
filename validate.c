#include "inverted_search.h"

int read_and_validate_args(int argc, char *argv[])
{
    FILE *fp;

    /* Check whether input files are given */

    if (argc < 2)
    {
        printf("ERROR: No input files passed\n");
        return FAILURE;
    }

    /* Check each file */

    for (int i = 1; i < argc; i++)
    {
        fp = fopen(argv[i], "r");

        if (fp == NULL)
        {
            printf("ERROR: File %s does not exist\n", argv[i]);
            return FAILURE;
        }

        fclose(fp);
    }

    /* Check duplicate files */

    for (int i = 1; i < argc; i++)
    {
        for (int j = i + 1; j < argc; j++)
        {
            if (strcmp(argv[i], argv[j]) == 0)
            {
                printf("ERROR: File %s is repeated\n", argv[i]);
                return FAILURE;
            }
        }
    }

    printf("Validation successful\n");

    return SUCCESS;
}