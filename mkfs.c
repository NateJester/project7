#include <fuse.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

int file;
int num_inodes;
int num_blocks;

static int parse_args(int argc, char **argv) {
        int op;
        while ((op = getopt(argc, argv, "d:i:b:")) != -1) {
                switch (op) {

                case 'd':
                printf("%s", optarg);
                break;

                case 'i':
                num_inodes = atoi(optarg);
                printf("%d", num_inodes);
                break;

                case 'b':
                num_blocks = atoi(optarg);
                num_blocks += 32;
                num_blocks -= (num_blocks % 32);
				printf("%d", num_blocks);
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
}
