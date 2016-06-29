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
 * $Log: thcShowHelpCgi.c,v $
 * Revision 1.1  2013/04/06 18:55:09  joao.duarte
 * Initial revision
 *
 * Revision 1.1  2013/03/21 23:15:27  joao.duarte
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
#include "thcConfig.h"
                   
#include "mlcgi.h"
                

                                              
int main (int argc, char **argv)
{
	environmentType enviro;
	thcErrorType errorCode;
	thcLanguageType language = english;
	char languageString[THC_LANGUAGE_MAXIMUM_LENGHT + 1];
	
		
	if (mlCgiInitialize (&enviro))
		exit (THC_OK);

	if (enviro == commandLine)
	{
		thcGetTextErrorMessage(language,THC_ERROR_INVALID_INTERFACE);
		mlCgiFreeResources();
		exit (THC_OK);
	}
	
	/*Start header*/
	mlCgiBeginHttpHeader("text/html");
	mlCgiEndHttpHeader();

	errorCode = mlCgiGetFormStringNoNewLines ("thcLanguage",languageString,THC_LANGUAGE_MAXIMUM_LENGHT);
	if (errorCode != ML_CGI_OK)
	{
		mlCgiEndHttpHeader ();
		thcGetHtmlErrorMessage(language,THC_ERROR_ON_WEB_FORM);
		mlCgiFreeResources();
		exit(THC_OK);
	}
	
	if (strcmp(languageString,"en") == 0 ) language = english;
	if (strcmp(languageString,"br") == 0 ) language = portuguese;

	if (language == english)
	{
		thcWebShowHeader();
		
		printf("<body>                                                                                  \n");
		printf("    <h1><center>Tree High CloudDropper </center></h1><br>                               \n");
		printf("    <h2><center>V 4.2.0</center></h2><br>                                               \n");
		printf("    Help Session:<br>                                                                   \n");
		printf("    &nbsp;&nbsp;&nbsp;&nbsp;Invite User: <br>                                           \n");
		printf("    &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;->This will invite a new user to join the system, he will receive an e-mail with login and temporary password to be able to use the system<br><br>\n");
		printf("                                                                                        \n");
		printf("    &nbsp;&nbsp;&nbsp;&nbsp;Change Passowrd: <br>\n");
		printf("    &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;->This will change your password to a new one<br><br>\n");
		printf("                                                                                        \n");
		printf("    &nbsp;&nbsp;&nbsp;&nbsp;Change e-mail: <br>                                    \n");
		printf("    &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;->This will change your e-mail, you will receive a confirmation e-mail to the new adress and a cancel e-mail to the old adress<br><br>\n");
		printf("                                                                                        \n");
		printf("    &nbsp;&nbsp;&nbsp;&nbsp;Change Username: <br>                      \n");
		printf("    &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;->This will change your username and generate a new nickname based on the new name<br><br>\n");
		printf("                                                                                        \n");
		printf("    &nbsp;&nbsp;&nbsp;&nbsp;Change User group (admin only): <br>   \n");
		printf("    &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;->This will change a selected user to the selected group <br><br>\n");
		printf("                                                                                        \n");
		printf("    &nbsp;&nbsp;&nbsp;&nbsp;Add User to group (admin only): <br>             \n");
		printf("    &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;->This will add a user to a selected group, e.g. if the he is a user and you add to owner group he will be user & owner<br><br>\n");
		printf("                                                                                        \n");
		printf("    &nbsp;&nbsp;&nbsp;&nbsp;Remove Account<br>                                         \n");
		printf("    &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;->This will remove a user account from the system and will delete all of his data<br><br>\n");
		printf("                                                                                        \n");
		printf("    &nbsp;&nbsp;&nbsp;&nbsp;Help: <br>                                           \n");
		printf("    &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;->Show this very informative screen in the selected language<br><br>\n");
		printf("                                                                                        \n");
		printf("    &nbsp;&nbsp;&nbsp;&nbsp;Contact: <br>                                           \n");
		printf("    &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;->Send an e-mail to sistem admin<br><br>\n");
		printf("                                                                                        \n");
		printf("    &nbsp;&nbsp;&nbsp;&nbsp;Logout: <br>                                           \n");
		printf("    &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;->Finish user session and return to initial screen<br><br>\n");
		printf("                                                                                        \n");
		printf("</body>");
	}
	
	if (language == portuguese)
	{
		thcWebShowHeader();
		
		printf("<body>                                                                                  \n");
		printf("    <h1><center>Tree High CloudDropper </center></h1><br>                               \n");
		printf("    <h2><center>V 4.2.0</center></h2><br>                                               \n");
		printf("    Sessão de ajuda :<br>                                                  \n");
		printf("    &nbsp;&nbsp;&nbsp;&nbsp;Convidar um amigo: <br>                                  \n");
		printf("    &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;->Essa opção convida um novo usuario para entrar no sistema, ele irá receber um e-mail de confirmação com o login e a senha temporária<br><br>\n");
		printf("                                                                                        \n");
		printf("    &nbsp;&nbsp;&nbsp;&nbsp;Trocar Senha: <br>\n");
		printf("    &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;->Essa opção troca a senha do usuário por uma nova<br><br>\n");
		printf("                                                                                        \n");
		printf("    &nbsp;&nbsp;&nbsp;&nbsp;Trocar e-mail: <br>                                    \n");
		printf("    &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;->Essa opção muda seu e-mail, você receberá um e-mail de confirmação no endereço novo e um e-mail para cancelar operação no endereço antigo<br><br>\n");
		printf("                                                                                        \n");
		printf("    &nbsp;&nbsp;&nbsp;&nbsp;Alterar Nome: <br>                      \n");
		printf("    &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;->Essa função altera o nome de um usuário e gera um novo nickname baseado no novo nome<br><br>\n");
		printf("                                                                                        \n");
		printf("    &nbsp;&nbsp;&nbsp;&nbsp;Trocar Grupo de Usuário (apenas administradores): <br>   \n");
		printf("    &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;->Essa opção troca um usuário para o grupo selecionado<br><br>\n");
		printf("                                                                                        \n");
		printf("    &nbsp;&nbsp;&nbsp;&nbsp;Adicionar Usuario ao Grupo (apenas administradores): <br>             \n");
		printf("    &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;->Essa opção ira adicionar um usuário ao grupo selecionado, ex: caso ele seja usuario e seja adicionado ao grupo de proprietários, ele exercerá ambas as funções<br><br>\n");
		printf("                                                                                        \n");
		printf("    &nbsp;&nbsp;&nbsp;&nbsp;Remover Conta<br>                                         \n");
		printf("    &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;->Essa opção irá remover um usuário e todos os seu dados do sistema<br><br>\n");
		printf("                                                                                        \n");
		printf("    &nbsp;&nbsp;&nbsp;&nbsp;Ajuda: <br>                                           \n");
		printf("    &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;->Exibe essa tela super informativa<br><br>\n");
		printf("                                                                                        \n");
		printf("    &nbsp;&nbsp;&nbsp;&nbsp;Contato: <br>                                           \n");
		printf("    &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;->Envia um e-mail para o administrador do sistema<br><br>\n");
		printf("                                                                                        \n");
		printf("    &nbsp;&nbsp;&nbsp;&nbsp;Sair: <br>                                           \n");
		printf("    &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;->Finaliza a sessão e volta para a página inicial<br><br>\n");
		printf("                                                                                        \n");
		printf("</body>");

	}
	return THC_OK;
}
                                              
                                              
                                              
                                              
                                              
/*$RCSfile: thcShowHelpCgi.c,v $*/                                  
