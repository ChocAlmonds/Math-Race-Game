#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#define SIZE 500
#define ROUNDS 10

/* is_invalid_option checks if the input is valid for picking the operations */
int is_invalid_option(char *option) {
    int opt;
    int i = 0;
    
    /* While loop checks if the input is a float */
    while (option[i++] != '\0') {
        if (option[i] == '.' || isdigit(option[i])) {
            return 1;
        }
    }
    /* if not a float, convert the string into a int */
    sscanf(option, "%d", &opt);

    if (opt  < 1 || opt > 5) {
        return 1;
    }
    
    return 0;
}

/* multiple_choice func randomizes the answer choices */
void multiple_choice(int *nums, int solution) {
    int i;
    int rand_ind = rand() % 3 ;
    nums[rand_ind] = solution;

    for (i = 0; i < 3; i++) {
        if (nums[i] == solution) {
            continue;
        }
        nums[i] = rand() % 101;
    }
}

/* the answer for multiplication would be too obvious  if the solution was the only big number */
/* so the function makes sure that the other choices are similar*/
void multiple_choice_multiplication(int *nums, int solution) {
    int i;
    int rand_ind = rand() % 3 ;
    int num1 = rand() % 100 + 1;
    int num2 = rand() % 100 + 1;
    nums[rand_ind] = solution;

    for (i = 0; i < 3; i++) {
        if (nums[i] == solution) {
            continue;
        }
        num1 = rand() % 100 + 1;
        num2 = rand() % 100 + 1;
        nums[i] = num1 * num2;
    }
}

/* print_choices prints the the answers with the corresponding letters */
void print_choices(char *choices, int *nums) {

    int i;

    for (i = 0; i < 3; i++) {
        printf("%c %d\n", choices[i], nums[i]);
    }
    printf("\n");

}

/*check_answer checks if the user chose the right answer*/
int check_answer(int *answer_choice, char answer, int sum) {
    switch (tolower(answer)) {
        case 'a':
            if (answer_choice[0] == sum) {
                printf("Correct!\n\n");
                return 1;
            }
            else {
                printf("Incorrect!\n\n");
                return 0;
            }
            break;
        case 'b':
            if (answer_choice[1] == sum) {
                printf("Correct!\n\n");
                return 1;
            }
            else {
                printf("Incorrect!\n\n");
                return 0;
            }
            break;
        case 'c':
            if (answer_choice[2] == sum) {
                printf("Correct!\n\n");
                return 1;
            }
            else {
                printf("Incorrect!\n\n");
                return 0;
            }
            break;
        default:
            printf("Not a valid option.\n\n");
            break;
    }
    return 0;
}

/* Get input from the user for their answer */
char get_answer(void) {
    char buffer[5];
    char answer;

    printf("Answer: ");
    fgets(buffer, 5, stdin);
    sscanf(buffer, "%c", &answer);

    return answer;
}

/* prints the operations the user chose */
void addition_name(void) {
    printf("\n");
    printf("*******************************\n");
    printf("*    Math R@ce - Addition     *\n");
    printf("*******************************\n\n");
}

/* prints the status line and updates the line depending on the users score */
void race_status(char *line, int line_count, int score_count) {
    int i;

    printf("Race Counter: %d/10\n", score_count);

    if (line_count == 1) {
        line[score_count] = '@';
        line[score_count - 1] = '_';
    }
    
    for (i = 0; i < 11; i++) {
        if (i == 10) {
            printf("%c\n", line[i]);
        }
        printf("%c ", line[i]);
    }
}

/* Message is printed when the race is done */
void end_message(char *name, int score_count) {
    int steps_remaining = ROUNDS - score_count;
    if (score_count == 10) {
        printf("Congratulations %s! You reached the finish line.", name);
    }
    else {
        steps_remaining = ROUNDS - score_count;
        printf("You did not finish the race %s.\n", name);
        printf("You were missing %d steps to reach the finish line.\n", steps_remaining);
    }
}

