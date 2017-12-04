#ifndef NUFS_H
#define NUFS_H

typedef struct jefe {
	int** bitmap_inode;
	int** bitmap_data;
	int inode_size;
	int data_block_size;
	void* nodes;
	void* data_blocks;
} jefe;

typedef struct inode {
	mode_t mode;
	uid_t uid;
	off_t size;
	time_t time;
	time_t ctime;
	time_t mtime;
	time_t dtime;
	gid_t gid;
	nlink_t links_count;
	blkcnt_t blocks;
} inode;

typedef struct file_data {
    const char* path;
    int         mode;
    const char* data;
} file_data;

#endif