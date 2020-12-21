#include <stdio.h>
#include <math.h>
#include <tgmath.h>
#include <float.h>

int main( void ){
    
    long double x11,x21,x12,x22,x13,x23,y11,y21,y12,y22,y13,y23,a1,a2,b1,b2,c1,c2,temp;
    char a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q;
    int coord1,coord2;
    coord1=0;
    coord2=0;
    
    printf( "Trojuhelnik #1:\n" );
    scanf( " %c",&a );
    if( a != '{' ){
        printf( "Nespravny vstup.\n" );
        return 0;
    }
    else if( scanf( "%Lf",&a1 ) == 1 ){
        if( scanf(" , %Lf , %Lf",&b1,&c1 ) != 2 ){
            printf( "Nespravny vstup.\n" );
            return 0;
        }
        else if(scanf( " %c",&m ) != 1 ){
            //printf("%c\n",m);
            printf( "Nespravny vstup.\n" );
            return 0;
        }
        else if (m != '}' ) {
            printf( "Nespravny vstup.\n" );
            return 0;
        }
    }
    else if( scanf(" %c %Lf ; %Lf ] , [ %Lf ; %Lf ] , [ %Lf ; %Lf %c",&b,&x11,&y11,&x12,&y12,&x13,&y13,&l ) != 8 ){
        printf( "Nespravny vstup.\n" );
        return 0;
    }
    else if ( b != '[' || l != ']' ){
        printf( "Nespravny vstup.\n" );
        return 0;
    }
    else if( scanf( " %c",&m ) != 1 ){
        printf( "Nespravny vstup.\n" );
        return 0;
    }
    else if ( m != '}' ){
        printf( "Nespravny vstup.\n" );
        return 0;
    }
    else coord1 = 1;
    if( coord1 == 1 ){
        if( fabsl( (( x12-x11 ) * ( y13-y11 )) - (( x13-x11 )) * ( y12-y11 )) < ((128*128) * DBL_EPSILON * (( x13-x11 ) * ( y12-y11 ))) ){
            printf( "Neplatny trojuhelnik.\n" );
            return 0;
        }
        else{
            a1 = sqrt( powl( ( x12 - x13 ), 2 ) + powl( ( y12 - y13 ), 2 ) );
            b1 = sqrt( powl( ( x11 - x13 ), 2 ) + powl( ( y11 - y13 ), 2 ) );
            c1 = sqrt( powl( ( x11 - x12 ), 2 ) + powl( ( y11 - y12 ), 2 ) );
        }
    }
    if( a1 <= 0 || b1 <= 0 || c1 <= 0 ){
        printf( "Neplatny trojuhelnik.\n" );
        return 0;
    }
    if ( a1 > c1 ){
        temp=c1;
        c1=a1;
        a1=temp;
    }
    if( b1 > c1 ){
        temp=c1;
        c1=b1;
        b1=temp;
    }
    if( (a1 + b1 - c1) <= 128*128 * DBL_EPSILON * c1 ){
        printf( "Neplatny trojuhelnik.\n" );
        return 0;
    }
   // printf( "%Lf,%Lf,%Lf\n%Lf..........%Lf\n",a1,b1,c1,fabsl(a1 + b1 - c1),128*128 * DBL_EPSILON * c1 );
    a=b=c=d=e=f=g=h=i=j=k=l=m=n=o=p=q = '0';
    
    printf( "Trojuhelnik #2:\n" );
    scanf( " %c",&a );
    if( a != '{' ){
        printf( "Nespravny vstup.\n" );
        return 0;
    }
    else if( scanf( "%Lf",&a2 ) == 1 ){
        if( scanf(" , %Lf , %Lf",&b2,&c2 ) != 2 ){
            printf( "Nespravny vstup.\n" );
            //printf("%c,%c\n",o,p);
            return 0;
        }
        else if( scanf( " %c",&m ) != 1 ){
            if ( m != '}' ) {
                printf( "Nespravny vstup.\n" );
                return 0;
            }
                printf( "Nespravny vstup.\n" );
                return 0;
            }
    }
    else if( scanf(" %c %Lf ; %Lf ] , [ %Lf ; %Lf ] , [ %Lf ; %Lf %c",&b,&x21,&y21,&x22,&y22,&x23,&y23,&l ) != 8 ){
        //printf("%s",stdin);
        printf( "Nespravny vstup.\n" );
        return 0;
    }
    else if ( b != '[' || l != ']' ) {
        printf( "Nespravny vstup.\n" );
        return 0;
    }
    else if( scanf( " %c",&m ) != 1 ){
        printf( "Nespravny vstup.\n" );
        return 0;
    }
    else if ( m != '}' ){
        printf( "Nespravny vstup.\n" );
        return 0;
    }
    else coord2 = 1;
    if( coord2 == 1 ){
        if( fabsl( (( x22-x21 ) * ( y23-y21 )) - (( x23-x21 )) * ( y22-y21 )) < ((128*128) * DBL_EPSILON * (( x23-x21 ) * ( y22-y21 ))) ){
            printf( "Neplatny trojuhelnik.\n" );
            return 0;
        }
        else{
            a2 = sqrt( powl( ( x22 - x23 ), 2 ) + powl( ( y22 - y23 ), 2 ) );
            b2 = sqrt( powl( ( x21 - x23 ), 2 ) + powl( ( y21 - y23 ), 2 ) );
            c2 = sqrt( powl( ( x21 - x22 ), 2 ) + powl( ( y21 - y22 ), 2 ) );
        }
    }
    if( a2 <= 0 || b2 <= 0 || c2 <= 0 ){
        printf( "Neplatny trojuhelnik.\n" );
        return 0;
    }
    //    printf( "%Lf,%Lf,%Lf....%Lf,%Lf,%Lf\n",a1,b1,c1,a2,b2,c2 );
    if ( a2 > c2 ){
        temp=c2;
        c2=a2;
        a2=temp;
    }
    if( b2 > c2 ){
        temp=c2;
        c2=b2;
        b2=temp;
    }
    if( fabsl(a2 + b2 - c2) <= 128*128 * DBL_EPSILON * c2 ){
        printf( "Neplatny trojuhelnik.\n" );
        return 0;
    }
    //    printf( "%Lf,%Lf,%Lf....%Lf,%Lf,%Lf\n",a1,b1,c1,a2,b2,c2 );
    //    printf( "%Lf...%Lf\n",a1+b1+c1,a2+b2+c2 );
    if( a1 == a2 && b1 == b2 && c1 == c2 ){
        printf( "Trojuhelniky jsou shodne.\n" );
        return 0;
    }
    else if( fabsl(( a1 + b1 + c1 ) - ( a2 + b2 + c2 )) < 128*128 * DBL_EPSILON * ( a2 + b2 + c2 ) ){
        printf( "Trojuhelniky nejsou shodne, ale maji stejny obvod.\n" );
        return 0;
    }
    else if( ( a1 + b1 + c1 ) > ( a2 + b2 + c2 ) ){
        printf( "Trojuhelnik #1 ma vetsi obvod.\n" );
        return 0;
    }
    else{
        printf( "Trojuhelnik #2 ma vetsi obvod.\n" );
        return 0;
    }
    return 0;
}

