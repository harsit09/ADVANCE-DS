//  To sort an array of 0's, 1's, and 2's  
  
#include<stdio.h>  
void sort_array_0_1_2 ( int A[ ] , int n )    
{  
    int i = 0 ,  countzero = 0 , countone = 0 ,  counttwo = 0 ;  
    while ( i < n )  
    {  
        if ( A [ i ] == 0 )  
        {  
            countzero = countzero + 1 ;  
        }  
        else if ( A [ i ] == 1 )  
        {  
            countone = countone + 1 ;  
        }  
        else  
        {  
            counttwo = counttwo + 2 ;  
        }  
        i = i + 1 ;  
    }  
    for  ( i = 0 ; i < countzero ; i++ )  
    {  
        A [ i ] = 0 ;  
    }  
    for ( i = countzero ; i < countzero + countone ; i++ )  
    {  
        A [ i ] = 1 ;  
    }  
    for ( i = countzero + countone ; i < n ; i++ )  
    {  
        A [ i ] = 2 ;  
    }  
}  
void main()  
{  
    int i ,  A[ 100 ] , n;  
    printf ( " Enter number of elements present in the array: " ) ;  
    scanf ( " %d " , &n) ;  
    printf ( " Enter array:  \n " ) ;  
    for ( i = 0 ; i < n ; i++ )  
    {  
        scanf ( " %d " , &A[ i ] ) ;  
    }  
    printf  ( " Array after sorting : \n " ) ;  
    sort_array_0_1_2 ( A , n ) ;  
    for ( i = 0 ; i < n ; i++ )  
    {  
        printf ( " %d \n " , A [ i ] ) ;  
    }  
      
}  
