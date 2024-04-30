#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "wfs.h"

char* file_name;
int num_inodes;
int num_blocks;

static int parse_args(int argc, char **argv) {
        int op;
        while ((op = getopt(argc, argv, "d:i:b:")) != -1) {
                switch (op) {

                case 'd':
                file_name = optarg;
                break;

                case 'i':
                num_inodes = atoi(optarg);
 				if (num_inodes % 32 == 0) {
 					break;
 				}
 				num_inodes -= (num_inodes % 32);
 				num_inodes += 32;
                break;

                case 'b':
                num_blocks = atoi(optarg);
                if (num_blocks % 32 == 0) {
                	break;
                }
                num_blocks -= (num_blocks % 32);
                num_blocks += 32;
                break;

                default:
                return 1;
                }

        }
        return 0;
}

int main(int argc, char** argv) {
	if (parse_args(argc, argv) != 0) {
		exit(EXIT_FAILURE);
	}

	printf("%s", file_name);
	FILE* fp = fopen(file_name, "r+");
	if (fp == NULL) {
		perror("fopen");
		return 1;
	}

	fseek(fp, 0, SEEK_END);
	int file_size = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	int size_needed = (num_blocks + 1) * BLOCK_SIZE;
	if (file_size < size_needed) {
		printf("Disk image file to small to accommodate number of blocks");
		return 1;
	}

	struct wfs_inode root;
	root.num = 0;
	root.nlinks = 1;
	
	struct wfs_sb superblock;
	superblock.num_inodes = num_inodes;
	superblock.num_data_blocks = num_blocks;
	superblock.i_bitmap_ptr = sizeof(superblock);
	superblock.d_bitmap_ptr = sizeof(superblock) + num_inodes / 8;
	superblock.i_blocks_ptr = superblock.d_bitmap_ptr + num_blocks / 8;
	superblock.d_blocks_ptr = superblock.i_blocks_ptr + num_inodes * 0x200;
	
	fwrite(&superblock, sizeof(struct wfs_sb), 1, fp);

	fseek(fp, superblock.i_blocks_ptr, SEEK_SET);
	fwrite(&root, sizeof(struct wfs_inode), 1, fp);

	char* i_bitmap = calloc(num_inodes / 8, 1);
	i_bitmap[0] = 1;
	fseek(fp, superblock.i_bitmap_ptr, SEEK_SET);
	fwrite(i_bitmap, sizeof(i_bitmap), 1, fp);
}
