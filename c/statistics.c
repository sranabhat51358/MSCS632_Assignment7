
#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int read_integer(const char *prompt, int *value) {
    char line[256];

    while (1) {
        printf("%s", prompt);
        fflush(stdout);

        if (fgets(line, sizeof(line), stdin) == NULL) {
            return 0;
        }

        if (line[0] != '\0' &&
            line[0] != '\n' &&
            line[sizeof(line) - 2] != '\n') {
            size_t length = 0;
            while (line[length] != '\0') {
                length++;
            }

            if (length == sizeof(line) - 1 &&
                line[length - 1] != '\n') {
                int ch;
                while ((ch = getchar()) != '\n' && ch != EOF) {}
                printf("Input is too long. Try again.\n");
                continue;
            }
        }

        errno = 0;
        char *end;
        long parsed = strtol(line, &end, 10);

        while (isspace((unsigned char)*end)) {
            end++;
        }

        if (end == line || *end != '\0' || errno == ERANGE ||
            parsed < INT_MIN || parsed > INT_MAX) {
            printf("Invalid input. Please enter an integer.\n");
            continue;
        }

        *value = (int)parsed;
        return 1;
    }
}

void sort_numbers(int numbers[], int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (numbers[j] > numbers[j + 1]) {
                int temp = numbers[j];
                numbers[j] = numbers[j + 1];
                numbers[j + 1] = temp;
            }
        }
    }
}

double calculate_mean(const int numbers[], int size) {
    long double sum = 0.0L;

    for (int i = 0; i < size; i++) {
        sum += numbers[i];
    }

    return (double)(sum / size);
}

double calculate_median(const int numbers[], int size) {
    int *sorted = malloc((size_t)size * sizeof(int));

    if (sorted == NULL) {
        return 0.0;
    }

    for (int i = 0; i < size; i++) {
        sorted[i] = numbers[i];
    }

    sort_numbers(sorted, size);

    double median;
    if (size % 2 == 1) {
        median = sorted[size / 2];
    } else {
        median = ((double)sorted[size / 2 - 1]
                + sorted[size / 2]) / 2.0;
    }

    free(sorted);
    return median;
}

int calculate_mode(const int numbers[], int size,
                   int modes[], int *mode_count) {
    int *sorted = malloc((size_t)size * sizeof(int));

    if (sorted == NULL) {
        return 0;
    }

    for (int i = 0; i < size; i++) {
        sorted[i] = numbers[i];
    }

    sort_numbers(sorted, size);

    int max_frequency = 0;
    int frequency = 1;
    *mode_count = 0;

    for (int i = 1; i <= size; i++) {
        if (i < size && sorted[i] == sorted[i - 1]) {
            frequency++;
        } else {
            if (frequency > max_frequency) {
                max_frequency = frequency;
                *mode_count = 0;
                modes[(*mode_count)++] = sorted[i - 1];
            } else if (frequency == max_frequency) {
                modes[(*mode_count)++] = sorted[i - 1];
            }

            frequency = 1;
        }
    }

    free(sorted);
    return 1;
}

int main(void) {
    int count;

    printf("C - Procedural Statistics Calculator\n");

    while (1) {
        if (!read_integer("Enter the number of integers: ", &count)) {
            fprintf(stderr, "\nInput ended unexpectedly.\n");
            return EXIT_FAILURE;
        }

        if (count > 0) {
            break;
        }

        printf("Please enter a positive number.\n");
    }

    if ((size_t)count > SIZE_MAX / sizeof(int)) {
        fprintf(stderr, "Requested input is too large.\n");
        return EXIT_FAILURE;
    }

    int *numbers = malloc((size_t)count * sizeof(int));

    if (numbers == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        return EXIT_FAILURE;
    }

    for (int i = 0; i < count; i++) {
        char prompt[64];
        snprintf(prompt, sizeof(prompt), "Enter integer %d: ", i + 1);

        if (!read_integer(prompt, &numbers[i])) {
            fprintf(stderr, "\nInput ended unexpectedly.\n");
            free(numbers);
            return EXIT_FAILURE;
        }
    }

    int *modes = malloc((size_t)count * sizeof(int));

    if (modes == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        free(numbers);
        return EXIT_FAILURE;
    }

    printf("\nNumbers: ");
    for (int i = 0; i < count; i++) {
        printf("%d%s", numbers[i], i == count - 1 ? "\n" : ", ");
    }

    printf("Mean: %.2f\n", calculate_mean(numbers, count));
    printf("Median: %.2f\n", calculate_median(numbers, count));

    int mode_count = 0;
    if (!calculate_mode(numbers, count, modes, &mode_count)) {
        fprintf(stderr, "Memory allocation failed while calculating mode.\n");
        free(modes);
        free(numbers);
        return EXIT_FAILURE;
    }

    printf("Mode: ");
    for (int i = 0; i < mode_count; i++) {
        printf("%d%s", modes[i], i == mode_count - 1 ? "\n" : ", ");
    }

    free(modes);
    free(numbers);

    return EXIT_SUCCESS;
}

