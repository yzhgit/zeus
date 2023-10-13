# tinycv

*tinycv* is a high-performance image processing library supporting x86, aarch64 platforms.

### How To Build

This project is configured by cmake scripts. A simple build script is provided.

#### Linux

```bash
$ cd ${path_to_tinycv}
$ ./build.sh x86_64                         # for linux-x86_64
$ ./build.sh aarch64                        # for linux-aarch64
```

#### Windows

Using vs2017 for example:

```
build.bat -G "Visual Studio 15 2017 Win64" -DTINYCV_USE_X86_64=ON
```

### License

This project is distributed under the [Apache License, Version 2.0](LICENSE).
