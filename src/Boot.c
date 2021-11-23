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

#include "Boot.h"
#include <stdio.h>
#include <stdlib.h>

void preboot(){
	puts("Please wait while we get things ready...");

	FILE* ptr = fopen("auth.txt","r");
	if (ptr==NULL)
	{
		puts("Creating needed files...");
		FILE* fp = fopen("auth.txt", "w");
		fputs("Jack JacksPassword101\n", fp);
		fputs("Bob BobsPassword101\n", fp); //some demo data.
		fputs("Mark MarksPassword101", fp);
		fflush(ptr);
	}

	ptr = fopen("leaderboard.txt", "r");
	if (ptr==NULL)
	{
		FILE* fp = fopen("leaderboard.txt", "w");
		fputs("NA 0\nNA 0\nNA 0\nNA 0\nNA 0\nNA 0\nNA 0\nNA 0\nNA 0\nNA 0\n", fp);
		fflush(ptr);
	}

	ptr = fopen("music.txt","r");
	if (ptr==NULL)
	{
		/* 50 default songs - demo data from
		 * http://www.mtv.co.uk/music/charts/the-official-uk-top-40-singles-chart
		 * https://www.bbc.co.uk/programmes/articles/TYv9MtpnqFRMPKP7QFcYfW/the-official-uk-top-40-singles-chart
		 * https://www.deezer.com/en/playlist/4450888122
		 */

		puts("Creating more needed files...");
		FILE* fp = fopen("music.txt", "w");

		fputs("--- Format: Song-Name Artist-Name ---\n",fp);
		fputs("Someone-You-Loved  Lewis-Capaldi\n",fp);
		fputs("Bad-Guy Billie-Eilish\n",fp);
		fputs("Just-You-and-I Tom-Walker\n",fp);
		fputs("Walk-Me-Home Pink\n",fp);
		fputs("Dont-Call-Me-Up Mabel\n",fp);
		fputs("What-I-Like-About-You Jonas-Blue\n",fp);
		fputs("Wow Post-Malone\n",fp);
		fputs("Sucker Jonas-Brothers\n",fp);
		fputs("Piece-of-Your-Heart Meduza\n",fp);
		fputs("Let-You-Down NF\n",fp);
		fputs("Demons Imagine-Dragons\n",fp);
		fputs("Wake-Me-Up Avicii\n",fp);
		fputs("Levels Avicii\n",fp);
		fputs("Paradise Coldplay\n",fp);
		fputs("Let-It-Go James-Bay\n",fp);
		fputs("Take-Me-To-Church Hozier\n",fp);
		fputs("Let-Her-Go Passenger\n",fp);
		fputs("All-Of-Me John-Legend\n",fp);
		fputs("7-Years Lukas-Graham\n",fp);
		fputs("Cups Anna-Kendrick\n",fp);
		fputs("The-Nights Avicii\n",fp);
		fputs("Shut-Up-And-Dance Walk-The-Moon\n",fp);
		fputs("Burn Ellie-Goulding\n",fp);
		fputs("Dynamite Taio-Cruz\n",fp);
		fputs("Dear-Darlin Olly-Murs\n",fp);
		fputs("2002 Anne-Marie\n",fp);
		fputs("Shotgun George-Ezra\n",fp);
		fputs("Not-Afraid Eminem\n",fp);
		fputs("Heathens Twenty-One-Pilots\n",fp);
		fputs("The-Man-Who-Cant-Be-Moved The-Script\n",fp);
		fputs("Superheroes The-Script\n",fp);
		fputs("Impossible James-Arthur\n",fp);
		fputs("Let-You-Love-Me Rita-Ora\n",fp);
		fputs("Back-To-You Selena-Gomez\n",fp);
		fputs("Mirrors Justin-Timberlake\n",fp);
		fputs("Royals Lorde\n",fp);
		fputs("Locked-Out-Of-Heaven Bruno-Mars\n",fp);
		fputs("Whistle Flo-Rida\n",fp);
		fputs("Feel-So-Close Calvin-Harris\n",fp);
		fputs("These-Days Take-That\n",fp);
		fputs("Ghost Ella-Henderson\n",fp);
		fputs("Lost-Without-You Freya-Ridings\n",fp);
		fputs("Without-Me Halsey\n",fp);
		fputs("Be-Alright Dean-Lewis\n",fp);
		fputs("Barcelona Max-George\n",fp);
		fputs("Vossi-Bop Stormzy\n", fp);
		fputs("SOS Avicci\n", fp);
		fputs("Location Dave\n", fp);
		fputs("Here-With-Me Marshmellow\n", fp);
		fputs("Talk Khalid\n", fp);
		fputs("Homocide Logic",fp);
		fflush(ptr); //fflush() found this the hard way while using my pi that it can sometimes store data in memory before writing, this forces it to clear cache and write to disk.
	}
}