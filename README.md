# Rhino XR-2 GCode

This is the final project for COMSC-11 Advanced C++ Programming class at Yuba Community College.
All code was written from scratch with reference to some material provided by the instructor.
Some parts have been cleaned up and commented to be more presentable.

Some questionable design decisions were required by the course.

The program interprets a limited subset of G-Code to control the ancient Rhino XR-2
educational robot arm to draw on a 2D plane. Sample inputs, as text files, can be found in the
`samples/` folder.

You probably don't have a Rhino XR-2 laying around, so this code won't be much use.
But if you do have one... upload the manual somewhere, please? I can only find the XR-3
manual online.

# Build instructions

Currently, the build script is a single POSIX shell script (`build.sh`) that accepts
`CFLAGS` and `CC` environment variables as parameters. A real Makefile and Visual Studio
solution coming SOON(tm)
