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
    hash_tree* example_2 = make_tree( "./example/example_2.bin", val_err);
    hash_tree* example_5 = make_tree( "./example/example_5.bin", val_err);
    hash_tree* example_6 = make_tree( "./example/example_6.bin", val_err);
    
    print_hash_tree( example_1 );
    print_hash_tree( example_5 );
    print_hash_tree( example_2 );
    print_hash_tree( example_6 );
    
    printf(" compar ex_1, ex_2 = %d\n", compar_tree( example_1, example_2, val_err));
    printf(" compar ex_1, ex_5 = %d\n", compar_tree( example_1, example_5, val_err));    
    printf(" compar ex_2, ex_6 = %d\n", compar_tree( example_2, example_6, val_err));    
    
    delete_hash_tree( example_1);
    delete_hash_tree( example_2);
    delete_hash_tree( example_5);
    delete_hash_tree( example_6);
    
    return 0;
}