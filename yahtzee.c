// include the C libraries
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>

// macros / global constants
#define ZERO 0
#define ONE 1
#define TWO 2
#define THREE 3
#define FOUR 4
#define FIVE 5
#define SIX 6
#define FALSE 0
#define TRUE 1
#define NAME 20
#define ROLLS 3
#define DICE 5
#define CATEGORY 13
#define COLS 2
#define FULLHOUSE 25
#define SMALLSTR 30
#define LARGESTR 40
#define YAHTZEE 50
#define BONUS 35
#define ISBONUS 63

// struct here
struct Player
{
    int playerNum;
    char playerName[NAME];
    int scoreCard [CATEGORY][COLS];
};

// function prototypes
void welcomeScreen();
void playGame();
void displayEmptyCard();
void displayDice();
int dieRoll();
void sameRandom();
void timeRandom();
void rollDice(int dice[], int keep[]);
int selectDice(int dice[], int keep[]);
void displayRoll(int dice[]);
int isValid(char data[]);
void trimTrailing(char * str);
void initDice(int dice[]);
void initScorecard();
int selectCategory();
void updateScores();
void displayScoreCard();
void scoreUpper();
void scoreLowerKind();
void scoreFullHouse();
void scoreStraight();
void scoreYahtzee();
void scoreChance();
int compare();
int upperTotal();
int upperBonus();
int lowerTotal();
int grandTotal();

// enumerations
enum scores {one, two, three, four, five, six, threekind, fourkind,
                fullhouse, smtr, lgstr, yahtzee, chance};

// main function
int main()
{
    // call function welcomeScreen
    welcomeScreen();

    srand((unsigned int)time(NULL));

    // call function playGame
    playGame();

    //program executed successfully
    return 0;
}

// displays hard coded welcome screen
void welcomeScreen()
{
    printf ("\tY   Y    A    H   H TTTTT ZZZZZ EEEEE EEEEE\n");
    printf ("\t Y Y    A A   H   H   T      Z  E     E\n");
    printf ("\t  Y    A   A  HHHHH   T     Z   EE    EE\n");
    printf ("\t  Y   A  A  A H   H   T    Z    E     E\n");
    printf ("\t  Y   A     A H   H   T   ZZZZZ EEEEE EEEEE\n");
    printf ("\n");
    printf ("\t 1. Five six-sided dice.\n");
    printf ("\t 2. Players roll all five dice.\n");
    printf ("\t 3. Players can roll selected dice three times per turn.\n");
    printf ("\t 4. Players must score one of the 13 categories per turn.\n");
    printf ("\t 5. Players alternate turns.\n");
    printf ("\t 6. Game ends when all players score 13 categories.\n");
    printf ("\t 7. Player with the highest score wins!\n");
}

void playGame()
{
    // declare local variables
    struct Player playerOne;
    struct Player playerTwo;
    int currentPlayer = ONE;
    int loop = ONE;

    // empty arrays for the dice
    int dice[DICE] = {0,0,0,0,0}; // datatype name[array size]
    int keep[DICE] = {0,0,0,0,0};

    // prompt player one for their name and store in array playerOne
    printf ("\nPlayer One, enter your name\n");
    scanf ("%s", playerOne.playerName);

    playerOne.playerNum = ONE;
    initScorecard(playerOne.scoreCard);

    //prompt player two for their name and store in array playerTwo
    printf ("\nPlayer Two, enter your name\n");
    scanf ("%s", playerTwo.playerName);

    playerTwo.playerNum = TWO;
    initScorecard(playerTwo.scoreCard);

    // prompt players to play game
    // %s refers to string variables, and coordinate to variables respectively
    printf ("\n%s and %s let's play Yahtzee!\n", playerOne.playerName, playerTwo.playerName);

    // each player gets 13 times. outputs 26 turns
    while(loop <= 26)
    {
        printf ("Round: %d\n", loop);

        if(currentPlayer == playerOne.playerNum)
        {
            // prompt player it is their turn
            printf ("\n%s it is your turn.\n", playerOne.playerName);

            // call function displayEmptyCard

            //delete later
            //displayEmptyCard();
            displayScoreCard(playerOne.scoreCard);

            // delete this later:
            // displayRandomDice();

            // calls function initDice() and passes array dice and keep to set all values to false
            initDice(dice);
            initDice(keep);

            // clears last input
            fflush(stdin);


            // passes arrays dice and keep into function rollDice
            rollDice(dice, keep);

            int category = selectCategory();
            updateScores(dice, playerOne.scoreCard, category);
            displayScoreCard(playerOne.scoreCard);

            //switch players
            currentPlayer = playerTwo.playerNum;

        }

        else if(currentPlayer == playerTwo.playerNum)
        {
            // prompts player it is their turn
            printf ("\n%s it is your turn.\n", playerTwo.playerName);

            // the following block of code repeats what was completed for player ONE

            // delete later:
            // displayEmptyCard();
            displayScoreCard(playerTwo.scoreCard);

            initDice(dice);
            initDice(keep);

            fflush(stdin);

            rollDice(dice, keep);

            int category = selectCategory();
            updateScores(dice, playerTwo.scoreCard, category);
            displayScoreCard(playerTwo.scoreCard);
            currentPlayer = playerOne.playerNum;
        }

        // increment the loop control variable
        loop++;
    }
}

