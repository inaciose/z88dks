# Z88dk instructions

To build using z88dk on docker, do the following steps:
1. Go to the folder that have your source or Make file
- cd folder
2. Run the command inside the docker
- docker run -v ${PWD}:/src/ -it z88dk/z88dk [command]
-- exemples
docker run -v ${PWD}:/src/ -it z88dk/z88dk make
docker run -v ${PWD}:/src/ -it z88dk/z88dk zcc +zx -vn test.c -o test.bin -lndos 
