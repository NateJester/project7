#include "wfs.h"
#include <fuse.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

static int wfs_getattr(const char *path, struct stat *stbuf) {
    // Implementation of getattr function to retrieve file attributes
    // Fill stbuf structure with the attributes of the file/directory indicated by path
    // ...
    return 0; // Return 0 on success
}

static int wfs_mknod(const char* path, mode_t mode, dev_t rdev) {
	return 0;
}

static int wfs_mkdir(const char* path, mode_t mode) {
	return 0;
}

static int wfs_unlink(const char* path) {
	return 0;
}

static int wfs_rmdir(const char* path) {
	return 0;
}

static int wfs_read(const char* path, char *buf, size_t size, off_t offset, struct fuse_file_info* fi) {
	return 0;
}
	
static int wfs_write (const char* path, const char *buf, size_t size, off_t offset, struct fuse_file_info* fi) {
	return 0;
}

static int wfs_readdir(const char* path, void* buf, fuse_fill_dir_t filler, off_t offset, struct fuse_file_info* fi) {
	return 0;
}

static struct fuse_operations ops = {
      .getattr = wfs_getattr,
	  .mknod   = wfs_mknod,
	  .mkdir   = wfs_mkdir,
	  .unlink  = wfs_unlink,
	  .rmdir   = wfs_rmdir,
	  .read    = wfs_read,
	  .write   = wfs_write,
	  .readdir = wfs_readdir,
};

int main(int argc, char *argv[]) {
    // Initialize FUSE with specified operations
    // Filter argc and argv here and then pass it to fuse_main
    return fuse_main(argc, argv, &ops, NULL);
}
