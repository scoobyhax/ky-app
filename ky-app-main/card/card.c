#include "card.h"

char *substr(const char *src, int m, int n) {
    // get the length of the destination string
    int len = n - m;

    // allocate (len + 1) chars for destination (+1 for extra null character)
    char *dest = (char *) malloc(sizeof(char) * (len + 1));

    // start with m'th char and copy `len` chars into the destination
    strncpy(dest, (src + m), len);

    // return the destination string
    return dest;
}

// Function used to get the card's holder name as an input from the user
EN_cardError_t getCardHolderName(ST_cardData_t *cardData) {
    // Define a string for the holder name and get its value from the user
    char holderName[25];
    printf("Enter your card holder name:\n");
    gets(holderName);
    char nameLength = strlen(holderName);

    // Check if the input length is larger than or equal to 20 and smaller than or equal to 24
    if (nameLength >= 20 && nameLength <= 24) {
        // Loop over each character in the name and check if it is a character
        for (int i = 0; i < nameLength; i++) {
            if (holderName[i] >= '0' && holderName[i] <= '9') {
                return WRONG_NAME;
            }
        }
        // Copy the input to the holder name in the card data
        strcpy(cardData->cardHolderName, holderName);
        return OK;
    }
    return WRONG_NAME;
}

// Function used to get the card's expiration date as an input from the user
EN_cardError_t getCardExpiryDate(ST_cardData_t *cardData) {
    // Define a string for the expiration date and get its value from the user
    char expiryDate[6];
    printf("Enter your card expiration date:\n");
    scanf("%s", expiryDate);
    char dateLength = strlen(expiryDate);

    // Check if the length is 5 five characters, and if the middle character is /
    if (dateLength == 5 && expiryDate[2] == '/') {
        // Loop over each character to check if it is an integer except for the middle character
        for (int i = 0; i < dateLength; i++) {
            if (i != 2 && (expiryDate[i] < '0' || expiryDate[i] > '9')) {
                return WRONG_EXP_DATE;
            }
        }

        // Get the month and year as integers and check if the month is a valid month
        char month = atoi(substr(expiryDate, 0, 2));
        char year = atoi(substr(expiryDate, 3, 5));
        if (month < 1 || month > 12) {
            return WRONG_EXP_DATE;
        }
        // Copy the input to the expiration date in the card data
        strcpy(cardData->cardExpirationDate, expiryDate);
        return OK;
    }
    return WRONG_EXP_DATE;
}

// Function used to get the card's primary account number as an input from the user
EN_cardError_t getCardPAN(ST_cardData_t *cardData) {
    // Define a string for the PAN and get its value from the user
    char cardPAN[20];
    printf("Enter your card PAN:\n");
    scanf("%s", cardPAN);
    char panLength = strlen(cardPAN);

    // Check if the input length is larger than or equal to 16 and smaller than or equal to 19
    if (panLength >= 16 && panLength <= 19) {
        // Loop over each character to check if it is an integer
        for (int i = 0; i < panLength; i++) {
            if (cardPAN[i] < '0' || cardPAN[i] > '9') {
                return WRONG_PAN;
            }
        }
        // Copy the input to the PAN in the card data
        strcpy(cardData->primaryAccountNumber, cardPAN);
        return OK;
    }
    return WRONG_PAN;
}
