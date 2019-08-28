# Installing libpreloadvaccine.so

## First step, build a release

First, visit the [build page](build_instructions.md) and build a release of `libpreloadvaccine`.

## Copy libpreloadvaccine.so to a library folder

```
cp libpreloadvaccine.so /usr/lib/libpreloadvaccine.so
```

## Set LD_AUDIT variable Globally

Add this line to the file `/etc/profile`:

```
export LD_AUDIT=/usr/lib/libpreloadvaccine.so
```

## Configure whitelisting

If you want to whitelist any preloads, add them to this configuration file: `/etc/libpreloadvaccine.allow`.

This list should be space delimited.

If you don't wish to whitelist preloads, you can simpy chose not to create this file or leave it blank.