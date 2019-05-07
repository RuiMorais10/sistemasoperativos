CC          = gcc
CFLAGS      = -Wall -O0 -g
#CFLAGS		= -Wall -O2
#############################################
#				  LIBS  					#
#############################################
#cache
ch_src  = $(wildcard src/libs/cache/*.c)
ch_obj  = $(ch_src:.c=.o)
# itoas
it_src  = $(wildcard src/libs/itoas/*.c)
it_obj  = $(it_src:.c=.o)
# readline
rl_src  = $(wildcard src/libs/readline/*.c)
rl_obj  = $(rl_src:.c=.o)
#strdup
sd_src  = $(wildcard src/libs/strdup/*.c)
sd_obj  = $(sd_src:.c=.o)
#############################################
#				 Client 					#
#############################################
cv_src  = $(wildcard src/cv/*.c)
cv_obj  = $(cv_src:.c=.o)
#############################################
#				 Server 					#
#############################################
sv_src  = $(wildcard src/sv/*.c)
sv_obj  = $(sv_src:.c=.o)
#############################################
#				Agregador					#
#############################################
ag_src  = $(wildcard src/ag/*.c)
ag_obj  = $(ag_src:.c=.o)
#############################################
#				Manutenção					#
#############################################
ma_src  = $(wildcard src/ma/*.c)
ma_obj  = $(ma_src:.c=.o)

.DEFAULT_GOAL = main

# ag requires:
#	- readline
ag: $(ag_obj) $(rl_obj)
	$(CC) $(CFLAGS) -o ag $(ag_obj) $(rl_obj)

# cv requires:
#	- readline
cl: $(cv_obj) $(rl_obj)
	$(CC) $(CFLAGS) -o cv $(cv_obj) $(rl_obj)

# sv requires:
#	- readline
sv: $(sv_obj) $(rl_obj)
	$(CC) $(CFLAGS) -o sv $(sv_obj) $(rl_obj)

# ma requires:
#	- readline
ma: $(ma_obj) $(rl_obj) $(it_obj)
	$(CC) $(CFLAGS) -o ma $(ma_obj) $(rl_obj)

clean:
	find . -name "*.o" -type f -delete
	rm -f artigos strings STOCKS VENDAS
	rm -f cv sv ma ag

main: cl sv ag ma

fresh: clean main