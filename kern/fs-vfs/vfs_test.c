
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <asm/segment.h>
#include <asm/uaccess.h>
#include <linux/buffer_head.h>

struct file* open_file;

/* Doing file I/O in kernel space using VFS commands. The vfs commands call the
 * respective file I/O functions using file->fop->read indirections. These fop
 * are filled by the kernel depending upon the type of file system, eg, FAT,
 * NTFS and are called when sys_read calls vfs_read
 		[ 3679.262505]  [<ffffffff811be8ca>] vfs_write+0xba/0x1e0
		[ 3679.262510]  [<ffffffff811bf416>] SyS_write+0x46/0xb0
		[ 3679.262515]  [<ffffffff8172f3bf>]
		tracesys+0xe1/0xe6
*/

struct file* file_open(const char* path, int flags, int rights) 
{
    	struct file* filp = NULL;
    	mm_segment_t oldfs;
    	int err = 0;

    	oldfs = get_fs();
    	set_fs(get_ds());
    	filp = filp_open(path, flags, rights);
    	set_fs(oldfs);
    	if(IS_ERR(filp)) {
    		err = PTR_ERR(filp);
        	return NULL;
    	}
    	return filp;
}

void file_close(struct file* file)
{
    	filp_close(file, NULL);
}

int file_read(struct file* file, unsigned long long offset, unsigned char* data, unsigned int size) 
{
    	mm_segment_t oldfs;
    	int ret;

    	oldfs = get_fs();
    	set_fs(get_ds());

    	ret = vfs_read(file, data, size, &offset);

    	set_fs(oldfs);
    	return ret;
}

int file_write(struct file* file, unsigned long long offset, unsigned char* data, unsigned int size) 
{
    	mm_segment_t oldfs;
    	int ret;

    	oldfs = get_fs();
    	set_fs(get_ds());

    	ret = vfs_write(file, data, size, &offset);

    	set_fs(oldfs);
    	return ret;
}

int file_sync(struct file* file)
{
    	vfs_fsync(file, 0);
    	return 0;
}

static int __init file_init(void)
{
  	char buffer[256];

	open_file = file_open("/etc/shadow", O_RDWR, 0);
	if (open_file == NULL) {
		pr_err("Error in opening the file");
		goto end;
	} else {
		pr_info("File opened without any issue");
	}

	file_read(open_file, 0, buffer, 256);
	pr_info("%s", buffer);

    end:
  	return 0;
}

static void __exit file_exit(void)
{
	file_close(open_file);
}

MODULE_LICENSE("GPL");
module_init(file_init);
module_exit(file_exit);

