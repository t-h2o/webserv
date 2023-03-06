all:
	docker build -t cpp-image .

run: all
	docker run --rm -v $(shell pwd):/paul cpp-image /bin/ls
