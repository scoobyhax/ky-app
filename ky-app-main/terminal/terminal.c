#include "terminal.h"

// Function used to generate the current data and store it in the transaction date in the terminal data
EN_terminalError_t getTransactionDate(ST_terminalData_t *termData) {
    time_t rawTime;
    time(&rawTime);
    strftime(termData->transactionDate, sizeof(termData->transactionDate), "%d/%m/%Y", localtime(&rawTime));
    return tOK;
}

// Function used to check if the card expired by comparing the card expiration date to the transaction date
EN_terminalError_t isCardExpired(ST_cardData_t cardData, ST_terminalData_t termData) {
    // Get the month and year of card expiration date and transaction date as integers
    char cardMonth = charToInt(cardData.cardExpirationDate[0]) * 10 + charToInt(cardData.cardExpirationDate[1]);
    char cardYear = charToInt(cardData.cardExpirationDate[3]) * 10 + charToInt(cardData.cardExpirationDate[4]);
    char currMonth = charToInt(termData.transactionDate[3]) * 10 + charToInt(termData.transactionDate[4]);
    char currYear = charToInt(termData.transactionDate[8]) * 10 + charToInt(termData.transactionDate[9]);

    // Check if card expiration year is less than transaction year
    if (cardYear < currYear) {
        return EXPIRED_CARD;
    }

    // Check if card expiration year is the same as the transaction year but the card expiration month is less than transaction month
    if (cardYear == currYear && cardMonth < currMonth) {
        return EXPIRED_CARD;
    }
    return tOK;
}

// Function used to check if the card primary account number is a luhn valid number
EN_terminalError_t isValidCardPAN(ST_cardData_t *cardData) {
    // Store the card PAN to a string and get its length
    char pan[20];
    strcpy(pan, cardData->primaryAccountNumber);
    int no = strlen(pan);

    // Loop over each character in the card PAN
    int sum = 0;
    bool isSecond = false;
    for (int i = no - 1; i >= 0; i--) {
        int d = pan[i] - '0';
        // If the integer is in second position, multiply it by 2
        if (isSecond == 1) d *= 2;
        // Add integer divided by 10 and integer modulus of 10 to the summation
        sum += d / 10 + d % 10;
        isSecond = !isSecond;
    }
    // Check if summation is dividable by 10
    if (sum % 10 != 0) return INVALID_CARD;
    return tOK;
}

// Function used to get the transaction amount as an input from the user
EN_terminalError_t getTransactionAmount(ST_terminalData_t *termData) {
    // Define a float for the transaction amount and get its value from the user
    float transactionAmount;
    printf("Enter the transaction amount:\n");
    scanf("%f", &transactionAmount);

    // Check whether the transaction amount is larger than 0 or not
    if (transactionAmount < 0) {
        return INVALID_AMOUNT;
    }
    termData->transAmount = transactionAmount;
    return tOK;
}

// Function used to compare between transaction amount and maximum transaction amount
EN_terminalError_t isBelowMaxAmount(ST_terminalData_t *termData) {
    return (termData->transAmount > termData->maxTransAmount) ? EXCEED_MAX_AMOUNT : OK;
}

// Function used to get the maximum transaction amount as an input from the user
EN_terminalError_t setMaxAmount(ST_terminalData_t *termData) {
    // Define a float for the maximum transaction amount and get its value from the user
    float maxAmount;
    printf("Enter the maximum transaction amount:\n");
    scanf("%f", &maxAmount);

    // Check whether the transaction amount is larger than 0 or not
    if (maxAmount < 0) {
        return INVALID_MAX_AMOUNT;
    }
    termData->maxTransAmount = maxAmount;
    return tOK;
}