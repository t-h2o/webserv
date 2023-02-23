#ifndef TESTS_H
#define TESTS_H

/* int check_argc_number(int); */

int arguments_launcher(void);
int test_check_argc_number_1(void);
int test_check_argc_number_2(void);

/* Json::read(char const *path); */

int json_launcher(void);
int test_json_normal_file(void);
int test_json_bad_path(void);

#endif /* TESTS_H */
