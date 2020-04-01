# An Emacs dynamic module for `strptime(3)`

Emacs provides `format-time-string` which is basically a wrapper of
`strftime(3)`. `strptime(3)` is the converse of `strftime(3)`, however Emacs
doesn't have a wrapper of it, hence this module.

``` emacs-lisp
(strptime "2020-04-01" "%Y-%m-%d")
;; => (0 0 0 1 4 2020 3 nil 0)

(strptime "2020-04-01T07:39:26+0800" "%FT%T%z")
;; => (26 39 7 1 4 2020 3 nil 28800)

(strptime "2020-04-XX" "%Y-%m-%d")
;; error→ STRING and FORMAT not match: "2020-04-XX", "%Y-%m-%d"
```

## Setup

Issue the `make` command to build the dynamic module, e.g.,

    ~/s/strptime.el $ make
    cc -shared -fpic strptime-core.c -o strptime-core.so

Add `load-path` and load the library, e.g.,

``` emacs-lisp
(add-to-list 'load-path "~/src/strptime.el")
(require 'strptime)
```

## API

### `(strptime STRING FORMAT)`

Parse the time in STRING according to FORMAT.
Return (SEC MINUTE HOUR DAY MONTH YEAR DOW DST UTCOFF).

## Requires

- Emacs 26.1
