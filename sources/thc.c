/*                                            
 * Universidade Federal do Rio de Janeiro     
 * Escola Politecnica                         
 * Departamento de Eletronica e de Computacao 
 * EEL270 - Computacao II - Turma 2012/2      
 * Prof. Marcelo Luiz Drumond Lanza           
 * Autor Joao Vitor Ferreira Duarte           
 *                                            
 *
 *                                      
 */          


#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <unistd.h>
#include <string.h>


#include "thcAddUser.h"
#include "thcFunctions.h"
#include "thcTypes.h"
#include "thcConst.h"
#include "thcError.h"
#include "thcShowCliHelp.h"
#include "thcRunNcursesInterface.h"        
#include "thcEditUserName.h"
#include "thcAddUserToGroup.h"
#include "thcChangeUserGroup.h" 
#include "thcRemoveUser.h"
#include "thcChangeUserPassword.h"

/*Global Arrays*/
char *groupsArray[7][2]=
{
	{"Administrator","Aministrador"},
	{"Owner","Proprietario"},
	{"Administrator & Owner","Administrador & Proprietario"},
	{"User","Usuario"},
	{"Administrator & User ","Administrador & Usuario"},
	{"User & Owner","Usuario & Proprietario"},
	{"ROOT","ROOT"}
};


static struct option longOptions []=
{
	{"add",			0,	NULL	, 'a'},
	{"change",		0,	NULL	, 'a'},
	{"edit",		0,	NULL	, 'e'},
	{"group", 		0,	NULL	, 'g'},
	{"help"	,		0,	NULL	, 'h'},
	{"invie",		0,	NULL	, 'i'},
	{"ncurses", 	0,	NULL	, 'n'},
	{"password",	0,	NULL	, 'p'},
	{"remove",		0,	NULL 	, 'r'},
	{"initialize",	0,	NULL 	, 'z'},
	{NULL, 			0, 	NULL	,  0 }
};

char *tokens [] =
{
	"user",
	"nickname",
	"email",
	"confirmation",
	"group",
	"username",
	"language",
	NULL
};
		
enum
{
	USER,
	NICKNAME,
	EMAIL,
	CONFIRMATION,
	GROUP,
	USERNAME,
	LANGUAGE,	
};


