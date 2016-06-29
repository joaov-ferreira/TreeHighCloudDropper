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
 * $Log: thcRenewCookie.h,v $
 * Revision 1.1  2013/04/06 18:55:09  joao.duarte
 * Initial revision
 *                                      
 */                                           
                                              
 #ifndef  THC_RENEW_COOKIE_H                                    
 #define  THC_RENEW_COOKIE_H			"@(#)thcRenewCookie.h $Revision: 1.1 $"                                    
     
/*
 * thcErrorType thcRenewCookie (char* cookieName, thcLanguageType* language)
 * 
 * Arguments : 
 * char* cookieName							- Cookie Name
 * thcLanguageType* language				- Language
 * 
 * Return Codes :
 * THC_ERROR_TRYING_TO_GET_COOKIE			- Could't get cookie from client browser
 * THC_ERROR_EXPIRATED_SESSION				- Expirated cookie
 * THC_PERMISSION_DENIED					- Invalid cookie
 * THC_ERROR_COOKIE_USERNAME   				- User field contains a null pointer
 * THC_ERROR_WRITING_FILE      				- Could't write the file
 * THC_ERROR_COOKIE_EXPIRATION 				- Error writing cookie expiration to file
 * THC_ERROR_COOKIE_CONTENT    				- Error writing cookie content to file
 * THC_ERROR_COOKIE_IP         				- Error writing cookie IP to file
 * THC_ERROR_COOKIE_CONTENT_POINTER			- Content field contains a null pointer
 * THC_ERROR_COOKIE_IP_POINTER				- IP field contais a null pointer
 * THC_ERROR_READING_FILE					- Error opening file for reading
 * THC_OK									- No errors
 * 
 * Description : 
 * This function renew a cookie with the selected name and
 * get language information from cookie
 * 
 */      
        
 thcErrorType thcRenewCookie (char* cookieName, thcLanguageType* language);
                                              
 #endif                                       
/*$RCSfile*/									
