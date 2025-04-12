# how do you get these .lib and .a files?

### windows:

vcpkg.exe install curl[core,http2,ssh,sspi,brotli,idn,winidn,winldap,websockets,non-http]:x86-windows-static

### linux:

sudo ./vcpkg install  curl[core,http2,ngtcp,ssh,brotli,websockets,non-http,ssl]:x86-linux

# Dependency versions

| Library       | Version  | Notes                                                              |
| ------------- | -------- | ------------------------------------------------------------------ |
| libcurl       | 8.4.0    | Built as shared with zlib v1.3                                     |
| SDL 2         | 2.28.5.0 | Built as shared with full feature set                              |
| fmt           | 10.1.1   | Built as static, PIC                                               |
| sentry-native | 0.7.11   | Built as static, with crashpad (Windows) and breakpad (Linux), PIC |
| PolyHook_V2   | 19e7cec  | Built as static, PIC                                               |

Compiler used is gcc-10
