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

notes

test is a 1st sample
rc2014f

# minicom, enable colors 
sudo minicom -c on --device /dev/ttyUSB0