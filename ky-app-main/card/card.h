#ifndef CARD_H
#define CARD_H

// Including libraries and files
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../../utils/types.h"

// Structure for the card data
typedef struct ST_cardData_t {
    uint8_t cardHolderName[25];
    uint8_t primaryAccountNumber[20];
    uint8_t cardExpirationDate[6];
} ST_cardData_t;

// Enum for the possible card errors
typedef enum EN_cardError_t {
    OK, WRONG_NAME, WRONG_EXP_DATE, WRONG_PAN
} EN_cardError_t;

// Function prototypes
EN_cardError_t getCardHolderName(ST_cardData_t *cardData);
EN_cardError_t getCardExpiryDate(ST_cardData_t *cardData);
EN_cardError_t getCardPAN(ST_cardData_t *cardData);

#endif