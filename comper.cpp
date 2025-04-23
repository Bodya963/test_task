#include "compar.h"

int compar_tree( hash_tree * tree1, hash_tree * tree2, int val_err)
{
    if( val_err == 0)
    {
        return 1;
    }

    if( val_err == 100)
    {
        return compar_hash( tree1->main_hash, tree2->main_hash);
    }

    if( compar_hash( tree1->main_hash, tree2->main_hash))
    {
        return 1;
    }

    if( (!(compar_hash( tree1->left->hash, tree2->left->hash)) && (!(compar_hash( tree1->right->hash, tree2->right->hash)))))
    {
        return 0;
    }

    if( (compar_node( tree1->left, tree2->left, val_err)) && (compar_node( tree1->right, tree2->right, val_err)))
    {
        return 1;
    }

    return 0;
    

}

int compar_node( node * node1, node * node2, int val_err)
{
    if( compar_hash( node1->hash, node2->hash))
    {
        return 1;
    }

    if( node1->lift == NULL && node2->lift == NULL && node1->right == NULL && node2->right == NULL)
    {
        return 0;
    }

    if( val_err <= 50)
    {
        if( (!(compar_hash( (node1->lift)->hash, (node2->lift)->hash))) && (!(compar_hash( (node1->right)->hash, (node2->right)->hash))))
        {
            return 0;
        }
    }

    if( (compar_node(node1->lift, node2->lift, val_err)) + (compar_node( node1->right, node2->right, val_err)))
    {
        return 1;
    }

    return 0;
}

int compar_hash( uint8_t * hash1, uint8_t * hash2)
{
    for ( int i = 0; i < BLAKE3_OUT_LEN; i++)
    {
        if( hash1[i] != hash2[i])
        {
            return 0;
        }
    }
    
    return 1;
}