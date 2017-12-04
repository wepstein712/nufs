
#include <stdio.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <assert.h>
#include <fcntl.h>
#include <errno.h>

#include "storage.h"
#include "nufs.h"

const int num_pages = 256;

static file_data file_table[30];

void
storage_init(const char* path)
{
	int pages_fd = open(path, O_CREAT | O_RDWR, 0644);
	void* the_mafia = mmap(0, 1024 * 1024, PROT_READ | PROT_WRITE, MAP_SHARED, pages_fd, 0);

    struct jefe* don = (jefe*)the_mafia;
	don->bitmap_inode = (int**)(the_mafia + sizeof(jefe));
	don->bitmap_data = (sizeof(int) * num_pages) + (void*)(don->bitmap_inode);
	
	/*int i;
	for (i = 0; i < 250; i++) {
		don->bitmap_inode[i] = 0;
		don->bitmap_data[i] = 0;
	}*/
	don->inode_size = sizeof(inode);
	don->data_block_size =4096;
	don->nodes = (void*)(don->bitmap_data) + (2 * sizeof(int));
	don->data_blocks = don->nodes + num_pages * sizeof(inode);
	
	//TODO: Initialize root path
}

static int
streq(const char* aa, const char* bb)
{
    return strcmp(aa, bb) == 0;
}

static file_data*
get_file_data(const char* path) {
    for (int ii = 0; 1; ++ii) {
        file_data row = file_table[ii];

        if (file_table[ii].path == 0) {
            break;
        }

        if (streq(path, file_table[ii].path)) {
            return &(file_table[ii]);
        }
    }

    return 0;
}

int
get_stat(const char* path, struct stat* st)
{
    file_data* dat = get_file_data(path);
    if (!dat) {
        return -1;
    }

    memset(st, 0, sizeof(struct stat));
    st->st_uid  = getuid();
    st->st_mode = dat->mode;
    if (dat->data) {
        st->st_size = strlen(dat->data);
    }
    else {
        st->st_size = 0;
    }
    return 0;
}

const char*
get_data(const char* path)
{
    file_data* dat = get_file_data(path);
    if (!dat) {
        return 0;
    }

    return dat->data;
}

