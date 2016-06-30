/*                                            
 * Universidade Federal do Rio de Janeiro     
 * Escola Politecnica                         
 * Departamento de Eletronica e de Computacao 
 * EEL270 - Computacao II - Turma 2012/2      
 * Prof. Marcelo Luiz Drumond Lanza           
 * Autor Joao Vitor Ferreira Duarte           
 *                                            
 *                                      
 */                                           
                                              
#include <stdlib.h>                           
#include <stdio.h>                            
#include <ncurses.h> 
#include <string.h>
                                              
#include "thcConst.h"                       
#include "thcTypes.h"                       
#include "thcError.h"                       
#include "thcFunctions.h"                   
                                              
#include "thcShowNcursesHelp.h"                          
     
void thcShowNcursesHelp(thcLanguageType language)           
{
	char *systemName="Tree High CloudDropper v4.2.0";
	
	
	
	if (language == english)
	{		
		mvprintw(0, COLS/2 - strlen(systemName), "%s\n",systemName);
		printw("Help session :                                                                                    \n");
		printw("Invite user : invite a friend to join the system as an user, sends him an e-mail with his password\n");
		printw("Change e-mail : begins change e-mail process for selected user                                    \n");
		printw("Change username : change the username and generates a new nickname in the format name.lastname    \n");
		printw("Show help : Show this help screen                                                                 \n");
		printw("\nadmin only :                                                                                      \n");
		printw(">Change group / Add to Group : this will change the selected user's group or add to a new group   \n");
		printw("                               so he would have functions from both groups                        \n");


	}
	
	if (language == portuguese)
	{		
		mvprintw(0, COLS/2 - strlen(systemName), "%s\n",systemName);
		printw("Ajuda :                                                                                    \n");
		printw("Convidar usuario : convida um amigo para participar do sistema como um usuario e envia um e-mail com sua senha temporaria\n");
		printw("Trocar e-mail : inicia o processo de troca de e-mail para o usuario nao selecionado              \n");
		printw("Trocar nome  : troca o nome de usuario e gera um nickname correspondente no formato padrao do sistema\n");
		printw("Mostrar ajuda : Mostrar essa tela de ajuda                                                            \n");
		printw("\nfuncoes de administrador                                                                          \n");
		printw(">Change group / Add to Group : this will change the selected user's group or add to a new group   \n");
		printw("                               so he would have functions from both groups                        \n");


	}
	
	getch();
	move(0,0);
	clrtobot();
}

                                                                                                         
