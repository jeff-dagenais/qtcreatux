This little program (which normally should have been a python script...) simply reads the autogenerated files created by the kernel's `make prepare` and dumps a qmake syntax'd file (autoconf.qmk) containing the proper defines. This file can then be included into a pro file which indexes the kernel source. The result is a properly highlighted browsing experience.

# install

```shell
cd kconfig2qmk
qmake
make
sudo make install
cd ..
sudo cp genlinuxpro /usr/local/bin
```

By default, will install the exe to /usr/local/bin)

# Usage

1. create a directory where you'll build the kernel
1. copy over an existing `.config` or
..1. create a new one using `make O=/build/directory/you/created ARCH=?? defconfig` (or `menuconfig` or whatever you prefer)
1. make `make O=/build/directory/you/created ARCH=?? prepare`
1. `cd build/directory/you/created`
1. `kconfig2qmk`
1. `genlinuxpro`

`genlinux` will generate a file named after the top-level directory it's in. This .pro can be opened by qt-creator for browsing and editing.

I personnaly replace the qmake-make build steps with kernel specific build and deploy steps. Making the integration more seamless.

# C-only support in qt-creator

I have a working ugly patch on top of qt-creator 3.2 which removes C++ keywords support from the syntax parser. This is necessary since the linux source code uses C++ keywords such as "new" and "class" as regular variables.

If not disabled, these will partially break the browsing and auto-completion behaviour.

