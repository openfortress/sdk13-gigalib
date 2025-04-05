# VPC - Library linking
This document describes available VPC script instructions that could be used to link against libraries.

## $Lib

Uses following name resolution scheme:

```
  windows:
     if dedicated server:
       path == <name>_srv.lib
     else:
       path == <name>.lib
   linux:
     if dedicated server:
       path == <name>_srv.a
     else:
       path == <name>.a
```

Intended for linking against internally compiled static libraries.

## $LibExternal

Uses following name resolution scheme:

```
   windows:
     path == <name>.lib
   linux:
     path == <name>.a
```

Intended for linking against externally compiled static libraries.

## $ImpLib

Uses following name resolution scheme:

```
   windows:
     if dedicated server:
       path == <name>_srv.lib
     else:
       path == <name>.lib
   linux:
    if dedicated server:
      path == <name>_srv.so
    else:
       path == <name>.so
```

Intended for linking against internally compiled shared libraries.

## $ImpLibExternal

Uses following name resolution scheme:

```
 $ImpLibExternal:
   windows:
     path == <name>.lib
   linux:
     path == <name>.so
```

Intended for linking against externally compiled shared libraries.
