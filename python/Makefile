build:
	docker build . -t my-python

test:
	docker run --tty \
	--name python-http \
	--network host \
	--add-host webserv.com:127.0.0.1 \
	--rm  my-python \

exec:
	docker run --tty \
	--name python-http \
	--network host \
	--add-host webserv.com:127.0.0.1 \
	--rm  my-python \
	python
