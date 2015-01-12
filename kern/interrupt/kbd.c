#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/interrupt.h>
#include <asm/io.h>

/* This function services keyboard interrupts */
irq_handler_t irq_handler (int irq, void *dev_id, struct pt_regs *regs) 
{
	static unsigned char scancode;
	static unsigned char status;
	
	// keyboard controller  
	status = inb(0x64); // status register
  	scancode = inb (0x60); //data port
	
	if ((scancode & 0x80)) {
		pr_info("KEY RELEASED\n");
	} else {
		pr_info("KEY PRESSED\n");
	}
	
  	if ((scancode == 0x01) || (scancode == 0x81)) {
      		pr_info("You pressed Esc !\n");
  	}

	if(scancode == 0x02)
		pr_info("1 pressed!\n");
  	return (irq_handler_t) IRQ_HANDLED;
}

/* Initialize the module and Register the IRQ handler */
static int __init keybrd_int_register(void)
{
  	int result;
  	/* Request IRQ 1, the keyboard IRQ */    
  	result = request_irq (1, (irq_handler_t) irq_handler, IRQF_SHARED, 
			"keyboard_stats_irq", (void *)(irq_handler));

  	if (result)
    		pr_info("can't get shared interrupt for keyboard\n");
	pr_info("Registed our keyboard handler\n");
  	return result;
}

/* Remove the interrupt handler */
static void __exit keybrd_int_unregister(void) {
  	free_irq(1, (void *)(irq_handler)); /* i can't pass NULL, this is a shared interrupt handler! */
}

MODULE_LICENSE ("GPL");
module_init(keybrd_int_register);
module_exit(keybrd_int_unregister);

