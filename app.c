#include "app.h"
void appStart(void)
{
    ST_cardData_t      *cardData = NULL;
    ST_terminalData_t  *termData = NULL;

    ST_cardData_t       cardData1 = { {0},{'\0'},{0} };
    ST_terminalData_t   termData1 = { {0},{'\0'},{0} };

    ST_transaction_t  *transData = NULL;


    EN_cardError_t error = getCardHolderName(&cardData);
    printf("%d\n", error);
    printf("-------------------------------------------------------\n");

    error = getCardExpiryDate(&cardData);
    printf("%d\n", error);
    printf("-------------------------------------------------------\n");

    error = getCardPAN(&cardData);
    printf("%d\n", error);
    printf("-------------------------------------------------------\n");

    EN_terminalError_t error_terminal = getTransactionDate(&termData);
    printf("%d\n", error_terminal);
    printf("-------------------------------------------------------\n");

    error_terminal = isCardExpired(cardData1, termData1);
    printf("%d\n", error_terminal);
    printf("-------------------------------------------------------\n");

    error_terminal = getTransactionAmount(&termData);
    printf("%d\n", error_terminal);
    printf("-------------------------------------------------------\n");

    error_terminal = setMaxAmount(&termData);
    printf("%d\n", error_terminal);
    printf("-------------------------------------------------------\n");

    error_terminal = isBelowMaxAmount(&termData);
    printf("%d\n", error_terminal);
    printf("-------------------------------------------------------\n");


    EN_transState_t error_server = recieveTransactionData(&transData);
    printf("%d\n", error_server);
    printf("-------------------------------------------------------\n");

}
int main()
{
    appStart();

}
