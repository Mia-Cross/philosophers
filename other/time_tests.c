#include <stdio.h>
#include <time.h>

int main( int argc, char * argv[] ) {

    time_t timestamp = time( NULL );
    printf( "Timestamp since January 1, 1970: %ld\n", timestamp );
    
    unsigned long seconds = difftime( timestamp, 0 );
    printf( "Number of seconds since January 1, 1970: %ld\n", seconds );
        
    return 0;
}