#ifndef SERVER_H
#define SERVER_H

// Including files
#include "../Terminal/terminal.h"

// Enum for the possible transaction states
typedef enum EN_transState_t {
    trOK, APPROVED, DECLINED_INSUFFICIENT_FUND, INTERNAL_SERVER_ERROR
} EN_transState_t;

// Enum for the possible server errors
typedef enum EN_serverError_t {
    sOK, SAVING_FAILED, TRANSACTION_NOT_FOUND, DECLINED_STOLEN_CARD, ACCOUNT_NOT_FOUND, LOW_BALANCE
} EN_serverError_t;

// Structure for the accounts database
typedef struct ST_accountsDB_t {
    uint8_t isBlocked;
    float balance;
    uint8_t primaryAccountNumber[20];
} ST_accountsDB_t;

// Structure for the transaction database
typedef struct ST_transaction_t {
    ST_cardData_t cardHolderData;
    ST_terminalData_t terminalData;
    EN_transState_t transState;
    uint32_t transactionSequenceNumber;
} ST_transaction_t;

// Function prototypes
EN_transState_t receiveTransactionData(ST_transaction_t *transData);
EN_serverError_t isValidAccount(ST_cardData_t *cardData);
EN_serverError_t isAmountAvailable(ST_terminalData_t *termData);
EN_serverError_t saveTransaction(ST_transaction_t *transData);
EN_serverError_t getTransaction(uint32_t transactionSequenceNumber, ST_transaction_t *transData);

#endif