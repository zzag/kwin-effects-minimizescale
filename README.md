# kwin-effects-minimizescale

KWin effect that animates the minimizing of windows with the scale animation.

## Installation

### Build from source

Install all the prerequisites:

* Arch Linux:

```
sudo pacman -S cmake extra-cmake-modules kwin
```

* Ubuntu:

```
sudo apt install cmake extra-cmake-modules kwin-dev libkf5config-dev \
    libkf5configwidgets-dev libkf5coreaddons-dev libkf5windowsystem-dev \
    qtbase5-dev
```

Once everything is installed, actually build the effect:

```
mkdir build
cd build
cmake -DCMAKE_INSTALL_PREFIX=/usr ..
make
sudo make install
```
