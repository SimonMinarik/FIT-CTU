#ifndef __PROGTEST__
#include <stdlib.h>
#include <assert.h>
#endif /* __PROGTEST__ */
#include <stdio.h>
#include <math.h>
int asseert = 0;
int gcd( int a, int b );

unsigned long long int hyperloop                           ( unsigned long long int length,
                                                            unsigned int        s1,
                                                            unsigned int        s2,
                                                            unsigned int        bulkhead,
                                                            unsigned int      * c1,
                                                            unsigned int      * c2 )
{
    double x,length2 = length - bulkhead,x2 = s1 + bulkhead;
    int vys = 0;
    int a = s1,b = s2,c=length - bulkhead;
    int sd,help;
    asseert++;
    printf( "Assert: %d\n",asseert );
    printf( "c1: %u, c2: %u\n",*c1,*c2 );
    if ( s1 > 0 )
    a = s1 + bulkhead;
    if ( s2 > 0 )
    b = s2 + bulkhead;
    printf( "A: %d, B: %d, C: %d, length: %llu, bulkhead: %u\n",a,b,c,length,bulkhead );
    if ( bulkhead > length ){
        printf( "ja som to1\n" );
        return 0;
    }
    printf( "ja este fungujem\n" );
    if ( s1 == 0 && s2 == 0 && c != 0 ){
        printf( "ja som to2\n" );
        return 0;
    }
    else if ( a == 0 && b == 0 && c == 0 ){
        *c1 = 0;
        *c2 = 0;
        printf( "c1: %u, c2: %u\n",*c1,*c2 );
        return 1;
    }
    printf( "ja este fungujem3\n" );
    sd = gcd(gcd(a,b),c);
    printf( "sd:   %d\n",sd );
    
    if ( fmod(length - bulkhead, gcd(a,b)) != 0 ){
        printf("hej\n");
    return 0;
    }
    else{
        a /= sd;
        b /= sd;
        c /= sd;
        printf( "a: %d\nb: %d\nc: %d\n",a,b,c );
    if ( isinf(length2/x2) == 0 )
        x = length2/x2;
        else{
            *c1 = 0;
            *c2 = 1;
            return 1;
        }
        printf( "x    %lf\n",x );
        long long int k = x;
    if ( fmod( x,1 ) == 0 ){
        vys++;
        printf( "ja\n" );
        *c1 = x;
        *c2 = 0;
        printf( "a: %d\nb: %d\nc: %d\n",a,b,c );
        if ( b == 0 ){
            printf( "keket\n" );
            return 1;
        }
        if ( a == b )
        return 1;
    }
        else{
            while ( (((length-bulkhead) - (s1+bulkhead)*k) % (s2+bulkhead)) != 0) {
                k--;
                if ( k < 0 ){
                    return 0;
                }
                printf( "jaaaa\n" );
            }
            *c1 = k;
            *c2 = (((length-bulkhead) - (s1+bulkhead)*k) / (s2+bulkhead));
            printf( "Ce1: %u..... Ce2: %u\n",*c1,*c2 );
            printf( "%lld,%u\n",k,*c2 );
        }
    
//    while (x - (s2 + bulkhead) >= 0) {
//        vys++;
//        x -= (s2 + bulkhead);
//        printf( "%lf\n",x );
//        printf( "jaaa\n" );
//    }
        if ( fmod(x,1) != 0 ){
            printf( "kokotko\n" );
        help = *c1 / b + 1;
        }
        else help = x / b;
        vys += help;
    printf( "%d\n",vys );
    return vys;
    }
}

int gcd( int a, int b ){
    int temp;
    while (b != 0) {
        temp = a % b;
        a = b;
        b = temp;
    }
    return a;
}

#ifndef __PROGTEST__
int main ( int argc, char * argv [] )
{
    unsigned int c1, c2;
    assert ( hyperloop ( 100, 4, 7, 0, &c1, &c2 ) == 4
            && 4 * c1 + 7 * c2 + 0 * (c1 + c2 + 1) == 100 );
    assert ( hyperloop ( 123456, 8, 3, 3, &c1, &c2 ) == 1871
            && 8 * c1 + 3 * c2 + 3 * (c1 + c2 + 1) == 123456 );
    assert ( hyperloop ( 127, 12, 8, 0, &c1, &c2 ) == 0 );
    assert ( hyperloop ( 127, 12, 4, 3, &c1, &c2 ) == 1
            && 12 * c1 + 4 * c2 + 3 * (c1 + c2 + 1) == 127 );
    assert ( hyperloop ( 100, 35, 0, 10, &c1, &c2 ) == 1
            && c2 == 0
            && 35 * c1 + 10 * (c1 + 1) == 100 );
    assert ( hyperloop ( 110, 30, 30, 5, &c1, &c2 ) == 1
            && 30 * c1 + 30 * c2 + 5 * (c1 + c2 + 1) == 110 );
    c1 = 2;
    c2 = 7;
    assert ( hyperloop ( 110, 30, 30, 0, &c1, &c2 ) == 0 && c1 == 2 && c2 == 7 );
    c1 = 4;
    c2 = 8;
    assert ( hyperloop ( 9, 1, 2, 10, &c1, &c2 ) == 0 && c1 == 4 && c2 == 8 );
    assert ( hyperloop ( 993000, 1, 2, 0, &c1, &c2) == 496501 && 1 * c1 + 2 * c2 + 0 * (c1 + c2 + 1) == 993000 );
    c1 = 4; c2 = 8;
    assert ( hyperloop ( 87791, 141, 81, 24, &c1, &c2 ) == 0 && c1 == 4 && c2 == 8 );
    c1 = 4; c2 = 8;
    assert ( hyperloop (780, 0, 0, 390, &c1, &c2) == 0 && c1 == 4 && c2 == 8 );
    assert ( hyperloop (742, 0, 742, 0, &c1, &c2) == 1 && 0 * c1 + 742 * c2 + 0 * (c1 + c2 + 1) == 742 );
    assert ( hyperloop (2406, 802, 1604, 0, &c1, &c2) == 2 && 802 * c1 + 1604 * c2 + 0 * (c1 + c2 + 1) == 2406 );
    assert ( hyperloop (81644, 40, 163, 14, &c1, &c2) == 26 && 40 * c1 + 163 * c2 + 14 * (c1 + c2 + 1) == 81644 );
    c1 = 4; c2 = 8;
    assert ( hyperloop (1760, 0, 0, 880, &c1, &c2) == 0 && c1 == 4 && c2 == 8 );
    assert ( hyperloop (263000, 1, 2, 1, &c1, &c2) == 43833 && 1 * c1 + 2 * c2 + 1 * (c1 + c2 + 1) == 263000 );
    assert ( hyperloop (985, 0, 0, 985, &c1, &c2) == 1 && 0 * c1 + 0 * c2 + 985 * (c1 + c2 + 1) == 985 );
    assert ( hyperloop (285, 285, 285, 0, &c1, &c2) == 1 && 285 * c1 + 285 * c2 + 0 * (c1 + c2 + 1) == 285 );
    assert ( hyperloop ( 1760, 0, 0, 880, &c1, &c2 ) == 0 );
    assert ( hyperloop ( 7387, 191, 155, 27, &c1, &c2 ) == 0 );
    assert ( hyperloop ( 16911, 161, 165, 33, &c1, &c2 ) == 1 );
    assert ( hyperloop ( 87791, 141, 81, 24, &c1, &c2 ) == 0 );
    return 0;
}
#endif /* __PROGTEST__ */

