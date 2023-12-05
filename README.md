# Leaf Package Manager

A very basic package manager for UNIX-like operating systems.
Designed for use with LFS systems.

## Install
```
$ git clone https://github.com/sage-etcher/leaf-pkg-manager.git
# cp ./leaf-pkg-manager/source/* /usr/bin/
```

## Using the Package Manager

### Creating a package

Building the program into a package is generally to be done as one of the ladder steps when installing a program from source.
The program must first be installed into a fake-root directoy, if available, DESTDIR will suffice.
Please note that `pkg_create` does NOT install the package, that is a separate command `pkg_install`.

```
pkg_create [package-name] [fakeroot-directory]
```

An example program (zlib) install with the package manager may look something like this. A mostly standard install w/ the main changes being, installing the program to a fake-root directory, then using `pkg_create` and `pkg_install`.

```
$ ./configure --prefix=/usr
$ make
$ make check
$ mkdir -pv fakeroot
$ make DESTDIR=./fakeroot install
# pkg_create zlib-1.2.13 ./fakeroot
# pkg_install zlib-1.2.13
```

### Installing a package

```
# pkg_install [package-name]
```

### Uninstalling a pacakge

```
# pkg_remove [package-name]
```

## Other info

By default package archives are saved at `/usr/pkg/archive/`, these files contain everything necessary to install the program. The package manager also creates a "trace" file at `/usr/pkg/traces/`, these files contain all the necessary information to remove a package.

Folder locations can be configured through the `pkg_init` file.
