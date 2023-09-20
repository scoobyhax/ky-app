#include "app.h"

ST_transaction_t x;

_Noreturn void appStart(void) {
    while (1) {
        // Store the card's holder name and check whether the card's holder name is correct or not, loop until user enters a correct name
        while (getCardHolderName(&x.cardHolderData) == WRONG_NAME) {
            printf("Please enter the correct card holder name.\n");
        }

        // Store the card's expiration date and check whether the card's expiration date is correct or not
        // loop until user enters a correct expiration date
        while (getCardExpiryDate(&x.cardHolderData) == WRONG_EXP_DATE) {
            printf("Please enter the correct expiry date in format MM/YY.\n");
        }

        // Store the card's primary account number and check whether the card's PAN is correct or not, loop until user enters a correct PAN
        while (getCardPAN(&x.cardHolderData) == WRONG_PAN) {
            printf("Please enter the correct PAN.\n");
        }

        // Check whether the PAN is a luhn number or not, loop until users enters a luhn number
        while (isValidCardPAN(&x.cardHolderData) == INVALID_CARD) {
            printf("The PAN isn't a luhn number.\n");
            getCardPAN(&x.cardHolderData);
        }

        // Gets the transaction date
        getTransactionDate(&x.terminalData);

        // Checks whether the card is expired or not, and stops the payment process in case card is expired
        if (isCardExpired(x.cardHolderData, x.terminalData) == EXPIRED_CARD) {
            printf("This card is expired.\nPress any button to restart the payment process.\n");
            getch();
            system("cls");
            continue;
        }

        // Store the transaction amount and check whether the amount is correct or not, loop until user enters a correct amount
        while (getTransactionAmount(&x.terminalData) == INVALID_AMOUNT) {
            printf("Please enter the correct amount of transaction.\n");
        }

        // Store the maximum transaction amount and check whether the amount is correct or not, loop until user enters a correct amount
        while (setMaxAmount(&x.terminalData) == INVALID_MAX_AMOUNT) {
            printf("Please enter the correct maximum amount of transaction.\n");
        }

        // Checks whether the transaction amount is below the the maximum amount, and stops the payment process in that case
        if (isBelowMaxAmount(&x.terminalData) == EXCEED_MAX_AMOUNT) {
            printf("The transaction amount exceeds the maximum amount.\nPress any button to restart the payment process.");
            getch();
            system("cls");
            continue;
        }

        // Store the transaction state
        EN_transState_t state = receiveTransactionData(&x);

        // Check whether the transaction is saved in the database or not
        if (state == INTERNAL_SERVER_ERROR) {
            printf("The transaction isn't saved.\n");
        }

        if (state == APPROVED) { // Check if the transaction is saved
            printf("The transaction is approved.\n");
        } else if (state == DECLINED_INSUFFICIENT_FUND) { // Stop the transaction in case balance is not enough
            printf("Declined, your balance is not enough for this transaction\nPress any button to restart the payment process.");
            getch();
            system("cls");
            continue;
        } else if (state == DECLINED_STOLEN_CARD) { // Stop the transaction in case the card is stolen
            printf("Declined, this account is invalid\nPress any button to restart the payment process.");
            getch();
            system("cls");
            continue;
        }

        // Restart the payment process
        printf("Press any button to restart the payment process.");
        getch();
        system("cls");
    }
}
