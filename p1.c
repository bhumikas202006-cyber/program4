#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct day  // use consistent lowercase name "day"
{
    char *dayname;   // lowercase to match usage everywhere
    int date;
    char *activity;
};

void create(struct day *day)
{
    day->dayname = (char *)malloc(sizeof(char) * 20);
    day->activity = (char *)malloc(sizeof(char) * 100);

    printf("Enter the day name: ");
    scanf("%19s", day->dayname);  // limit input size to avoid overflow

    printf("Enter the date: ");
    scanf("%d", &day->date);

    printf("Enter the activity for the day: ");
    getchar();  // consume leftover newline

    // Use fgets to allow spaces in activity input
    fgets(day->activity, 100, stdin);

    // Remove trailing newline if present
    size_t len = strlen(day->activity);
    if (len > 0 && day->activity[len - 1] == '\n')
    {
        day->activity[len - 1] = '\0';
    }
}

void read(struct day *calendar, int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("\nEnter details for day %d:\n", i + 1);
        create(&calendar[i]);
    }
}

void display(struct day *calendar, int size)
{
    printf("\nWeek's activity details:\n");
    for (int i = 0; i < size; i++)
    {
        printf("Day %d:\n", i + 1);
        printf("Day name: %s\n", calendar[i].dayname);
        printf("Date: %d\n", calendar[i].date);   // %d for int
        printf("Activity: %s\n\n", calendar[i].activity);
    }
}

void freeMemory(struct day *calendar, int size)
{
    for (int i = 0; i < size; i++)
    {
        free(calendar[i].dayname);
        free(calendar[i].activity);
    }
}

int main()
{
    int size;
    printf("Enter the number of days in the week: ");
    scanf("%d", &size);

    struct day *calendar = (struct day *)malloc(sizeof(struct day) * size);  // sizeof, not "size of"

    if (calendar == NULL)  // comparison operator, not assignment
    {
        printf("Memory allocation failed. Exiting program.\n");
        return 1;
    }

    read(calendar, size);
    display(calendar, size);
    freeMemory(calendar, size);
    free(calendar);

    return 0;
}
