/*                                            
 * Universidade Federal do Rio de Janeiro     
 * Escola Politecnica                         
 * Departamento de Eletronica e de Computacao 
 * EEL270 - Computacao II - Turma 2012/2      
 * Prof. Marcelo Luiz Drumond Lanza           
 * Autor Joao Vitor Ferreira Duarte           
 *                                            
 * $Author: joao.duarte $                                   
 * $Date: 2013/04/06 18:55:09 $                                     
 * $Log: thcCgiShowResetPasswordForm.c,v $
 * Revision 1.1  2013/04/06 18:55:09  joao.duarte
 * Initial revision
 *
 *                                      
 */                                           
                                              
#include <stdlib.h>                           
#include <stdio.h>                            
#include <string.h>
                                              
#include "thcConst.h"                       
#include "thcTypes.h"                       
#include "thcError.h"                       
#include "thcFunctions.h"                   
                                                                       
#include "mlcgi.h"

char *text [][2]=
{
	{"Enter with your username : ","Entre com o nome de usuário :"},
	{"Enter with your e-mail :","Entre com o seu e-mail :"},	
	{"Confirm your e-mail :","Confirme seu e-mail :"},	
	{"en","br"}
};

int main (int argc, char **argv)
{                          
	environmentType enviro;
	thcErrorType errorCode;
	thcLanguageType language;
	char lang[THC_LANGUAGE_MAXIMUM_LENGHT+1];
	
		
	if (mlCgiInitialize (&enviro))
		exit (THC_OK);

	if (enviro == commandLine)
	{
		printf ("Isso é uma CGI seu imbecil !\n");
		exit (THC_OK);
	}

	mlCgiBeginHttpHeader("text/html");
	mlCgiEndHttpHeader();
	
	errorCode = mlCgiGetFormStringNoNewLines("thcLanguage",lang,THC_LANGUAGE_MAXIMUM_LENGHT);
	if (errorCode != ML_CGI_OK)
	{
		printf("Erro, run to the hills\n");
		mlCgiFreeResources();
		exit(THC_OK);
	}
	
	if (strcmp(lang,"en") == 0) language = english;
	if (strcmp(lang,"br") == 0) language = portuguese;

	                    
	thcWebShowHeader();
	
	printf("                                                                                                            \n");
	printf("<body>                                                                                                      \n");
	printf("	<ul class='table'>                                                                                      \n");
	printf("	<form action=\"thcResetPassword.cgi\" method=\"post\">                                                  \n");
	printf("       %s            <br><INPUT TYPE=\"text\" NAME=\"thcNickname\" SIZE=\"25\" MAXLENGTH='100'><br>         \n",text[0][language]);
	printf("       %s      <br><INPUT TYPE=\"text\" NAME=\"thcEmail\" SIZE=\"25\" MAXLENGTH=\"100\"><br>                \n",text[1][language]);
	printf("       %s      <br><INPUT TYPE=\"text\" NAME=\"thcConfirm\" SIZE=\"25\" MAXLENGTH=\"100\"><br>              \n",text[2][language]);
	printf("			<input type = \"hidden\" name='thcLanguage' value='%s'>                                         \n",text[3][language]);
	printf("			<input type = \"submit\" value = \"enviar\">                                                    \n");
	printf("	</form><br><br><br>                                                                                     \n");
	printf("    </ul>                                                                                                   \n");
	printf(" </body>                                                                                                    \n");	
	
	thcWebShowFooter();
	
	mlCgiFreeResources();
	
	return THC_OK;
 
}                                             
/*$RCSfile: thcCgiShowResetPasswordForm.c,v $*/                                  
