#!/bin/python3

import requests
import sys

exit_code = 0

class bcolors:
    HEADER    = '\033[95m'
    OKBLUE    = '\033[94m'
    OKCYAN    = '\033[96m'
    OKGREEN   = '\033[92m'
    WARNING   = '\033[93m'
    FAIL      = '\033[91m'
    ENDC      = '\033[0m'
    BOLD      = '\033[1m'
    UNDERLINE = '\033[4m'

def print_error(message):
    print(bcolors.FAIL + message + bcolors.ENDC)

def print_success(message):
    print(bcolors.OKGREEN + message + bcolors.ENDC)

def request_get (url, expected_status_code):
    global exit_code
    print("Request get on: " + url)

    request_index = requests.get(url)

    if request_index.status_code != expected_status_code:
        print_error(f"[KO] : http status code : {request_index.status_code} / {expected_status_code}")
        exit_code = 1
    else:
        print_success(f"[OK] : http status code : {request_index.status_code} / {expected_status_code}")

    print()

def main ():
    request_get("http://webserv.com:6060/index.html", 200)
    request_get("http://webserv.com:6060/", 200)
    request_get("http://webserv.com:6060/bad_page", 404)
    request_get("http://webserv.com:6060/uploads", 401)
    request_get("http://webserv.com:6060/favicon.ico", 200)

if __name__ == "__main__":
    main()
    sys.exit(exit_code)
