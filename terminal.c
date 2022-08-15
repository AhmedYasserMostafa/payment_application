#include <time.h>
#include <math.h>
#include "terminal.h"
EN_terminalError_t getTransactionDate(ST_terminalData_t* termData)
{
    EN_terminalError_t error = ok;
    termData = &terminaldata_object;
    uint8_t count1 = 0, count2 = 0, count3 = 0;
    uint8_t countall = 0;
    printf("transaction data in the format  DD/MM/YYYY\n");
    //read date from system
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    termData->transactionDate[0] = tm.tm_mday;
    termData->transactionDate[1] = tm.tm_mon + 1;
    termData->transactionDate[2] = tm.tm_year - 100;
    printf("%d-%d-%d\n", termData->transactionDate[0], termData->transactionDate[1],
        termData->transactionDate[2]);
    count1 = log10(termData->transactionDate[0]) + 1;
    count2 = log10(termData->transactionDate[1]) + 1;
    count3 = log10(termData->transactionDate[2]) + 1;
    countall = count1 + count2 + count3;
    if (countall < 5)
    {
        error = WRONG_DATE;
        printf("WRONG_DATE \n");
    }
    return error;
}
EN_terminalError_t isCardExpired(ST_cardData_t cardData, ST_terminalData_t termData)
{
    EN_terminalError_t error = ok;
    termData = terminaldata_object;
    cardData = cardData_object;
    if ((termData.transactionDate[2]) > (cardData.cardExpirationDate[2]))//year
    {
        error = EXPIRED_CARD;
        printf("EXPIRED CARD\n");
        exit(0);
    }
    else if ( ((termData.transactionDate[2]) == (cardData.cardExpirationDate[2])) && ((termData.transactionDate[1]) > (cardData.cardExpirationDate[0])) )
    {
        error = EXPIRED_CARD;
        printf("EXPIRED CARD\n");
        exit(0);
    }
    else
    {
        printf("VALID CARD\n");

    }

    return error;
}
EN_terminalError_t getTransactionAmount(ST_terminalData_t* termData)
{
    EN_terminalError_t error = ok;
    termData = &terminaldata_object;
    printf("please Enter transaction amount\n");
    scanf("%f", &termData->transAmount);
    if (termData->transAmount <= 0)
    {
        error = INVALID_AMOUNT;
        printf("INVALID_AMOUNT\n");
    }
    return error;
}
EN_terminalError_t setMaxAmount(ST_terminalData_t* termData)
{
    EN_terminalError_t error = ok;
    termData = &terminaldata_object;
    termData->maxTransAmount = 10000;
    printf("the mAX transaction amount is %0.3f\n", termData->maxTransAmount);
    if (termData->maxTransAmount <= 0)
    {
        error = INVALID_MAX_AMOUNT;
        printf("INVALID_MAX_AMOUNT\n");
    }
    return error;
}
EN_terminalError_t isBelowMaxAmount(ST_terminalData_t* termData)
{
    EN_terminalError_t error = ok;
    termData = &terminaldata_object;
    if (termData->maxTransAmount < termData->transAmount)
    {
        error = EXCEED_MAX_AMOUNT;
        printf("EXCEED_MAX_AMOUNT\n");
        exit(0);
    }
    return error;
}
