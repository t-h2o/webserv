#!/bin/sh

PATH_PHP="${HOME}"/goinfre/php

# $1 : message
# $2 : color
print_big_message () {
	if [ -z "${2}" ]; then
		printf ""
	elif [ "${2}" = "red" ]; then
		printf "%b" "\033[31;1m"
	elif [ "${2}" = "green" ]; then
		printf "%b" "\033[32;1m"
	elif [ "${2}" = "yellow" ]; then
		printf "%b" "\033[33;1m"
	fi

	printf "################################################################################\n"
	printf "# %s\n" "${1}"
	printf "################################################################################\n\n"
	printf "%b" "\033[0m"
}

# $1 : link
# $2 : extension
download_handle () {
	FILE_DOWNLOADED=$(basename "$1")
	FOLDER_CREATED=$(basename -s "$2" "${FILE_DOWNLOADED}")
	if [ -d "${FOLDER_CREATED}" ] ; then
		print_big_message "folder \"${FOLDER_CREATED}\" already exist" "yellow"
		return 0
	fi

	curl -LO "$1"
	print_big_message "curl -LO ${1}"
	printf "Download %s\n" "${FILE_DOWNLOADED}"
	if ! tar xvzf "${FILE_DOWNLOADED}" 2>/dev/null ; then
		print_big_message "do not find \"${FILE_DOWNLOADED}\"\n" "red"
		exit 1
		return 0
	fi
	rm "${FILE_DOWNLOADED}"
}

download_sources () {

	download_handle "https://www.php.net/distributions/php-8.2.5.tar.gz" ".tar.gz"
	download_handle "https://download.gnome.org/sources/libxml2/2.9/libxml2-2.9.9.tar.xz" ".tar.xz"
	download_handle	"https://www.sqlite.org/src/tarball/sqlite.tar.gz" ".tar.gz"

}

compilate_libxml2 () {
	cd libxml2-2.9.9 || exit
	./configure
	make

	export PKG_CONFIG_PATH="${PWD}":"${PKG_CONFIG_PATH}"
	print_big_message "PKG_CONFIG_PATH = ${PKG_CONFIG_PATH}"
	cd .. || exit
}

compilate_php () {
	cd php-8.2.5 || exit
	./configure --without-iconv
}

compilate_sqlite3 () {
	cd sqlite || exit
	./configure
	make

	export PKG_CONFIG_PATH="${PWD}":"${PKG_CONFIG_PATH}"
	print_big_message "PKG_CONFIG_PATH = ${PKG_CONFIG_PATH}"
	cd .. || exit
}

main () {
	mkdir -p "${PATH_PHP}"
	cd "${PATH_PHP}" || exit

	print_big_message "Download source files" "green"
	download_sources

	print_big_message "Compilate libxml2" "green"
	compilate_libxml2

	print_big_message "Compilate sqlite3" "green"
	compilate_sqlite3

	print_big_message "Compilate php8" "green"
	compilate_php
}

print_big_message "launch the main()" "green"
main
