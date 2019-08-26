#ifndef LIBPRELOADVACCINE_H
#define LIBPRELOADVACCINE_H

#define _GNU_SOURCE
#define UNUSED(x) (void)(x)
#include <link.h>
#include <stdbool.h>

unsigned int la_version(unsigned int version);

char *la_objsearch(const char *name, uintptr_t *cookie, unsigned int flag);

bool is_preload(const char *object);

#endif