// function displays a hard-coded version of a Yahtzee card
void displayEmptyCard()
{
    printf ("+-------------------------------+\n");
    printf ("| UPPER SECTION | LOWER SECTION |\n");
    printf ("|-------------------------------|\n");
    printf ("|-------------------------------|\n");
    printf ("| Aces   |      | 3 Kind  |     |\n");
    printf ("|-------------------------------|\n");
    printf ("| Twos   |      | 4 Kind  |     |\n");
    printf ("|-------------------------------|\n");
    printf ("| Threes |      | Full Hs |     |\n");
    printf ("|-------------------------------|\n");
    printf ("| Fours  |      | Sm Str  |     |\n");
    printf ("|-------------------------------|\n");
    printf ("| Fives  |      | Lg Str  |     |\n");
    printf ("|-------------------------------|\n");
    printf ("| Sixes  |      | Yahtzee |     |\n");
    printf ("|-------------------------------|\n");
    printf ("| Total  |      | Chance  |     |\n");
    printf ("|-------------------------------|\n");
    printf ("| Bonus  |      | Total   |     |\n");
    printf ("|-------------------------------|\n");
    printf ("|-------------------------------|\n");
    printf ("|             Game Total  |     |\n");
    printf ("+-------------------------------+\n");
    return;
}

// function displays hard-coded dice
void displayDice()
{
    printf("+---+ +---+ +---+ +---+ +---+\n");
    printf("| 6 | | 3 | | 5 | | 2 | | 4 |\n");
    printf("+---+ +---+ +---+ +---+ +---+\n");

}

// function displays a randomly generated dice for three rolls
void displayRandomDice()
{
    int roll;
    int die1;
    int die2;
    int die3;
    int die4;
    int die5;

    //rolls 3 times
    for (roll = ZERO; roll < ROLLS; roll++)
        {
            die1 = dieRoll();
            die2 = dieRoll();
            die3 = dieRoll();
            die4 = dieRoll();
            die5 = dieRoll();

            printf("Roll %d\n", (roll+1));
            printf("+---+ +---+ +---+ +---+ +---+\n");
            printf("| %d | | %d | | %d | | %d | | %d |\n", die1, die2, die3, die4, die5);
            printf("+---+ +---+ +---+ +---+ +---+\n");
        }
}

// randomly rolls a die
int dieRoll()
{
    // declares and initializes the variable
    int dieValue = rand() % SIX + ONE;

    // returns the value
    return dieValue;
}

// sets all values in the array to 0, or FALSE
void initDice(int dice[DICE])
{
    int i;
    for (i = 0; i < DICE; i++) {
        dice[i] = FALSE;
    }
}

// displays the three rolls, which dice are kept, and if the one kept is invalid.
void rollDice(int dice[DICE], int keep[DICE])
{
    // to store the number of rolls
    int roll = ZERO;
    int i;

    // rolls the dice 3 times
    while (roll < ROLLS)
        {
            printf("Roll number : %d \n", (roll + 1));

            // determines which dice to keep
            for (i = 0; i < DICE; i++) {
                if(keep[i] == FALSE) {
                    dice[i] = dieRoll();
                }
            }

            // calls function displayRoll passing array dice as an argument
            displayRoll(dice);

            // asks user to reselect dice if their selection was out of bounds
            if(selectDice(dice, keep) == FALSE) {
                printf("Invalid dice roll. Please try again\n");
                }
            // increments roll
            else {
                roll += 1;
            }
        }
        return;
}

