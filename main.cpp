#include "header.h"
#include "hasher.h"
#include "compar.h"

int main( int argc, char ** argv)
{
    if( argc != 2)
    {
        printf( "there must be one argument, this is a valid error( in percentage 0-100).\n");
        exit(1);
    }

    int val_err = atoi( argv[1]);

    if( 0 > val_err || val_err > 100)
    {
        printf( "valid error must be 0-100\n");
        exit(1);
    }

    hash_tree* example_1 = make_tree( "./example/example_1.bin", val_err);

    print_hash_tree( example_1 );
    
    delete_hash_tree( example_1);

    return 0;
}