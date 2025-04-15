#include <stdio.h>
#define CSIZE 4

// Define the student structure
struct student {
    char name[50];
    float grades[3];
    float average;
};

// Function prototypes
void get_scores(struct student ar[], int lim);
void find_means(struct student ar[], int lim);
void show_class(struct student ar[], int lim);

int main() {
    // Declare and initialize an array of 4 students
    struct student class[CSIZE] = {
        {"Alice"},
        {"Bob"},
        {"Charlie"},
        {"Diana"}
    };

    // Get scores, calculate averages, and display class data
    get_scores(class, CSIZE);
    find_means(class, CSIZE);
    show_class(class, CSIZE);

    return 0;
}

// Function to acquire scores for each student
void get_scores(struct student ar[], int lim) {
    for (int i = 0; i < lim; i++) {
        printf("Enter grades for %s (3 scores):\n", ar[i].name);
        for (int j = 0; j < 3; j++) {
            printf("Grade %d: ", j + 1);
            scanf("%f", &ar[i].grades[j]);
        }
    }
}

// Function to calculate the average score for each student
void find_means(struct student ar[], int lim) {
    for (int i = 0; i < lim; i++) {
        float sum = 0.0;
        for (int j = 0; j < 3; j++) {
            sum += ar[i].grades[j];
        }
        ar[i].average = sum / 3.0;
    }
}

// Function to display all the information for the class
void show_class(struct student ar[], int lim) {
    printf("\nClass Information:\n");
    for (int i = 0; i < lim; i++) {
        printf("Student: %s\n", ar[i].name);
        printf("Grades: %.2f, %.2f, %.2f\n", ar[i].grades[0], ar[i].grades[1], ar[i].grades[2]);
        printf("Average: %.2f\n\n", ar[i].average);
    }
}