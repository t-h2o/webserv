#!/bin/sh

PATH_PHP="$HOME"/goinfre/php

# $1 : link
# $2 : extension
download_handle () {
	FILE_DOWNLOADED=$(basename "$1")
	FOLDER_CREATED=$(basename -s "$2" "$FILE_DOWNLOADED")
	if [ -d "$FOLDER_CREATED" ] ; then
		printf "folder \"%s\" already exist\n" "$FOLDER_CREATED"
		return 0
	fi

	curl -LO "$1"
	printf "Download %s\n" "$FILE_DOWNLOADED"
	if ! tar xvzf "${FILE_DOWNLOADED}" 2>/dev/null ; then
		printf "do not find \"%s\"\n" "$FILE_DOWNLOADED"
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

	export PKG_CONFIG_PATH="$PWD":"$PKG_CONFIG_PATH"
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

	export PKG_CONFIG_PATH="$PWD":"$PKG_CONFIG_PATH"
	cd .. || exit
}

main () {
	mkdir -p "$PATH_PHP"
	cd "$PATH_PHP" || exit

	download_sources
	compilate_libxml2
	compilate_sqlite3
	compilate_php
}

main
