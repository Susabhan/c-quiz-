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

//Player structure, char* name and int score.
#include "Leaderboard.h"

int saveScore(Player player){
    FILE *scoreboardFile = fopen("leaderboard.txt", "r");
    
	Player LoadedP[10];
	int place = 0;
	int size = 0;
	int i = 0;
	
	//LOADED DATA:
	
	if (scoreboardFile == NULL) {
		puts("ERROR, FILE NOT EXIST (LB)");
		return 0;
	}
	
	char buf[BUFSIZE];
	int score;
	while (fscanf(scoreboardFile, "%s %d", buf, &score) == 2){
	    Player player;
	    strcpy(player.name, buf);
	    player.score = score;
	    
	    LoadedP[size] = player;
	    
	    size++;
	}
	
	if(size != 10){
		puts("Beware the scoreboard data is not complete and has been tampered with.");
	}
	
	for(i = 0; i <= size; i++){
		if(LoadedP[i].score < player.score){
		    int z;
		    for(z = size; z > i; z--){
		        strcpy(LoadedP[z].name, LoadedP[z-1].name);
		        LoadedP[z].score = LoadedP[z-1].score;
		    }
		    //LoadedP[i].name = player.name;
		    strcpy(LoadedP[i].name, player.name);
		    LoadedP[i].score = player.score;
			place = i+1; //starts at 0.
			break;
		}
	}
	
	fclose(scoreboardFile);
	
	FILE *scoreboardfile = fopen("leaderboard.txt", "w");
 
	printf("Current Leaderboard:\n");
    for(i = 0; i < size; i++){
		printf("%d. %s: %d\n",i+1,LoadedP[i].name, LoadedP[i].score);
		fprintf(scoreboardfile, "%s %d\n", LoadedP[i].name, LoadedP[i].score);
	}
    fflush(scoreboardfile);
    fclose(scoreboardfile);
	
	//Load data from leaderboard, parse and sort, then find position and save. (return index/position)
	//Always have 10 items in txt file used for counting the lines.
	return place;
};
