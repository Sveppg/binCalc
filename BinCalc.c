#include <stdio.h>

#include "escapesequenzen.h" 

void printFrame();
char askAgain();
short getNumber(int zeile);
void refreshGetNumber(short zeile);
char getOperator();
void refreshGetOperator();
void printInputOperator(char operator);
short calcresult(short zahl1, short zahl2, char operator);
short calcResultWithFunction(short zahl1, short zahl2, void (*functionPointer)(short *, short));
void leftShift(short *zahl, short bit);
void rightShift(short *zahl, short bit);
void and(short *zahl, short bit);
void or(short *zahl, short bit);
void xor(short *zahl, short bit);
void printResultNumber(int zeile, short zahl);
void printBinary(int zeile, short zahl);
void printResultOperator(char operator);
void setBit(short *b, short x);
void unsetBit(short *b, short x);
short checkBit(short b, short x);
short checkBit2(short b, short x);
void switchBit(short *b, short x);


void clearPuffer();

int main ()
{
	do
	{
		printFrame();
        short zahl1 = getNumber(3);
        char operator = getOperator();
        printInputOperator(operator);
        short zahl2 = getNumber(5);

        printResultNumber(10, zahl1);
        printResultOperator(operator);
        printResultNumber(12, zahl2);
        printResultNumber(14, calcresult(zahl1, zahl2, operator));

	} while(askAgain());
	return 0;
}

void printFrame()
{
    CLEAR;
    HOME;

    printf("|----------------------------------------------------|\n");
    printf("|Bitoperatoren-Rechner                               |\n");
    printf("|Eingabe Zahl:                                       |\n");
    printf("|Eingabe Operator:                                   |\n");
    printf("|Eingabe Zahl:                                       |\n");
    printf("|                                                    |\n");
    printf("|----------------------------------------------------|\n");
    printf("|                                                    |\n");
    printf("|         | dez. | okt. | hex. | Binaerdarstellung   |\n");
    printf("|Zahl     |      |      |      |                     |\n");
    printf("|Operator |      |      |      |                     |\n");
    printf("|Zahl     |      |      |      |                     |\n");
    printf("|----------------------------------------------------|\n");
    printf("|Ergebnis |      |      |      |                     |\n");
    printf("|----------------------------------------------------|\n");
}

short getNumber(int zeile) // Eingabe Zahlen
{
	CLEAR_LINE; //bessere Darstellung??
	HOME;
	short zahl = 0;

	refreshGetNumber(zeile);
	while(!scanf("%hd", &zahl))
	{
		clearPuffer();
		refreshGetNumber(zeile);
	}
	clearPuffer();
	return zahl;
}

void refreshGetNumber(short zeile) // Zeile erneuern
{
	POSITION(zeile,1);
	CLEAR_LINE;
	printf("|Eingabe Zahl:                                       |\n");
	POSITION(zeile,15);
}

char getOperator() // Abfrage Operator
{
	char ScanOp;
	POSITION(4,19);
	do
	{
		scanf("%c", &ScanOp);
        refreshGetOperator();
			
	} while((ScanOp != '&') && (ScanOp != '<') && (ScanOp !='>') &&  (ScanOp != '^') &&(ScanOp != '|'));
	
	return ScanOp;
}

void refreshGetOperator() // Zeile erneuern
{
	POSITION(4,1);
    clearPuffer();
    CLEAR_LINE;
    printf("|Eingabe Operator:                                   |\n");
    POSITION(4,19); 
}

void printInputOperator(char operator) // Ausgabe Operator Eingabefeld
{
	POSITION(4,1);
	CLEAR_LINE;
	switch (operator)
	{
		case '<':
			printf("|Eingabe Operator:<<                                 |");
			break;
		
		case '>':
			printf("|Eingabe Operator:>>                                 |");
			break;

		default:
			printf("|Eingabe Operator:%c                                  |",operator);
			break;
	}
}

