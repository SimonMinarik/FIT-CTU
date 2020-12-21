#include <stdio.h>
#include <stdlib.h>

struct udaje {
    double toll[26];
    long int length;
    long int start;
};

struct UDAJE {
    struct udaje *highway;
};

int readToll ( struct UDAJE *x, int * count, int allocSize );
int startingPoint ( struct UDAJE *x, long travel, int lo, int hi );
void err ( void );
void trollToll ( struct UDAJE *x, int indexOfStart, int indexOfEnd, int startOfTravel, long lengthOfTravel );

int main ( void ) {
    int count = 0, allocSize = 100;
    long int lengthOfHighway = 0, startOfTravel = 0, endOfTravel = 0, lengthOfTravel = 0, temp = 0;
    char c;
    struct UDAJE x;
    
    /* Creating the array */
    x.highway = ( udaje* ) realloc (NULL,allocSize * sizeof( udaje ));
    
    printf ( "Myto:\n" );
    
    /* Reading the input - tolls and lengths */
    if ( ! readToll ( &x, &count, allocSize ) ) {
        err ();
        free ( x.highway );
        return 0;
    }
    else {
        lengthOfHighway = x.highway[count-1].start + x.highway[count-1].length;
        printf ( "Hledani:\n" );
        while ( 1 ) {
            if ( scanf ( "%ld %ld", &startOfTravel, &endOfTravel ) == 2 ) {
                if ( startOfTravel <= lengthOfHighway && endOfTravel <= lengthOfHighway && startOfTravel != endOfTravel && startOfTravel >= 0 && endOfTravel >= 0 ) {
                    printf ( "%ld - %ld:", startOfTravel, endOfTravel );
                    if ( startOfTravel > endOfTravel ) {
                        temp = startOfTravel;
                        startOfTravel = endOfTravel;
                        endOfTravel = temp;
                        lengthOfTravel = endOfTravel - startOfTravel;
                    }
                    else {
                        lengthOfTravel = endOfTravel - startOfTravel;
                    }
                    trollToll ( &x, startingPoint ( &x, startOfTravel, 0, count-1 ), startingPoint ( &x, endOfTravel, 0, count-1 ), startOfTravel, lengthOfTravel );
                }
                else {
                    err ();
                    free ( x.highway );
                    return 0;
                }
            }
            else if ( scanf ( "%c",&c ) == EOF ) {
                free ( x.highway );
                return 0;
            }
            else {
                err ();
                free ( x.highway );
                return 0;
            }
        }
    }
    
    /* Free the allocated memory */
    free ( x.highway );
    return 0;
}

/* Printing the error message */
void err ( void ){
    printf ( "Nespravny vstup.\n" );
}

/* Read the input - tolls and lengths
 * struct udaje *highway - dynamically allocated array of structure udaje - storing  *
 * the length of each part of the highway (.length), its starting point (.start) and *
 * tolls from A to Z.                                                                */
