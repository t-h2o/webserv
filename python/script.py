#!/bin/python3

import requests

def request_get (url, expected_status_code):
    print("Request get on: " + url)
    print("method GET on " + url)
    request_index = requests.get(url)
    if request_index.status_code != expected_status_code:
        print ("error")
    else:
        print ("good")

def main ():
    request_get("http://localhost:6060/index.html", 200)
    request_get("http://webserv.com:6060/index.html", 200)

if __name__ == "__main__":
    main()
