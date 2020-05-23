#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/string.h>

// Documentation
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Manuel Ruiz López");
MODULE_DESCRIPTION("Driver example");
MODULE_SUPPORTED_DEVICE("testdevice");

// Definitions
int init_module(void);
void cleanup_module(void);
static int device_open(struct inode *, struct file *);
static int device_release(struct inode *, struct file *);
static ssize_t device_read(struct file *, char *, size_t, loff_t*);
static ssize_t device_write(struct file *, const char *, size_t, loff_t*);

// Globals
#define DEV_NAME "hello"
#define BUF_LEN 256

static int Major;
static int Dev_Open = 0;
static char msg[BUF_LEN] = "Hello, world\n";


static struct file_operations fops = {
	.read = device_read,
	.write = device_write,
	.open = device_open,
	.release = device_release
};


int init_module(void)
{
	Major = __register_chrdev(0, 0, 1, DEV_NAME, &fops);

	if (Major < 0) {
		printk(KERN_ALERT "Error in register_chrdev: %d\n", Major);
		return Major;
	}

	printk(KERN_INFO "I was assigned major number %d\n", Major);

	return 0;
}

void cleanup_module(void)
{
	__unregister_chrdev(Major, 0, 1, DEV_NAME);
}


// Methods
static int device_open(struct inode * inode, struct file * file)
{
	if (Dev_Open) {
		return -EBUSY;
	}

	Dev_Open++;
	try_module_get(THIS_MODULE);

	return 0;
}

static int device_release(struct inode * inode, struct file * file)
{
	Dev_Open--;
	module_put(THIS_MODULE);

	return 0;
}

static ssize_t device_read(struct file * file, char * buffer, size_t length, loff_t* offset)
{
	int bytes_to_read;
	int bytes_read;

	if (BUF_LEN > length) {
		bytes_to_read = length;
	} else {
		bytes_to_read = BUF_LEN;
	}

	bytes_read = bytes_to_read - copy_to_user(buffer, msg, bytes_to_read);

	return bytes_read;
}

static ssize_t device_write(struct file * file, const char * buffer, size_t length, loff_t* offset)
{
	int max = BUF_LEN - 7;
	int bytes_to_write;

	if (max > length) {
		bytes_to_write = length;
	} else {
		bytes_to_write = max;
	}

	memset(&msg[7], 0, max);
	copy_from_user(&msg[7], buffer, bytes_to_write);

	return length;
}

