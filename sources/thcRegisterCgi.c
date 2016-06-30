/*
 * Universidade Federal do Rio de Janeiro
 * Escola Politecnica
 * Departamento de Eletronica e de Computacao
 *
 * Prof. Marcelo Luiz Drumond Lanza
 * EEL310 - Computacao II - Turma 3112/2
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
	{"Registration completed","Cadastro efetuado com sucesso"},
	{"You will receive an e-mail with confirmation data","Você receberá um e-mail com as informações de login"}	
};

int main (int argc, char **argv)
{
	thcUserDataType data;
	environmentType enviro;
	thcErrorType errorCode;
	thcLanguageType language;
	char username[THC_FULL_NAME_MAXIMUM_LENGHT+1];
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
	
	errorCode = mlCgiGetFormStringNoNewLines ("thcFullname", username, THC_FULL_NAME_MAXIMUM_LENGHT);
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
	
	if ((strlen(email) == 0) || (strlen(username) == 0 ))
	{
		printf("Campos vazios");
		exit(THC_OK);	
		
	}
        
 	data.group = user;	
	strcpy(data.email,email);
	strcpy(data.fullName,username);
	errorCode = thcAddUser(&data);
	if (errorCode != THC_OK)
	{
		printf("Erro numero : %d",errorCode);
		exit(THC_OK);
	}
	errorCode = thcGenerateTextFile();
	if (errorCode != THC_OK)
	{
		printf("Erro numero : %d",errorCode);
		exit(THC_OK);
	}
	
	errorCode = thcSendConfirmationMail(username,data.codedPassword,email,data.nickname,language);
	if (errorCode != THC_OK)
	{
		printf("Erro numero : %d",errorCode);
		exit(THC_OK);
	}
	
	
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