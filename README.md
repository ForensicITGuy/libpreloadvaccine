# libpreloadvaccine

## Description
`libpreloadvaccine` is a project to attempt whitelisting of shared objects loaded via LD_PRELOAD. 

This libary implements portions of the [rtld-audit](http://man7.org/linux/man-pages/man7/rtld-audit.7.html) API to intercept searches for shared objects at runtime. If the searched-for library is part of a preload list and not part of the whitelist, it gets ignored by the dynamic linker at runtime.

To use the library, simply define the LD_AUDIT environment variable to the path of `libpreloadvaccine.so` and enjoy.

To whitelist preloads, add them to `/etc/libpreloadvaccine.allow`.

## Documentation
- [Building](docs/build_instructions.md)
- [Installing](docs/library_installation.md)

## Disclaimer
Like a real vaccine, this is not 100% effective against all types of preloads attacks. You may still define preloads via command line arguments to the dymanic linker for effect. And just like a vaccine, this is better than running around without protection!