int main(int argc, char **argv)
{ 
	int option,argumentIndex,index;
	unsigned passwordErrorCounter = THC_PASSWORD_ATTEMPTS;	
	char *stringShortOptions = "AaCcEeGgHhIiNnPpRrZz";
	char *value;
	char systemUser [THC_NICKNAME_MAXIMUM_LENGHT+1];
	char nickname   [THC_NICKNAME_MAXIMUM_LENGHT+1];
	char username   [THC_FULL_NAME_MAXIMUM_LENGHT+1];
	char email      [THC_EMAIL_MAXIMUM_LENGHT+1];
	char confEmail  [THC_EMAIL_MAXIMUM_LENGHT+1];
	char *password;
	char passwordConfirm [THC_PASSWORD_MAXIMUM_LENGHT+1];
	char confirm;
	thcLanguageType language = english;
	thcUserDataType *data;
	thcErrorType errorCode;
	thcGroupType group = THC_DEFAULT_GROUP;


	/********************************************************************************/
	/*********************START OF THE MAIN PROGRAM**********************************/
	/********************************************************************************/

	/*Checks for arguments*/
	if (argc == 1)
	{
		thcGetTextErrorMessage(language,THC_INVALID_ARGUMENT_NUMBER);
		exit(THC_INVALID_ARGUMENT_NUMBER);
	}
	
	/*Erases trash from variables*/
	memset(nickname	,0x00,THC_NICKNAME_MAXIMUM_LENGHT+1);
	memset(username	,0x00,THC_FULL_NAME_MAXIMUM_LENGHT+1);
	memset(email	,0x00,THC_EMAIL_MAXIMUM_LENGHT+1);
	memset(confEmail,0x00,THC_EMAIL_MAXIMUM_LENGHT+1);
	opterr = 0;

	option = getopt_long(argc, argv, stringShortOptions,longOptions, NULL);
	switch (option)
	{
		/*******************************************Add User to Group*****************************************************/
		/************************************************OR***************************************************************/
		/*******************************************Change user group*****************************************************/
		case 'A':
		case 'a':
		case 'G':
		case 'g':
			/*Allocates space for data*/
			data = malloc (sizeof(thcUserDataType));
			memset(data,0x00,sizeof(thcUserDataType));			
		
			/*Get subotions*/
			argumentIndex = 0;
			while (argumentIndex < argc)
			{
				index = getsubopt (&argv[argumentIndex],tokens,&value);
								
				switch (index)
				{
					case USER:
						if(value != NULL)
							strcpy(systemUser,value);
					break;
					
					case LANGUAGE:
						if(value != NULL)
						{
							if (strcmp(value,"english") == 0) language = 0;
							if (strcmp(value,"portuguese") == 0) language = 1;
						}
					break;
					
					case NICKNAME:
						if(value != NULL)
							strcpy(nickname,value);
					break;
					
					case GROUP:
						if (!value)
							exit(THC_INVALID_ARGUMENT);
						if (strcmp(value, "administrators") == 0) group = administrador;
						if (strcmp(value,"owners") == 0) group = owner;
						if (strcmp(value,"users") == 0) group = user;
					break;
					
				}
				
				argumentIndex++;
			}	/*while*/
			
			/*Check for arguments*/
			if (strlen(systemUser) == 0)
			{
				thcGetTextErrorMessage(language,THC_INVALID_ARGUMENT);
				exit (THC_INVALID_ARGUMENT);
			}
			/*Check for user*/
			errorCode = thcSearchUser(systemUser,data);
			if (errorCode != THC_OK)
			{
				thcGetTextErrorMessage(language,errorCode);
				exit (errorCode);
			}
			
			/*ask for password*/
			do
			{
				if (passwordErrorCounter == 0)
				{
					thcGetTextErrorMessage(language,THC_INCORRECT_PASSWORD);
					exit(THC_INCORRECT_PASSWORD);
				}
				passwordErrorCounter--;
				
				if (language == portuguese)	password = getpass("Entre com a senha de usuario :");
				if (language == english)	password = getpass("Enter with user password :");

			} while (thcUserLogin(systemUser,password,data) != THC_OK);
			
			/*Check for admin member*/
			if ((data->group != administrador) && (data->group != userAdmin) && (data->group != ownerAdmin) &&(data->group != root))
			{
				thcGetTextErrorMessage(language,THC_PERMISSION_DENIED);
				exit (THC_PERMISSION_DENIED);
			}
			
			/*Check for nickname argument*/
			if (strlen(nickname) != 0)
			{
				errorCode = thcSearchUser(nickname,data);
				if (errorCode != THC_OK)
				{
					thcGetTextErrorMessage(language,errorCode);
					exit(errorCode);
				}
				strcpy(username,nickname);
			}
			
			if ((option == 'a') || (option == 'A'))
				errorCode = thcAddUserToGroup(username,group);	
			if ((option == 'g') || (option == 'G'))
				errorCode = thcChangeUserGroup(username,group);
				
			if (errorCode != THC_OK)
				{
					thcGetTextErrorMessage(language,errorCode);
					exit(errorCode);
				}
				
			free(data);
			thcGetTextErrorMessage(language,THC_OK);	
		break;
		
		/************************************** Change user e-mail ***************************************************/
		case 'C':
		case 'c':
			
			/*Allocates space for data*/
			data = malloc (sizeof(thcUserDataType));
			memset(data,0x00,sizeof(thcUserDataType));
			
			/*Get subotions*/
			argumentIndex = 0;
			while (argumentIndex < argc)
			{
				index = getsubopt (&argv[argumentIndex],tokens,&value);
								
				switch (index)
				{
					case USER:
						if(value != NULL)
							strcpy(systemUser,value);
					break;
					
					case LANGUAGE:
						if(value != NULL)
						{
							if (strcmp(value,"english") == 0) language = 0;
							if (strcmp(value,"portuguese") == 0) language = 1;
						}
					break;
					
					case NICKNAME:
						if(value != NULL)
							strcpy(nickname,value);
					break;
					
					case USERNAME:
						if(value != NULL)
							strcpy(username,value); 
					break;	
					
					case EMAIL:
						if (!value)
							exit(THC_INVALID_ARGUMENT);
						strcpy(email,value);
					break;
					
					case CONFIRMATION:
						if (!value)
							exit(THC_INVALID_ARGUMENT);
						strcpy(confEmail,value);
					break;
				}
				
				argumentIndex++;
			}	/*while*/
			
			/*Check for valid arguments*/
			if (strlen(systemUser) == 0)
			{
				thcGetTextErrorMessage(language,THC_INVALID_ARGUMENT);
				exit(THC_INVALID_ARGUMENT);
			}
			
			if (strlen(email) < THC_EMAIL_MINUMUM_LENGHT)
			{
				thcGetTextErrorMessage(language,THC_INVALID_ARGUMENT);
				exit (THC_INVALID_ARGUMENT);	
			}
			
			if (strcmp(email,confEmail) != 0)
			{
				thcGetTextErrorMessage(language,THC_INVALID_ARGUMENT);
				exit (THC_INVALID_ARGUMENT);	
			}
			
			/*ask for password*/
			do
			{
				if (passwordErrorCounter == 0)
				{
					thcGetTextErrorMessage(language,THC_INCORRECT_PASSWORD);
					exit(THC_INCORRECT_PASSWORD);
				}
				passwordErrorCounter--;
				
				if (language == portuguese)	password = getpass("Entre com a senha de usuario :");
				if (language == english)	password = getpass("Enter with user password :");

			} while (thcUserLogin(systemUser,password,data) != THC_OK);
			
			/*Check for nickname argument*/
			if (strlen(nickname) != 0)
			{       /*This will check if user is admin \/*/
				if ((data->group != administrador) && (data->group != userAdmin) && (data->group != ownerAdmin) &&(data->group != root))
				{
					thcGetTextErrorMessage(language,THC_PERMISSION_DENIED);
					exit (THC_PERMISSION_DENIED);
				}
				
				errorCode = thcSearchUser(nickname,data);
				if (errorCode != THC_OK)
				{
					thcGetTextErrorMessage(language,errorCode);				
					exit(errorCode);
				}
				strcpy(systemUser, nickname);
			}
			
			errorCode = thcChangeEmailAdress(systemUser, email, language);
			if (errorCode != THC_OK)
			{
				thcGetTextErrorMessage(language,errorCode);				
				exit(errorCode);
			}
			
			free(data);
			thcGetTextErrorMessage(language, THC_OK);
			
		break; /*Change e-mail*/
		
		/***************************************Edit user name********************************************************/
		case 'E':
		case 'e':
			
			/*Allocates space for data*/
			data = malloc (sizeof(thcUserDataType));
			memset(data,0x00,sizeof(thcUserDataType));
			
			/*Get subotions*/
			argumentIndex = 0;
			while (argumentIndex < argc)
			{
				index = getsubopt (&argv[argumentIndex],tokens,&value);
								
				switch (index)
				{
					case USER:
						if(value != NULL)
							strcpy(systemUser,value);
					break;
					
					case LANGUAGE:
						if(value != NULL)
						{
							if (strcmp(value,"english") == 0) language = 0;
							if (strcmp(value,"portuguese") == 0) language = 1;
						}
					break;
					
					case NICKNAME:
						if(value != NULL)
							strcpy(nickname,value);
					break;
					
					case USERNAME:
						if(value != NULL)
							strcpy(username,value); 
					break;	
				}
				
				argumentIndex++;
			}	/*while*/
			
			/*Check for valid arguments*/
			if (strlen(systemUser) == 0)
			{
				thcGetTextErrorMessage(language,THC_INVALID_ARGUMENT);
				exit(THC_INVALID_ARGUMENT);
			}
			
			if (strlen(username) == 0)
			{
				thcGetTextErrorMessage(language,THC_INVALID_ARGUMENT);
				exit(THC_INVALID_ARGUMENT);
			}
			
			/*Check for user*/
			errorCode = thcSearchUser(systemUser,data);
			if (errorCode != THC_OK)
			{
				thcGetTextErrorMessage(language,errorCode);
				exit (errorCode);
			}
			
			/*ask for password*/
			do
			{
				if (passwordErrorCounter == 0)
				{
					thcGetTextErrorMessage(language,THC_INCORRECT_PASSWORD);
					exit(THC_INCORRECT_PASSWORD);
				}
				passwordErrorCounter--;
				
				if (language == portuguese)	password = getpass("Entre com a senha de usuario :");
				if (language == english)	password = getpass("Enter with user password :");

			} while (thcUserLogin(systemUser,password,data) != THC_OK);
			
			/*Check for nickname argument*/
			if (strlen(nickname) != 0)
			{       /*This will check if user is admin \/*/
				if ((data->group != administrador) && (data->group != userAdmin) && (data->group != ownerAdmin) &&(data->group != root))
				{
					thcGetTextErrorMessage(language,THC_PERMISSION_DENIED);
					thcGetTextErrorMessage(language,THC_ERROR_EDIT_NAME);
					exit (THC_PERMISSION_DENIED);
				}
				
				errorCode = thcSearchUser(nickname,data);
				if (errorCode != THC_OK)
				{
					thcGetTextErrorMessage(language,errorCode);				
					exit(errorCode);
				}
			}
			
			strcpy(data->fullName,username);
			errorCode = thcEditUserName(data);
			if (errorCode != THC_OK)
				thcGetTextErrorMessage(language,errorCode);
						
			free(data);		
			thcGetTextErrorMessage(language,THC_OK);	
		break; /*Edit*/
		
		/*****************************************************Show help screen*****************************************************/
		case 'H':
		case 'h':
		
			argumentIndex = 0;
		
			while (argumentIndex < argc)
			{
				index = getsubopt (&argv[argumentIndex],tokens,&value);
								
				switch (index)
				{
					case LANGUAGE:
						if (strcmp(value,"english") == 0) language = 0;
						if (strcmp(value,"portuguese") == 0) language = 1;
					break;
				}
				
				argumentIndex++;
			}	
			
			thcShowCliHelp(language);
			
		break; /*Help*/
		
		
		/*****************************************************Invite Users to system*****************************************************/
		case 'I':
		case 'i': 

			/*Initiate pointer*/
			data = malloc (sizeof(thcUserDataType));
			if (!data)
				exit (THC_ERROR_INSUFICIENT_MEMORY);

			
			/*Checks for suboptions*/
			argumentIndex = 0;
			while (argumentIndex < argc)
			{
				index = getsubopt (&argv[argumentIndex],tokens,&value);
								
				switch (index)
				{
					case LANGUAGE:
						if (strcmp(value,"english") == 0) language = 0;
						if (strcmp(value,"portuguese") == 0) language = 1;
					break;
					
					case USER:
						if (!value)
							exit(THC_INVALID_ARGUMENT);
						strcpy(systemUser,value);
					break;
					
					case EMAIL:
						if (!value)
							exit(THC_INVALID_ARGUMENT);
						strcpy(email,value);
					break;
					
					case CONFIRMATION:
						if (!value)
							exit(THC_INVALID_ARGUMENT);
						strcpy(confEmail,value);
					break;
					
					case GROUP:
						if (!value)
							exit(THC_INVALID_ARGUMENT);
						if (strcmp(value, "administrators") == 0) group = administrador;
						if (strcmp(value,"owners") == 0) group = owner;
			
					break;
					
				}
			
				argumentIndex++;
			} /*while*/		
			

			/*Test arguments*/
			if ((strlen(systemUser) == 0) || (strlen(email) == 0) || (strlen(confEmail) == 0))
			{
				thcGetTextErrorMessage(language,THC_INVALID_ARGUMENT);
				exit (THC_INVALID_ARGUMENT);
			}
			
			errorCode = thcSearchUser(systemUser,data);
			if (errorCode != THC_OK)
			{
				thcGetTextErrorMessage(language,errorCode);
				exit(errorCode);				
			}
			
			
			/*User login*/			
			do
			{
				if (passwordErrorCounter == 0)
				{
					thcGetTextErrorMessage(language,THC_INCORRECT_PASSWORD);
					exit(THC_INCORRECT_PASSWORD);
				}
				passwordErrorCounter--;
				
				if (language == portuguese)	password = getpass("Entre com a senha de usuario :");
				if (language == english)	password = getpass("Enter with user password :");

			} while (thcUserLogin(systemUser,password,data) != THC_OK);
			
			/*Check for system admins*/
			if ((data->group != administrador) && (data->group != userAdmin) && (data->group != ownerAdmin) && (data->group != root))
				group = 4;
			
			
			/*Clear data variable, because we don't need it*/
			memset(data,0x00,sizeof(thcUserDataType));

			/*Save new user group*/	
			data->group = group;

			/*Get the username from CLI*/
			do
			{
				if (language == portuguese)	printf("Entre com o nome do completo do usuario a ser convidado:");
				if (language == english)	printf("Enter with the full name of the invited user:");
				fgets(username,THC_FULL_NAME_MAXIMUM_LENGHT,stdin);
				
				if (username[strlen(username)-1] == '\n')
					username[strlen(username)-1] = '\0';
				
				if (language == portuguese)
				{
					printf("Nome do usuario : \"%s\"\nEmail : %s\nGrupo: %s\n",username,email,groupsArray[group-1][1]);
					printf("Pressione ENTER para confirmar convite, qualquer outra tecla para corrigir");					
				}
				if (language == english)
				{
					printf("User name : %s\nEmail : %s\nGroup: %s\n",username,email,groupsArray[group-1][0]);
					printf("Press ENTER to confirm user invite, any other key to change username");
				}
				
				confirm = fgetc(stdin);
				
				
			} while (confirm != '\n');

			
			strcpy(data->fullName,username);

			/*Check for email*/
			strcpy(data->email,email);

			/*Creating new user*/
			errorCode = thcAddUser(data);
			if (errorCode != THC_OK)
			{
				thcGetTextErrorMessage(language,errorCode);
				exit(errorCode);
			}
			
			errorCode = thcGenerateTextFile();
			if (errorCode != THC_OK)
			{
				thcGetTextErrorMessage(language,errorCode);
				exit(errorCode);
			}
			
			errorCode = thcSendConfirmationMail(username,data->codedPassword,email,data->nickname,language);
			if (errorCode != 0)
				printf("Erro enviando e-mail : %d\n",errorCode);
			free(data);
			thcGetTextErrorMessage(language,THC_OK);
		break; /*invite*/
		
		/*****************************************************Initiate Ncurses interface*****************************************************/
		case 'N':
		case 'n':
			/*Checks for username*/
			if (argv[optind] != NULL)
				strcpy(nickname,argv[optind]);

			/*Check for language subotiopns*/
			argumentIndex = 0;
			while (argumentIndex < argc)
			{
				index = getsubopt (&argv[argumentIndex],tokens,&value);
								
				switch (index)
				{
					
					case LANGUAGE:
						if (strcmp(value,"english") == 0) language = 0;
						if (strcmp(value,"portuguese") == 0) language = 1;
					break;
				}
				
				argumentIndex++;
			}	

			thcRunNcursesInterface(nickname,english);
		break; /*Ncurses*/
		
		/*****************************************************Change user password************************************************/
		case 'P':
		case 'p':
			/*Initiate pointer*/
			data = malloc (sizeof(thcUserDataType));
			if (!data)
				exit (THC_ERROR_INSUFICIENT_MEMORY);
			
			
			/*Checks for suboptions*/
			argumentIndex = 0;
			while (argumentIndex < argc)
			{
				index = getsubopt (&argv[argumentIndex],tokens,&value);
								
				switch (index)
				{
					case LANGUAGE:
						if (strcmp(value,"english") == 0) language = 0;
						if (strcmp(value,"portuguese") == 0) language = 1;
					break;
					
					case USER:
						if (!value)
						{
							thcGetTextErrorMessage(language,THC_INVALID_ARGUMENT);
							exit(THC_INVALID_ARGUMENT);
						}						
						strcpy(systemUser,value);
					break;
					
					case NICKNAME:
						if (!value)
						{
							thcGetTextErrorMessage(language,THC_INVALID_ARGUMENT);
							exit(THC_INVALID_ARGUMENT);
						}
						strcpy(nickname,value);
					break;
					
				}
				argumentIndex++;
			}
		
			/*Check for user name*/
			errorCode = thcSearchUser(systemUser,data);
			if (errorCode != THC_OK)
			{
				thcGetTextErrorMessage(language,errorCode);
				exit(errorCode);				
			}
			
			
			/*User login*/			
			do
			{
				if (passwordErrorCounter == 0)
				{
					thcGetTextErrorMessage(language,THC_INCORRECT_PASSWORD);
					exit(THC_INCORRECT_PASSWORD);
				}
				passwordErrorCounter--;
				
				if (language == portuguese)	password = getpass("Entre com a senha de usuario :");
				if (language == english)	password = getpass("Enter with user password :");

			} while (thcUserLogin(systemUser,password,data) != THC_OK);
			
			
			if (strlen(nickname) != 0)
			{
				if ((data->group != administrador) && (data->group != userAdmin) && (data->group != ownerAdmin) &&(data->group != root))
				{
					thcGetTextErrorMessage(language,THC_PERMISSION_DENIED);
					thcGetTextErrorMessage(language,THC_ERROR_EDIT_NAME);
					exit (THC_PERMISSION_DENIED);
				}
				
				errorCode = thcSearchUser(nickname,data);
				if (errorCode != THC_OK)
				{
					thcGetTextErrorMessage(language,errorCode);				
					exit(errorCode);
				}
			}
			
			/*Data now contais desired user to change password*/
			do
			{
						
				if (language == portuguese)	password = getpass("Entre com a nova senha de usuario :");
				if (language == english)	password = getpass("Enter with new user password :");
				
				strcpy(passwordConfirm,password);
				
				if (language == portuguese)	password = getpass("Confirme a nova senha :");
				if (language == english)	password = getpass("Confirm new user password :");
				
				
			} while (strcmp(password,passwordConfirm) != 0);
			
			strcpy(data->codedPassword,password);
			
			errorCode = thcChangeUserPassword(data);
			if (errorCode != THC_OK)
			{
				thcGetTextErrorMessage(language,errorCode);				
				exit(errorCode);
			}
			
			thcGetTextErrorMessage(language,THC_OK);
		
		break; /*Password*/
		
		
		/*****************************************************Remove user from the system************************************************/
		case 'R':
		case 'r':
			/*Allocates space for data*/
			data = malloc (sizeof(thcUserDataType));
			memset(data,0x00,sizeof(thcUserDataType));	
			
			/*Checks for suboptions*/
			argumentIndex = 0;
			while (argumentIndex < argc)
			{
				index = getsubopt (&argv[argumentIndex],tokens,&value);
								
				switch (index)
				{
					case LANGUAGE:
						if (strcmp(value,"english") == 0) language = 0;
						if (strcmp(value,"portuguese") == 0) language = 1;
					break;
					
					case USER:
						if (!value)
							exit(THC_INVALID_ARGUMENT);
						strcpy(systemUser,value);
					break;
					
					case NICKNAME:
						if(value != NULL)
							strcpy(nickname,value);
					break;		
				}
				
				argumentIndex++;
			}		
			
			/*Test arguments*/
			if (strlen(systemUser) == 0)
			{
				thcGetTextErrorMessage(language,THC_INVALID_ARGUMENT);
				exit (THC_INVALID_ARGUMENT);
			}

			/*ask for password*/
			do
			{
				if (passwordErrorCounter == 0)
				{
					thcGetTextErrorMessage(language,THC_INCORRECT_PASSWORD);
					exit(THC_INCORRECT_PASSWORD);
				}
				passwordErrorCounter--;
				
				if (language == portuguese)	password = getpass("Entre com a senha de usuario :");
				if (language == english)	password = getpass("Enter with user password :");

			} while (thcUserLogin(systemUser,password,data) != THC_OK);
			
			if (strlen(nickname) != 0)
			{
				if ((data->group != administrador) && (data->group != userAdmin) && (data->group != ownerAdmin) &&(data->group != root))
				{
					thcGetTextErrorMessage(language,THC_PERMISSION_DENIED);
					thcGetTextErrorMessage(language,THC_ERROR_EDIT_NAME);
					exit (THC_PERMISSION_DENIED);
				}
				
				errorCode = thcSearchUser(nickname,data);
				if (errorCode != THC_OK)
				{
					thcGetTextErrorMessage(language,errorCode);				
					exit(errorCode);
				}
			}
			
			errorCode = thcRemoveUser(data->nickname);
			if (errorCode != THC_OK)
			{
				thcGetTextErrorMessage(language,errorCode);				
				exit(errorCode);
			}
			free(data);
			thcGetTextErrorMessage(language,THC_OK);
			
		break; /*Remove*/
	
	
		/*****************************************************Initiate system*****************************************************/
		case 'Z':
		case 'z':
			if (getuid() != THC_ADMINISTRATOR_USER_IDENTIFIER)
			{
				thcGetTextErrorMessage(language,THC_PERMISSION_DENIED);
				exit (THC_PERMISSION_DENIED);
			}
			
			data = malloc (sizeof(thcUserDataType));
			if (!data)
				exit (THC_ERROR_INSUFICIENT_MEMORY);
			
			/*Checks for suboptions*/
			argumentIndex = 0;
			while (argumentIndex < argc)
			{
				index = getsubopt (&argv[argumentIndex],tokens,&value);
								
				switch (index)
				{
					case LANGUAGE:
						if (strcmp(value,"english") == 0) language = 0;
						if (strcmp(value,"portuguese") == 0) language = 1;
					break;
					
					case USERNAME:
						if (!value)
							exit(THC_INVALID_ARGUMENT);
						strcpy(username,value);
					break;
					
					case EMAIL:
						if (!value)
							exit(THC_INVALID_ARGUMENT);
						strcpy(email,value);
					break;
					
					case CONFIRMATION:
						if (!value)
							exit(THC_INVALID_ARGUMENT);
						strcpy(confEmail,value);
					break;
				}
				
				argumentIndex++;
			}		
			
			/*Test arguments*/
			if ((strlen(username) == 0) || (strlen(email) == 0) || (strlen(confEmail) == 0))
			{
				thcGetTextErrorMessage(language,THC_INVALID_ARGUMENT);
				exit (THC_INVALID_ARGUMENT);
				
			}
			
			/*Check username lenght*/
			if (strlen(username) < THC_MINUMUM_FULL_NAME_LENGHT)
			{
				thcGetTextErrorMessage(language,THC_INVALID_ARGUMENT);
				exit (THC_INVALID_ARGUMENT);	
			}
			
			strcpy(data->fullName,username);
			
			/*Check for email*/
			if (strlen(email) < THC_EMAIL_MINUMUM_LENGHT)
			{
				thcGetTextErrorMessage(language,THC_INVALID_ARGUMENT);
				exit (THC_INVALID_ARGUMENT);	
			}
			if (strcmp(email,confEmail) != 0)
			{
				thcGetTextErrorMessage(language,THC_INVALID_ARGUMENT);
				exit (THC_INVALID_ARGUMENT);	
			}
			
			strcpy(data->email,email);
			
			/*Adds root as nickname*/
			strcpy(data->nickname,"root");
			
			data->group = root;
			data->flag = ok;
			
			errorCode = thcAddUser(data);
			if (errorCode != THC_OK)
			{
				thcGetTextErrorMessage(language,errorCode);
				exit (errorCode);
			}
			
			free(data);
			
			thcGetTextErrorMessage(language,THC_OK);
			
		break;
	
	}/*switch option*/
	

	return THC_OK;
}