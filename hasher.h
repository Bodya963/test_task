#pragma once 

#include "header.h"

//-FUNC---------------------


int make_size_leaf( float val_err, int *); // считает на сколько частей нужно разделить файл в
// зависимоти от допустимой ошибки var_err                                                        
long get_size_file( int fd); // возваращает размер файла в байтах




hash_tree * make_tree( const char * path, int val_err ); // Делает дерева Меркла из бинарного файла по пути path 
                                                            //с допустимым ошибкой var_err

node* create_struct_tree( int count); // создает подеревья c количеством листьев count

void make_hash_in_tree( int fd, long size_part, node * ); // заполняет дерево хешами данных из fd 
                                                    
uint8_t * merge_hash( u_int8_t *, u_int8_t *); // создает хеш этих двух хешей

uint8_t * make_hash( int fd , long size_part); // создает хеш из данных fd

void delete_tree( node * tree);

void delete_hash_tree( hash_tree * tree);



void print_hash(uint8_t* hash); // печатает хеш

void print_tree(const node* p_node, int level); // рекурсивно печатает дерево

void print_hash_tree(const hash_tree* h_tree); //печатает полностью дерево


int my_pow( int, int); // целочисленное возведение в степень