# ft_ssl_md5
In this project I recoded part of the OpenSSL program, specifically the MD5, SHA224, SHA256, SHA384 and SHA512 hashing algorithms.

# Installation MacOS and Ubuntu
```
git clone https://github.com/ssupremus/ft_ssl_md5.git
cd ft_ssl_md5
make
```
# Usage
```
./ft_ssl [message digest command] [flags] [strings or files]
```
or if you want to run ft_ssl in console mode:
```
./ft_ssl
```
## Available Message Digest commands:
* ```md5```
* ```sha224```
* ```sha256```
* ```sha384```
* ```sha512```
## Flags:
* ```-p``` echo STDIN to STDOUT and append the checksum to STDOUT
* ```-q``` quiet mode
* ```-r``` reverse the format of the output
* ```-s``` print the sum of the given string
