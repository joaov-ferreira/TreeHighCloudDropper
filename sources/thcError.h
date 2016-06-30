/*                                            
 * Universidade Federal do Rio de Janeiro     
 * Escola Politecnica                         
 * Departamento de Eletronica e de Computacao 
 * EEL270 - Computacao II - Turma 2012/2      
 * Prof. Marcelo Luiz Drumond Lanza           
 * Autor Joao Vitor Ferreira Duarte                      
 */    

#ifndef THC_ERROR_H

#define THC_ERROR_H	

#include "thcTypes.h"

/*
 * void thcGetTextErrorMessage(const thcLanguageType language, const thcErrorType errorCode)
 * 
 * Arguments: 
 * const thcLanguageType language			- language
 * const thcErrorType errorCode				- Error Code			
 * 
 * Description:
 * This function prints the correspondent error conde on the selected language
 * on CLI interface
 */
void thcGetTextErrorMessage(const thcLanguageType language, const thcErrorType errorCode);

/*
 * void thcGetHtmlErrorMessage(const thcLanguageType language, const thcErrorType errorCode)
 * 
 * Arguments: 
 * const thcLanguageType language			- language
 * const thcErrorType errorCode				- Error Code			
 * 
 * Description:
 * This function show the error page on web interface for the correspondent error code
 * in the selected language
 */
void thcGetHtmlErrorMessage(const thcLanguageType language, const thcErrorType errorCode);

/*
 * void thcGetCursesErrorMessage(const thcLanguageType language, const thcErrorType errorCode)
 * 
 * Arguments: 
 * const thcLanguageType language			- language
 * const thcErrorType errorCode				- Error Code			
 * 
 * Description:
 * Prints the error messages on NCurses interface on selected language
 */
void thcGetCursesErrorMessage(const thcLanguageType language, const thcErrorType errorCode);

/*********************************************************************************************/
/*									ERROR MACROS											 */
/*********************************************************************************************/

#define THC_OK										0
#define THC_ERROR_WRITING_FILE						1
#define THC_ERROR_READING_FILE						2
#define THC_ERROR_USERNAME_NOT_FOUND				3
#define THC_ERROR_WRITING_DATA_TO_FILE				4
#define THC_ERROR_MKSTEMP							5
#define THC_ERROR_CREATING_FILE						6
#define THC_ERROR_NICKNAME_USED						7
#define THC_ERROR_GENERATE_NICKNAME					8
#define THC_ERROR_UID_USED							9			
#define THC_ERROR_INSUFICIENT_MEMORY				10
#define THC_ERROR_EMPTY_POINTER						11
#define THC_ERROR_WRITING_TEXT_FILE					12
#define THC_ERROR_READING_TEXT_FILE					13
#define THC_ERROR_COOKIE_USERNAME					14
#define THC_ERROR_COOKIE_IP							15
#define THC_ERROR_COOKIE_CONTENT					16
#define THC_ERROR_COOKIE_EXPIRATION					17
#define THC_ERROR_COOKIE_CONTENT_POINTER			18
#define THC_ERROR_COOKIE_IP_POINTER					19
#define THC_PERMISSION_DENIED						20
#define THC_INCORRECT_PASSWORD						21
#define THC_CORRECT_PASSWORD						22
#define THC_INVALID_ARGUMENT_NUMBER					23
#define THC_INVALID_ARGUMENT						24
#define THC_ERROR_EDIT_NAME							25
#define THC_ERROR_USER_GROUP						26
#define THC_ERROR_CHANGE_ROOT						27
#define THC_ERROR_CHANGE_TO_ROOT					28
#define THC_USER_NOT_CONFIRMED						29
#define THC_ERROR_EMAIL								30
#define THC_ERROR_USER_DIDNT_RESET					31
#define THC_ERROR_USER_DIDNT_EMAIL					32
#define THC_ERROR_UID_NOT_FOUND						33		
#define THC_CORRECT_RESETED_PASSWORD				34
#define THC_ERROR_INVALID_CODE						35
#define THC_ERROR_INVALID_INTERFACE					36
#define THC_ERROR_ON_WEB_FORM						37
#define THC_ERROR_GENERATING_COOKIE_NAME			38
#define THC_ERROR_TRYING_TO_GET_COOKIE				39
#define THC_ERROR_EXPIRATED_SESSION					40

#endif