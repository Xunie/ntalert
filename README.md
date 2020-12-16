![Screenshot of NT Alert v0.1](https://github.com/Xunie/ntalert/blob/master/img/v0.1.png?raw=true)

## NTalert
Automatic alerts for NeoTokyo.

Because manual alerts require human intervention.

### Getting started:
```
# clone:
git clone https://github.com/Xunie/ntalert.git
cd ntalert
git submodule init && git submodule update
cd .. # exit dir

# build:
mkdir ntalert-build
cd ntalert-build
cmake ../sfmleton
make -j
```

If you're on MSYS2 MinGW64 like the real pros are, generate build with:
```
cmake -G "MSYS Makefiles" ../sfmleton
````
