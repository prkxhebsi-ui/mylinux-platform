#ifndef MYLINUX_EXIT_MODULE_H
#define MYLINUX_EXIT_MODULE_H

#define EXIT_DEFAULT_ERROR_LIMIT 10

int exit_module_parse_code(const char *text, int *code);
int exit_module_report_error(const char *state_file, unsigned int limit);
int exit_module_read_errors(const char *state_file, unsigned int *count);

#endif