short calcresult(short zahl1, short zahl2, char operator) // Berechnung
{	
    void (*functionPointer)(short *, short);
	switch (operator)
	{
		case '<':
			functionPointer  = &leftShift;
			break;

		case '>':
			functionPointer  = &rightShift;
			break;
			
		case '&':
			functionPointer  = &and;
			break;
		
		case '|':
			functionPointer  = &or;
			break;
		
		case '^':
			functionPointer  = &xor;
			break;
	}

	return calcResultWithFunction(zahl1, zahl2, functionPointer);
}

short calcResultWithFunction(short zahl1, short zahl2, void (*functionPointer)(short *, short))
{
    short ergebnis = zahl1;
    char bitsOfShort = sizeof(short) * 8;
    
    for(int i = bitsOfShort; i >= 0; i--)
    {
        short bit2 = checkBit(zahl2, i);
        (*functionPointer)(&ergebnis, bit2);
    }
    return ergebnis;
}

void leftShift(short *zahl, short bit){
    *zahl = *zahl << bit;
}

void rightShift(short *zahl, short bit){
    *zahl = *zahl >> bit;
}

void and(short *zahl, short bit){
    *zahl = *zahl & bit;
}

void or(short *zahl, short bit){
    *zahl = *zahl | bit;
}

void xor(short *zahl, short bit){
    *zahl = *zahl ^ bit;
}

void printResultNumber(int zeile, short zahl) // Ausgabe Ausgabefeld Zahlen
{
	
	POSITION(zeile, 12);
	printf("%6.4i", zahl);
	POSITION(zeile, 19);
	printf("%6.4ho", zahl);
	POSITION(zeile, 26);
	printf("%6.4hx", zahl);
	printBinary(zeile, zahl);
}

void printBinary(int zeile, short zahl)
{
    char bitsOfShort = sizeof(short) * 8;

    for(int i = 0; i < bitsOfShort; i++)
    {
        POSITION(zeile, 34 + bitsOfShort - i);
        printf("%d", checkBit2(zahl, i) ? 1 : 0);
    }
}

void printResultOperator(char operator) // Ausgabe Operator Ausgabefeld
{
	POSITION(11,1);
	
	switch (operator)
	{
		case '<':
			CLEAR_LINE;
			printf("|Operator |   << |   << |   << |               <<    |\n");
			break;
		
		case '>':
			CLEAR_LINE;
			printf("|Operator |   >> |   >> |   >> |               >>    |\n");
			break;

		default:
			POSITION(11, 17);
			printf("%c", operator);
			POSITION(11, 24);
			printf("%c", operator);
			POSITION(11, 31);
			printf("%c", operator);
			POSITION(11, 49);
			printf("%c", operator);
			break;
	}
}

void setBit(short *zahl, short stelle)
{
    *zahl = *zahl | (1 << stelle);
}

void unsetBit(short *zahl, short stelle)
{
    *zahl = *zahl & (0 << stelle);
}

short checkBit(short b, short x)
{
    return b & (1 << x);
}

short checkBit2(short b, short x)
{
    return checkBit(b, x) ;
}

void switchBit(short *b, short x)
{
    *b ^= 1 << x;
}

char askAgain() // Wiederholung ja nein
{
    char eingabe;
    char dummy;
    do
    {
        POSITION(16, 1);
        CLEAR_LINE;
        
        printf("Moechten Sie noch einmal (j/n)?\n");
        scanf("%c", &eingabe); 
        
        if (eingabe != '\n') //Wurde mehr als die Eingabetaste eingegeben?
        {
            do
            {
                scanf("%c" , &dummy);
            } while (dummy != '\n');
        }

        if( (eingabe == 'n') || (eingabe == 'N') )
        {
            return(0);
        }
        else if( (eingabe == 'j') || (eingabe == 'J') )
        {
            return(1);
        }

        printf("Falsche Eingabe! Bitte 'j' oder 'n' eingeben!\n");
        POSITION(17, 1);
        CLEAR_LINE;
    } while (1);
}
		
void clearPuffer()
{
	char dummy;
	do
	{
		dummy= getc(stdin);
	} while (dummy != '\n');
}
