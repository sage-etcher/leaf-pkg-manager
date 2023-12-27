# Leaf Package Manager (WIP)

A very basic package manager for UNIX-like operating systems.
Designed for use with LFS systems.

## Config File

| priority | file |
|:-------- |:---- |
| 1        | file passed with `-t` or `--use-config` arguement |
| 2        | `$XDG_CONFIG_HOME/pkg/config.toml` |
| 3        | `$HOME/.pkg.toml` |
| 4        | `/etc/pkg/config.toml` |


### Example config file

A general basic config file may look like this

```
[general]

# package database, contains list of installed packages and package information
database_file = "/usr/share/pkg/packages.db"

# directory to store local packages
local_package_path = "/usr/share/pkg/local"

# prefix for installing packages (DESTDIR)
install_prefix = "/"

# temporary location used when installing a package
extract_path = "/tmp/pkg_extract"

# logs errors, installs, creates, aliases, etc. 
log_file = "/var/log/pkg.log"
```

## Console Arguments

| argument | param |
|:-------- |:----- |
| `-S` or `--install` | install package to system |
| `-s` or `--uninstall` | unintall package from system |
| `-C` or `--create` | create a package |
| `-c` or `--delete` | permanently delete a package from the system |
| `-A` or `--alias` | create an alias (symbolic link) for a package |
| `-a` or `--remove-alias` | remove a package alias |
| `-l` or `--list` | list all packages that you have access to |
| `-t` or `--use-config` | specify an alternate config file to use |
| `-v` or `--verbose` | be verbose, log more information to stdout |
| `-b` or `--brief` | dont be verbose, just shut up and do stuff |
| `-h` or `--help` | print help message |
| `-V` or `--version` | print versioning information |

## License

Copyright 2023-2024 Sage I. Hendricks  

Licensed under the Apache License, Version 2.0 (the "License");  
you may not use this file except in compliance with the License.  
You may obtain a copy of the License at  

&nbsp;&nbsp;&nbsp;&nbsp;<http://www.apache.org/licenses/LICENSE-2.0>  

Unless required by applicable law or agreed to in writing, software  
distributed under the License is distributed on an "AS IS" BASIS,  
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  
See the License for the specific language governing permissions and  
limitations under the License.  

