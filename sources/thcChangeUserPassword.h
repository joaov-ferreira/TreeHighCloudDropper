/*                                            
 * Universidade Federal do Rio de Janeiro     
 * Escola Politecnica                         
 * Departamento de Eletronica e de Computacao 
 * EEL270 - Computacao II - Turma 2012/2      
 * Prof. Marcelo Luiz Drumond Lanza           
 * Autor Joao Vitor Ferreira Duarte           
 *                                      
 */                                           
                                              
 #ifndef 	THC_CHANGE_USER_PASSWORD_H                                      
 #define    THC_CHANGE_USER_PASSWORD_H	                                
 
 
 /*
 *  thcErrorType thcChangeUserPassword (thcUserDataType *); 
 * 
 * Arguments: 
 * thcUserDataType * 					- User data necessary to change password, with the new plain password 
 * 									      on the Coded password field
 *
 * Returned Code:
 * THC_ERROR_WRITING_FILE				- Error creating file
 * THC_ERROR_WRITING_DATA_TO_FILE		- Error writing data to the file
 * THC_ERROR_READING_FILE				- Error reading file, this error only ocour when file already exists
 * THC_ERROR_MKSTEMP					- Error creating a temporary file			
 * THC_ERROR_NICKNAME_USED				- Error nickname already used
 * THC_ERROR_INSUFICIENT_MEMORY			- Could't allocate necessary memory 
 * THC_OK								- No errors
 * 
 * Description:
 * This function changes an user's password to the password that is given in plain form on the coded password
 * field from thcUserDataType, it keeps any other information on thcUserDataType *
 */
 thcErrorType thcChangeUserPassword (thcUserDataType *); 
                                              
 #endif                                       								
