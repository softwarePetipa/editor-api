# Petipa API draft

The main design goal of the API is to keep the Native part as thin as possible.


## Core--UI separation

The software has two main parts:


### Core

The Core is written in C++, and uses the same code for all the supported platforms.
It handles all the business logic, and controls the Editor window,
doing all the rendering and controlling all the user interactions of the choreography editor.

The Core API is divided in two files:
dashboard.h, with methods to be called from the app dashboard (project list), and
editor.h, with methods to be called from the native dialogs that open while the Editor is running.

It uses the following libraries:

* [SDL](https://libsdl.org) to access device's display and input
* [libnyquist](https://github.com/ddiakopoulos/libnyquist) to decode audio files
* [PortAudio](http://portaudio.com) to play audio
* [SOIL2](https://github.com/SpartanJ/soil2) to load image files as OpenGL textures
* [JSON for Modern C++](https://github.com/nlohmann/json) to handle JSON files for serialization


### Native UI

The Native UI part is to be written in the "natural" language of each platform (eg. Swift for iOS, Java or Kotlin for Android).
It will initialize the application, call the Editor when the user opens a project, and provide methods for the Editor to open some dialogs:

* Visualization options
* Music setup
* Stage setup
* Charactgers and Tags setup
* Notifications
* Project file sharing
* Alert, Choice and Text Input dialogs
* About dialog


## How it should work

The Native UI part is responsible for starting the application, and the introductory screens:
the splash, the login dialog, and the dashboard.

From the dashboard the user can open an existing project or create a new one,
and when doing so, the Native UI part calls the Editor, which is the main activity.
The core will control the Editor window, and eventually will call the Native UI methods
described above.
