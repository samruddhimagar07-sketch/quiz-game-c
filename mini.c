#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MAX_ATTEMPTS_EASY   4
#define MAX_ATTEMPTS_MEDIUM  7
#define MAX_ATTEMPTS_HARD    10


void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}


int get_valid_int(const char *prompt, int min, int max) {
    int value;
    char extra;

    while (1) {
        printf("%s", prompt);
        if (scanf("%d%c", &value, &extra) == 2 && extra == '\n') {
            if (value >= min && value <= max) {
                return value;
            }
            printf("  [!] Please enter a number between %d and %d.\n", min, max);
        } else {
            printf("  [!] Invalid input. Enter a whole number.\n");
            clear_input_buffer();
        }
    }
}


void choose_difficulty(int *max_attempts, int *range) {
    printf("\n  Select Difficulty:\n");
    printf("  [1] Easy    1 to 50,  %d attempts\n", MAX_ATTEMPTS_EASY);
    printf("  [2] Medium  1 to 100, %d attempts\n", MAX_ATTEMPTS_MEDIUM);
    printf("  [3] Hard    1 to 200, %d attempts\n", MAX_ATTEMPTS_HARD);

    int choice = get_valid_int("\n  Your choice (1-3): ", 1, 3);

    switch (choice) {
        case 1:
            *max_attempts = MAX_ATTEMPTS_EASY;
            *range = 50;
            printf("\n  [Easy] Guess between 1 and 50. You have %d attempts.\n", *max_attempts);
            break;
        case 2:
            *max_attempts = MAX_ATTEMPTS_MEDIUM;
            *range = 100;
            printf("\n  [Medium] Guess between 1 and 100. You have %d attempts.\n", *max_attempts);
            break;
        case 3:
            *max_attempts = MAX_ATTEMPTS_HARD;
            *range = 200;
            printf("\n  [Hard] Guess between 1 and 200. You have %d attempts.\n", *max_attempts);
            break;
    }
}


void give_hint(int guess, int secret, int range) {
    int diff = abs(guess - secret);
    float percent = (float)diff / range * 100;

    if (guess < secret)
        printf("  >> Too LOW!  ");
    else
        printf("  >> Too HIGH! ");

    if (percent <= 5)
        printf("(You're BURNING HOT!)\n");
    else if (percent <= 15)
        printf("(Very warm...)\n");
    else if (percent <= 30)
        printf("(Getting warmer)\n");
    else if (percent <= 50)
        printf("(Cold)\n");
    else
        printf("(ICE COLD)\n");
}


int calculate_score(int max_attempts, int attempts_used) {
    return (max_attempts - attempts_used + 1) * 100;
}


void play_game() {
    int max_attempts, range;
    choose_difficulty(&max_attempts, &range);

    int secret = (rand() % range) + 1;
    int attempts = 0;
    int guess;
    int won = 0;

    printf("\n  --- Game Start! ---\n\n");

    while (attempts < max_attempts) {
        int remaining = max_attempts - attempts;
        printf("  Attempts left: %d\n", remaining);

        char prompt[50];
        sprintf(prompt, "  Your guess (1-%d): ", range);
        guess = get_valid_int(prompt, 1, range);
        attempts++;

        if (guess == secret) {
            won = 1;
            break;
        }

        give_hint(guess, secret, range);
        printf("\n");
    }

    printf("\n  ==========================================\n");
    if (won) {
        int score = calculate_score(max_attempts, attempts);
        printf("  *** YOU WIN! ***\n");
        printf("  The number was: %d\n", secret);
        printf("  Guessed in %d attempt%s.\n", attempts, attempts == 1 ? "" : "s");
        printf("  Score: %d points\n", score);
    } else {
        printf("  GAME OVER! Out of attempts.\n");
        printf("  The number was: %d\n", secret);
        printf("  Better luck next time!\n");
    }
    printf("  ==========================================\n");
}
int main() {
    srand((unsigned int)time(NULL));

    printf("\n");
    printf("  ==========================================\n");
    printf("       NUMBER GUESSING GAME   \n");
    printf("  ==========================================\n");

    char play_again;

    do {
        play_game();

        printf("\n  Play again? (y/n): ");
        scanf(" %c", &play_again);
        clear_input_buffer();
    } while (play_again == 'y' || play_again == 'Y');

    printf("\n  Thanks for playing! Goodbye!\n\n");
    return 0;
}