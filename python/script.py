#!/bin/python3

import requests

print("start the python3 script")
request_index = requests.get('http://172.17.0.1:6060/index.html')
print(request_index.text)
print(request_index.status_code)

request_index = requests.get('http://172.17.0.1:6060/asdf')
print(request_index.text)
print(request_index.status_code)
