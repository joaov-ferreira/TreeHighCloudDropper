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
 * $Log: thcConfirmNewUserEmail.h,v $
 * Revision 1.2  2013/04/06 18:55:09  joao.duarte
 * Final Revision for first part
 *
 * Revision 1.1  2013/03/26 02:46:09  joao.duarte
 * Initial revision
 *                                      
 */                                           
                                              
 #ifndef   THC_CONFIRM_NEW_USER_EMAIL_H                                   
 #define   THC_CONFIRM_NEW_USER_EMAIL_H             "@(#) thcConfirmNewUserEmail.h $Revision: 1.2 $"       
 
 
/*
 * thcErrorType thcConfirmNewUserEmail(thcUserIdentifier , char *)
 * 
 * Arguments: 
 * thcUserIdentifier 				- User's ID
 * char *							- New e-mail
 * 
 * Returned Code:					
 * THC_ERROR_READING_FILE			- Error reading the file
 * THC_ERROR_UID_NOT_FOUND			- User not found
 * THC_ERROR_MKSTEMP				- Error generatins temporary file
 * THC_ERROR_WRITING_FILE			- Error creating file
 * THC_ERROR_WRITING_DATA_TO_FILE	- Error writing data to the file
 * THC_ERROR_USER_DIDNT_RESET		- Selected user didn't reseted his password
 * THC_ERROR_USER_DIDNT_EMAIL		- Selected user didn't reseted his e-mail
 * THC_OK							- No erros
 * 
 * Description:
 * This function confirms a new e-mail from user with selected ID, and changes it to
 * the new email given to the file
 */
 thcErrorType thcConfirmNewUserEmail(thcUserIdentifier , char *);
                                              
 #endif                                       
/*$RCSfile: thcConfirmNewUserEmail.h,v $*/									
