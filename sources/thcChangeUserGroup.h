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
                                              
 #ifndef    THC_CHANGE_USER_GROUP_H                                  
 #define    THC_CHANGE_USER_GROUP_H	                                
 
 /*
 * thcErrorType thcChangeUserGroup (char *, thcGroupType)
 * 
 * Arguments: 
 * char *								- User nickname
 * thcGroupType							- New group
 * 			
 * Returned Code:
 * THC_ERROR_CHANGE_ROOT				- User tried to change systems root group
 * THC_ERROR_USERNAME_NOT_FOUND			- Nickname not found on the file
 * THC_ERROR_INSUFICIENT_MEMORY			- Could't allocate necessary memory
 * THC_ERROR_READING_FILE				- Error reading the file
 * THC_ERROR_MKSTEMP					- Error creating a temporary file	
 * THC_ERROR_WRITING_FILE				- Error creating file
 * THC_ERROR_WRITING_DATA_TO_FILE		- Error writing data to the file
 * THC_OK								- No errors
 * 
 * Description:
 * This functions changes an user group to a new on
 * e.g. : if he is an user and user this function to change to admin, he will be only admin
 */
 thcErrorType thcChangeUserGroup (char *, thcGroupType);
                                              
 #endif                                       