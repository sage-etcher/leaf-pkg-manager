# leaf-pkg-manager
verry basic package manager for UNIX like operating systems

## Install
```
$ git clone https://github.com/sage-etcher/leaf-pkg-manager.git
# cp ./leaf-pkg-manager/source/* /usr/bin/
```

## Using the Package Manager

### creating a package

```
(while compiling program from source)
$ ./configure --prefix=/usr
$ make
$ make check
$ mkdir -pv fakeroot
$ make DESTDIR=./fakeroot install
# pkg_create [package-name] ./fakeroot
```

### installing a package

```
# pkg_install [package-name]
```

### uninstallign a pacakge

```
# pkg_remove [package-name]
```

## other info

By default package archives are saved at `/usr/pkg/archive/`, these files contain everything necissary to install the program. The package manager also creates a "trace" file at `/usr/pkg/traces`, these files contain all the necisary information to remove a package.

Folder locations can be configured through the `pkg_init` file.



