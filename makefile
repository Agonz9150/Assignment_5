CC=gcc
Program_files = validateMain.c Function.c
Program_files_2 = convertMain.c Function.c

Build:
	$(CC) -o validateMain $(Program_files)
Build_2:
	$(CC) -o convertMain $(Program_files_2)
Build_3:
	make Build
	make Build_2
