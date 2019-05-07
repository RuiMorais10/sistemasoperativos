CC          = gcc
CFLAGS      = -Wall -O0 -g
#CFLAGS		= -Wall -O2
#############################################
#				  LIBS  					#
#############################################
# dynread
dr_src  = $(wildcard src/libs/dynread/*.c)
dr_obj  = $(dr_src:.c=.o)
# dynread
it_src  = $(wildcard src/libs/itoas/*.c)
it_obj  = $(it_src:.c=.o)
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

ag: $(ag_obj) $(dr_obj)
	$(CC) $(CFLAGS) -o ag $(ag_obj) $(dr_obj)

cl: $(cv_obj) $(dr_obj)
	$(CC) $(CFLAGS) -o cv $(cv_obj) $(dr_obj)

sv: $(sv_obj) $(dr_obj)
	$(CC) $(CFLAGS) -o sv $(sv_obj) $(dr_obj)

ma: $(ma_obj) $(dr_obj) $(it_obj)
	$(CC) $(CFLAGS) -o ma $(ma_obj) $(dr_obj)

remfiles:
	rm -f artigos stringsmake

clean:
	find . -name "*.o" -type f -delete
	rm -f artigos strings STOCKS VENDAS
	rm -f cv sv ma ag

main: cl sv ag ma

fresh: clean main