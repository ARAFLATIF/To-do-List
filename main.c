#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILENAME "todo.txt"
#define MAX_TASK_LENGTH 256

void addTask();
void listTasks();
void removeTask();
void showMenu();

int main() {
    int choice;

    while (1) {
        showMenu();
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // consume newline character

        switch (choice) {
            case 1:
                addTask();
                break;
            case 2:
                listTasks();
                break;
            case 3:
                removeTask();
                break;
            case 4:
                printf("Exiting...\n");
                exit(0);
            default:
                printf("Invalid choice! Please enter a valid option.\n");
        }
    }

    return 0;
}

void showMenu() {
    printf("\nTodo List Application\n");
    printf("1. Add Task\n");
    printf("2. List Tasks\n");
    printf("3. Remove Task\n");
    printf("4. Exit\n");
}

void addTask() {
    FILE *file = fopen(FILENAME, "a");
    if (file == NULL) {
        perror("Unable to open file");
        return;
    }

    char task[MAX_TASK_LENGTH];
    printf("Enter the task: ");
    fgets(task, MAX_TASK_LENGTH, stdin);
    task[strcspn(task, "\n")] = '\0'; // remove newline character

    fprintf(file, "%s\n", task);
    fclose(file);
    printf("Task added successfully.\n");
}

void listTasks() {
    FILE *file = fopen(FILENAME, "r");
    if (file == NULL) {
        perror("Unable to open file");
        return;
    }

    char task[MAX_TASK_LENGTH];
    int taskNumber = 1;
    printf("\nTodo List:\n");

    while (fgets(task, MAX_TASK_LENGTH, file)) {
        task[strcspn(task, "\n")] = '\0'; // remove newline character
        printf("%d. %s\n", taskNumber++, task);
    }

    fclose(file);
}

void removeTask() {
    FILE *file = fopen(FILENAME, "r");
    if (file == NULL) {
        perror("Unable to open file");
        return;
    }

    char **tasks = NULL;
    size_t count = 0;
    char task[MAX_TASK_LENGTH];

    while (fgets(task, MAX_TASK_LENGTH, file)) {
        tasks = realloc(tasks, (count + 1) * sizeof(char *));
        tasks[count] = strdup(task);
        count++;
    }
    fclose(file);

    if (count == 0) {
        printf("No tasks to remove.\n");
        return;
    }

    int taskNumber;
    printf("Enter the task number to remove: ");
    scanf("%d", &taskNumber);
    getchar(); // consume newline character

    if (taskNumber < 1 || taskNumber > count) {
        printf("Invalid task number.\n");
        for (size_t i = 0; i < count; i++) {
            free(tasks[i]);
        }
        free(tasks);
        return;
    }

    file = fopen(FILENAME, "w");
    if (file == NULL) {
        perror("Unable to open file");
        return;
    }

    for (size_t i = 0; i < count; i++) {
        if (i != taskNumber - 1) {
            fprintf(file, "%s", tasks[i]);
        }
        free(tasks[i]);
    }
    free(tasks);
    fclose(file);
    printf("Task removed successfully.\n");
}
