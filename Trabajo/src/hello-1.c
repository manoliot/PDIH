#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Manuel Ruiz Lopez");
MODULE_DESCRIPTION("Driver example");
MODULE_SUPPORTED_DEVICE("testdevice");

static char *name = "world";

module_param(name, charp, 0000);
MODULE_PARM_DESC(name, "Your name");

static int __init hello_init(void)
{
	printk(KERN_INFO "Hello, %s\n", name);
	return 0;
}

static void __exit hello_exit(void)
{
	printk(KERN_INFO "Goodbye, %s\n", name);
}

module_init(hello_init);
module_exit(hello_exit);

