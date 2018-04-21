# Jetcash desktop wallet

## Requirements

1. Qt5 libraries</br>
To install all required packages on Ubuntu use the following command:
```
sudo apt install qt5-qmake qtbase5-dev qtbase5-dev-tools
```

## How to build binaries from source code

## Building on Windows

You need Microsoft Visual Studio Community 2017. [Download](https://microsoft.com) and install it selecting `C++`, `git`, `cmake integration` packages.
Run `Visual Studio x64 command prompt` or `Visual Studio x86 command prompt` (if you need 32-bit jetcash binaries)  from start menu.

Create directory `jetcash` somewhere and go there:
```
$C:> md <path-to-jetcash-folder>
$C:> cd <path-to-jetcash-folder>
```
Find and add cmake to system PATH. From the Start Menu, right-click Computer on the right side. In the appearing window, select Advanced system settings in the left area - the System properties will appear. Select Environment Variables at the bottom. Change the Path variable there and it will be always active. For example:
```
C:\PROGRAM FILES (X86)\MICROSOFT VISUAL STUDIO\2017\COMMUNITY\COMMON7\IDE\COMMONEXTENSIONS\MICROSOFT\CMAKE\CMake\bin
```
Find and add qmake to system PATH. For example, 64-bit version:
```
C:\Qt\Qt5.10.0\5.10.0\msvc2017_64\bin
```
or 32-bit version:
```
C:\Qt\Qt5.10.0\5.10.0\msvc2017_32\bin
```

Get [Boost](https://boost.org) and unpack it into a folder inside `jetcash` and rename it from `boost_1_66_0` or similar to just `boost`.

Build boost (build 32-bit boost version only if you need 32-bit jetcash binaries).
```
$> cd boost
$C:\jetcash\boost> bootstrap.bat
$C:\jetcash\boost> b2.exe address-model=64 link=static -j 8 --build-dir=build64 --stagedir=stage
$C:\jetcash\boost> b2.exe address-model=32 link=static -j 8 --build-dir=build32 --stagedir=stage32
cd ..
```
You need to build openssl, first install ActivePerl (select "add to PATH" option, then restart console):
```
$C:\jetcash> git clone https://github.com/openssl/openssl.git
$C:\jetcash> cd openssl
$C:\jetcash\openssl> perl Configure VC-WIN64A no-shared no-asm
$C:\jetcash\openssl> nmake
$C:\jetcash\openssl> cd ..
```
If you want to build 32-bit binaries, you will also need 32-bit build of openssl in separate folder (configuring openssl changes header files, so there is no way to have both 32-bit and 64-bit versions in the same folder):
```
$C:\jetcash> git clone https://github.com/openssl/openssl.git openssl32
$C:\jetcash> cd openssl32
$C:\jetcash\openssl> perl Configure VC-WIN32 no-shared no-asm
$C:\jetcash\openssl> nmake
$C:\jetcash\openssl> cd ..
```

Git-clone (or git-pull) Jetcash source code in that folder:
```
C:\jetcash> git clone https://github.com/jetcash/jetcash.git
```
Put LMDB source code in `jetcash` folder (source files are referenced via relative paths, so you do not need to separately build it):
```
$jetcash> git clone https://github.com/jetcash/lmdb.git
```
Create build directory inside jetcash, go there and run CMake:
```
$C:\jetcash> md jetcash\build64
$C:\jetcash> cd jetcash\build64
$C:\jetcash\jetcash\build64> cmake -G "Visual Studio 15 2017 Win64"  --DCMAKE_BUILD_TYPE="Release" ..
$C:\jetcash\jetcash\build64> cmake --build . --config Release
$C:\jetcash\jetcash\build64> cd ..
$C:\jetcash\jetcash> for %I in (bin\Release\jetcashd.exe bin\Release\walletd.exe) do copy /Y %I bin
$C:\jetcash\jetcash> for %I in (libs\Release\*.lib) do copy /Y %I libs
$C:\jetcash\jetcash> cd ..
$C:\jetcash> git clone https://github.com/jetcash/desktop-wallet.git
$C:\jetcash> md desktop-wallet\build64
$C:\jetcash> cd desktop-wallet\build64
$C:\jetcash\desktop-wallet\build64> cmake -G "Visual Studio 15 2017 Win64"  --DCMAKE_BUILD_TYPE="Release" ..
$C:\jetcash\desktop-wallet\build64> qmake ..\src\jetwallet.pro
$C:\jetcash\desktop-wallet\build64> nmake -f Makefile
$C:\jetcash\desktop-wallet\build64> windeployqt release\jetwallet.exe
```
Create installer
```
$C:\jetcash\desktop-wallet\build64> cd "..\Windows Installer"
$C:\jetcash\desktop-wallet\Windows Installer> devenv Installer.vdproj /build Release /project "Jetcash"
```

## Building on Mac OSX

### Building with standard options (10.11 El Capitan or newer)

You need command-line tools. Either get XCode from an App Store or run 'xcode-select --install' in terminal and follow instructions. First of all, you need [Homebrew](https://brew.sh).

Then open terminal and install CMake and Boost:

* `brew install cmake`
* `brew install boost`
* `brew install qt5` 

Create directory `jetcash` somewhere and go there:
```
$~/Downloads> mkdir <path-to-jetcash-folder>
$~/Downloads> cd <path-to-jetcash-folder>
```

Git-clone (or git-pull) Jetcash source code in that folder:
```
$jetcash> git clone https://github.com/jetcash/jetcash.git
```
Put LMDB source code in `jetcash` folder (source files are referenced via relative paths, so you do not need to separately build it):
```
$jetcash> git clone https://github.com/jetcash/lmdb.git
```

Create build directory inside jetcash, go there and run CMake and Make:
```
$jetcash> mkdir jetcash/build
$jetcash> cd jetcash/build
$jetcash/jetcash/build> cmake ..
$jetcash/jetcash/build> make -j4 jetcash-crypto
$jetcash/jetcash/build> cd ../..
$jetcash> git clone https://github.com/jetcash/desktop-wallet.git
$jetcash> mkdir desktop-wallet/build
$jetcash> cd desktop-wallet/build
$jetcash/desktop-wallet/build> qmake ../src/jetwallet.pro
$jetcash/desktop-wallet/build> make
$jetcash/desktop-wallet/build> macdeployqt ../bin/jetwallet.app
```

### Linux
```
$jetcash> git clone https://github.com/jetcash/jetcash.git
$jetcash> cd jetcash
$jetcash/jetcash> mkdir -p build
$jetcash/jetcash> cd build
$jetcash/jetcash/build> cmake ..
$jetcash/jetcash/build> make -j4 jetcash-crypto
$jetcash/jetcash/build> cd ../..
$jetcash> git clone https://github.com/jetcash/desktop-wallet.git
$jetcash> cd desktop-wallet
$jetcash/desktop-wallet> mkdir -p build
$jetcash/desktop-wallet> cd build
$jetcash/desktop-wallet/build> qmake ../src/jetwallet.pro
$jetcash/desktop-wallet/build> make -j4
```
