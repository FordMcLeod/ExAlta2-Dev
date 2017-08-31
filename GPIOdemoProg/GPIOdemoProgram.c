#define LED1 IOPORT_CREATE_PIN(PORTA,5)

ioport_init();
ioport_set_pin_dir(LED1, IOPORT_DIR_OUTPUT);
ioport_set_pin_level(LED1, 1);