int readToll ( struct UDAJE *x, int * count, int allocSize ) {
    char c, comma;
    int notOkay = 0, canExit = 0, temp;
    double zoll;
    
    if ( scanf ( " %c", &c ) == 1 ) {
        if ( c == '{' ) {
            while ( ! notOkay ) {
                if ( scanf ( " [ %d %c ", &temp, &c ) == 2 ) {
                    if ( temp > 0 ) {
                        (*count)++;
                        if ( *count == allocSize - 1 ) {
                            allocSize *= 2;
                            x->highway = ( udaje* ) realloc (x->highway,allocSize * (sizeof( udaje )));
                        }
                        if ( c != ':' ) {
                            notOkay = 1;
                        }
                        x->highway[*count-1].length = temp;
                        if ( ! (*count - 1) ) {
                            x->highway[*count-1].start = 0;
                            for (int i=0; i<26; i++) {
                                x->highway[*count-1].toll[i] = 0;
                            }
                        } else {
                            x->highway[*count-1].start = x->highway[*count-2].start + x->highway[*count-2].length;
                            for (int i=0; i<26; i++) {
                                x->highway[*count-1].toll[i] = x->highway[*count-2].toll[i];
                            }
                        }
                        while ( scanf ( " %c = %lf %c", &c, &zoll, &comma ) == 3 && ! notOkay ) {
                            if ( (int) c > 64 && (int) c < 91 && zoll >= 0 ) {
                                x->highway[*count-1].toll[(int)c - 65] = zoll;
                                if ( comma == ',' ) {
                                    //fajne
                                }
                                else if ( comma == ']' ) {
                                    if ( scanf ( " %c",&c ) == 1 ) {
                                        if ( c == ',' ) {
                                            notOkay = 0;
                                            canExit = 0;
                                            break;
                                        } else if ( c == '}' ) {
                                            canExit = 1;
                                            notOkay = 1;
                                            break;
                                        }
                                    }
                                }
                                else {
                                    notOkay = 1;
                                    break;
                                }
                            }
                            else {
                                notOkay = 1;
                                break;
                            }
                        }
                    } else {
                        notOkay = 1;
                    }
                }
                else if ( canExit ) {
                    notOkay = 0;
                    break;
                }
                else {
                    notOkay = 1;
                }
            }
            if ( notOkay && canExit ) {
                return 1;
            }
            else {
                return 0;
            }
        }
        else {
            return 0;
        }
    }
    else {
        return 0;
    }
}

/* Searching for an index of the part of the highway on which the journey starts, using (something *
 * similar to) binary search. The function is checking from the middle of the array upwards or     *
 * downwards, depending on the value of the integer and divides the value by 2, until it finds     *
 * the right part of the highway.                                                                  */
int startingPoint ( struct UDAJE *x, long travel, int lo, int hi ) {
    int mid = ( lo + hi ) / 2;
    if ( travel >= x->highway[mid].start  && x->highway[mid].start + x->highway[mid].length >= travel ) {
        return mid;
    }
    else if ( travel <= x->highway[mid].start ) {
        return startingPoint ( x, travel, lo, mid-1 );
    }
    else {
        return startingPoint ( x, travel, mid+1, hi );
    }
}

void trollToll ( struct UDAJE *x, int indexOfStart, int indexOfEnd, int startOfTravel, long lengthOfTravel ) {
    double tollToPay[26];
    int commaWritten = 0;
    for ( int i = 0; i < 26; i++ ) {
        tollToPay[i] = 0;
    }
    int helpIndex = indexOfStart;
    if ( indexOfStart == indexOfEnd ) {
        for ( int i = 0; i < 26; i++ ) {
            tollToPay[i] += lengthOfTravel * x->highway[helpIndex].toll[i];
        }
        lengthOfTravel = 0;
    }
    else {
        lengthOfTravel -= ( x->highway[helpIndex].length - ( startOfTravel - x->highway[helpIndex].start ) );
        for ( int i = 0; i < 26; i++ ) {
            tollToPay[i] += ( x->highway[helpIndex].length - ( startOfTravel - x->highway[helpIndex].start ) ) * x->highway[helpIndex].toll[i];
        }
        helpIndex++;
    }
    while ( lengthOfTravel > 0 && helpIndex != indexOfEnd ) {
        lengthOfTravel -= x->highway[helpIndex].length;
        for ( int i = 0; i < 26; i++ ) {
            tollToPay[i] += x->highway[helpIndex].length * x->highway[helpIndex].toll[i];
        }
        helpIndex++;
    }
    if ( lengthOfTravel > 0 ) {
        for ( int i = 0; i < 26; i++ ) {
            tollToPay[i] += lengthOfTravel * x->highway[helpIndex].toll[i];
        }
    }
    for ( int i = 0; i < 26; i++ ) {
        if ( tollToPay[i] > 0 ) {
            if ( ! commaWritten ) {
                printf ( " %c=%lf",i+65,tollToPay[i] );
                commaWritten = 1;
            }
            else {
                printf ( ", %c=%lf",i+65,tollToPay[i] );
            }
        }
    }
    printf ( "\n" );
}
