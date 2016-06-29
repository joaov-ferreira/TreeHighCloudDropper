/*
 * thcCLI.c
 * 
 * Copyright 2013 Joao <joao@System>
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
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <getopt.h>
#include <unistd.h>

#include "types.h"
#include "functions.h"
#include "macros.h"

void thcShowHelpCLI()
{
	printf("Tree High CloudDropper v0.1 \n");
	printf("\n");
	printf("Usage : thc [OPTION...] (SUBOPTIONS...)\n");
	printf("\n");
	printf("\t-a --adduser     :   Add a new user eg: --adduser [nickname] email=\"mail@server.com\"\n");
	printf("\t                   group=\"user\" fullname=\"Mary Jane\"\n");
	printf("\t-l --listusers   :   Show the full list of registered users in the form:\n");
	printf("\t                   UID : nickname : group : full name : e-mail \n");
	printf("\t-h --help        :   Show this screen with the options\n");
	printf("\t\n");
	printf("\t-s --setlanguage :   Change program default language [NOT IMPLEMENTED YET]\n");
	printf("\t\n");
	printf("\t-n --ncurses     :   Starts NCurses interface [NOT IMPLEMENTED YET]\n");
	printf("\t\n");
	printf("\n");
	
}

unsigned thcListUsersCLI()
{
	FILE *escrita;
	thcUserStruct buffer;
	int i=1;
	
	escrita = fopen(FILE_NAME,READ);
	if (!escrita)
		return ERROR_READING_FILE;
	
	while (fread(&buffer,1,sizeof(thcUserStruct),escrita) != 0)
	{
		printf("User #%d : %s\n",i,buffer.nickname);
		i++;
	}
	
	fclose(escrita);
	return OK;
}

//traduzir pra português
unsigned thcShowUserInfoCLI (thcUserStruct *data)
{
	if (!data)
		return ERROR_EMPTY_POINTER;
	printf("Name : %s\n",data->nickname);
	printf("E-mail : %s\n",data->email);
	printf("Full name : %s\n",data->fullName);
	printf("Group : %d\n",data->group);
	printf("User ID : %d\n",data->UID);
	return OK;	
}

void thcErrorMsg(int errorCode);
{
	if (errorCode == ERROR_COOKIE_CONTENT)
		printf()
	
	
	
}
