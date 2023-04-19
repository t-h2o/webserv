#!/bin/sh

curl -O https://www.php.net/distributions/php-8.2.5.tar.gz
curl -LO https://github.com/GNOME/libxml2/archive/refs/tags/v2.10.4.tar.gz
curl -LO http://ftp.gnu.org/gnu/autoconf/autoconf-latest.tar.gz
curl -LO https://ftp.gnu.org/gnu/automake/automake-1.16.tar.gz

tar xvzf v2.10.4.tar.gz
tar xv php-8.2.5.tar.gz
tar xvzf autoconf-2.10.tar.gz
tar xvzf automake-1.16.tar.gz