// allows users to select which dice to keep
int selectDice(int dice[DICE], int keep[DICE])
{
    char input[NAME];
    char data[NAME];

    char * value;

    int valid = FALSE;

    // prompts users to select the dice, and passes their selection into array input
    printf("Select which dice you'd like to keep:\n");
    fgets(input, NAME, stdin);

    // calls function trimTrailing passing array input
    trimTrailing(input);

    // copies values from input into data
    strcpy(data, input);

    // calls function isValid
    valid = isValid(data);

    if (!valid)
    {
        return FALSE;
    }
    // calls initDice passing array keep to reset the array keep
    initDice(keep);
    value = strtok(input, " ");

    // while loop checks each input, and sets each corresponding position in
    // array keep to true.
    // also sets valid to true if the input is within 1 to 5
    while(value != NULL) {
        int number = atoi(value);
        if (number == 1) {
            keep[0] = TRUE;
            valid = TRUE;
        }
        else if (number == 2) {
            keep[1] = TRUE;
            valid = TRUE;
        }
        else if (number == 3) {
            keep[2] = TRUE;
            valid = TRUE;
        }
        else if (number == 4) {
            keep[3] = TRUE;
            valid = TRUE;
        }
        else if (number == 5) {
            keep[4] = TRUE;
            valid = TRUE;
        }
        value = strtok(NULL, " ");
    }
    return valid;
}

// displays array dice
void displayRoll(int dice[DICE])
{
    printf("\n+---+ +---+ +---+ +---+ +---+\n");
    int i;
    for(i = 0; i < DICE; i++) {
        printf("| %d | ", dice[i]);
    }
    printf("\n+---+ +---+ +---+ +---+ +---+\n");
    printf(" (1)   (2)   (3)   (4)   (5) \n");
}

// checks if the user input for array data is valid
int isValid(char data[NAME])
{
    char * value;
    int valid = FALSE;

    value = strtok(data, " ");

    // checks if each pointer in the array is within 1 and 5
    while(value != NULL) {
        int number = atoi(value);
        if(number >= ONE && number <= FIVE) {
            valid = TRUE;
        }
        else {
            valid = FALSE;
            break;
        }
        // sets value = NULL
        value = strtok(NULL, " ");
    }
    return valid;
}

// removes all extra spaces
void trimTrailing(char * str)
{
    // Set default index to invalid number
    int index = -1;
    // loop control variable
    int i = 0;
    // Find last index of non-white space character
    while(str[i] != '\0')
    {
        if(str[i] != ' ' && str[i] != '\t' && str[i] != '\n')
        {
            index = i;
        }
        i++;
    }
    // Mark next character to last non-white space character as NULL
    str[index + 1] = '\0';
}

void initScorecard (int card[CATEGORY][COLS])
{
    for(int i = ZERO; i < CATEGORY; i++)
    {
        for(int j = ZERO; j < COLS; j++)
        {
            if(j == ZERO)
            {
                card[i][j] = i;
            }
            else
            {
                card[i][j] = ZERO;
            }
        }
    }
}

int selectCategory()
{
    int select = ZERO;
    int valid = FALSE;
    while (valid == FALSE)
    {
        printf("         Select category for dice:\n");
        printf("0.  Ones \n");
        printf("1.  Twos \n");
        printf("2.  Threes \n");
        printf("3.  Fours \n");
        printf("4.  Fives \n");
        printf("5.  Sixes \n");
        printf("6.  Three of a kind \n");
        printf("7.  Four of a kind \n");
        printf("8.  Full house \n");
        printf("9.  Small straight \n");
        printf("10. Large straight \n");
        printf("11. Yahtzee \n");
        printf("12. Chance \n");

        scanf("%d", &select);
        fflush(stdin);

        if(select >= ZERO && select <= CATEGORY)
        {
            valid = TRUE;
        }
        else {
            printf("Your selection was invalid. Please try again.\n");
            valid = FALSE;
        }
    }
    return select;
}

