/*                                            
 * Universidade Federal do Rio de Janeiro     
 * Escola Politecnica                         
 * Departamento de Eletronica e de Computacao 
 * EEL270 - Computacao II - Turma 2012/2      
 * Prof. Marcelo Luiz Drumond Lanza           
 * Autor Joao Vitor Ferreira Duarte           
 *                                      
 */                                           
                                              
#include <stdlib.h>                           
#include <stdio.h>                            
                                              
#include "thcConst.h"                       
#include "thcTypes.h"                       
#include "thcError.h"                       
#include "thcFunctions.h"                   
                                              
#include "thcShowCliHelp.h"                          
                                              
               
       
void thcShowCliHelp (thcLanguageType language)
{
		
	if (language == english)
	{
		printf("Tree High CloudDropper v4.2.0 \n");
		printf("\n");
		printf("Usage : thc [OPTION...] (SUBOPTIONS...)\n");
		printf("\n");
		printf("-a | --add : Add a user to a group                                                      \n");
		printf("             usage : -a user=<username> [nickname=<user to include in selected group>]  \n");
		printf("                      group=administrators|owners|users [language=english|portuguese]   \n");
		printf("             This function will add a user to a selected group, only admins can do this \n");
		printf("             changes, you can either cange your group or another user's group           \n");
		printf("             e.g. : If the user is an owner and add to admin it will be owner & admin   \n");
		printf("                    after this changes                                                  \n");
		printf("                                                                                        \n");
		printf("-e | --edit  : Edit a username                                                          \n");		
		printf("               usage: -e user=<user using the system> [nickname=<user to change name]   \n");
		printf("		              username=<new name> [language=english|portuguese]                 \n");
		printf("               This function will change the username from selected user, note: only    \n");
		printf("               system admins can change another user's name                             \n");
		printf("                                                                                        \n");
		printf("-g | --group : Change user group                                                        \n");
		printf("               usage : -g user=<username> [nickname=<user to change to selected group>] \n");
		printf("                      group=administrators|owners|users [language=english|portuguese]   \n");
		printf("             This function will change a user to another group, only admins can use this\n");
		printf("             function                                                                   \n");
		printf("             e.g. : If the user is an owner & user and you change it to admin it will be\n");
		printf("                    only an admin                                                       \n");
		printf("                                                                                        \n");
		printf("-h | --help : Show this screen                                                          \n");
		printf("              usage: -h  [language=english|portuguese]                                  \n");
		printf("              This functions will show this screen on the select language               \n");
		printf("                                                                                        \n");
		printf("-i | --invite : Invite a new user                                                       \n");
		printf("                usage : -i user=<user using the system> email=<invite email>            \n");
		printf("                        confirmation=<confir invite email> group=administrators|owners|users\n");
		printf("                        [language=english|portuguese]                                   \n");
		printf("                This function invites a user for the system, it will ask the name of the\n");
		printf("                invited person, and will send an email to <email> with your name to join\n");
		printf("                the system. The person will receive a nickname and a temporary password \n");
		printf("                if a normal user invite someone, he will be in the users groups, only   \n");
		printf("                admins can invite a user to another group                               \n");
		printf("                                                                                        \n");
		printf("-n | --ncurses : Start NCurses interface of the program                                 \n");
		printf("                 usage : -n [user=<username>] [language=english|portuguese]             \n");
		printf("                 This function will start the system on a more friendly interface       \n");
		printf("                 if the function don't receive username it will ask via command line    \n");
		printf("                 You can do everthing via this interface                                \n");
		printf("                                                                                        \n");
		printf("-p | --password : Change user password                                                  \n");
		printf("                  usage : -p user=<username> [nickname=<user to change password>]       \n");
		printf("                           [language=english|portuguese]                                \n");
		printf("                  This function will ask you a new password via command line and it     \n");
		printf("                  will change it in the system, an admin can change another user's      \n");
		printf("                  password                                                              \n");
		printf("                                                                                        \n");
		printf("-r | --remove : Removes a user or yourself from the system                              \n");
		printf("                usage : -r user=<username> [nickname=<nickname from user to remove>]    \n");
		printf("                           [language=english|portuguese]                                \n");
		printf("                This function removes a user data from the system, only an admin can    \n");
		printf("                remove data from another user, if nickname field is blank the user will \n");
		printf("                remove himself                                                          \n");
		printf("                                                                                        \n");
		printf("-z | --initialize : Initialize the system creating a root user and initial users file   \n");
		printf("                    usage : -z username=<Admin's full name> email=<Admin's email>       \n");
		printf("                             confirmation=<confirm e-mail> [language=english|portuguese]\n");
		printf("                    This functions initiates the system creating the root user and the  \n");
		printf("                    users file. This function can only be used in the system admin's    \n");
		printf("                    user account                                                        \n");
	}
	
	if (language == portuguese)
	{
		printf("Tree High CloudDropper v4.2.0 \n");
		printf("\n");
		printf("Uso : thc [OPCAO...] (SUBOPCOES...)\n");
		printf("\n");
		printf("-a | --add : Adiciona um usuario a um grupo                                             \n");
		printf("             usage : -a user=<usuário> [nickname=<usuario a ser incluido no grupo]      \n");
		printf("                      group=administrators|owners|users [language=english|portuguese]   \n");
		printf("             Essa funcao ira adicionar um usuario ao grupo selecionado, apenas admins   \n");
		printf("             podem fazer essa mudanca, voce pode alterar o proprio grupo ou o grupo de  \n");
		printf("             outro usuario                                                              \n");
		printf("             ex: se o usuario esta no grupo de proprietarios e adicionar ele ao grupo   \n");
		printf("                 de administradores, ele sera um proprietario & administrador           \n");
		printf("                                                                                        \n");
		printf("-e | --edit  : Edita o nome de um usuario                                               \n");		
		printf("               usage: -e user=<usuario> [nickname=<usario que tera o nome alterado]     \n");
		printf("		              username=<novo nome> [language=english|portuguese]                \n");
		printf("               Essa funcao ira alterar o nome de um usuario e ira gerar um novo username\n");
		printf("               correspondente ao seu nome, apenas administradores podem trocar o nome   \n");
		printf("               de outro usuario                                                         \n");
		printf("                                                                                        \n");
		printf("-g | --group : Trocar grupo de um usuario                                               \n");
		printf("               usage : -g user=<usuário> [nickname=<usuario a ter seu grupo alterado>]  \n");
		printf("                      group=administrators|owners|users [language=english|portuguese]   \n");
		printf("             Essa funcao ira alterar o grupo do usuario ou de outro usuario para o grupo\n");
		printf("             selecionado, apenas administradores podem executar essa funcao             \n");
		printf("             ex: Se o usuario é um proprietario e usuario e for trocado para admin ele  \n");
		printf("                 sera apenas admin.                                                     \n");
		printf("                                                                                        \n");
		printf("-h | --help : Mostra essa tela                                                          \n");
		printf("              usage: -h  [language=english|portuguese]                                  \n");
		printf("              Essa funcao ira mostrar esta tela no idioma selecionado                   \n");
		printf("                                                                                        \n");
		printf("-i | --invite : Convida um novo usuario                                                 \n");
		printf("                usage : -i user=<usuario> email=<email do convite>                      \n");
		printf("                        confirmation=<confirmacao do email> group=administrators|owners|users\n");
		printf("                        [language=english|portuguese]                                   \n");
		printf("                Essa funcao convida um usuario para o systema, ela ira perguntar o nome \n");
		printf("                completo da pessoa a ser convidada e ira enviar um email para o email   \n");
		printf("                dado contento os dados de nome de usuario e senha temporaria para que o \n");
		printf("                usuario possa utilizar o sistema                                        \n");
		printf("                Se um usuario normal convidar alguem, ele sera do grupo \"users\" apenas\n");
		printf("                administradores podem convidar para outro grupo                         \n");
		printf("                                                                                        \n");
		printf("-n | --ncurses : Inicia a interface NCurses do programa                                 \n");
		printf("                 usage : -n [user=<ususario>] [language=english|portuguese]             \n");
		printf("                 Essa funcao ira iniciar uma interface mais amigavel do sistema         \n");
		printf("                 Se a funcao nao receber o nome de usuario, ela ira perguntar via linha \n");
		printf("                 de comando, essa interface possui todas as funcoes implementadas       \n");
		printf("                                                                                        \n");
		printf("-p | --password : Troca a senha do usuario                                              \n");
		printf("                  usage : -p user=<usuario> [nickname=<usuario q tera senha alterada>]  \n");
		printf("                           [language=english|portuguese]                                \n");
		printf("                  Essa funcao ira pedir uma nova senha via linha de comando e ira trocar\n");
		printf("                  a senha no sistema para essa nova, apenas um admin pode alterar a     \n");
		printf("                  senha de outro usuario                                                \n");
		printf("                                                                                        \n");
		printf("-r | --remove : Remove voce mesmo ou outro usuario do sistema                           \n");
		printf("                usage : -r user=<usuario> [nickname=<usuario a ser removido>]           \n");
		printf("                           [language=english|portuguese]                                \n");
		printf("                Essa funcao remove os dados de usuario do sistema, apenas um admin pode \n");
		printf("                remover outro usuario, se o campo nickname estiver vazio, o usuario ira \n");
		printf("                se remover do sistema                                                   \n");
		printf("                                                                                        \n");
		printf("-z | --initialize : Inicia o sistema creando o root e arquivo inicial de usuarios       \n");
		printf("                    usage : -z username=<nome completo> email=<email>                   \n");
		printf("                             confirmation=<confirmacao de email> [language=english|portuguese]\n");
		printf("                    Essa funcao inicia o sistema criando um usuario root e o arquivo de \n");
		printf("                    dados de usuario. Essa funcao so pode ser usada a partir da conta do\n");
		printf("                    administrador do sistema                                            \n");
	
	}
	
	
}                                       
                                              
