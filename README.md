# libftTester - 42 Gyeongsan Ubuntu Edition
Enhanced tester for the libft project of 42 school, updated for Ubuntu 24.04 based 42 Gyeongsan systems.
This fork keeps the original Tripouille-style workflow, but adds broader edge-case coverage, Linux-safe leak tracking, and Makefile validation for common 42 subject requirements.
Clone this tester in your libft repository, or somewhere else and customize the path to your libft project by changing the LIBFT_PATH variable inside the Makefile.  

![alt text](https://i.imgur.com/EWmbpxx.png)  


## Commands
make m = launch all tests  
make a = same as make m (legacy alias)  
make [function name] = launch associated test ex: `make calloc`  
make checkmakefile = validate the libft Makefile only
 
make dockerm = launch all tests in linux container  
make dockera = same as make dockerm (legacy alias)  
make docker [function name] = launch associated test in linux container ex: `make dockercalloc`  
Thanks to gurival- for the docker idea (https://github.com/grouville/valgrind_42)  

make vs [function name] = open the corresponding tests in vscode ex: `make vscalloc`  

Note: Bonus-only targets were removed because list functions are now part of mandatory libft.  


## Additional checks in this fork
- Broader tests for ASCII boundaries, signed/unsigned byte behavior, NULL-length memory operations, allocation sizes, file descriptor output, and list edge cases.
- Linux/WSL-safe leak tracker guard to avoid recursive malloc-hook crashes on Ubuntu-based environments.
- Makefile validation before tests:
  - Makefile must exist.
  - `NAME` must be set to `libft.a`.
  - `all`, `clean`, `fclean`, and `re` rules must exist.
  - `$(wildcard ...)`, `*.c`, `*.o`, and shell-based source discovery with `ls`/`find` are rejected.
  - Mandatory libft source files must exist and be explicitly listed in the Makefile.


## Setup docker in goinfre for 42 mac  
```sh
rm -rf ~/Library/Containers/com.docker.docker  
rm -rf ~/.docker  
rm -rf /goinfre/${USER}/docker /goinfre/${USER}/agent  
mkdir -p /goinfre/${USER}/docker /goinfre/${USER}/agent  
ln -s /goinfre/${USER}/agent ~/Library/Containers/com.docker.docker  
ln -s /goinfre/${USER}/docker ~/.docker 
```


## Outputs
![alt text](https://i.imgur.com/en8rJpS.png)  
![alt text](https://i.imgur.com/ZvzhIoZ.png)  
![alt text](https://i.imgur.com/KrlN2Pg.png)  

MOK / MKO = test about your malloc size (this shouldn't be tested by moulinette)  


## Report bugs / Improvement
Contact me on slack or discord : jgambard  