/* Perfomrs the addition race */
void addition(char *name) {
    int operation_count = 1;
    int sum = 0;
    int num1, num2;
    char line[11] = {'@','_', '_', '_', '_', '_', '_', '_', '_', '_', '%'};
    char letter_choice[3] = {'a', 'b', 'c'};
    int answer_choice[3];
    char answer;
    int score_count = 0;
    int line_count = 0;
    int i;

    /* Name of operation is called */
    addition_name();

    /* loops through the rounds of the game */
    for (i = 0; i < 10; i++) {
        race_status(line, line_count, score_count);
        if (i == 0) {
            printf("<Start>\n\n");
        }
        /* get two random sums and the actual solution */
        num1 = rand() % 100 + 1;
        num2  = rand() % 100 + 1;
        sum = num1 + num2;

        /* show the question number and the operation to be performed */
        printf("Operation %d:\n", operation_count++);
        printf("%d + %d\n", num1, num2);
        /* printf("%d\n", sum); print statement for testing */

        multiple_choice(answer_choice, sum);

        /* loop allows for both lower and and upper case answers */
        do {
            print_choices(letter_choice, answer_choice);
            answer = get_answer();
            line_count = check_answer(answer_choice, answer, sum);
        } while (tolower(answer) != 'a' && tolower(answer) != 'b' && tolower(answer) != 'c');

        score_count += line_count;
    }
    race_status(line, line_count, score_count);
    end_message(name, score_count);
}

/* Prints the Subraction operation name */
void subtraction_name(void) {
    printf("\n");
    printf("*******************************\n");
    printf("*   Math R@ce - Substraction  *\n");
    printf("*******************************\n\n");
}

/* Performs the subtraction race */
void subtraction(char *name) {
    int operation_count = 1;
    int difference = 0;
    int num1, num2;
    char line[11] = {'@','_', '_', '_', '_', '_', '_', '_', '_', '_', '%'};
    char letter_choice[3] = {'a', 'b', 'c'};
    int answer_choice[3];
    char answer;
    int score_count = 0;
    int line_count = 0;
    int i;

    subtraction_name();

    for (i = 0; i < ROUNDS; i++) {
        race_status(line, line_count, score_count);
        if (i == 0) {
            printf("<Start>\n\n");
        }

        /* loop validates the operation to prevent negative answers */
        do {
            num1 = rand() % 100 + 1;
            num2  = rand() % 100 + 1;
        } while(num1 < num2);
        difference = num1 - num2;

        printf("Operation %d:\n", operation_count++);
        printf("%d - %d\n", num1, num2);
        /* printf("%d\n", difference); */

        multiple_choice(answer_choice, difference);

        do {
            print_choices(letter_choice, answer_choice);
            answer = get_answer();
            line_count = check_answer(answer_choice, answer, difference);
        } while (tolower(answer) != 'a' && tolower(answer) != 'b' && tolower(answer) != 'c');

        score_count += line_count;
    }
    race_status(line, line_count, score_count);
    end_message(name, score_count);

}

/* Prints the multiplication operation name */
void multiplication_name(void) {
    printf("\n");
    printf("*******************************\n");
    printf("* Math R@ce - Multiplication  *\n");
    printf("*******************************\n\n");
}

void multiplication(char *name) {
    int operation_count = 1;
    int product = 0;
    int num1, num2;
    char line[11] = {'@','_', '_', '_', '_', '_', '_', '_', '_', '_', '%'};
    char letter_choice[3] = {'a', 'b', 'c'};
    int answer_choice[3];
    char answer;
    int score_count = 0;
    int line_count = 0;
    int i;

    multiplication_name();

    for (i = 0; i < ROUNDS; i++) {
        race_status(line, line_count, score_count);
        if (i == 0) {
            printf("<Start>\n\n");
        }

        num1 = rand() % 100 + 1;
        num2  = rand() % 100 + 1;
        product = num1 * num2;

        printf("Operation %d:\n", operation_count++);
        printf("%d * %d\n", num1, num2);
        /* printf("%d\n", product); */

        multiple_choice_multiplication(answer_choice, product);

        do {
            print_choices(letter_choice, answer_choice);
            answer = get_answer();
            line_count = check_answer(answer_choice, answer, product);
        } while (tolower(answer) != 'a' && tolower(answer) != 'b' && tolower(answer) != 'c');

        score_count += line_count;
    }
    race_status(line, line_count, score_count);
    end_message(name, score_count);
}

/* Prints the division operation name */
void division_name(void) {
    printf("\n");
    printf("*******************************\n");
    printf("*    Math R@ce - Division     *\n");
    printf("*******************************\n\n");
}

