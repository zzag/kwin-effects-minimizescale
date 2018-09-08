# kwin-effects-minimizescale

KWin effect that animates the minimizing of windows with the scale animation.

## Installation

### Build from source

Install all the prerequisites:

* Arch Linux:

```sh
sudo pacman -S cmake extra-cmake-modules kwin
```

* Fedora:

```sh
sudo dnf install cmake extra-cmake-modules kf5-kconfig-devel kf5-kconfigwidgets-devel \
    kf5-kcoreaddons-devel kf5-kwindowsystem-devel kwin-devel qt5-qtbase-devel
```

* Ubuntu:

```sh
sudo apt install cmake extra-cmake-modules libkf5config-dev libkf5configwidgets-dev \
    libkf5coreaddons-dev libkf5windowsystem-dev kwin-dev qtbase5-dev
```

Once everything is installed, actually build the effect:

```sh
mkdir build
cd build
cmake -DCMAKE_INSTALL_PREFIX=/usr ..
make
sudo make install
```
