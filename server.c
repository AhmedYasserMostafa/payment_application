#include "server.h"
#include <stdio.h>
#include <stdlib.h>

ST_accountsDB_t  accountsDB[255] = { 20000,{1,2,3,4,5,6,7,8,9,1,2,3,4,5,6,7} };
ST_transaction_t transaction[255];

EN_serverError_t isValidAccount(ST_cardData_t* cardData)
{
    EN_serverError_t error = Ok;
    uint8_t flag = 0;
    for (int i = 0; i < 16; i++)
        printf("%d\n", cardData_object.primaryAccountNumber[i]);
    for (int i = 0; i < 16; i++)
    {
        if (accountsDB[0].primaryAccountNumber[i] == cardData_object.primaryAccountNumber[i])
        {
            flag = 1;
        }
        else
        {
            flag = 0;
            break;
        }
    }
    if (flag == 1)
    {
        printf("SAME PAN\n");
        
    }
    else
    {
        flag = 0;
        error = DECLINED_STOLEN_CARD;
        printf("WRONG PAN\n");
        exit(0);
    }

    return error;
}

EN_serverError_t isAmountAvailable(ST_terminalData_t* termData)
{
    EN_serverError_t error = Ok;
    printf("YOUR TRANSICTION AMOUnt=%.02f\n", terminaldata_object.transAmount);
    printf("YOUR BALANCE =%.2f\n", accountsDB[0].balance);

    if (terminaldata_object.transAmount > accountsDB[0].balance)
    {
        error = LOW_BALANCE;
        printf("LOW_BALANCE\n");
        exit(0);
    }

    return error;
}
EN_serverError_t saveTransaction(ST_transaction_t* transData)
{
    EN_serverError_t error = Ok;
    transData = &cardData_object;
    if (terminaldata_object.transAmount < accountsDB[0].balance)
    {
        accountsDB[0].balance = accountsDB[0].balance - terminaldata_object.transAmount;
        printf("YOUR new Blance%.2f\n", accountsDB[0].balance);
    }

    strcpy( transaction[0].cardHolderData.cardHolderName , transData->cardHolderData.cardHolderName);
    printf("YOUR CARD HOLDER NAME is %s\n", transaction[0].cardHolderData.cardHolderName);
    printf("your card PAN\n");
    for (int i = 0; i < 16; i++)
    {
        strcpy(transaction[0].cardHolderData.primaryAccountNumber, cardData_object.primaryAccountNumber);
        printf("%d\n", transaction[0].cardHolderData.primaryAccountNumber[i]);
    }
    transaction[0].terminalData.maxTransAmount = 10000;
        
    transData->transactionSequenceNumber = 0;
    transData->transactionSequenceNumber= transData->transactionSequenceNumber+1;

    printf("transaction Sequence Number =%d\n", transData->transactionSequenceNumber);
    transaction[0].transactionSequenceNumber = transData->transactionSequenceNumber;
    printf("your sequence number =%d\n", transaction[0].transactionSequenceNumber);
    transData->transState = APPROVED;
    transaction[0].transState = transData->transState;
    printf("trans State is %d\n", transaction[0].transState);
    //check array is full or not 
    if (transaction[255].transactionSequenceNumber != NULL)
    {
        transData->transState = SAVING_FAILED;
        transaction[0].transState = transData->transState;
        error = SAVING_FAILED;

    }
    
    return error;

}
EN_transState_t  recieveTransactionData(ST_transaction_t* transData)
{
    EN_transState_t error = APPROVED;
     ST_cardData_t* cardData;
     ST_terminalData_t* termData;
     printf("---------------------------------------\n");
     if (isValidAccount(&cardData) == DECLINED_STOLEN_CARD)
     {
         error = DECLINED_STOLEN_CARD;
         printf("DECLINED_STOLEN_CARD\n");
     }
     else  if (isAmountAvailable(&termData) == LOW_BALANCE)
     {
         error = DECLINED_INSUFFECIENT_FUND;
         printf("DECLINED_INSUFFECIENT_FUND\n");
     }
     else if (saveTransaction(&transData) == SAVING_FAILED)
     {
         error = SAVING_FAILED;
         printf("SAVING_FAILED\n");
     }
     else
     {
         error = APPROVED;
         printf("APPROVED\n");
     }
     
    return error;
}
