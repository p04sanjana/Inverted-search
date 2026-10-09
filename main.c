#include "inverted_search.h"

int main(int argc, char *argv[])
{
    MainNode *head[SIZE] = {NULL};

    int choice;

    char word[50];
    char backup_file[50];


    /* Validate command line arguments */

    if (read_and_validate_args(argc, argv)
        == FAILURE)
    {
        return FAILURE;
    }


    while (1)
    {
        printf("\n");
        printf("========== INVERTED SEARCH ==========\n");

        printf("1. Create Database\n");
        printf("2. Display Database\n");
        printf("3. Search Database\n");
        printf("4. Save Database\n");
        printf("5. Update Database\n");
        printf("6. Exit\n");

        printf("Enter your choice: ");

        scanf("%d", &choice);


        switch (choice)
        {
            case 1:

                create_database(argv, head);

                break;


            case 2:

                display_database(head);

                break;


            case 3:

                printf("Enter the word to search: ");

                scanf("%49s", word);

                search_database(head, word);

                break;


            case 4:

                printf("Enter backup filename: ");

                scanf("%49s", backup_file);

                save_database(head, backup_file);

                break;


            case 5:

                printf("Enter backup filename: ");

                scanf("%49s", backup_file);

                update_database(head,
                                backup_file);

                break;


            case 6:

                printf("Exiting program...\n");

                return SUCCESS;


            default:

                printf("Invalid choice\n");
        }
    }

    return SUCCESS;
}