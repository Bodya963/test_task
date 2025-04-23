#pragma once


//----------------------------

#include <stdio.h>
#include <stdlib.h>
#include "blake3.h"
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <math.h>
#include <assert.h>

//----------------------------

//--------------define-------

#define SIZE_NAME 59

//--struct hash---------------

struct node
{
    
    uint8_t * hash;
    
    node * lift;
    node * right;
    
};

typedef struct node node;

typedef struct  
{

    int capacity;
    int count_leaf;

    char name[SIZE_NAME];

    uint8_t* main_hash ;

    node * left;
    node *  right;

}hash_tree;

//----------------------------

