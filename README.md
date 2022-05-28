# ConfMsg

Simple test program which prints a message on the terminal given by configuration files.

## Author
- Markus Pawellek "lyrahgames" (lyrahgames@mailbox.org)

## Background

If a program needs to access user and system directories to retrieve resources, assets, configurations or to store other pesistent data, it must know about the absolute paths of those files.
These absolute paths should not be hardcoded inside the source code but should be given by the build system when compiling or installing, because typically a build system configuration could be highly customized.

    install_root = /usr/local
    system_data_dir = /usr/local/share/<project>
    system_config_dir = /usr/local/etc/<project>

This makes sense if the program is already compiled and installed.
But for developing purposes, installing a program before testing it, is not a good idea.
The question which directories to choose when the program is not installed is not easy to answer and has to be decided by the code and the build system.

One way would be to provide program flags which allow overriding those directories.
Inside the build system all tests could use those flags to tell the running program that it is not installed and that it should at another location for its resources and configs.
Furthermore, this functionality seems to be quite useful regardless of build system tests.

## Build, Test and Install
### Linux

## References
- [Filesystem Hierarchy Standard for UNIX-like Operating Systems](https://refspecs.linuxfoundation.org/FHS_3.0/fhs/index.html)
- [build2 Build System Manual](https://build2.org/build2/doc/build2-build-system-manual.xhtml)
- [XDG Base Directory Specification](https://specifications.freedesktop.org/basedir-spec/basedir-spec-latest.html)