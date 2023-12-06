#include <linux/module.h>
#include <linux/irq.h>
#include <linux/interrupt.h>
#include <linux/init.h>
#include <linux/kernel.h>

#define IRQ_NUM 1

static struct tasklet_struct keyboard_tasklet;

static irqreturn_t irq_handler_isr(int irq, void *dev_id) {
    printk(KERN_INFO "Kokou: Caught the IRQ. Urgent work Muhaha\n");
    tasklet_schedule(&keyboard_tasklet);
    return IRQ_HANDLED;
}

static void tasklet_fn(unsigned long data) {
    printk(KERN_INFO "Kokou: Doing the hackey pending work Muhaha\n");
}

static int __init keyboard_driver_init(void) {
    int result;

    result = request_irq(IRQ_NUM, irq_handler_isr, IRQF_SHARED, "keyboard_irq", NULL);
    if (result) {
        printk(KERN_ERR "Failed to request IRQ %d, error: %d\n", IRQ_NUM, result);
        return result;
    }

    tasklet_init(&keyboard_tasklet, tasklet_fn, 0);
    printk(KERN_INFO "Keyboard driver initialized\n");
    return 0;
}

static void __exit keyboard_driver_exit(void) {
    tasklet_kill(&keyboard_tasklet);
    free_irq(IRQ_NUM, NULL);
    printk(KERN_INFO "Keyboard driver unloaded\n");
}

module_init(keyboard_driver_init);
module_exit(keyboard_driver_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Your Name");
MODULE_DESCRIPTION("Simple keyboard driver using Hard IRQ ISR and Tasklet");
