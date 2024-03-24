# SCM api calls for C as functions using ZD88k
Work in progress, just a few for now. New ones will be added when I need them.

# Z88dk instructions

To build using z88dk on docker, do the following steps:
1. Go to the folder that have your source or Make file
- cd folder
2. Run the command inside the docker
- docker run -v ${PWD}:/src/ -it z88dk/z88dk [command]
-- exemples
docker run -v ${PWD}:/src/ -it z88dk/z88dk make
docker run -v ${PWD}:/src/ -it z88dk/z88dk zcc +zx -vn test.c -o test.bin -lndos 

# compile
zcc +rc2014 -subtype=basic -clib=sdcc_iy

Some remarks:
- Noticed that the ret instruction, is required
- seeams that we dont need to preserve hl (push/pop)

Some links:
- https://github.com/z88dk/z88dk
- https://smallcomputercentral.com/
