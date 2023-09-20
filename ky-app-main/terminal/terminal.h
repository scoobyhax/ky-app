#ifndef TERMINAL_H
#define TERMINAL_H

// Including libraries and files
#include <time.h>
#include <stdbool.h>
#include "../Card/card.h"
#include "../../utils/types.h"

// Function-like-macro
#define charToInt(x) ((x) % 48)

// Structure for the terminal data
typedef struct ST_terminalData_t {
    float transAmount;
    float maxTransAmount;
    uint8_t transactionDate[11];
} ST_terminalData_t;

// Enum for the possible terminal errors
typedef enum EN_terminalError_t {
    tOK, WRONG_DATE, EXPIRED_CARD, INVALID_CARD, INVALID_AMOUNT, EXCEED_MAX_AMOUNT, INVALID_MAX_AMOUNT
} EN_terminalError_t;

// Function prototypes
EN_terminalError_t getTransactionDate(ST_terminalData_t *termData);

EN_terminalError_t isCardExpired(ST_cardData_t cardData, ST_terminalData_t termData);

EN_terminalError_t isValidCardPAN(ST_cardData_t *cardData);

EN_terminalError_t getTransactionAmount(ST_terminalData_t *termData);

EN_terminalError_t isBelowMaxAmount(ST_terminalData_t *termData);

EN_terminalError_t setMaxAmount(ST_terminalData_t *termData);

#endif
