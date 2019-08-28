# Building libpreloadvaccine

Building libpreloadvaccine is relatively easy, follow the instructions to build for testing or release.

## Building for testing

To build and execute unit tests, run this command from the root of the `libpreloadvaccine` folder:

```
make test
```

This will run all the Unity tests and produce a `test.out` binary.

## Building for release

To build for release as a shared object library, run this command from the root of the `libpreloadvaccine` folder:

```
make build
```

This will create `libpreloadvaccine.so`, a library that is ready for use with `LD_AUDIT`.