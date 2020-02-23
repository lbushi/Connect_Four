# Connect_Four
Implementation of Connect Four with GUI using the OpenGL API.
This repository contains the full implementation of a Connect Four, which is a popular board game, written in C++ together with the OpenGL API which provides a decent Graphical User Interface. 

There are several files which are not directly relevant to the application but which can be used to efficiently add a command line interface to the game. However, as it stands, the driver file only contains code for the GUI but contributions towards the CLI are welcomed. Perhaps you can have both of them as options and exclude one or the other with preprocessor directives. 

The app uses the well known notifier-observer pattern which as usual makes the game open to modification. The OpenGL code however needs some serious refactoring into its own header/source files because it is currently embedded in the driver code. Again, contributions are welcomed from people comfortable with OpenGL.
Documentation for most files will be added eventually.

To build the app, simply copy these files into a Visual Studio Project and run the build command or for Linux Users you could simply download these files, run dos2unix * to convert them to linux format and then write a simple Makefile to automate the build.

Note that for the build to work, you must first download the GLFW, GLEW and GLM libraries and do the linking with files with glfw3.lib and glew32s.lib in addition to including the proper header files.
