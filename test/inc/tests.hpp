#ifndef TESTS_H
#define TESTS_H

/* int check_argc_number(int); */

int arguments_launcher(void);
int test_check_argc_number_1(void);
int test_check_argc_number_2(void);

/* class httpRequest */

int http_request_launcher(void);
int test_http_request(void);

/* Value class */

int value_launcher(void);
int test_value_string(void);
int test_value_number(void);
int test_value_array_number(void);
int test_value_boolean(void);
int test_value_map_value(void);
int test_value_object_array(void);
/* class http response */

int http_response_launcher(void);
int test_http_response(void);
/* class http status code */

int status_code_launcher(void);
int test_status_code(void);

#endif /* TESTS_H */
