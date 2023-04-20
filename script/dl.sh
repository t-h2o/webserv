#!/bin/sh

curl -O https://www.php.net/distributions/php-8.2.5.tar.gz
curl -LO https://github.com/GNOME/libxml2/archive/refs/tags/v2.10.4.tar.gz
curl -LO http://ftp.gnu.org/gnu/autoconf/autoconf-latest.tar.gz
curl -LO https://ftp.gnu.org/gnu/automake/automake-1.16.tar.gz

tar xvzf v2.10.4.tar.gz
tar xv php-8.2.5.tar.gz
tar xvzf autoconf-2.10.tar.gz
tar xvzf automake-1.16.tar.gz


######## libxml2

curl -LO https://download.gnome.org/sources/libxml2/2.9/libxml2-2.9.9.tar.xz
tar xvzf libxml2-2.9.9.tar.xz
cd libxml2-2.9.9
./configure
make

# path to find the dynamic library
export PKG_CONFIG_PATH=$PWD:$PKG_CONFIG_PATH

#######

curl -LO https://www.sqlite.org/2023/sqlite-tools-osx-x86-3410200.zip
unzip sqlite-tools-osx-x86-3410200.zip

export PATH=$PWD/sqlite-tools-osx-x86-3410200/:$PATH
