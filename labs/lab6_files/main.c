#define _CRT_SECURE_NO_WARNINGS
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "locale.h"

#define MAXLINE 1024

int is_snake_case(const char* str) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (isupper(str[i])) return 0;
    }
    return strchr(str, '_') != NULL;
}

int is_small_camel_case(const char* str) {
    if (!islower(str[0])) return 0;
    for (int i = 1; str[i] != '\0'; i++) {
        if (str[i] == '_') return 0;
    }
    return 1;
}

int is_camel_case(const char* str) {
    if (islower(str[0])) return 0;
    for (int i = 1; str[i] != '\0'; i++) {
        if (str[i] == '_') return 0;
    }
    return 1;
}

void snake_to_camel(const char* snake, char* camel) {
    int j = 0;
    int capitalize = 1;
    for (int i = 0; snake[i] != '\0'; i++) {
        if (snake[i] == '_') {
            capitalize = 1;
        }
        else if (capitalize) {
            camel[j++] = toupper(snake[i]);
            capitalize = 0;
        }
        else {
            camel[j++] = snake[i];
        }
    }
    camel[j] = '\0';
}

void small_camel_to_snake(const char* smallCamel, char* snake) {
    int j = 0;
    for (int i = 0; smallCamel[i] != '\0'; i++) {
        if (isupper(smallCamel[i])) {
            snake[j++] = '_';
            snake[j++] = tolower(smallCamel[i]);
        }
        else {
            snake[j++] = smallCamel[i];
        }
    }
    snake[j] = '\0';
}

int main() {
    setlocale(LC_ALL, "Rus");
    FILE* file = fopen("input.txt", "r");
    FILE* file_output = fopen("output.txt", "w");
    if (file == NULL || file_output == NULL) {
        fprintf(file_output, "Ошибка открытия файла.\n");
        return 1;
    }

    int line_count;
    if (fscanf(file, "%d\n", &line_count) != 1) {
        fprintf(file_output, "Ошибка чтения количества строк.\n");
        fclose(file);
        return 1;
    }

    int current_line = 0;

    char* line = (char*) malloc(MAXLINE * sizeof(char));

    fprintf(file_output, "------------------------------------------------------\n");
    while (fgets(line, MAXLINE, file)) {
        char* result = (char*) malloc(((strlen(line) + 1) * 2) * sizeof(char));

        printf("%d ", strlen(line)+1);
        printf("%d\n", ((strlen(line) + 1) * 2));
        line[strcspn(line, "\n")] = '\0';

        if (++current_line > line_count) {
            break;
        }

        if (is_snake_case(line)) {
            fprintf(file_output, "\n%s : ", line);
            snake_to_camel(line, result);
            fprintf(file_output,"snake_case -> CamelCase : %s\n", result);
        }
        else if (is_small_camel_case(line)) {
            fprintf(file_output, "\n%s : ", line);
            small_camel_to_snake(line, result);
            fprintf(file_output, "smallCamelCase -> snake_case : %s\n", result);
        }
        else if (is_camel_case(line)) {
            fprintf(file_output, "\n%s : eto CamelCase\n", line);
            small_camel_to_snake(line, result);
        }
        else {
            fprintf(file_output, "\n%s : vne formata\n", line);
        }
        fprintf(file_output, "\n------------------------------------------------------\n");
        free(result);
    }


    if (current_line < line_count) {
        fprintf(file_output, "!!! количество строк в файле меньше, чем указано !!!\n");
    }

    free(line);

    fclose(file);
    fclose(file_output);
    return 0;
}
