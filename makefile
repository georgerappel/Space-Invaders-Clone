all: space

space: main.o alien.o aliens.o bunker.o jogo.o tanque.o tiro.o navemae.o
	g++ main.o alien.o aliens.o bunker.o jogo.o tanque.o tiro.o navemae.o -o space -lallegro -lallegro_primitives -lallegro_image -lallegro_audio -lallegro_acodec -lallegro_font -lallegro_ttf
	rm *.o

main.o:
	g++ -c main.c

alien.o:
	g++ -c alien.c

aliens.o:
	g++ -c aliens.c

bunker.o:
	g++ -c bunker.c

jogo.o:
	g++ -c jogo.c

tanque.o:
	g++ -c tanque.c

tiro.o:
	g++ -c tiro.c

navemae.o:
	g++ -c navemae.c
