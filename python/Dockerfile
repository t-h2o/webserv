FROM python:alpine

RUN python -m pip install requests

RUN mkdir -p /script

COPY script.py /script

ENTRYPOINT ["python3", "/script/script.py"]

