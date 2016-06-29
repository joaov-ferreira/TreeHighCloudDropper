/*
 * Universidade Federal do Rio de Janeiro
 * Escola Politecnica
 * Departamento de Eletronica e de Computacao
 *
 * Prof. Marcelo Luiz Drumond Lanza
 * EEL310 - Computacao II - Turma 3112/2
 *
 * $Author: joao.duarte $
 * $Date: 2013/04/06 18:55:09 $
 * $Log: thcResetPasswordCgi.c,v $
 * Revision 1.1  2013/04/06 18:55:09  joao.duarte
 * Initial revision
 *
 * Revision 1.1  2013/03/20 23:05:16  joao.duarte
 * Initial revision
 *
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "thcFunctions.h"
#include "thcConst.h"
#include "thcError.h"
#include "thcTypes.h"
#include "thcAddUser.h"

#include "mlcgi.h"

char *menssages[][2]=
{
	{"Password reseted","Senha resetada"},
	{"You will receive an e-mail with temporary password","Você receberá um e-mail com a senha temporária"}	
};

int main (int argc, char **argv)
{
	thcUserDataType data;
	environmentType enviro;
	thcErrorType errorCode;
	thcLanguageType language;
	char nickname[THC_NICKNAME_MAXIMUM_LENGHT+1];
	char email   [THC_EMAIL_MAXIMUM_LENGHT+1];
	char confirm [THC_EMAIL_MAXIMUM_LENGHT+1];
	char languageString[THC_LANGUAGE_MAXIMUM_LENGHT+1];

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
	
	errorCode = mlCgiGetFormStringNoNewLines ("thcNickname", nickname, THC_FULL_NAME_MAXIMUM_LENGHT);
	if (errorCode != ML_CGI_OK)
	{
		printf("Error username %d",errorCode);
		mlCgiFreeResources();
		exit(THC_OK);
	}
	
	errorCode = mlCgiGetFormStringNoNewLines ("thcEmail", email, THC_EMAIL_MAXIMUM_LENGHT);
	if (errorCode != ML_CGI_OK)
	{
		printf("Error email %d",errorCode);
		mlCgiFreeResources();
		exit(THC_OK);
	}

	errorCode = mlCgiGetFormStringNoNewLines ("thcConfirm", confirm, THC_EMAIL_MAXIMUM_LENGHT);
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
	
	/*Check for e-mail*/
	if (strcmp(email,confirm) != 0)
	{
		printf("E-mails incorretos<br>");
		printf("Pressione voltar no seu navegador pq eu to com preguiça de fazer isso por vc ¬¬");
		exit(THC_OK);
		
	}
	
	if ((strlen(email) == 0) || (strlen(nickname) == 0 ))
	{
		printf("Campos vazios");
		exit(THC_OK);	
		
	}
    
    /*Check for valid e-mail*/
    errorCode = thcSearchUser(nickname,&data);
    if (errorCode != THC_OK)
	{
		printf("Error #%d",errorCode);
		mlCgiFreeResources();
		exit(THC_OK);		
	}
    
    if (strcmp(data.email,email) != 0)
    {
		printf("Email incorreto<br>");
		mlCgiFreeResources();
		exit(THC_OK);		
	}
        
	/*Reset user password*/   
 	errorCode = thcResetPassword(nickname,language);
	if (errorCode != THC_OK)
	{
		printf("Erro #%d",errorCode);
		mlCgiFreeResources();
		exit(THC_OK);		
	}
	
	
	/*Show confirmation*/
	
	thcWebShowHeader();
	
	printf("<body>                                         \n");
	printf("<div class='content'>                          \n");
	printf("                                               \n");
	printf("%s<br>                                         \n",menssages[0][language]);
	printf("%s<br>                                         \n",menssages[1][language]);
	printf("</div>                                         \n");
	printf("                                               \n");


	
	thcWebShowFooter();

	mlCgiFreeResources();
	return THC_OK;
}
