#include <stdio.h>
#include <limits.h>

void chyba ();
long long int dlzka ( long long int lo, long long int hi, int r );
long long int sekvence ( long long int lo, long long int hi, int r );
long long int nuly ( long long int lo, long long int hi, int r );
void useky ();
long long int vys[37][64];
int main ( void ){
    long long int lo,hi;
    char ukol;
    int d;
    useky();
    printf ( "Zadejte intervaly:\n" );
    while (scanf ( "%d",&d ) != EOF ){
        int r = 10;
        
        if ( scanf( " < %lld ; %lld > %c", &lo, &hi, &ukol ) != 3)
        if ( scanf( " r %d : < %lld ; %lld > %c", &r, &lo, &hi, &ukol ) != 4 ){
            chyba();
            //            printf("ja1\n");
            return 0;
        }
        if ( lo > hi || lo < 0 || hi < 0 || r > 36 || r < 2){
            chyba();
            //        printf("ja2\n");
            return 0;
        }
        else
        switch (ukol) {
            case 'l':
            printf ( "Cifer: %lld\n", dlzka ( lo, hi, r ) );
            break;
            
            case 's':
            printf ( "Sekvence: %lld\n", sekvence ( lo, hi, r ) );
            break;
            
            case 'z':
            printf( "Nul: %lld\n", nuly ( lo, hi, r ) );
            break;
            
            default:
            chyba();
            //        printf("ja3\n");
            return 0;
            break;
        }
//                printf( "r:  %d\n%lld,%lld\n", r, lo, hi );
    }
    return 0;
}

void chyba ( void ){
    printf ( "Nespravny vstup.\n" );
}

long long int dlzka ( long long int lo, long long int hi, int r ){
    long long int l = 0;
    int lo_p = 0;
    int hi_p = 0;
    while ( lo >= vys[r][lo_p] ){
        lo_p++;
    }
    lo_p--;
    while ( hi >= vys[r][hi_p] ){
        hi_p++;
    }
    hi_p--;
    #ifndef __PROGTEST__
//    printf( "lo: %d, hi: %d\n",lo_p,hi_p );
    #endif /* __PROGTEST__ */
    
    if ( lo_p != hi_p ){
    l += ( (hi - (vys[r][hi_p]-1)) * (hi_p + 1) );
//        printf( "(hi - (hi_p - 1)) * (hi_p + 1):   %lld\n", ( (hi - (vys[r][hi_p]-1)) * (hi_p + 1) ));
    int temp_p = hi_p-1;
//        printf( "temp_p:  %d\n",temp_p );
    while ( temp_p > lo_p ) {      //(vys[r][temp_p] - lo) > vys[r][temp_p-1]
        l += ((vys[r][temp_p+1] - vys[r][temp_p]) * (temp_p+1));
        temp_p--;
//        printf( "ja\n" );
    }
    l += ((vys[r][temp_p+1] - lo) * (temp_p+1));
//        printf( "((vys[r][temp_p] - lo) * (temp_p)):      %lld\n",((vys[r][temp_p] - lo) * (temp_p)) );
    }
    else{
        l += (hi - lo + 1) * (lo_p + 1);
    }
    if ( lo == 0)
    l += 1;
    return l;
}

long long int nuly ( long long int lo, long long int hi, int r ){
    long long int l = 0;
    long long int temp;
    for (long long int i = lo; i <= hi; i++){
        temp = i;
        do {
            if ( temp % r == 0 )
            l++;
            temp = temp / r;
        } while (temp != 0);
    }
    return l;
}

long long int sekvence ( long long int lo, long long int hi, int r ){
    long long int l = 0;
    long long int sek = 0;
    long long int temp;
    for (long long int i = lo; i <= hi; i++){
        temp = i;
        do {
            if ( temp % r == 0 ){
                l++;
                if ( l > sek )
                sek = l;
            }
            else
            l = 0;
            temp = temp / r;
        } while (temp != 0);
    }
    return sek;
}

void useky ( void ){
    for ( int i = 2; i <= 36; i++ ){
        int j = 1;
        vys[i][0] = 1;
        vys[i][j] = i;
        do {
            j++;
            vys[i][j] = vys[i][j-1];
            if ( vys[i][j] < LLONG_MAX / i )
            vys[i][j] = vys[i][j] * i;
            #ifndef __PROGTEST__
//            printf( "vys[%d][%d]: %lld\n",i,j,vys[i][j] );
            #endif /* __PROGTEST__ */
        } while ( vys[i][j] < LLONG_MAX / i );
    }
}
