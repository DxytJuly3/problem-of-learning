.PHONY:all
all:env_Test execl_Test execv_Test execle_Test execlp_Test execvp_Test execvpe_Test 

env_Test:env_Test.c
	gcc $^ -o $@ 
execvpe_Test:execvpe_Test.c
	gcc $^ -o $@ 
execle_Test:execle_Test.c
	gcc $^ -o $@
execvp_Test:execvp_Test.c
	gcc $^ -o $@
execlp_Test:execlp_Test.c
	gcc $^ -o $@
execv_Test:execv_Test.c
	gcc $^ -o $@
execl_Test:execl_Test.c
	gcc $^ -o $@

.PHONY:clean
clean:
	rm -f execvpe_Test execl_Test execv_Test execlp_Test execvp_Test env_Test execle_Test 
