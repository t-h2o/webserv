#ifndef TESTS_H
#define TESTS_H

/* int check_argc_number(int); */

int launcher_arguments(void);
int test_check_argc_number_1(void);
int test_check_argc_number_2(void);

/* Config class */

int launcher_config(void);
int test_config_insert(void);
int test_config_get(void);

/* class httpRequest */

int launcher_http_request(void);
int test_http_request(void);

/* Json::read(char const *path); */

int launcher_json(void);
int test_json_normal_file(void);
int test_json_bad_path(void);
int test_json_empty_string(void);
int test_json_missing_brace(void);
int test_json_number(void);
int test_json_string_number(void);

/* class Value */

int launcher_value(void);
int test_value_string(void);
int test_value_number(void);
int test_value_array_number(void);
int test_value_boolean(void);
int test_value_map_value(void);
int test_value_object_array(void);

/* class http response */

int launcher_http_response(void);
int test_http_response(void);

/* class http status code */

int launcher_status_code(void);
int test_status_code(void);

#endif /* TESTS_H */
