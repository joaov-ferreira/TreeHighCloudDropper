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



#ifndef THC_CONST_H

#define THC_CONST_H								"@(#)thcConst.h $Revision: 1.4 $"


/*********************************************************************************************/
/*					                GENERAL PROGRAM MACROS									 */
/*********************************************************************************************/

#define THC_FILE_MAXIMUM_NICKNAME_LENGHT			64
#define THC_FILE_ENCRYPTED_PASSWORD_LENGHT			106
#define THC_FILE_MAXIMUM_NAME_LENGHT				100
#define THC_FILE_MAXIMUM_EMAIL_LENGHT				100

#define THC_BASE64_STRING							"0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ./"

#define THC_WRITE									"w"
#define THC_READ									"r"
#define THC_APPEND									"a"

#define THC_MAXIMUM_GROUP_NAME						8 //corrigir

#define THC_COOKIE_NAME_LENGHT						20
#define THC_COOKIE_NAME_PRINTF_FORMAT 				"%020llu"

#define THC_CONFIRM_FORM_NAME_LENGHT				3
#define THC_SALT_LENGHT								16
#define THC_FULL_SALT_LENGHT						20
#define THC_ENCRYPTED_PASSWORD_LENGHT				106


#endif