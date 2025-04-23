#pragma once

#include "header.h"

int compar_tree( hash_tree * tree1, hash_tree *tree2, int val_err ); // сравнивает два дерева Мекла. 
//1 - если они равны с допустимой ошибкой val_err. 2 - не равны

int compar_hash( uint8_t * hash1, uint8_t * hash2); // сравнивает два хеша. 1 - равны, 0 - не равны

int compar_node( node * node1, node* node2, int val_err); // сравнивает два поддерева,  
// если val_err <= 50, то 1 - если они совпадают или есть только один лист, который не совпадает, иначе 0
// если val_err > 50, то  1 - если есть хотя бы один лист который совпадает, иначе 0