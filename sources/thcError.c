/*                                            
 * Universidade Federal do Rio de Janeiro     
 * Escola Politecnica                         
 * Departamento de Eletronica e de Computacao 
 * EEL270 - Computacao II - Turma 2012/2      
 * Prof. Marcelo Luiz Drumond Lanza           
 * Autor Joao Vitor Ferreira Duarte 
 *                                      
 */                                           
                      

#include <stdio.h>
#include <curses.h>

#include "thcFunctions.h"
#include "thcError.h"
#include "thcTypes.h"


char *thcTextErrorMessages[][2]=
{
/*0*/	{"Program successfull executed","Programa Executado com sucesso"},
/*1*/	{"Error creating file","Erro criando arquivo"},
/*2*/	{"Error reading file","Erro lendo arquivo"},
/*3*/	{"Error user not found","Erro usuario nao encontrado"},
/*4*/	{"Error writing data to file, check for storage space","Erro gravando dados no arquivo, verifique espaco em disco"},
/*5*/	{"Error creating temporary file","Erro criando arquivo temporario"},
/*6*/	{"Error creating file","Erro criando arquivo"},
/*7*/	{"Error nickname already used","Erro nome de usuario ja usado"},
/*8*/	{"Error generating nickname","Erro gerando nome de usuario"},
/*9*/	{"Error UID already used","Erro UID ja usada"},
/*10*/	{"Error insuficiente memory","Erro memoria insuficiente"},
/*11*/	{"Error empty pointer given as argument","Erro ponteiro vazio passado como argumento"},
/*12*/	{"Error writing text file","Erro escrevendo arquivo texto"},
/*13*/	{"Error reading text file","Erro lendo arquivo texto"},
/*14*/	{"Error on cookie username","Erro no nome de usuario do cookie"},
/*15*/	{"Error on cookie IP","Erro no endereco de IP do cookie"},
/*16*/	{"Error on cookie content","Erro no conteudo do cookie"},
/*17*/	{"Error on cookie expiration","Erro na validade do cookie"},
/*18*/	{"Error on cookie content pointer","Erro no ponteiro do conteudo do cookie"},
/*19*/	{"Error on cookie IP pointer","Erro no ponteiro do IP do cookie"},
/*20*/	{"Permission denied !","Permissao negada!"},
/*21*/	{"Incorrect password","Senha incorreta"},
/*22*/	{"Password correct","Senha correta"},
/*23*/	{"Arguments missing, \ntry --help for help","Argumentos faltando, \ntente --help para ajuda"},
/*24*/	{"Invalud argument, \ntry --help for help","Argumento invalido, \ntente --help para ajuda com o programa"},
/*25*/	{"Only administrator can change another username","Apenas administrador pode mudar o nome de outro usuario"},
/*26*/	{"Error, User already in the selected group","Erro, usuario já esta no grupo selecionado"}, 
/*27*/	{"Error, can't change root user","Erro, nao e possivel mudar o root"},
/*28*/	{"Error, can't change user to root","Erro, nao e possivel mudar usuario para root"},
/*29*/	{"Error can't change data for an unconfirmed user","Erro, nao e possivel mudar dados de usuario nao confirmado"},
/*30*/	{"Error sending e-mail to user","Erro enviando e-mail para usuario"},
/*31*/	{"Error user didn't reseted the password","Erro usuario nao havia resetado a senha"},
/*32*/	{"Error user didn't change the e-mail","Erro usuario nao havia trocado o e-mail"},
/*33*/	{"Error ID not found on system","Erro ID nao encontrada no sitema"},
/*34*/	{"Correct Reseted Password","Senha Resetada correta"},
/*35*/	{"Error Invalid confirmation code","Erro código de confirmação incorreto"},
/*36*/	{"This program can only be used via web","Este programa só pode ser usado via web"},
/*37*/	{"Error on web form","Erro no formulário web"},
/*38*/	{"Error generating cookie name","Erro gerando nome do cookie"},
/*39*/	{"Error trying to get cookie from client browser","Erro ao tentar obter cookie do cliente"},
/*40*/	{"Error expirated session","Erro sessão expirada"},
};

char *error[2]={"Error #","Erro #"};
char *getKey[2]={"Press any key to continue","Pressione qualquer tecla para voltar"};


void thcGetTextErrorMessage(const thcLanguageType language, const thcErrorType errorCode)
{
	printf("%s\n",thcTextErrorMessages[errorCode][language]);
}

void thcGetCursesErrorMessage(const thcLanguageType language, const thcErrorType errorCode)
{
	printw("\n%s%d : %s\n",error[language],errorCode,thcTextErrorMessages[errorCode][language]);
	printw("%s\n",getKey[language]);
	getch();
}

void thcGetHtmlErrorMessage(const thcLanguageType language, const thcErrorType errorCode)
{
		
	thcWebShowHeader();
	
	
	printf("	<body>                                                     \n");
	printf("		<div class=\"content\">                                \n");
	printf("		%s%d<br>                                               \n",error[language],errorCode);
	printf("		%s<br>                                                 \n",thcTextErrorMessages[errorCode][language]);
	printf("        </div>                                                 \n");
                                                                                                               
	
	
	thcWebShowFooter();
}