void updateScores (int dice[DICE], int scoreCard[CATEGORY][COLS], int category)
{
    switch (category)
    {
    case one:
        printf("Scoring Ones:\n");
        scoreUpper(dice, scoreCard, category);
        break;
    case two:
        printf("Scoring Twos:\n");
        scoreUpper(dice, scoreCard, category);
        break;
    case three:
        printf("Scoring Threes:\n");
        scoreUpper(dice, scoreCard, category);
        break;
    case four:
        printf("Scoring Fours:\n");
        scoreUpper(dice, scoreCard, category);
        break;
    case five:
        printf("Scoring Fives:\n");
        scoreUpper(dice, scoreCard, category);
        break;
    case six:
        printf("Scoring Sixes:\n");
        scoreUpper(dice, scoreCard, category);
        break;
    case threekind:
        printf("Scoring Three of a kind:\n");
        scoreLowerKind(dice, scoreCard, category);
        break;
    case fourkind:
        printf("Scoring Four of a kind:\n");
        scoreLowerKind(dice, scoreCard, category);
        break;
    case fullhouse:
        printf("Scoring Full House:\n");
        scoreFullHouse(dice, scoreCard, category);
        break;
    case smtr:
        printf("Scoring Small straight:\n");
        scoreStraight(dice, scoreCard, category);
        break;
    case lgstr:
        printf("Scoring Long Straight:\n");
        scoreStraight(dice, scoreCard, category);
        break;
    case yahtzee:
        printf("Scoring Yahtzee:\n");
        scoreYahtzee(dice, scoreCard, category);
        break;
    case chance:
        printf("Scoring Chance:\n");
        scoreChance(dice, scoreCard, category);
        break;
    }
}
void displayScoreCard(int scoreCard[CATEGORY][COLS])
{
    printf ("+-------------------------------+\n");
    printf ("| UPPER SECTION | LOWER SECTION |\n");
    printf ("|-------------------------------|\n");
    printf ("|-------------------------------|\n");
    printf ("| Aces   |   %d   | 3 Kind  |  %d |\n", scoreCard[one][ONE], scoreCard[threekind][ONE]);
    printf ("|-------------------------------|\n");
    printf ("| Twos   |   %d   | 4 Kind  | %d  |\n", scoreCard[two][ONE], scoreCard[fourkind][ONE]);
    printf ("|-------------------------------|\n");
    printf ("| Threes |   %d   | Full Hs | %d  |\n", scoreCard[three][ONE], scoreCard[fullhouse][ONE]);
    printf ("|-------------------------------|\n");
    printf ("| Fours  |   %d   | Sm Str  | %d  |\n", scoreCard[four][ONE], scoreCard[smtr][ONE]);
    printf ("|-------------------------------|\n");
    printf ("| Fives  |   %d   | Lg Str  | %d  |\n", scoreCard[five][ONE], scoreCard[lgstr][ONE]);
    printf ("|-------------------------------|\n");
    printf ("| Sixes  |   %d   | Yahtzee | %d  |\n", scoreCard[six][ONE], scoreCard[yahtzee][ONE]);
    printf ("|-------------------------------|\n");
    printf ("| Total  |   %d   | Chance  | %d  |\n", upperTotal(scoreCard), scoreCard[chance][ONE]);
    printf ("|-------------------------------|\n");
    printf ("| Bonus  |   %d   | Total   | %d  |\n", upperBonus(scoreCard), lowerTotal(scoreCard));
    printf ("|-------------------------------|\n");
    printf ("|-------------------------------|\n");
    printf ("|             Game Total  |   %d |\n", grandTotal(scoreCard));
    printf ("+-------------------------------+\n");
}

void scoreUpper(int dice[DICE], int scoreCard[CATEGORY][COLS], int category)
{
    int score = 0;
    for (int i = 0; i < DICE; ++i)
    {
        if(dice[i] == category + ONE)
        {
            score += dice[i];
        }
    }
    scoreCard[category][ONE] = score;
}

