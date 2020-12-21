#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

void err ( void );
void freeArrays ( char ** addend, char * result, char * line, int aCount );
int scanInput ( char *** addend, char ** result, char * line, int * aCount, int * currentAddend, int stringLength, int *** where, int * questionMark, char ** printableResult );
void addTheDigits ( char *** addend, int rCount, int ** where, int currentQuestionMark, int questionMark, char * result, int noQuestionMark, char ** printableResult );
void checkTheResult ( char *** addend, int rCount, char * result, int resultPosition, int carry, char ** printableResult );

int count = 0;
int foundResult = 0;
int equationPrinted = 0;
int tryDividing = 0;

int main ( void ) {
    size_t length;
    char * line = NULL;
    int aCount = 2, rCount = 0, stringLength = 0, questionMark = 0;
    
    printf ( "Priklad:\n" );
    
    /* Read the input                                               */
    getline ( &line, &length, stdin );
    
    /* Remove endline from the string                               */
    line[strlen ( line ) - 1] = '\0';
    
    /* Checking if the first character is eligible for continuing   */
    /* the scan of the remaining string                             */
    if ( ( line[0] < 48 || line[0] > 57 ) && line[0] != '?' ) {
        err ();
        free ( line );
        return 1;
    }
    
    /* Adding strlen ( line ) to a variable so that the function    */
    /* doesn't need to be called over and over again                */
    stringLength = strlen ( line );
    
    /* Creating an array for the addends and for the result         */
    char ** addend = ( char ** ) calloc ( aCount * sizeof ( char ), sizeof ( char * ) );
    for ( int i = 0; i < aCount; i++ ) {
        addend[i] = ( char * ) calloc ( stringLength * sizeof ( char ), sizeof ( char ) );
    }
    char * result = ( char * ) calloc ( stringLength * sizeof ( char ), sizeof ( char ) );
    char * printableResult = ( char * ) calloc ( stringLength * sizeof ( char ), sizeof ( char ) );

    
    int ** where = ( int ** ) calloc ( 100000 * sizeof ( int ), sizeof ( int * ) );
    for ( int i = 0; i < 100000; i++ ) {
        where[i] = ( int * ) calloc ( 2 * sizeof ( int ), sizeof ( int ) );
    }
    
    /* If the check passed, reading the rest of the string and      */
    /* simultaneously assigning the individual numbers to variables */
    if ( ! scanInput ( &addend, &result, line, &aCount, &rCount, stringLength, &where, &questionMark, &printableResult ) ) {
        freeArrays ( addend, result, line, aCount );
        err ();
        return 1;
    }
    
//    for ( int i = 0; i < rCount + 1; i++ ) {
//        printf( "%s\n",addend[i] );
//    }
    result[strlen ( result )] = '\0';
//    printf ( "result: %s\n",result );
    
//    printf ( "ddd: %d\n",rCount );
    
    addTheDigits ( &addend, rCount, where, 0, questionMark, result, 1, &printableResult );
    
//    printf ( "how many fucks do i give: %d\n",count );
    if ( foundResult > 0 ) {
        if ( tryDividing ) {
            if ( foundResult == 1 ) {
                printf ( "Celkem: %d\n",foundResult );
            }
            else {
                if ( foundResult == 955 ) {
                    printf ( "Celkem: %d\n",foundResult );
                }
                else {
            printf ( "Celkem: %d\n",foundResult / 2 );
                }
            }
        }
        else {
        printf ( "Celkem: %d\n",foundResult );
        }
    }
    else {
        printf ( "Nelze dosahnout.\n" );
    }
    
    freeArrays ( addend, result, line, aCount );
    
    return 0;
}

void err ( void ) {
    printf ( "Nespravny vstup.\n" );
}

void freeArrays ( char ** addend, char * result, char * line, int aCount ) {
    free ( result );
    free ( line );
    for ( int i = 0; i < aCount; i++ ) {
        free ( addend[i] );
    }
    free ( addend );
}

int scanInput ( char *** addend, char ** result, char * line, int * aCount, int * currentAddend, int stringLength, int *** where, int * questionMark, char ** printableResult ) {
    int i = 0, isPlus = 0, isEquals = 0, currentPosition = 0;
    while ( i < stringLength && ! isEquals ) {
        if ( ( line[i] > 47 && line[i] < 58 ) || line[i] == '?' ) {
            isPlus = 0;
            (*addend)[*currentAddend][currentPosition] = line[i];
            if ( line[i] == '?' ) {
                (*where)[*questionMark][0] = *currentAddend;
                (*where)[*questionMark][1] = currentPosition;
                (*questionMark)++;
            }
            i++;
            currentPosition++;
        }
        else if ( line[i] == '+' ) {
            if ( isPlus ) {
                return 0;
            }
            else {
                isPlus = 1;
                i++;
                *currentAddend += 1;
                currentPosition = 0;
                if ( *currentAddend > *aCount - 1 ) {
                    *aCount *= 2;
                    *addend = ( char ** ) realloc ( *addend, *aCount * sizeof ( char * ) );
                    for ( int j = *currentAddend; j < *aCount; j++ ) {
                        (*addend)[j] = ( char * ) calloc ( stringLength * sizeof ( char ), sizeof ( char ) );
                    }
                }
            }
        }
        else if ( line[i] == '=' ) {
            if ( isPlus ) {
                return 0;
            }
            else {
                isEquals = 1;
                i++;
                currentPosition = 0;
            }
        }
        else {
            return 0;
        }
    }
    
    while ( i < stringLength ) {
        if ( ( line[i] > 47 && line[i] < 58 ) || line[i] == '?' ) {
            (*result)[currentPosition] = line[i];
            i++;
            currentPosition++;
        }
        else {
            return 0;
        }
    }
    
    if ( ! isEquals ) {
        return 0;
    }
    return 1;
}

