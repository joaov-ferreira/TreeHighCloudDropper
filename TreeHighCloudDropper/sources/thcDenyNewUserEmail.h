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
 * $Log: thcDenyNewUserEmail.h,v $
 * Revision 1.2  2013/04/06 18:55:09  joao.duarte
 * Final Revision for first part
 *
 * Revision 1.1  2013/03/26 02:40:54  joao.duarte
 * Initial revision
 *                                      
 */                                           
                                              
 #ifndef THC_DENY_NEW_USER_EMAIL_H                                     
 #define THC_DENY_NEW_USER_EMAIL_H				"@(#)thcDenyNewUserEmail.h $Revision: 1.2 $"                                     

/*
 * thcErrorType thcDenyNewUserEmail(thcUserIdentifier  , char *); 
 * 
 * Arguments :
 * thcUserIdentifier   - User ID to have e-mail denied
 * char *			   - Confirmation code
 * 
 * Return code :
 * THC_ERROR_READING_FILE			- Error reading the file
 * THC_ERROR_MKSTEMP				- Error generatins temporary file
 * THC_ERROR_WRITING_FILE			- Error creating file
 * THC_ERROR_WRITING_DATA_TO_FILE	- Error writing data to the file
 * THC_OK							- No errors
 * 
 * Description :
 * This function will take a user UID and his confirmation code to deny the new e-mail
 * Using a confirmation code, the function will be safer than using the e-mail
 * 
 */ 


thcErrorType thcDenyNewUserEmail(thcUserIdentifier  , char *);    
                                              
 #endif                                       
/*$RCSfile: thcDenyNewUserEmail.h,v $*/									
