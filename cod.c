#include<stdio.h>
#include<conio.h>
#include<ctype.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

#define MAX_QUESTIONS 100
#define MAX_LINE_LENGTH 256

typedef struct {
    char question[MAX_LINE_LENGTH];
    char optionA[MAX_LINE_LENGTH];
    char optionB[MAX_LINE_LENGTH];
    char optionC[MAX_LINE_LENGTH];
    char optionD[MAX_LINE_LENGTH];
    char correctanswer;
} Question;

void loadQuestions(Question questions[], int *totalQuestions) {
    FILE *file = fopen("questions.txt", "r");
    if (file == NULL) {
        printf("Error loading the question bank!\n");
        exit(1);
    }
    int i = 0;
    while (i < MAX_QUESTIONS && fgets(questions[i].question, MAX_LINE_LENGTH, file)) {
        fgets(questions[i].optionA, MAX_LINE_LENGTH, file);
        fgets(questions[i].optionB, MAX_LINE_LENGTH, file);
        fgets(questions[i].optionC, MAX_LINE_LENGTH, file);
        fgets(questions[i].optionD, MAX_LINE_LENGTH, file);
        questions[i].correctanswer = fgetc(file);
        fgetc(file);
        i++;
    }
    *totalQuestions = i;
    fclose(file);
}

void shuffleQuestions(int arr[], int n) {
    srand(time(0));
    for (int i = n - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }
}

int main() {
    int countr, count, totalQuestions, i;
    int score;
    char choice;
    char playername[20];
    Question questions[MAX_QUESTIONS];
    int randomIndices[10];
    FILE *f;

    loadQuestions(questions, &totalQuestions);

mainhome:
    system("cls");
    printf("\t\t\tC PROGRAM IQ BASED QUIZ GAME\n");
    printf("\n\t\t\t    WELCOME ");
    printf("\n\t\t\t      TO   ");
    printf("\n\t\t\t   THE GAME");
    printf("\n\n\n\t\t>Press S to start the game");
    printf("\n\t\t>Press V to view the highest score");
    printf("\n\t\t>Press R to reset score");
    printf("\n\t\t>Press H for help");
    printf("\n\t\t>Press Q to quit\n\n\n");

    choice = toupper(getch());
    if (choice == 'V') {
        system("cls");
        char name[20];
        int scr;
        f = fopen("score.txt", "r");
        if (f != NULL) {
            fscanf(f, "%s %d", name, &scr);
            printf("\n\n\t\t%s has secured the Highest Score %d", name, scr);
            fclose(f);
        } else {
            printf("\n\t\tNo records found.");
        }
        getch();
        goto mainhome;

    } else if (choice == 'H') {
    system("cls");
    FILE *helpFile = fopen("help.txt", "r");
    if (helpFile == NULL) {
        printf("Oops! Cannot load the instructions right now!");
        printf("\nHow about you figure it out yourself? It's not rocket science!\n");
    } else {
        char line[MAX_LINE_LENGTH];
        while (fgets(line, sizeof(line), helpFile)) {
            printf("%s", line);
        }
        fclose(helpFile);
    }
    getch();
    goto mainhome;

    } else if (choice == 'R') {
        system("cls");
        f = fopen("score.txt", "w");
        fprintf(f, "NoName 0");
        fclose(f);
        printf("\n\n\t\tScore reset successful!");
        getch();
        goto mainhome;

    } else if (choice == 'Q') {
        exit(1);

    } else if (choice == 'S') {
        system("cls");
        printf("\n\n\n\n\n\t\t\tEnter your name, brave contender: ");
        gets(playername);
        system("cls");
        printf("\n\t\tWelcome, %s! Get ready to prove your skills!", playername);
        printf("\n\n\nBefore you begin, here's how it works:");
        printf("\n>> Face 10 questions to determine your IQ level.");
        printf("\n>> Choose the correct answer by pressing A, B, C, or D.");
        printf("\n>> No penalties for wrong answers - give it your best shot!");
        printf("\n\n\tBEST OF LUCK, %s! Let's begin the adventure!", playername);
        printf("\n\n\nPress Y to start the game!\n");
        printf("\nPress any other key to return to the main menu!");

        if (toupper(getch()) == 'Y') {
            goto home;
        } else {
            goto mainhome;
        }

home:
        system("cls");
        countr = 0;
        for (i = 0; i < totalQuestions; i++) {
            randomIndices[i] = i;
        }
        shuffleQuestions(randomIndices, totalQuestions);
        for (i = 0; i < 10; i++) {
            int qIndex = randomIndices[i];
            system("cls");
            printf("\n\n%s", questions[qIndex].question);
            printf("\n\nA.%s\n\t\tB.%s\nC.%s\n\t\tD.%s", questions[qIndex].optionA, questions[qIndex].optionB, questions[qIndex].optionC, questions[qIndex].optionD);
            char answer = toupper(getch());
            if (answer == questions[qIndex].correctanswer) {
                printf("\n\nCorrect!");
                countr++;
            } else {
                printf("\n\nWrong! The correct answer is %c.", questions[qIndex].correctanswer);
            }
            getch();
        }
        score = (int)countr;
        if (score > 0 && score <= 3) {
            printf("\n\nYOUR IQ LEVEL IS NOVICE!");
            printf("\nYou're just getting started. Keep at it!");
        } else if (score > 3 && score <= 6) {
            printf("\n\nYOUR IQ LEVEL IS EXPLORER!");
            printf("\nNice job! You're on your way - keep it going!");
        } else if (score > 6 && score < 10) {
            printf("\nYOUR IQ LEVEL IS MASTERMIND!");
            printf("\nLooking good! You've got a solid grasp on this.");
        } else if (score == 10) {
            printf("\nYOUR IQ LEVEL IS GENIUS!");
            printf("\nYou nailed it! Awesome work!");
        } else {
            printf("\n\nTHANKS FOR YOUR PARTICIPATION.");
        }
        f = fopen("score.txt", "w");
        if (f != NULL) {
            fprintf(f, "%s %d", playername, score);
            fclose(f);
        }
        printf("\n\nPress Y if you want to play the next game");
        printf("\nPress any other key to return to the main menu");
        if (toupper(getch()) == 'Y') {
            goto home;
        } else {
            goto mainhome;
        }
    }
    return 0;
}
