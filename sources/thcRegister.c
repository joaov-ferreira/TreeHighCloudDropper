/*
 * Universidade Federal do Rio de Janeiro
 * Escola Politecnica
 * Departamento de Eletronica e de Computacao
 *
 * Prof. Marcelo Luiz Drumond Lanza
 * EEL310 - Computacao II - Turma 3112/2
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



int main (int argc, char **argv)
{
	thcUserDataType data;
	environmentType enviro;
	thcErrorType errorCode;
	char username[THC_FULL_NAME_MAXIMUM_LENGHT+1];
	char email   [THC_EMAIL_MAXIMUM_LENGHT+1];
	char confirm [THC_EMAIL_MAXIMUM_LENGHT+1];

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
	
	mlCgiGetFormStringNoNewLines ("thcFullname", username, THC_FULL_NAME_MAXIMUM_LENGHT);
	mlCgiGetFormStringNoNewLines ("thcEmail", email, THC_EMAIL_MAXIMUM_LENGHT);
	mlCgiGetFormStringNoNewLines ("thcConfirm", confirm, THC_EMAIL_MAXIMUM_LENGHT);
	
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
	errorCode = thcSendConfirmationMail(username,data.codedPassword,email,data.nickname);
	if (errorCode != THC_OK)
	{
		printf("Erro numero : %d",errorCode);
		exit(THC_OK);
	}
	
	
	printf("Cadastrado com sucesso<br>");
	printf("Dados enviados para o e-mail<br>");

	
	return THC_OK;
}
