/*
 * Universidade Federal do Rio de Janeiro
 * Escola Politecnica
 * Departamento de Eletronica e de Computacao
 *
 * Prof. Marcelo Luiz Drumond Lanza
 * EEL310 - Computacao II - Turma 2012/2
 * Autor Joao Vitor Ferreira Duarte 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "thcFunctions.h"
#include "thcConst.h"
#include "thcError.h"
#include "thcTypes.h"
#include "thcDenyNewUserEmail.h"

#include "mlcgi.h"

char *menssages[][2]=
{
	{"Successfully denied new e-mail","Mudança de e-mail rejeitada com sucesso"},
	{"Click here to return","Clique aqui para retornar"}	
};

int main (int argc, char **argv)
{
	thcUserDataType data;
	environmentType enviro;
	thcErrorType errorCode;
	thcLanguageType language;
	char nickname[THC_NICKNAME_MAXIMUM_LENGHT+1];
	char code [THC_COOKIE_CONTENT_LENGHT+1];
	char languageString[THC_LANGUAGE_MAXIMUM_LENGHT+1];
	

	/*Clears trash from data*/
	memset(&data,0x00,sizeof(thcUserDataType));

	if (mlCgiInitialize (&enviro))
		exit (THC_OK);

	if (enviro == commandLine) /* programa executado via CLI */
	{
		printf ("Este programa so pode ser executado via web\n");
		exit (THC_OK);
	}

	/* programa executado via web */
	mlCgiBeginHttpHeader ("text/html");
	/* mlCgiBeginHttpHeader (NULL); */
	mlCgiEndHttpHeader ();
	
	
	errorCode = mlCgiGetFormStringNoNewLines ("thcNickname", nickname, THC_NICKNAME_MAXIMUM_LENGHT);
	if (errorCode != ML_CGI_OK)
	{
		printf("Error confimation %d",errorCode);
		mlCgiFreeResources();
		exit(THC_OK);
	}

	errorCode = mlCgiGetFormStringNoNewLines ("thcConfirmationCode", code, THC_COOKIE_CONTENT_LENGHT);
	if (errorCode != ML_CGI_OK)
	{
		printf("Error confimation %d",errorCode);
		mlCgiFreeResources();
		exit(THC_OK);
	}

	errorCode = mlCgiGetFormStringNoNewLines ("thcLanguage",languageString,THC_LANGUAGE_MAXIMUM_LENGHT);
	if (errorCode != ML_CGI_OK)
	{
		mlCgiEndHttpHeader ();
		printf("Erro idioma\n");
		mlCgiFreeResources ();
		exit(THC_OK);		
	}
	
	if (strcmp(languageString,"br") == 0) language = portuguese;
	if (strcmp(languageString,"en") == 0) language = english;
	
	
    
    errorCode = thcSearchUser(nickname,&data);
    if (errorCode != THC_OK)
    {
		printf("Error %d",errorCode);
		mlCgiFreeResources();
		exit (THC_OK);
	}
 
    
    /*Check for valid code*/
	errorCode = thcConfirmEmailCode(data.UID, code);
	if (errorCode != THC_OK)
	{
		mlCgiEndHttpHeader ();
		printf("Codigo errado (?)\n");
		mlCgiFreeResources ();
		exit(THC_OK);		
	}
    
    thcDenyNewUserEmail(data.UID, NULL);
    if (errorCode != THC_OK)
	{
		mlCgiEndHttpHeader ();
		printf("erro %d\n",errorCode);
		mlCgiFreeResources ();
		exit(THC_OK);		
	}
    

	thcWebShowHeader();
	
	printf("<body>                                         \n");
	printf("<div class='content'>                          \n");
	printf("                                               \n");
	printf("%s<br>                                         \n",menssages[0][language]);
	printf("<a href='thcHome.cgi'>%s</a>                   \n",menssages[1][language]);
	printf("</div>                                         \n");
	printf("                                               \n");


	
	thcWebShowFooter();

	mlCgiFreeResources();
	return THC_OK;
}