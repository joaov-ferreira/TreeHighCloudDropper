/*
 * Universidade Federal do Rio de Janeiro
 * Escola Politecnica
 * Departamento de Eletronica e de Computacao
 *
 * Prof. Marcelo Luiz Drumond Lanza
 * EEL310 - Computacao II - Turma 3112/2
 *
 * $Author: joao.duarte $
 * $Date: 2013/03/20 23:05:16 $
 * $Log: thcLogin.c,v $
 * Revision 1.1  2013/03/20 23:05:16  joao.duarte
 * Initial revision
 *
 *
 */

#include <stdio.h>
#include <stdlib.h>

#include "mlcgi.h"
#include "thcTypes.h"
#include "thcFunctions.h"
#include "thcError.h"



int main (int argc, char **argv)
{
	environmentType enviro;
	thcUserDataType data;            
	char username [THC_NICKNAME_MAXIMUM_LENGHT + 1];
	char password [THC_PASSWORD_MAXIMUM_LENGHT + 1];
	thcErrorType errorCode;

	if (mlCgiInitialize (&enviro))
		exit (ML_CGI_OK);

	if (enviro == commandLine) /* programa executado via CLI */
	{
		printf ("Este programa so pode ser executado via web\n");
		exit (THC_OK);
	}

	/* programa executado via web */
	mlCgiBeginHttpHeader ("text/html");
	/* mlCgiBeginHttpHeader (NULL); */
	mlCgiEndHttpHeader ();

	mlCgiGetFormStringNoNewLines ("xyzUsername", username, THC_NICKNAME_MAXIMUM_LENGHT);
	mlCgiGetFormStringNoNewLines ("xyzPassword", password, THC_PASSWORD_MAXIMUM_LENGHT);

	
	
	errorCode = thcUserLogin(username,password,&data);
	if (errorCode == 0)
	{
		printf("<html>												  \n");			
//		mlCgiSetCookie(data.nickname, "1234567890abcdefghijklmnopqrstuvwxyz", 300, NULL, NULL, NULL);
		printf("<head>                                                \n");
		printf("  <title>Tree High CloudDropper</title>               \n");
		printf("</head>                                               \n");
		printf("<body>                                                \n");
		printf("<h1>Logado com sucesso</h1>                           \n");
		printf("<p>Nome Completo : %s<br>                             \n",data.fullName);
		printf("Email : %s <br>                                       \n",data.email);
		printf("Você tem 0 amigos :(                                  \n");
		printf("</body>                                               \n");
		printf("</html>");
		
	}
	if (errorCode == THC_INCORRECT_PASSWORD)
	{
		printf("<head>                                                ");
		printf("<title>Tree High CloudDropper</title> ");
		printf("</head>                                               ");
		printf("<body>                                                ");
		printf("<h1>Senha Incorreta</h1>                           ");
		printf("Nickname : %s <br>",username);
		printf("Senha : \"%s\"  <br> ",password);
		printf("</body>                                               ");
		
	
	}	
	if (errorCode == THC_ERROR_USERNAME_NOT_FOUND)
	{
		printf("<head>                                                ");
		printf("<title>Tree High CloudDropper</title>");
		printf("</head>                                               ");
		printf("<body>                                                ");
		printf("<h1>Usuário Incorreto</h1>                            ");
		printf("</body>                                               ");			
	}		
	
	

	mlCgiFreeResources ();
	return THC_OK;
}
