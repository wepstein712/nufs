#ifndef PAGES_H
#define PAGES_H

#include <stdio.h>

#include "nufs.h"

void   pages_init(const char* path);
void   pages_free();
void*  pages_get_page(int pnum);
inode* pages_get_node(int node_id);
int    pages_find_empty();
void   print_node(inode* node);

#endif
