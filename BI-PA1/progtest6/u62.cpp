#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void err ( void );
int checkLine ( char * line, long long int rWidth );
void freeOsemsmerovka ( char ** osemsmerovka, long long int aHeight );
void freeWords ( char ** words, long long int aWords );
int findWords ( char ** osemsmerovka, char ** words, long long int rHeight, int long long rWidth, int long long rWords );

int main ( void ) {
    long long int aHeight = 100, rWidth = 0, aWords = 100, rWords = -1, max = 0;
    char * line = NULL;
    char ** words = NULL;
    size_t length;
    
    printf ( "Zadejte osmismerku:\n" );
    
    rWidth = getline ( &line, &length, stdin ) - 1;
    
    if ( line[0] == '\n' || ! strlen ( line ) ) {
        err ();
        free ( line );
        free ( words );
        return 0;
    }
    
    if ( ! checkLine ( line, rWidth ) ) {
        err ();
        free ( line );
        free ( words );
        return 0;
    }
    
    char ** osemsmerovka = ( char ** ) calloc ( aHeight * sizeof ( char ), sizeof ( char * ) );
    for ( int i = 0 ; i < aHeight; i++ ) {
        osemsmerovka[i] = ( char * ) calloc ( rWidth * sizeof ( char ) + 2 , sizeof ( char ) );
    }
    
    long long int rHeight = 0;
    strncpy ( osemsmerovka[rHeight], line, rWidth );
//    printf ( "%s\n",osemsmerovka[rHeight] );

    while ( getline ( &line, &length, stdin ) > 1 ) {
        if ( ( int ) strlen ( line ) - 1 != rWidth ) {
            err ();
            freeOsemsmerovka ( osemsmerovka, aHeight );
            free ( line );
            free ( words );
            return 0;
        }
        if ( ! checkLine ( line, rWidth ) ) {
            err ();
            freeOsemsmerovka ( osemsmerovka, aHeight );
            free ( line );
            free ( words );
            return 0;
        }
        rHeight++;
        if ( rHeight > aHeight - 1 ) {
            aHeight *= 2;
            osemsmerovka = ( char ** ) realloc ( osemsmerovka, aHeight * sizeof ( char * ) );
            
            for ( long long int i = rHeight; i < aHeight; i++ ) {
                osemsmerovka[i] = ( char * ) calloc ( rWidth * sizeof ( char ) + 1, sizeof ( char ) );
            }
//            printf ( "😱\n" );
        }
        strncpy ( osemsmerovka[rHeight], line, rWidth );
//        printf ( "%s\n",osemsmerovka[rHeight] );
    }
    
    if ( line[0] == '\n' ) {
        
        if ( rHeight + 1 >= rWidth ) {
            max = rHeight + 1;
        }
        else {
            max = rWidth;
        }
        
        words = ( char ** ) calloc ( aWords * sizeof ( char ), sizeof ( char * ) );
        for ( long long int i = 0; i < aWords; i++ ) {
            words[i] = ( char * ) calloc ( max * sizeof ( char ) + 1, sizeof ( char ) );
        }
        
        while ( getline ( &line, &length, stdin ) > 1 ) {
            rWords++;
            if ( rWords > aWords - 1 ) {
                aWords *= 2;
                words = ( char ** ) realloc ( words, aWords * sizeof ( char * ) );
                
                for ( long long int i = rWords; i < aWords; i++ ) {
                    words[i] = ( char * ) calloc ( max * sizeof ( char ) + 1 , sizeof ( char ) );
                }
            }
            if ( ( int ) strlen ( line ) - 1 > max ) {
                
                char * notFound = ( char * ) calloc ( strlen ( line ) * sizeof ( char ) + 1, sizeof ( char ) ) ;
                strncpy ( notFound, line, strlen ( line ) - 1 );
                printf ( "Slovo '%s' nenalezeno.\n",notFound );
                free ( notFound );
                free ( line );
                freeOsemsmerovka ( osemsmerovka, aHeight );
                freeWords ( words, aWords );
                return 0;
            }
            strncpy ( words[rWords], line, strlen ( line ) - 1 );
        }
        free ( line );
        }
    else {
        err ();
        free ( line );
        freeOsemsmerovka ( osemsmerovka, aHeight );
        free ( words );
        return 0;
    }
    
//    printf ( "hei %d\n",rHeight );
//    printf ( "wid %d\n",rWidth );
    
    if ( ! findWords ( osemsmerovka, words, rHeight, rWidth, rWords ) ) {
        freeOsemsmerovka ( osemsmerovka, aHeight );
        freeWords ( words, aWords );
        return 0;
    }
    else {
        long long int formatInt = 0;
        long long int writtenSomething = 0;
        printf ( "Vysledek:\n" );
        for ( long long int i = 0; i < rHeight + 1; i++ ) {
            for ( long long int j = 0; j < rWidth; j++ ) {
                if ( osemsmerovka[i][j] > 96 && osemsmerovka[i][j] < 123 ) {
                    writtenSomething = 1;
                    printf ( "%c",osemsmerovka[i][j] );
                    formatInt++;
                    if ( formatInt == 60 ) {
                        printf ( "\n" );
                        formatInt = 0;
                    }
                }
            }
        }
        if ( writtenSomething ) {
            printf ( "\n" );
        }
    }
    
    freeOsemsmerovka ( osemsmerovka, aHeight );
    freeWords ( words, aWords );
    return 0;
}

