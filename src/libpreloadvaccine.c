#include "libpreloadvaccine.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>

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

    if(is_preload(name) && !allowed_preload(name))
    {
        printf("Found preload not allowed");
        return NULL;
    }
    else
    {
        printf("Found object allowed");
        return (char *)name;
    }
}

bool is_preload(const char *object)
{
    printf("Testing preloads");
    bool in_ld_preload = env_variable_contains_object(object, "LD_PRELOAD");
    bool in_ld_so_preload = file_contains_object(object, "/etc/ld.so.preload");

    return (in_ld_preload || in_ld_so_preload);
}

bool allowed_preload(const char *object)
{
    printf("Testing allow file");
    return file_contains_object(object, "/etc/libpreloadvaccine.allow");
}

bool env_variable_contains_object (const char *object, const char *env_variable)
{
    printf("Testing env var");
    bool contains_object;
    const char *ld_preload = getenv(env_variable);

    if (ld_preload != NULL)
    {
        if (strstr(ld_preload,object) != NULL)
        {
            contains_object = true;
        }
        else
        {
            contains_object = false;
        }
    }

    return contains_object;
}

bool file_contains_object(const char *object, const char *specified_file)
{
    printf("Testing file");
    bool contains_object = false;

    int fd;
    struct stat file_info;
    size_t size;

    char *mapped_file;

    if ((fd = open(specified_file, O_RDONLY)) >= 0)
    {    
        fstat(fd, &file_info);
        size = file_info.st_size;

        mapped_file = mmap(NULL, size, PROT_READ, MAP_PRIVATE, fd, 0);

        if (strstr(mapped_file,object) != NULL)
        {
            contains_object = true;
        }
        else
        {
            contains_object = false;
        }
        
        munmap(mapped_file, size);

        if(fd)
        {
            close(fd);
        }
    }
    else
    {
        contains_object = false;
    }
    

    // Return boolean
    return contains_object;
}