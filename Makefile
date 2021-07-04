# Makefile for executable adjust

# *****************************************************
# Parameters to control Makefile operation

CC = gcc

# ****************************************************
# Entries to bring the executable up to date

shell: 
	$(CC) -o shell Env.c cd.c Compute.c convert.c display.c echo.c history.c ls.c pinfo.c pwd.c Redirect.c RWX.c shell.c TakeInput.c undo.c FBPro.c Jobs.c FgBG.c kjob.c -lreadline
