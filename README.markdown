gdn is a command line program that encodes mathematical notation into a Gödel numbers and decodes Gödel numbers into mathematical notation. 

## Building
Prerequisites:

* GMP

```
$ make
$ sudo make install
```

## Usage

```
$ gdn
usage: gdn
       -d, --decode [number]
       -e, --encode [expression]
```

Depending on your shell, you may have to wrap certain expressions in quotation marks. For example, on a shell with file globbing, `gdn -e 2 * 2` will error out because the shell will replace `*` with the files in the current directory. 