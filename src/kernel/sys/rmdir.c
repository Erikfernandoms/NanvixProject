#include <nanvix/klib.h>
#include <nanvix/mm.h>
#include <unistd.h>
#include <nanvix/const.h>
#include <nanvix/fs.h>
#include <nanvix/pm.h>
#include <errno.h>
#include <unistd.h>
#include <nanvix/syscall.h>
#include <nanvix/clock.h>
#include <nanvix/const.h>
#include <nanvix/fs.h>
#include <nanvix/klib.h>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>


PUBLIC int sys_rmdir(const char *path){
	int ret;

	ret = sys_unlink(path);
	if (ret == 0){
		kprintf("rmdir: %s deleted successfully!", path);
	}
	return 0;
    
}

