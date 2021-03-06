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
1. copy over an existing `.config` or create a new one using `make O=/build/directory/you/created ARCH=?? defconfig` (or `menuconfig` or whatever you prefer)
1. The kernel's prepare step will generate the input files kconfig2qmk needs. (make `make O=/build/directory/you/created ARCH=?? prepare`)
1. `genlinuxpro build/directory/you/created` (the .pro file will be one dir up, i.e. `build/directory/you' in this example)

This .pro can be opened by qt-creator for browsing and editing.

You can hack qt-creator's build steps to do whatever you want (`bitbake virtual/linux -c kernel_modules -c deploy` or `make` in the build dir). You can even use the "deploy" steps to do whatever you need. This configuration all goes in the *.pro.user file next to the .pro.

The generate .pro file contains DEFINES which allow qt-creator's c++ parser to tolerate certain keywords (like 'new') without breaking the nice indexing.