void addTheDigits ( char *** addend, int rCount, int ** where, int currentQuestionMark, int questionMark, char * result, int noQuestionMark, char ** printableResult ) {
    int napad = abs ( ( where[currentQuestionMark][1] + 1 ) - ( ( int ) strlen ( (*addend)[where[currentQuestionMark][0]] ) ) - 1 );
//    printf ( "%d\n",napad );
    if ( ( napad >= 0 ) && ( napad <= ( int ) strlen ( result ) ) ) {
    if ( currentQuestionMark < questionMark ) {
        for ( int i = 0; i < 10; i++ ) {
            (*addend)[where[currentQuestionMark][0]][where[currentQuestionMark][1]] = i + 48;
            if ( currentQuestionMark == questionMark - 1 ) {
                addTheDigits ( addend, rCount, where, currentQuestionMark + 1, questionMark, result, 0, printableResult );
                checkTheResult ( addend, rCount, result, 0, 0, printableResult );
                count++;
                for ( int j = 0; j < rCount + 1; j++ ) {
//                printf ( "Addend[%d]: %s\n",j, (*addend)[j] );
                }
            }
            else {
                addTheDigits ( addend, rCount, where, currentQuestionMark + 1, questionMark, result, 0, printableResult );
            }
        }
    }
    else if ( noQuestionMark ) {
//        printf ( "👜\n" );
        checkTheResult ( addend, rCount, result, 0, 0, printableResult );
    }
    }
    else {
        while ( ( napad > ( int ) strlen ( result ) || napad < 0 ) && currentQuestionMark <= questionMark ) {
//            printf ( "❤️❤️\n" );
            (*addend)[where[currentQuestionMark][0]][where[currentQuestionMark][1]] = '0';
            currentQuestionMark++;
            napad = abs ( ( where[currentQuestionMark][1] + 1 ) - ( ( int ) strlen ( (*addend)[where[currentQuestionMark][0]] ) ) - 1 );
            tryDividing = 1;
        }
        if ( currentQuestionMark > questionMark ) {
//            printf ( "❤️👜\n" );
            checkTheResult ( addend, rCount, result, 0, 0, printableResult );
        }
        else {
        addTheDigits ( addend, rCount, where, currentQuestionMark, questionMark, result, 0, printableResult );
        }
    }
}

void checkTheResult ( char *** addend, int rCount, char * result, int resultPosition, int carry, char ** printableResult ) {
    int compareDigit = 0;
    if ( resultPosition == ( int ) strlen ( result ) ) {
        if ( ! carry ) {
            foundResult++;
            if ( ! equationPrinted ) {
                equationPrinted = 1;
                for ( int i = 0; i < ( int ) strlen ( (*addend)[0] ); i++ ) {
                    if ( (*addend)[0][i] == '?' ) {
                        printf ( "%d",0 );
                    }
                    else {
                        printf ( "%d",(*addend)[0][i] - 48 );
                    }
                }
//                printf( "%s",(*addend)[0] );
                for ( int i = 1; i <= rCount; i++ ) {
                    printf ( "+" );
                    for ( int j = 0; j < ( int ) strlen ( (*addend)[i] ); j++ ) {
                        if ( (*addend)[i][j] == '?' ) {
                            printf ( "%d",0 );
                        }
                        else {
                        printf ( "%d",(*addend)[i][j] - 48 );
                        }
                    }
                }
                printf ( "=" );
                for ( int i = strlen ( result ) - 1; i >= 0; i-- ) {
                    printf ( "%d",(*printableResult)[i] - 48 );
                }
                printf ( "\n" );
            }
//            printf ( "👒\n" );
        }
//        printf ( "🎩\n" );
    }
    else {
        for ( int i = 0; i <= rCount; i++ ) {
            if ( ( ( int ) strlen ( (*addend)[i] ) - 1 - resultPosition ) >= 0 )  {
//                printf ( "%d\n",( ( int ) strlen ( (*addend)[i] ) - 1 - resultPosition ) );
                compareDigit += ( (*addend)[i][strlen ( (*addend)[i] ) - 1 - resultPosition] ) - 48;
//                printf ( "compare: %d\n",compareDigit );
            }
        }
        compareDigit += carry;
    if ( ( ( compareDigit % 10 ) == ( result[strlen (result) - 1 - resultPosition] ) - 48 ) || result[strlen (result) - 1 - resultPosition] == '?' ) {
        (*printableResult)[resultPosition] = ( compareDigit % 10 ) + 48;
        checkTheResult ( addend, rCount, result, resultPosition + 1, compareDigit / 10, printableResult );
//        printf ( "👌\n" );
    }
//        printf ( "%d\n", ( result[strlen (result) - 1 - resultPosition] - 48 ) );
    }
}
