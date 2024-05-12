build:
	gcc lists.c tasksFunctions.c queue.c stacks.c BTS.c lanParty.c -o lanParty
clean:
	rm -f lanParty