void err ( void ) {
    printf ( "Nespravny vstup.\n" );
}

int checkLine ( char * line, long long int rWidth ) {
    for ( long long int i = 0; i < rWidth; i++ ) {
        if ( ( line[i] < 96 || line[i] > 123 ) && line[i] != '.' ) {
            return 0;
      }
    }
    return 1;
}

void freeOsemsmerovka ( char ** osemsmerovka, long long int aHeight ) {
    for ( long long int i = 0 ; i < aHeight; i++ ) {
        free ( osemsmerovka[i] );
    }
    free ( osemsmerovka );
}

void freeWords ( char ** words, long long int aWords ) {
    for ( int i = 0 ; i < aWords; i++ ) {
        free ( words[i] );
    }
    free ( words );
}

int findWords ( char ** osemsmerovka, char ** words, long long int rHeight, long long int rWidth, long long int rWords ) {
    long long int found = 0, j = 0, k = 0, l = 0, m = 0, n = 0, foundCount = 0, globalFound = 0;
    char * problematicWord = NULL;
    for ( long long int i = 0; i < rWords + 1; i++ ) {
//        printf ( "searching for: %s\n",words[i] );
        found = 0;
        globalFound = 0;
        j = 0;
        k = 0;
        foundCount = 0;
//        printf ( "slovo %d\n",i );
        while ( j < rHeight + 1 ) {
            k = 0;
            while ( k < rWidth ) {
                if ( words[i][0] == tolower ( osemsmerovka[j][k] ) ) {
//                    printf ( "dostal som sa\n" );
                    // ->
                    if ( k + ( int ) strlen ( words[i] ) <= rWidth ) {
                        while ( words[i][l] == tolower ( osemsmerovka[j][k+m] ) && ! found ) {
                            foundCount++;
//                            printf ( "1 %d\n",foundCount );
//                            printf ( "1. %lu\n",strlen ( words[i] ) );
                            if ( ( int ) strlen ( words[i] ) == foundCount ) {
                                found = 1;
                                globalFound = 1;
//                                printf ( "found %s\n",words[i] );
                                for ( long long int p = 0; p < ( int ) strlen ( words[i] ); p++ ) {
//                                    printf ( "char pred: %c\n",osemsmerovka[j][k+p] );
                                    if ( osemsmerovka[j][k+p] > 96 && osemsmerovka[j][k+p] < 123 ) {
//                                        printf ( "PREDTYM na %c\n",osemsmerovka[j][k+p] );
                                        osemsmerovka[j][k+p] -= 32;
//                                        printf ( "prepisujem na %c\n",osemsmerovka[j][k+p] );
//                                        printf ( "char po: %c\n",osemsmerovka[j][k+p] );
                                    }
                                }
                            }
                            else {
                            m++;
                            l++;
                            }
                        }
                        foundCount = 0;
                        m = 0;
                        l = 0;
                    }
                    found = 0;
//                    printf ( "tu1\n" );
                    // <-
                    if ( ( k + 1 ) - ( int ) strlen ( words[i] ) >= 0 ) {
                        while ( words[i][l] == tolower ( osemsmerovka[j][k-m] ) && ! found ) {
                            foundCount++;
//                            printf ( "2 %d\n",foundCount );
                            if ( ( int ) strlen ( words[i] ) == foundCount ) {
                                found = 1;
                                globalFound = 1;
                                for ( long long int p = 0; p < ( int ) strlen ( words[i] ); p++ ) {
                                    if ( osemsmerovka[j][k-p] > 96 && osemsmerovka[j][k-p] < 123 ) {
//                                        printf ( "predtym na %c\n",osemsmerovka[j][k-p] );
                                        osemsmerovka[j][k-p] -= 32;
//                                        printf ( "prepisujem na %c\n",osemsmerovka[j][k-p] );
                                    }
                                }
                            }
                            else {
                            m++;
                            l++;
                            }
                        }
                        foundCount = 0;
                        m = 0;
                        l = 0;
                    }
                    found = 0;
//                    printf ( "tu2\n" );
                    // |
                    // ˇ
                    if ( j + ( int ) strlen ( words[i] ) <= rHeight + 1 ) {
                        while ( words[i][l] == tolower ( osemsmerovka[j+m][k] ) && ! found ) {
                            foundCount++;
//                            printf ( "3 %d\n",foundCount );
                            if ( ( int ) strlen ( words[i] ) == foundCount ) {
                                found = 1;
                                globalFound = 1;
                                for ( long long int p = 0; p < ( int ) strlen ( words[i] ); p++ ) {
                                    if ( osemsmerovka[j+p][k] > 96 && osemsmerovka[j+p][k] < 123 ) {
//                                        printf ( "predtym na %c\n",osemsmerovka[j+p][k] );
                                        osemsmerovka[j+p][k] -= 32;
//                                        printf ( "prepisujem na %c\n",osemsmerovka[j+p][k] );
                                    }
//                                    printf( "%s\n",words[i] );
                                }
                            }
                            else {
                            m++;
                            l++;
                            }
                        }
                        foundCount = 0;
                        m = 0;
                        l = 0;
                    }
                    found = 0;
//                    printf ( "tu3\n" );
                    // ^
                    // |
                    if ( ( j + 1 ) - ( int ) strlen ( words[i] ) >= 0 ) {
                        while ( words[i][l] == tolower ( osemsmerovka[j-m][k] ) && ! found ) {
                            foundCount++;
//                            printf ( "4 %d\n",foundCount );
                            if ( ( int ) strlen ( words[i] ) == foundCount ) {
                                found = 1;
                                globalFound = 1;
                                for ( long long int p = 0; p < ( int ) strlen ( words[i] ); p++ ) {
                                    if ( osemsmerovka[j-p][k] > 96 && osemsmerovka[j-p][k] < 123 ) {
//                                        printf ( "predtym na %c\n",osemsmerovka[j-p][k] );
                                        osemsmerovka[j-p][k] -= 32;
//                                        printf ( "prepisujem na %c\n",osemsmerovka[j-p][k] );
                                    }
                                }
                            }
                            else {
                            m++;
                            l++;
                            }
                        }
                        foundCount = 0;
                        m = 0;
                        l = 0;
                    }
                    found = 0;
//                    printf ( "tu4\n" );
                    // vpravo dole
                    if ( k + ( int ) strlen ( words[i] ) <= rWidth && j + ( int ) strlen ( words[i] ) <= rHeight + 1 ) {
                        while ( words[i][l] == tolower ( osemsmerovka[j+n][k+m] ) && ! found ) {
                            foundCount++;
//                            printf ( "5 %d\n",foundCount );
                            if ( ( int ) strlen ( words[i] ) == foundCount ) {
                                found = 1;
                                globalFound = 1;
                                for ( long long int p = 0; p < ( int ) strlen ( words[i] ); p++ ) {
                                    if ( osemsmerovka[j+p][k+p] > 96 && osemsmerovka[j+p][k+p] < 123 ) {
//                                        printf ( "predtym na %c\n",osemsmerovka[j+p][k+p] );
                                        osemsmerovka[j+p][k+p] -= 32;
//                                        printf ( "prepisujem na %c\n",osemsmerovka[j+p][k+p] );
                                    }
                                }
                            }
                            else {
                            m++;
                            n++;
                            l++;
                            }
                        }
                        foundCount = 0;
                        m = 0;
                        n = 0;
                        l = 0;
                    }
                    found = 0;
//                    printf ( "tu5\n" );
                    // vlavo hore
                    if ( ( k + 1 ) - ( int ) strlen ( words[i] ) >= 0 && ( j + 1 ) - ( int ) strlen ( words[i] ) >= 0 ) {
                        while ( words[i][l] == tolower ( osemsmerovka[j-n][k-m] ) && ! found ) {
                            foundCount++;
//                            printf ( "6 %d\n",foundCount );
                            if ( ( int ) strlen ( words[i] ) == foundCount ) {
                                found = 1;
                                globalFound = 1;
                                for ( long long int p = 0; p < ( int ) strlen ( words[i] ); p++ ) {
                                    if ( osemsmerovka[j-p][k-p] > 96 && osemsmerovka[j-p][k-p] < 123 ) {
//                                        printf ( "predtym na %c\n",osemsmerovka[j-p][k-p] );
                                        osemsmerovka[j-p][k-p] -= 32;
//                                        printf ( "prepisujem na %c\n",osemsmerovka[j-p][k-p] );
                                    }
                                }
                            }
                            else {
                            m++;
                            n++;
                            l++;
                            }
                        }
                        foundCount = 0;
                        m = 0;
                        n = 0;
                        l = 0;
                    }
                    found = 0;
//                    printf ( "tu6\n" );
                    // vlavo dole
                    if ( ( k + 1 ) - ( int ) strlen ( words[i] ) >= 0 && ( int ) strlen ( words[i] ) <= rHeight + 1 ) {
                        if ( words[i][l] == 'e' ) {
//                        printf ( "kontrolujem [%d,%d]\n",j,k );
                        }
                        while ( words[i][l] == tolower ( osemsmerovka[j+n][k-m] ) && ! found ) {
                            foundCount++;
                            if ( words[i][l] == 'e' ) {
//                                printf ( "found \"e\"\n" );
//                                printf ( "%c\n",osemsmerovka[j+n][k-m] );
//                                printf ( "%s\n",words[i] );
                            }
                            //                            printf ( "7 %d\n",foundCount );
                            if ( ( int ) strlen ( words[i] ) == foundCount ) {
                                found = 1;
                                globalFound = 1;
                                for ( long long int p = 0; p < ( int ) strlen ( words[i] ); p++ ) {
                                    if ( osemsmerovka[j+p][k-p] > 96 && osemsmerovka[j+p][k-p] < 123 ) {
//                                        printf ( "predtym na %c\n",osemsmerovka[j+p][k-p] );
                                        osemsmerovka[j+p][k-p] -= 32;
//                                        printf ( "prepisujem na %c\n",osemsmerovka[j+p][k-p] );
                                    }
                                }
                            }
                            else {
                            m++;
                            n++;
                            l++;
                                if ( words[i][0] == 'e' ) {
//                                    printf ( "word: %c, osem: %c\n",words[i][l], osemsmerovka[j+n][k-m] );
                                }
                            }
                        }
                        foundCount = 0;
                        m = 0;
                        n = 0;
                        l = 0;
                    }
                    found = 0;
//                    printf ( "tu7\n" );
                    // vpravo hore
                    if ( k + ( int ) strlen ( words[i] ) <= rWidth && ( j + 1 ) - ( int ) strlen ( words[i] ) >= 0 ) {
                        while ( words[i][l] == tolower ( osemsmerovka[j-n][k+m] ) && ! found ) {
                            foundCount++;
//                            printf ( "8 %d\n",foundCount );
                            if ( ( int ) strlen ( words[i] ) == foundCount ) {
                                found = 1;
                                globalFound = 1;
                                for ( long long int p = 0; p < ( int ) strlen ( words[i] ); p++ ) {
                                    if ( osemsmerovka[j-p][k+p] > 96 && osemsmerovka[j-p][k+p] < 123 ) {
//                                        printf ( "predtym na %c\n",osemsmerovka[j-p][k+p] );
                                        osemsmerovka[j-p][k+p] -= 32;
//                                        printf ( "prepisujem na %c\n",osemsmerovka[j-p][k+p] );
                                    }
                                }
                            }
                            else {
                            m++;
                            n++;
                            l++;
                            }
                        }
                        foundCount = 0;
                        m = 0;
                        n = 0;
                        l = 0;
                    }
                    found = 0;
                    k++;
                }
                else {
                    k++;
//                    printf ( "😭\n" );
                }
            }
            j++;
        }
        if ( ! globalFound ) {
            char * problematicWord = ( char * ) calloc ( strlen ( words[i] ) * sizeof ( char ) + 1, sizeof ( char ) ) ;
            strncpy ( problematicWord, words[i], strlen ( words[i] ) - 1 );
            printf ( "Slovo '%s' nenalezeno.\n",words[i] );
            free ( problematicWord );
            return 0;
        }
        else {
//            for ( int i = 0; i < rHeight + 1; i++ ) {
//                for ( int j = 0; j < rWidth; j++ ) {
//                        printf ( "%c",osemsmerovka[i][j] );
//            }
//                printf ( "\n" );
//                }
//            printf ( "found the word: %s\n",words[i]  );
        }
    }
    free ( problematicWord );
    return 1;
}