void scoreLowerKind(int dice[DICE], int scoreCard[CATEGORY][COLS], int category)
{
    int counts[6] = {0,0,0,0,0,0};
    int score = 0;
    for (int i = 0; i < DICE; ++i)
    {
        counts[dice[i] - 1]++ ;
    }
    for (int i = 0; i < DICE; ++i)
    {
        score += dice[i];
    }
    for (int i = 0; i < SIX; ++i)
    {
        if (category == threekind && counts[i] >= 3)
        {
            scoreCard[category][ONE] = score;
        }
        else if (category == fourkind && counts[i] >= 4)
        {
            scoreCard[category][ONE] = score;
        }
    }
}

void scoreFullHouse (int dice[DICE], int scoreCard[CATEGORY][COLS], int category)
{
    int triple = ZERO;
    int pair = ZERO;
    int counts[6] = {0,0,0,0,0,0};

    for(int i = 0; i < DICE; ++i)
    {
        counts[dice[i] - 1]++;
    }
    for(int i = 0; i < SIX; ++i)
    {
        if (counts[i] == THREE) {
            triple = TRUE;
        }
        if (counts[i] == TWO) {
            pair = TRUE;
        }
    }
    if (triple == TRUE && pair == TRUE) {
        scoreCard[category][ONE] = FULLHOUSE;
    }
}

void scoreStraight (int dice[DICE], int scoreCard[CATEGORY][COLS], int category)
{
    qsort(dice, DICE, sizeof(int), compare);
    int unique [5];
    int uniqueSize = 0;

    for(int i = 0; i < DICE; ++i)
    {
        if(uniqueSize == 0 || unique[uniqueSize - 1]!= dice[i])
        {
            unique[uniqueSize++] = dice[i];
        }
    }
    if(category == smtr)
    {
        for(int j = 0; j <= uniqueSize - 4; ++j)
        {
            if(unique[j] == 1 && unique[j+1] == 2 && unique[j+2] == 3 && unique[j+3] == 4 ||
               unique[j] == 2 && unique[j+1] == 3 && unique[j+2] == 4 && unique[j+3] == 5 ||
               unique[j] == 3 && unique[j+1] == 4 && unique[j+2] == 5 && unique[j+3] == 6 )
            {
                scoreCard[category][ONE] = SMALLSTR;
            }
        }
    }
    if(category == lgstr)
    {
        if(unique[0] == 1 && unique[1] == 2 && unique[2] == 3 && unique[3] == 4 && unique[4] == 5 ||
           unique[0] == 2 && unique[1] == 3 && unique[2] == 4 && unique[3] == 5 && unique[4] == 6)
        {
            scoreCard[category][ONE] = LARGESTR;
        }
    }
}

void scoreYahtzee(int dice[DICE], int scoreCard[CATEGORY][COLS], int category)
{
    int isYahtzee = TRUE;
    for(int i = 1; i < DICE; ++i)
    {
        if(dice[i] != dice[0])
        {
            isYahtzee = FALSE;
            break;
        }
    }
    if(isYahtzee == TRUE)
    {
        scoreCard[category][ONE] = YAHTZEE;
    }
}

void scoreChance(int dice[DICE], int scoreCard[CATEGORY][COLS], int category)
{
    int score = ZERO;
    for (int i = 0; i < DICE; ++i)
    {
        score += dice[i];
    }
    scoreCard[category][ONE] = score;
}

int upperTotal(int scoreCard[CATEGORY][COLS])
{
    int total = ZERO;
    for (int i = one; i <= six; ++i)
    {
        total += scoreCard[i][ONE];
    }
    return total;
}

int lowerTotal(int scoreCard[CATEGORY][COLS])
{
    int total = ZERO;
    for (int i = threekind; i <= chance; ++i)
    {
        total += scoreCard[i][ONE];
    }
    return total;
}

int upperBonus(int scoreCard[CATEGORY][COLS])
{
    int total = ZERO;
    if (upperTotal(scoreCard) >= ISBONUS)
    {
        total = BONUS;
    }
    return total;
}

int grandTotal(int scoreCard[CATEGORY][COLS])
{
    int total = upperTotal(scoreCard) + upperBonus(scoreCard) + lowerTotal(scoreCard);
    return total;
}

// Function to compare two integers for qsort
int compare(const void *a, const void *b)
{
return (*(int *)a - *(int *)b);
}
