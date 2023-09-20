#include "server.h"

// Accounts database
ST_accountsDB_t accounts[255] = {
        {0, 3500,  "5078034830297201"},
        {0, 14565, "4117394584032808"},
        {0, 452,   "5370233590092076"},
        {0, 23684, "6076597269416704"}
};

// Transactions database
ST_transaction_t transactions[255] = {0};

float tempCardBalance = -1;
char tempCardIndex = -1;
char transactionIndex = 0;

// Function used to validate the transaction process
EN_transState_t receiveTransactionData(ST_transaction_t *transData) {
    // First check whether the entered PAN is for a valid account or not
    if (isValidAccount(&transData->cardHolderData) != sOK) {
        transData->transState = DECLINED_STOLEN_CARD;
        saveTransaction(transData);
        return DECLINED_STOLEN_CARD;
    }

    // Second check whether the card has sufficient fund for the transaction process or not
    if (isAmountAvailable(&transData->terminalData) != sOK) {
        transData->transState = DECLINED_INSUFFICIENT_FUND;
        saveTransaction(transData);
        return DECLINED_INSUFFICIENT_FUND;
    }

    // Decrease the card balance and update the database
    accounts[tempCardIndex].balance -= transData->terminalData.transAmount;
    printf("Now your balance is %.2f\n", accounts[tempCardIndex].balance);
    transData->transState = APPROVED;

    // Check whether transaction data is saved or not
    if (saveTransaction(transData) != sOK) {
        return INTERNAL_SERVER_ERROR;
    }
    tempCardIndex = -1;
    tempCardBalance = -1;
    return APPROVED;
}

// Function used to check whether the account is valid or not
EN_serverError_t isValidAccount(ST_cardData_t *cardData) {
    // Loop over each element of the accounts database
    for (int i = 0; i < sizeof(accounts) / sizeof(accounts[0]); i++) {
        // Check whether the entered PAN exists in the database or not
        if (strcmp(cardData->primaryAccountNumber, accounts[i].primaryAccountNumber) == 0) {
            // Check whether account is blocked or not
            if (accounts[i].isBlocked)
                return DECLINED_STOLEN_CARD;
            // Set the card balance global variable and card index global variable
            tempCardBalance = accounts[i].balance;
            tempCardIndex = i;
            return sOK;
        }
    }
    return DECLINED_STOLEN_CARD;
}

// Function used to check whether the transaction amount is available in the card or not
EN_serverError_t isAmountAvailable(ST_terminalData_t *termData) {
    if (termData->transAmount <= tempCardBalance)
        return sOK;
    return LOW_BALANCE;
}

// Function used to save the current transaction in the transactions database
EN_serverError_t saveTransaction(ST_transaction_t *transData) {
    // Check whether the transactions database is empty or not
    if (transactionIndex == sizeof(transactions) / sizeof(transactions[0]))
        return SAVING_FAILED;
    // Save the transaction data in the transactions database
    transactions[transactionIndex] = *transData;
    transactionIndex++;
    return sOK;
}