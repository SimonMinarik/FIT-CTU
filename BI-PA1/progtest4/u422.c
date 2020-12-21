#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>

void err ( void );
int readPlaces ( int * place, int * count );
int comp ( const void * a, const void * b );
void billboardPlacement ( int * place, int numOfBillboards, int count );
void binaryMyAss ( int * place, int numOfBillboards, int count );

int main ( void ){
    int place[1000000];
    int count = 0,numOfBillboards;
    char c;
    
    printf( "Mozna umisteni:\n" );
    if ( readPlaces(place, &count) == 1 ){                                      //read the input - places
        err ();
        return 0;
    }
    
    qsort ( place, count, sizeof(int), comp );                                  //sort the array of places
    for (int i = 0; i < count; i++) {
        #ifndef __PROGTEST__
//        printf( "place[%d]: %d\n",i,place[i] );
        #endif /* __PROGTEST__ */
    }
    
    
    printf ( "Pocet billboardu:\n" );
    
    while ( 1 ) {
        if ( scanf ( "%d",&numOfBillboards ) == 1 ) {
            if ( numOfBillboards >= 0 ){
            billboardPlacement ( place, numOfBillboards, count );
            }
            else{
                printf ( "Nespravny vstup.\n" );
                return 0;
            }
        }
        else{
            if ( scanf ( "%c",&c ) == EOF ) {
                return 0;
            }
            else{
            printf ( "Nespravny vstup.\n" );
            return 0;
            }
        }
    }
    
    return 0;
}

int readPlaces ( int * place, int * count ){
    int temp,numIsLoaded = 0;
    char c;
    scanf ( " %c",&c );
    if (c != '{')
        return 1;
    else{
        while ( scanf ( "%d",&temp ) == 1 ){
            if ( temp >= 0 ) {
                numIsLoaded = 1;
                place[*count] = temp;
                *count += 1;
#ifndef __PROGTEST__
//                printf ( "pole[%d] = %d\n",*count-1,place[*count-1] );
#endif /* __PROGTEST__ */
                if ( scanf( " %c",&c ) == 1 ){
                    if ( c == '}' && numIsLoaded == 1 ){
                        return 0;
                    }
                    else if ( c == '}' && numIsLoaded == 0){
                        return 1;
                    }
                    if ( c != ',' ){
                        return 1;
                    }
                    else{
                        numIsLoaded = 0;
                    }
                }
                else return 1;
            }
        }
        if ( scanf( " %c",&c ) == 1 ){
            if ( c == '}' && numIsLoaded == 1 ) {
                return 0;
            }
            else{
                return 1;
            }
        }
        else{
            return 1;
        }
    }
    return 0;
}

void err ( void ){
    printf ( "Nespravny vstup.\n" );
}

int comp ( const void * a, const void * b ) {
    return ( *(int*)a - *(int*)b );
}

void billboardPlacement ( int * place, int numOfBillboards, int count ){
    if ( numOfBillboards > count ) {
        printf( "N/A\n" );
    }
    else if ( numOfBillboards < 2 ){
        printf ( "Vzdalenost: inf\n" );
        }
        else if ( numOfBillboards == 2 ){
            printf ( "Vzdalenost: %d\n",place[count-1] - place[0] );
            }
        else{
            binaryMyAss ( place, numOfBillboards, count );
        }
}

