#ifndef TESTS_H
#define TESTS_H

/* int check_argc_number(int); */

int arguments_launcher(void);
int test_check_argc_number_1(void);
int test_check_argc_number_2(void);

/* Config class */

int config_launcher(void);
int test_config_insert(void);
int test_config_get(void);

/* Json::read(char const *path); */

int json_launcher(void);
int test_json_normal_file(void);
int test_json_bad_path(void);
int test_json_empty_string(void);
int test_json_missing_brace(void);
int test_json_number(void);
int test_json_string_number(void);
int test_json_array_number(void);

/* Value class */

int value_launcher(void);
int test_value_string(void);
int test_value_number(void);

#endif /* TESTS_H */
