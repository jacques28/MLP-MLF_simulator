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
#######################################################__________________________##################################################



#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/interrupt.h>
#include <linux/init.h>

#define IRQ_NUM 1 // Typically the IRQ number for the keyboard

static struct tasklet_struct my_tasklet;

// Tasklet function
static void my_tasklet_function(unsigned long data) {
    printk(KERN_INFO "Keyboard Tasklet: Deferred work\n");
    // Add your deferred task code here
}

// ISR function
static irqreturn_t irq_handler_isr(int irq, void *dev_id) {
    printk(KERN_INFO "Keyboard ISR: Interrupt Occurred\n");
    tasklet_schedule(&my_tasklet);  // Schedule the tasklet
    return IRQ_HANDLED;
}

// Module initialization
static int __init keyboard_driver_init(void) {
    int result;

    // Initialize the tasklet
    tasklet_init(&my_tasklet, my_tasklet_function, 0);

    // Request IRQ for the keyboard
    result = request_irq(IRQ_NUM, irq_handler_isr, IRQF_SHARED, "keyboard_irq", NULL);
    if (result) {
        printk(KERN_ERR "Failed to request IRQ %d\n", IRQ_NUM);
        return result;
    }

    printk(KERN_INFO "Keyboard driver initialized\n");
    return 0;
}

// Module cleanup
static void __exit keyboard_driver_exit(void) {
    tasklet_kill(&my_tasklet);  // Disable the tasklet
    free_irq(IRQ_NUM, NULL);    // Free the IRQ
    printk(KERN_INFO "Keyboard driver unloaded\n");
}

module_init(keyboard_driver_init);
module_exit(keyboard_driver_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("kokou");
MODULE_DESCRIPTION("Simple Keyboard Device Driver with Tasklet");