void binaryMyAss ( int * place, int numOfBillboards, int count ){
    int i = 0, j = 1, distance = 0, found = 1, realDistance = INT_MAX, low = 0, high = place[count-1];
    distance = ( place[count-1] - place[0] ) / 2;
//    fuckMe = distance;
    #ifndef __PROGTEST__
//    printf ( "firstdist: %d\n",distance );
    #endif /* __PROGTEST__ */
    while ( found != numOfBillboards ){
        if ( distance == 0 ){
            realDistance = 0;
            break;
        }
        found = 1;
        j = 1;
        i = 0;
        while ( j <= count - 1 ){
            #ifndef __PROGTEST__
//            printf ( "i a j na zaciatku: %d a %d\n",i,j );
//            printf ( "najdene pole: place[%d] = %d\n",i,place[i] );
            #endif /* __PROGTEST__ */
            if ( place[i] + distance <= place[j] ){
                if ( place[j] - place[i] < realDistance ){
                    realDistance = place[j] - place[i];
                }
                #ifndef __PROGTEST__
//                printf ( "pole vlavo: %d\n",place[i] );
//                printf ( "pole vpravo: %d\n",place[j] );
                #endif /* __PROGTEST__ */
                i = j;
                #ifndef __PROGTEST__
//                printf ( "najdene pole: place[%d] = %d\n",i,place[i] );
                #endif /* __PROGTEST__ */
                j++;
                found++;
                while ( place[i] == place[j] ){
                    i++;
                    j++;
                    #ifndef __PROGTEST__
//                    printf ( "place[%d] = %d\n",j,place[j] );
                    #endif /* __PROGTEST__ */
                }
                #ifndef __PROGTEST__
//                printf ( "2pole vlavo: %d\n",place[i] );
//                printf ( "2pole vpravo: %d\n",place[j] );
                #endif /* __PROGTEST__ */
            }
            else{
                j++;
            }
            #ifndef __PROGTEST__
//            printf ( "found: %d\n",found );
            #endif /* __PROGTEST__ */
        }
//         place[i] + distance > place[count-1]
        #ifndef __PROGTEST__
//        printf ( "place[%d](%d) + distance(%d) > place[%d](%d)\n",i,place[i],distance,count-1,place[count-1] );
        #endif /* __PROGTEST__ */
        if ( found < numOfBillboards ){
            high = distance;
            if ( distance == 1 ) {
                distance--;
            }
            distance = distance - ( ( distance ) / 2 );
//            distance = distance - ( ( distance ) / 2 );
//            if ( fuckMe == distance ) {
//                weAreFucked = 1;
//            }
//            else{
//                fuckMe = distance;
//            }
            low = distance;
            #ifndef __PROGTEST__
//            printf ( "found: %d\n",found );
            #endif /* __PROGTEST__ */
//            found = 1;
            #ifndef __PROGTEST__
//            printf ( "zmensujem distance na: %d\n",distance );
            #endif /* __PROGTEST__ */
//            i = 0;
//            j = 1;
            realDistance = INT_MAX;
        }
        else if ( found > numOfBillboards ){
            low = distance;
            distance = distance + ( high - distance ) / 2;
//            distance = distance + ( ( distance ) / 2 );
//            if ( fuckMe == distance ) {
//                weAreFucked = 1;
//            }
//            else{
//                fuckMe = distance;
//            }
            high = distance;
            #ifndef __PROGTEST__
//            printf ( "found: %d\n",found );
            #endif /* __PROGTEST__ */
//            found = 1;
            #ifndef __PROGTEST__
//            printf ( "zvacsujem distance na: %d\n",distance );
            #endif /* __PROGTEST__ */
//            i = 0;
//            j = 1;
            realDistance = INT_MAX;
            }
//        printf ( "low: %d, high: %d\n",low, high );
//        if ( weAreFucked ) {
//            break;
//        }
        #ifndef __PROGTEST__
//        printf ( "cyklim sa2\n" );
//        printf ( "diqst: %d\n",distance );
        #endif /* __PROGTEST__ */
        //( distance == 0 && found > numOfBillboards ) ||
        if ( ( high == distance && low == distance ) ) {
            found = numOfBillboards;
        }
    }
//    distance = realDistance;
    realDistance = INT_MAX;
//    int k = found;
    while ( found == numOfBillboards || found > numOfBillboards ) {
        found = 1;
        distance ++;
        j = 1;
        i = 0;
        while ( j <= count - 1 ){
            #ifndef __PROGTEST__
//            printf ( "i a j na zaciatku: %d a %d\n",i,j );
//            printf ( "najdene pole: place[%d] = %d\n",i,place[i] );
            #endif /* __PROGTEST__ */
            if ( place[i] + distance <= place[j] ){
                if ( place[j] - place[i] < realDistance ){
                    realDistance = place[j] - place[i];
                }
                #ifndef __PROGTEST__
//                printf ( "pole vlavo: %d\n",place[i] );
//                printf ( "pole vpravo: %d\n",place[j] );
                #endif /* __PROGTEST__ */
                i = j;
                #ifndef __PROGTEST__
//                printf ( "najdene pole: place[%d] = %d\n",i,place[i] );
                #endif /* __PROGTEST__ */
                j++;
                found++;
                while ( place[i] == place[j] ){
                    i++;
                    j++;
                    #ifndef __PROGTEST__
//                    printf ( "place[%d] = %d\n",j,place[j] );
                    #endif /* __PROGTEST__ */
                }
                #ifndef __PROGTEST__
//                printf ( "2pole vlavo: %d\n",place[i] );
//                printf ( "2pole vpravo: %d\n",place[j] );
                #endif /* __PROGTEST__ */
            }
            else{
                j++;
            }
            #ifndef __PROGTEST__
//            printf ( "found: %d\n",found );
            #endif /* __PROGTEST__ */
        }
        i = 0;
        j = 1;
    }
    distance --;
    #ifndef __PROGTEST__
//    printf ( "realDistance = %d\n",realDistance );
    #endif /* __PROGTEST__ */
    if ( distance == -1 ) {
        printf ( "Vzdalenost: %d\n",distance+1 );
    }
    else printf ( "Vzdalenost: %d\n",distance );
}
