/*
 *  Music Quiz 2019 - OCR Programming Task 1
 *  Copyright (C) 2019 - Jack Honour (JaxkDev)
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along with this program.
 *  If not, see <https://www.gnu.org/licenses/>.
 *
 */
#define BUFSIZE 1024
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>

#if defined(_WIN32) || defined(_WIN64) || defined(__CYGWIN__)
#include <direct.h> // windows sleep();
#else
#include <unistd.h> // linux sleep();
#endif
// https://stackoverflow.com/questions/142508/how-do-i-check-os-with-a-preprocessor-directive <----

#include "Auth.h"
#include "Boot.h"
#include "Leaderboard.h"

void startGame();
void printRules();
void authLoop();
void loadAllSongs();
char* getRandomSong();
void cleanInput(char *msg);

char songs[0][40] = {}; //0 for current size, 40 for max char* length that goes in it in this case 36 but rounded for safety.
int songsSize = 0;
char username[BUFSIZE];

int main(int argc, char *argv[])
{
	if(argc >= 2)
	{
		if(strlen(argv[1]) == strlen("--ci") && strcmp(argv[1],"--ci") == 0){
			puts("CI Mode Enabled, loading resources then shutting down.");
			preboot();
			loadAllSongs();
			puts("Boot completed, exiting now.");
			return 0;
		} else {
			printf("Unknown argument provided: %s", argv[1]);
		}
	}
	srand(time(NULL));
	puts("Music Quiz 2019 by Jack Honour AKA JaxkDev");
	preboot();
	loadAllSongs();
	authLoop();
	printRules();
	startGame();
	return 0; //*note to self, always return a int, or prog will not end.
}

void authLoop(){
	//returns when finally authenticated.
	printf("\nWelcome, Please enter your username: ");
	fgets(username, BUFSIZE, stdin);
	username[strcspn(username, "\n")] = 0; //remove trailing new lines from fgets.
	printf("And your password please: ");
	char password[BUFSIZE];
	fgets(password, BUFSIZE, stdin);
	password[strcspn(password, "\n")] = 0; //remove trailing new lines from fgets.
	printf("Please wait while we verify your details...\n");
	sleep(3);
	if(checkAuth(username, password) == 1){
		printf("Authentication Success.\n\n");
		sleep(1);
		return;
	} else {
		printf("Authentication Failed, Please try again...\n\n");
		authLoop();
	}
}

void startGame(){
	int score = 0;
	int try = 1;
	int question = 1;
	int playing = 1;

	while(playing == 1){
		char song[BUFSIZE];
		char tmpName[BUFSIZE];
		strcpy(song, getRandomSong()); //must copy first as strtok changes string directly and as getRandomSong returns a pointer and so it will change the song and so if used again it will not work.
		char *name = strtok(song, " ");
		char *artist = strtok(NULL, " ");
		cleanInput(artist);
		cleanInput(name); //lowercase but also a failsafe to strip other characters.

		try = 1;

		while(try < 3){
			if(try == 1) printf("\nQuestion %d:\n",question);
			else printf("\n\nQ%d Attempt %d:\n", question, try);
			strcpy(tmpName, name);
			char *tmp = strtok(tmpName, " ");
			printf("Song Name: ");
			while(tmp != NULL){
				printf("%c", tmp[0]);
				for(int i = 0; i < strlen(tmp)-1; i++){
					printf(".");
				}
				printf(" ");
				tmp = strtok(NULL, " ");
			}
			printf("\nSong Artist: %s\n\n", artist);
			//Input here.
			char guessName[BUFSIZE];
			printf("%s, Try and guess the song name:\n", username);
			gets(guessName);
			cleanInput(guessName);
			printf("%s, Your guess: '%s' by '%s' is...",username, guessName, artist);
			fflush(stdout); //found that without flushing before sleep will mean whole print will wait until finished sleeping.
			sleep(2);
			if(strcmp(name, guessName) == 0){
				printf("Correct !\n");
				question++;
				if(try == 1){
					score += 3;
					printf("3 added to your score, current score: %d", score);
				}
				else{
					score += 1;
					printf("1 added to your score, current score: %d", score);
				}
				break;
			} else {
				printf("Incorrect !\n");
				try++;
			}
		}
		if(try >= 3) playing = 0; //stop loop.
	}

	printf("\n\n%s You have finally been defeated, your final score... ", username);
	fflush(stdout);
	sleep(2);
	printf("%d\n\n", score);


	// ---- LEADERBOARD ----

	Player player;
	strcpy(player.name,username);
	player.score = score;

	int place = saveScore(player);

	if(place != 0){
		printf("\nCongratulations, you are #%d on the leaderboard.", place);
	} else {
		printf("\nUnfortunately you did not make it onto the leaderboard.");
	}

	// ---- LEADERBOARD ----
	return;
}

/**
 * loadAllSongs()
 * Loads songs from music.txt into songs[]
 */
void loadAllSongs(){
	int i = 0;
	char buffer[BUFSIZE];
	FILE *file = fopen("music.txt","r");
	while(fgets(buffer, BUFSIZE, file)){
		if(strcmp(buffer,"\n") != 0 && strcmp(buffer,"") != 0){
			int len = strlen(buffer);
			if( buffer[len-1] == '\n' )
				buffer[len-1] = 0; //strip new lines from ending, thanks to St0rmD3v for making it much smaller then what i had :)
			strcpy(songs[i], buffer);
			i++;
		}
	}
	songsSize = i;
	return;
}

/**
 * getRandomSong()
 * Returns random char* from songs[]
 */
char* getRandomSong(){
	int index = ( rand() % songsSize )+1; //get random int between 0 and array size
	if(index >= songsSize) index = songsSize-1;
	return songs[index];
}

/**
 * printRule()
 * Says it all.
 */
void printRules(){
	printf("--- Rules of the game ---\n");
	printf("1. No cheating (eg. Internet)\n");
	printf("2. Dont edit external files.\n");
	printf("\nYou get 2 chances to guess the song.\n");
	printf("^ Remember all the above ^\n");
	printf("-------------------------\n");
	fflush(stdout);
	sleep(5);
	return;
}

/**
 * cleanInput()
 * Lowercase whole string (modifies original not reference) and replace's '-' with ' '
 */
void cleanInput(char* msg){
	char space = ' ';
	char find = '-';
	for(int i = 0; i <strlen(msg); i++){
		if(msg[i] == find) msg[i] = space;
	}
	for(; *msg; ++msg){
		*msg = tolower(*msg);
	}
}
