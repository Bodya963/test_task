#include "hasher.h"


hash_tree * make_tree( const char * path, int val_err)
{
    int fd = open( path, O_RDONLY);
    long size_file = get_size_file( fd);

    if( fd == -1)
    {
        printf("make_tree: cant open %s\n", path);
        return NULL;
    }

    hash_tree * h_tree = (hash_tree *)calloc( 1, sizeof( hash_tree));  // создаем корневой узел

    if (h_tree == NULL) {
        printf("make_tree: memory allocation failed\n");
        close(fd);
        exit(1);
    }

    strcpy( h_tree->name, path);
    assert( strlen( path) < SIZE_NAME);

    h_tree->count_leaf = make_size_leaf( val_err, &(h_tree->capacity)); // считаем сколько нам нужно листрев
    
    long size_part = 0;
    if( h_tree->count_leaf != 0)
    {
        size_part = size_file / h_tree->count_leaf;     // размер одного кусочка 
    }
    
    h_tree->left = create_struct_tree( (h_tree->count_leaf) / 2);      // создали структуру дерева, но пока пустое 
    h_tree->right = create_struct_tree( (h_tree->count_leaf) / 2);

    make_hash_in_tree( fd, size_part, h_tree->left);  // заполняем дерево хешами
    make_hash_in_tree( fd, size_part, h_tree->right);

    if( h_tree->count_leaf == 0)
    {
        h_tree->main_hash = make_hash( fd, size_file);
    }
    else
    {
        h_tree->main_hash = merge_hash( (h_tree->left)->hash, (h_tree->right)->hash);
    }

    close( fd);

    return h_tree;
}


node* create_struct_tree( int count)
{

    if( count != 0 )
    {
        node * my_node = (node *)calloc( 1, sizeof( node));

        assert( my_node != NULL);

        my_node->lift = create_struct_tree( count / 2);
        my_node->right = create_struct_tree( count / 2);

        return my_node;
    }

    return NULL;


}

void make_hash_in_tree( int fd, long size_part, node * p_node)
{

    if( p_node != NULL)
    {

        if( p_node->lift == NULL && p_node->right == NULL)  //Если это листок создаем для него хеш
        {
            p_node->hash = make_hash( fd, size_part);
        }
        else
        {
            make_hash_in_tree( fd, size_part, p_node->lift);
            make_hash_in_tree( fd, size_part, p_node->right);
            
            p_node->hash = merge_hash( (p_node->lift)->hash, (p_node->right)->hash);  // обьединяем два хеша в один
        }
        
        return;
    }

    return;
}

uint8_t * make_hash( int fd, long size_part)
{
    char * buf = (char *)calloc( size_part, 1);
    uint8_t * output = ( uint8_t *)calloc( BLAKE3_OUT_LEN, sizeof( uint8_t));

    assert( buf != NULL || output != NULL);

    if (read( fd, buf, size_part) == -1)
    {
        printf( "Make_hash: read send error\n");
        exit(1);
    }

    blake3_hasher hasher;
    blake3_hasher_init(&hasher);
    blake3_hasher_update(&hasher, buf, size_part);
    blake3_hasher_finalize(&hasher, output, BLAKE3_OUT_LEN);

    free( buf);

    return output;
}

uint8_t * merge_hash( uint8_t * hash_1, uint8_t * hash_2)
{
    uint8_t * output =(uint8_t *)calloc( BLAKE3_OUT_LEN, sizeof( uint8_t));

    assert( output != NULL);

    blake3_hasher hasher;
    blake3_hasher_init(&hasher);
    blake3_hasher_update(&hasher, hash_1, BLAKE3_OUT_LEN);
    blake3_hasher_update(&hasher, hash_2, BLAKE3_OUT_LEN);
    blake3_hasher_finalize(&hasher, output, BLAKE3_OUT_LEN);

    return output;
}

int make_size_leaf( float val_err, int * capacity)
{
    if ( (val_err == 100) || (val_err == 0) )
    {
        return 0;
    }
    
    int size_pow = 0;

    if( val_err == 50)
    {
        val_err = 50;
    }
    else
    {
        val_err = (int)val_err % 50;
    }

    int size_leaf = 100;
    int next_leaf = 50;

    while( true)
    {
        size_pow++;

        size_leaf = size_leaf / 2;
        next_leaf = next_leaf / 2;

        if( val_err == size_leaf)
        {
            *capacity = size_pow;

            return my_pow( 2, size_pow);
        }

        if( next_leaf <= val_err && val_err < size_leaf)
        {
            *capacity = size_pow+1;

            return my_pow( 2, size_pow+1);
        }
    }

}

long get_size_file( int fd)
{
    long size_file = lseek( fd, 0, SEEK_END);
    lseek( fd, 0, SEEK_SET);


    return size_file;
}

void print_hash(uint8_t* hash) 
{
    for (size_t i = 0; i < BLAKE3_OUT_LEN; i++) 
    {
        printf("%02x", hash[i]);
    }
}

void print_tree(const node* p_node, int level) 
{
    if (p_node == NULL) 
    {
        return;
    }

    for (int i = 0; i < level; i++) 
    {
        printf("    ");
    }

    printf("Hash: ");
    print_hash(p_node->hash);
    printf("\n");

    print_tree(p_node->lift, level + 1);
    print_tree(p_node->right, level + 1);
}

void print_hash_tree(const hash_tree* h_tree) 
{
    if (h_tree == NULL) 
    {
        printf("Tree is empty\n");
        return;
    }

    printf("Tree Name: %s\n", h_tree->name);
    printf("Main Hash: ");
    print_hash(h_tree->main_hash);
    printf("\n");

    printf("Left Subtree:\n");
    print_tree(h_tree->left, 1);

    printf("Right Subtree:\n");
    print_tree(h_tree->right, 1);

    printf("\n");
}

void delete_hash_tree( hash_tree * tree)
{
    assert( tree != NULL);

    delete_tree( tree->left);
    delete_tree( tree->right);

    free( tree->main_hash);

    free( tree);
}

void delete_tree( node * tree)
{
    if( tree != NULL)
    {
        assert( tree->hash != NULL);

        free(tree->hash);
        
        delete_tree( tree->lift);
        delete_tree( tree->right);

        free( tree);

        return;
    }

    return;
}

int my_pow( int num, int step)
{
    assert( num >= 0);
    assert( step >= 0);

    int res = 1;

    for ( int i = 0; i < step; i++)
    {
        res*= num;
    }

    return res;
}