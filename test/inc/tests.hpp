#ifndef TESTS_H
#define TESTS_H

/* int check_argc_number(int); */

int launch_arguments(void);
int test_check_argc_number_1(void);
int test_check_argc_number_2(void);

/* arguments::check_argv_access */

int launch_arguments_argv(void);
int test_check_argv_access_valid(void);
int test_check_argv_access_unvalid(void);

/* php:: */

<<<<<<< HEAD
int launch_php(void);
int test_php_output(void);
int test_cgi_with_php(void);
int test_cgi_with_php_query(void);
int test_cgi_with_php_query2(void);
int test_cgi_with_files(void);
=======
/* http::Redirection */

int launch_http_redirection(void);
int test_http_redirection(void);

/* http::Request */
>>>>>>> http::Redirection

/* http::Method */

int launch_http_method(void);
int test_http_method(void);

/* http::Response */

int launch_http_response(void);
int test_http_response(void);

/* http::StatusCodes */

int launch_status_code(void);
int test_status_code(void);

/* json::check_config(t_object *config) */

int launch_check_json_config(void);
int test_json_check_config_normal(void);
int test_json_check_config_bad_port(void);

/* Json::read(char const *path); */

int launch_json(void);
int test_json_normal_file(void);
int test_json_bad_path(void);
int test_json_empty_string(void);
int test_json_missing_brace(void);
int test_json_number(void);
int test_json_string_number(void);
int test_json_object00(void);
int test_json_object01(void);

/* json::Value */

int launch_value(void);
int test_value_string(void);
int test_value_number(void);
int test_value_array_number(void);
int test_value_boolean(void);
int test_value_map_value(void);
int test_value_object_array(void);
int test_value_no_existing_key(void);

/* json::File */

int launch_file(void);
int test_file(void);
int test_file_all_file(void);
int test_file_not_valid_file(void);
int test_file_get_string(void);
int test_file_get_number(void);
int test_file_get_string_empty_string(void);

#endif /* TESTS_H */
