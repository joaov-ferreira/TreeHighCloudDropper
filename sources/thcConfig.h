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



#ifndef THC_CONFIG_H

#define THC_CONFIG_H


/*********************************************************************************************/
/*					                GENERAL PROGRAM MACROS									 */
/*********************************************************************************************/

#ifndef THC_WEB_SERVER_URL 
#define THC_WEB_SERVER_URL							"http://www2.del.ufrj.br/~joao.duarte/eel270/thc/index.html"
#define THC_WEB_SERVER_URL_BR						"http://www2.del.ufrj.br/~joao.duarte/eel270/thc/index_br.html"
#endif  

#define THC_OPERATING_SYSTEM_FREE_BSD

#ifdef THC_OPERATING_SYSTEM_LINUX
#include <crypt.h>
#endif

#define THC_FILE_NAME								"/users/joao.duarte/private/eel270/thc/data/thcData.bin"	
#define THC_TEXT_FILE_NAME							"/users/joao.duarte/private/eel270/thc/data/usuarios"
#define THC_TEMP_FILE_NAME							"tmpXXXXXX"
#define THC_TEMP_FILE_NAME_LENGHT					9
#define THC_LANGUAGE_MAXIMUM_LENGHT					2

#define THC_COOKIE_MAXIMUM_USERNAME_LENGHT			128
#define THC_COOKIE_MAXIMUM_IP_LENGHT				15
#define THC_COOKIE_CONTENT_LENGHT					128
#define THC_MAXIMUM_COOKIE_PATH						300
#define THC_DEFAULT_COOKIE_DIRECTORY				"/users/joao.duarte/private/eel270/thc/data/cookies/"
#define THC_COOKIE_EXPIRATION						3600 /*1 hour*/
/*The system don't check for user ip, this is given so the field won't be blank*/
#define THC_DEFAULT_COOKIE_IP						"146.164.96.154" 

#define THC_TEMP_PASSWORD_LENGHT					10
#define THC_PASSWORD_ATTEMPTS						4
#define THC_PASSWORD_RESET_EXPIRATION				86400 /*24 hous*/
#define THC_EMAIL_RESET_EXPIRATION					86400 /*24 hous*/

#define THC_PASSWORD_MAXIMUM_LENGHT					50
#define THC_NICKNAME_MAXIMUM_LENGHT					80
#define THC_EMAIL_MAXIMUM_LENGHT					100
#define THC_EMAIL_MINUMUM_LENGHT					4
#define THC_FULL_NAME_MAXIMUM_LENGHT				300
#define THC_MINUMUM_FULL_NAME_LENGHT				3
#define THC_MAXIMUM_NAMES							8
#define THC_MINUMUM_NICKNAME_LENGHT					3

#define THC_ROOT_NAME								"root"

#define THC_ABEYANCES_FILE_NAME						"/users/joao.duarte/private/eel270/thc/data/usuarios.abeyances"
#define THC_ABEYANCES_PASSWORD_FILE_NAME			"/users/joao.duarte/private/eel270/thc/data/password.abeyances"
#define THC_ABEYANCES_EMAIL_FILE_NAME				"/users/joao.duarte/private/eel270/thc/data/email.abeyances"
#define THC_ABEYANCES_EMAIL_CODES_FILE_NAME			"/users/joao.duarte/private/eel270/thc/data/email.abeyances.codes"
#define THC_ABEYANCES_EXPIRATION					259200 /*259200 seconds = 72h*/
#define THC_ABEYANCES_EMAIL_EXPIRATION				86400 /*24 hous*/

#define THC_EMAIL_CONFIRM_CGI_NAME					"http://www2.del.ufrj.br/~joao.duarte/eel270/thc/cgis/thcConfirmEmail.cgi"
#define THC_EMAIL_DENY_CGI_NAME						"http://www2.del.ufrj.br/~joao.duarte/eel270/thc/cgis/thcDenyEmail.cgi"


#define THC_ADMINISTRATOR_USER_IDENTIFIER			30537

#define THC_DEFAULT_LANGUAGE						english
#define THC_DEFAULT_GROUP							user


#endif