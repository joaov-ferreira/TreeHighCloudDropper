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
#include <string.h>                           
                                              
#include "thcConst.h"                       
#include "thcTypes.h"                       
#include "thcError.h"                       
#include "thcFunctions.h"    
#include "thcConfig.h"
#include "mlcgi.h"               
                                              
#include "thcRenewCookie.h"                          
                                              
thcErrorType thcRenewCookie (char* cookieName, thcLanguageType* language)
{
	thcErrorType errorCode;
	char content[THC_COOKIE_CONTENT_LENGHT + 1];
	char readedContent [THC_COOKIE_CONTENT_LENGHT + 1];
	char IP [THC_COOKIE_MAXIMUM_IP_LENGHT + 1];
	time_t expiration, localTime;
	
	/*Get Local Time*/
	localTime = time(NULL);
	
	/*Get cookie from user*/
	errorCode = mlCgiGetSpecificCookie(cookieName, THC_COOKIE_NAME_LENGHT, content, THC_COOKIE_CONTENT_LENGHT);
	if (errorCode != ML_CGI_OK)
		return THC_ERROR_TRYING_TO_GET_COOKIE;
	
	errorCode = thcReadCookie(cookieName ,&expiration,readedContent, IP);
	if (errorCode !=  THC_OK)
		return errorCode;
	
	/*Check for cookie expiration*/
	if (expiration < localTime)
		return THC_ERROR_EXPIRATED_SESSION;
	
	/*Check for cookie content*/
	if (strcmp(content, readedContent) != 0)
		return THC_PERMISSION_DENIED;
	
	/*Sends the new cookie*/
	expiration = time (NULL) + THC_COOKIE_EXPIRATION;
	
	mlCgiSetCookie(cookieName, content, THC_COOKIE_EXPIRATION, NULL, NULL, NULL);
	
	/*Saves cookie on file*/
	errorCode = thcGenerateCookie(cookieName, &expiration, content, IP);
	if (errorCode != THC_OK)
		return errorCode;
		
	if (content[0] == 'e') *language = english;
	if (content[0] == 'b') *language = portuguese;
	
	return THC_OK;
}                                             
                                              
                                              
                                                                          
