/*
 * main.c
 * 
 * Copyright 2018 Unknown <solow@localhost>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * 
 */


#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>
#include <pwd.h>
#include <string.h>

int DecToOctal(int decimal){
	int OctalNum = 0;
	int i = 1;
	
	while(decimal != 0){
		OctalNum += (decimal % 8) * i;
		decimal /= 8;
		i *= 10;
		}
	return OctalNum;
	}

void  Type(const char * chemin){
	int type;
	struct stat buf;
	
	type = stat(chemin,&buf);
	
	if(S_ISREG(buf.st_mode)){
		printf("file");
		}
	if(S_ISDIR(buf.st_mode)){
		printf("rep");
		}
	if(S_ISCHR(buf.st_mode)){
		printf("devc");
		}
	if(S_ISBLK(buf.st_mode)){
		printf("blk");
		}
	if(S_ISFIFO(buf.st_mode)){
		printf("fifo");
		}
	if(S_ISLNK(buf.st_mode)){
		printf("link");
		}
	if(S_ISSOCK(buf.st_mode)){
		printf("sock");
		}
	printf("\t");
}

void Rights(const char * chemin){
	int type;
	struct stat buf;
	
	type = stat(chemin,&buf);
//owner rights	
	if(buf.st_mode & S_IRUSR){
		printf("r");
		}
	else{
		printf("-");
		}
	if(buf.st_mode & S_IWUSR){
		printf("w");
		}
	else{
		printf("-");
		}
	if(buf.st_mode & S_IXUSR){
		printf("x");
		}
	else{
		printf("-");
		}
//group rights
	if(buf.st_mode & S_IRGRP){
		printf("r");
		}
	else{
		printf("-");
		}
	if(buf.st_mode & S_IWGRP){
		printf("w");
		}
	else{
		printf("-");
		}
	if(buf.st_mode & S_IXGRP){
		printf("x");
		}
	else{
		printf("-");
		}
		
//other rights
	if(buf.st_mode & S_IROTH){
		printf("r");
		}
	else{
		printf("-");
		}
	if(buf.st_mode & S_IWOTH){
		printf("w");
		}
	else{
		printf("-");
		}
	if(buf.st_mode & S_IXOTH){
		printf("x");
		}
	else{
		printf("-");
		}
		printf("\t");
}

void Ownership(const char * chemin){
	struct stat buf;
	struct passwd *owner;
	
	stat(chemin,&buf);
	owner = getpwuid(buf.st_uid);
	printf("%s",owner->pw_name);
	printf("\t");
	}

void Size(const char * chemin){
	struct stat buf;
	
	stat(chemin, &buf);
	printf("%ld",buf.st_size);
	printf("\t");
	}


/*void Displaydir(const char * chemin){ //obsolete -> cf Displayfct()
	DIR* buf;
	struct dirent* dir;
	
	buf = opendir(chemin);
	while((dir=readdir(buf)) != NULL){
		printf("%s\n",dir->d_name);
		}
	}*/

void DisplayCombo(const char * chemin){
	Type(chemin);
	Rights(chemin);
	Ownership(chemin);
	Size(chemin);
	printf("\n");
}

void DisplayFct(const char * chemin){
	DIR* buf;
	struct dirent* dir;
	buf = opendir(chemin);
	while((dir=readdir(buf)) != NULL){
		char * str = malloc(sizeof(char) * (strlen(chemin) + strlen(dir->d_name) + 2));
		sprintf(str, "%s/%s", chemin, dir->d_name);
		printf("%-42s \t",dir->d_name); //fomatage -42/42
		DisplayCombo(str);
		free(str);
		}
	closedir(buf);
	}

int main(int argc, char **argv)
{	
	if(argc == 2){
		DisplayFct(argv[1]);
	}
	return 0;
}

