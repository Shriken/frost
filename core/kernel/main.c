#include "main.h"

void int_handler_5();

int main() {
	puts("Hello, world of kernels\n\n");

	int hal_err = hal_initialize();
	if (hal_err) printf("hal_err: %x\n", hal_err);

	// Install exception handlers
	install_handlers();

	// Enable interrupts
	enable();

	setvect(5, int_handler_5);
	puts("generating interrupt 5\n");
	geninterrupt(5);
	puts("done interrupting\n");

	for (;;) {
		move_cursor(0, ROWS - 1);
		printf("Current tick count: %d\n", get_tick_count());
	}

	hal_shutdown();
	return 0;
}

void int_handler_5() {
	asm(
		"pushad\n"
		::: "memory", "esp"
	);

	puts("caught interrupt 5!\n");

	asm(
		"popad\n"
		"leave\n"
		"iretd\n"
		::: "memory", "esp"
	);
}
