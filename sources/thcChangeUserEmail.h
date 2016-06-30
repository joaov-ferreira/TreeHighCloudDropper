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
                                              
 #ifndef   THC_CHANGE_USER_EMAIL_H                                   
 #define   THC_CHANGE_USER_EMAIL_H                                  
 
 /*
 * thcErrorType thcChangeUserEmail (thcUserDataType *)
 * 
 * Arguments: 
 * thcUserDataType *   				- User data with new e-mail on email field
 * 									  and the language on UID field
 * 
 * Returned Code:
 * THC_ERROR_USERNAME_NOT_FOUND		- Nickname not found on the file
 * THC_ERROR_INSUFICIENT_MEMORY		- Could't allocate necessary memory
 * THC_ERROR_READING_FILE			- Error reading the file
 * THC_ERROR_MKSTEMP				- Error creating a temporary file	
 * THC_ERROR_WRITING_FILE			- Error creating file
 * THC_ERROR_WRITING_DATA_TO_FILE	- Error writing data to the file
 * THC_OK							- No errors
 *  
 * Description:
 * This function start the change e-mail process for an user, the new e-mail must be in the
 * email field from the struct and the e-mail language must be on the UID field
 */
 
 thcErrorType thcChangeUserEmail (thcUserDataType *);
                                       
 #endif                                       							
