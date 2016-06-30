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
                                              
#ifndef   THC_REMOVE_USER_H                            
#define   THC_REMOVE_USER_H		

#include "thcTypes.h"   

/*
 * thcErrorType thcRemoveUser(char *nickname)
 * 
 * Arguments: 
 * char *nickname - nickname
 * 
 * Returned Code:
 * THC_ERROR_INSUFICIENT_MEMORY			- Could't allocate necessary memory
 * THC_ERROR_READING_FILE				- Error reading the file
 * THC_ERROR_MKSTEMP					- Error creating a temporary file	
 * THC_ERROR_WRITING_FILE				- Error creating file
 * THC_ERROR_WRITING_DATA_TO_FILE		- Error writing data to the file
 * THC_OK								- User removed from the file
 * Description:
 * This functions removes a user from the file THC_FILE_NAME
 */
thcErrorType thcRemoveUser(char *nickname);    
                                              
 #endif                                       