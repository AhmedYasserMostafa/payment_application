#include <stdio.h>
#include <string.h>
#include <math.h>
#include "card.h"

EN_cardError_t getCardHolderName(ST_cardData_t* cardData)
{
    EN_cardError_t error = OK;
    cardData = &cardData_object;
    printf("please Enter Your Card Holder Name....\n");
    gets(cardData->cardHolderName);
    uint8_t length = strlen(cardData->cardHolderName);
    if ((cardData->cardHolderName == NULL) && (cardData->cardHolderName[0] == '\0'))
    {
        error = WRONG_NAME;
        printf("wrong Name \n");
    }
    else if ((length < 20) || (length > 24))
    {
        error = WRONG_NAME;
        printf("wrong Name \n");
    }
    return error;
}
EN_cardError_t getCardExpiryDate(ST_cardData_t* cardData)
{
    EN_cardError_t error = OK;
    cardData = &cardData_object;
    uint8_t count1 = 0, count2 = 0, count = 0;
    printf("Please Enter Card Expiry Date  in the format MM/YY\n");
    printf("Enter Month\n");
    scanf_s("%i",&cardData->cardExpirationDate[0]);
    count1 = log10(cardData->cardExpirationDate[0]) + 1;
    //printf("%d\n",count1);
    cardData->cardExpirationDate[1] = '/';
    printf("%c\n", cardData->cardExpirationDate[1]);
    printf("Enter year\n");
    scanf_s("%i",&cardData->cardExpirationDate[2]);
    count2 = log10(cardData->cardExpirationDate[2]) + 1;
    //printf("%d\n",count2);
    count = count1 + count2;
   // printf("%d\n",count);
    if ((cardData->cardExpirationDate[0] == NULL) &&(cardData->cardExpirationDate[0] == NULL))
    {
        error = WRONG_EXP_DATE;
        printf("WRONG_EXP_DATE\n");
    }
    else if (count > 4 || count < 4)
    {
        error = WRONG_EXP_DATE;
        printf("WRONG_EXP_DATE\n");
    }
    return error;
}

EN_cardError_t getCardPAN(ST_cardData_t* cardData)
{
    EN_cardError_t error = OK;
    cardData = &cardData_object;
    uint8_t count = 0, i = 0;
    printf("please Enter Your Card PAN....\n");
    for (i = 0; i < 16; i++)
    {
        scanf("%d",&cardData->primaryAccountNumber[i]);
        fflush(stdin);
        count += log10(cardData->primaryAccountNumber[i]) + 1;
    }
    printf("Your PAN is %d digits\n", count);
    for (int i = 0; i < 16; i++)
        if (cardData->primaryAccountNumber[i] == NULL)
        {
               error = WRONG_PAN;
            // printf("wrong PAN \n");
        }
        if ((count < 16) || (count > 19))
        {
        error = WRONG_PAN;
        printf("wrong PAN \n");
        }
    return error;
}


