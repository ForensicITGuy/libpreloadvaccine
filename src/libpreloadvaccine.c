#include "libpreloadvaccine.h"
#include <stdio.h>

/*
    From the rtld-audit manpage:
    This is the only function that must be defined by an auditing
    library: it performs the initial handshake between the dynamic linker
    and the auditing library.  When invoking this function, the dynamic
    linker passes, in version, the highest version of the auditing
    interface that the linker supports.  If necessary, the auditing
    library can check that this version is sufficient for its
    requirements.

    As its function result, this function should return the version of
    the auditing interface that this auditing library expects to use
    (returning version is acceptable).  If the returned value is 0, or a
    version that is greater than that supported by the dynamic linker,
    then the audit library is ignored.
*/
unsigned int la_version(unsigned int version)
{
    // Version == 0 means the library will be ignored by the linker.
    if(version == 0)
    {
        return version;
    }
    else
    {
        return LAV_CURRENT;
    }    
}

/*
    From the rtld-audit manpage:
    The dynamic linker invokes this function to inform the auditing
    library that it is about to search for a shared object.  The name
    argument is the filename or pathname that is to be searched for.
    cookie identifies the shared object that initiated the search.  flag
    is set to one of the following values:

    LA_SER_ORIG      This is the original name that is being searched
                    for.  Typically, this name comes from an ELF
                    DT_NEEDED entry, or is the filename argument given
                    to dlopen(3).

    LA_SER_LIBPATH   name was created using a directory specified in
                    LD_LIBRARY_PATH.

    LA_SER_RUNPATH   name was created using a directory specified in an
                    ELF DT_RPATH or DT_RUNPATH list.

    LA_SER_CONFIG    name was found via the ldconfig(8) cache
                    (/etc/ld.so.cache).

    LA_SER_DEFAULT   name was found via a search of one of the default
                    directories.

    LA_SER_SECURE    name is specific to a secure object (unused on
                    Linux).

    As its function result, la_objsearch() returns the pathname that the
    dynamic linker should use for further processing.  If NULL is
    returned, then this pathname is ignored for further processing.  If
    this audit library simply intends to monitor search paths, then name
    should be returned.
*/
char *la_objsearch(const char *name, uintptr_t *cookie, unsigned int flag)
{
    UNUSED(cookie);
    UNUSED(flag);
    printf("%s\n",name);

    if (is_preload(name))
    {
        return NULL;
    }
    else
    {
        return (char *)name;
    }
}

bool is_preload(const char *object)
{
    bool in_ld_preload = ld_preload_contains_object(object);
    bool in_ld_so_preload = ld_so_preload_contains_object(object);

    return (in_ld_preload || in_ld_so_preload);
}

bool ld_preload_contains_object (const char *object)
{
    return false;
}

bool ld_so_preload_contains_object(const char *object)
{
    return false;
}