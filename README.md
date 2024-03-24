# z88dks
Projects for z88dk

# Install docker
https://hub.docker.com/r/z88dk/z88dk
docker pull z88dk/z88dk

# Using docker
To build using z88dk on docker, do the following steps:
1. Go to the folder that have your source or Make file
- cd myfolder
2. Run the command inside the docker
- docker run -v ${PWD}:/src/ -it z88dk/z88dk [command]
-- exemples
docker run -v ${PWD}:/src/ -it z88dk/z88dk make
docker run -v ${PWD}:/src/ -it z88dk/z88dk zcc +zx -vn test.c -o test.bin -lndos 
-- Using Makefiles its easier, because the command its allways:
docker run -v ${PWD}:/src/ -it z88dk/z88dk make

# notes
- mixasmc_: passing arguments btw C and asm
- ansi lib: colors, cursor & screen (usable on rc2014)
- rc2014scmapi: SCM api calls for C as functions using ZD88k

# minicom, enable colors 
sudo minicom -c on --device /dev/ttyUSB0