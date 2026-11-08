/*
 * These variables demonstrate ELF sections.
 * The compiler/linker place them into ELF sections.
 */

__attribute__((used, section(".rodata")))
const char apexd_readonly_data[] = "APEX_READ_ONLY_DATA";

__attribute__((used, section(".data")))
volatile int apexd_initialized_data = 30;

__attribute__((used, section(".bss")))
volatile int apexd_uninitialized_data;

int apexd_section_test(void) {
    apexd_uninitialized_data = apexd_initialized_data;
    return apexd_uninitialized_data;
}