void division(char *name) {
    int operation_count = 1;
    int quotient = 0;
    int num1, num2;
    char line[11] = {'@','_', '_', '_', '_', '_', '_', '_', '_', '_', '%'};
    char letter_choice[3] = {'a', 'b', 'c'};
    int answer_choice[3];
    char answer;
    int score_count = 0;
    int line_count = 0;
    int i;

    division_name();

    for (i = 0; i < ROUNDS; i++) {
        race_status(line, line_count, score_count);
        if (i == 0) {
            printf("<Start>\n\n");
        }

        /* validates the division operation */
        do {
            num1 = rand() % 100 + 1;
            num2  = rand() % 100 + 1;
        } while(num1 < num2 || num2 == 0 || num1 % num2 != 0);
        quotient = num1 / num2;

        printf("Operation %d:\n", operation_count++);
        printf("%d / %d\n", num1, num2);
        /* printf("%d\n", quotient); */

        multiple_choice(answer_choice, quotient);

        do {
            print_choices(letter_choice, answer_choice);
            answer = get_answer();
            line_count = check_answer(answer_choice, answer, quotient);
        } while (tolower(answer) != 'a' && tolower(answer) != 'b' && tolower(answer) != 'c');

        score_count += line_count;
    }
    race_status(line, line_count, score_count);
    end_message(name, score_count);
}

/* option_select gets input from the user on what operation they want to perform */
int option_select(char *name) {
    char buffer[SIZE];
    char option[SIZE];
    int opt;

    printf("1. Addition\n");
    printf("2. Subtraction\n");
    printf("3. Multiplication\n");
    printf("4. Division\n");
    printf("5. Quit\n\n");

    printf("Select an option: ");
    fgets(buffer, SIZE, stdin);
    sscanf(buffer, "%s", option);

    /* loop to make the user enter the right option */
    while (is_invalid_option(option) == 1) {
        printf("Invalid input. Try again.\n\n");
        printf("Select an option: ");
        fgets(buffer, SIZE, stdin);
        sscanf(buffer, "%s", option);
    }
    sscanf(option, "%d", &opt);

    switch (opt) {
        case 1:
            addition(name);
            break;
        case 2:
            subtraction(name);
            break;
        case 3:
            multiplication(name);
            break;
        case 4:
            division(name);
            break;
        case 5:
            printf("Quitting\n");
            return 1;
            break;
        default:
            printf("Invalid Option. Try again.\n\n");
            break;
    }

    return 0;
}

/* check_return_key makes sure the user enters the return key */
int check_return_key(char key) {
    char buffer[100];
    char enter_key;

    if (key == '\n') {
        return key;
    }

    /* loop to ensure the return key is pressed */
    do {
        printf("Not the enter key. Try again.\n");
        fgets(buffer, 100, stdin);
        sscanf(buffer, "%c", &enter_key);
    } while(enter_key != '\n');

    return enter_key;
}

/* men()u gets input of the user's name and calls option_select to start the race */
int menu(void) {
    char buffer[SIZE];
    char player_name[50];
    char reset;
    int opt_num;

    /* Welcome message is printed */
    printf("\n");
    printf("*******************************\n");
    printf("*     Welcome to Math R@ce    *\n");
    printf("*******************************\n");
    printf("\n");

    /* validate the user's name */
    do {
        if (strlen(player_name) > 35) {
            printf("Enter a name less than or equal to 35 characters: ");
            fgets(buffer, SIZE, stdin);
            sscanf(buffer, "%s", player_name);
            printf("\n");
        }
        else {
            printf("Player's name: ");
            fgets(buffer, SIZE, stdin);
            sscanf(buffer, "%s", player_name);
            printf("\n");
        }
    } while (strlen(player_name) > 35);

    /* loop to keep playing the game when the return key is pressed; quits when the user chooses to */
    do {
        opt_num = option_select(player_name);

        /* checks if the user wants to quit, to break out of loop */
        if (opt_num == 1) {
            break;
        }
        printf("Press <return> to go back to the menu: \n");
        fgets(buffer, SIZE, stdin);
        sscanf(buffer, "%c", &reset);
        reset = check_return_key(reset);
    } while(reset == '\n');

    return 0;
}

int main(void) {
    srand(time(NULL));
    menu();

    return 0;
}

