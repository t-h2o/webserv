#!/bin/python3

import requests

def request_get (url, expected_status_code):
    print("Request get on: " + url)

    request_index = requests.get(url)

    if request_index.status_code != expected_status_code:
        print ("error")
    else:
        print ("good")
    print()

def main ():
    request_get("http://webserv.com:6060/index.html", 200)
    request_get("http://webserv.com:6060/index.html", 200)
    request_get("http://webserv.com:6060/bad_page", 404)

if __name__ == "__main__":
    main()
