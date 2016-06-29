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
 * $Log: thcRemoveUser.h,v $
 * Revision 1.2  2013/04/06 18:55:09  joao.duarte
 * Final Revision for first part
 *
 * Revision 1.1  2013/03/20 23:05:16  joao.duarte
 * Initial revision
 *                                      
 */                                           
                                              
 #ifndef   THC_REMOVE_USER_H                            
 #define   THC_REMOVE_USER_H					"@(#)thcRemoveUser.h $Revision: 1.2 $"                                   

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
/*$RCSfile: thcRemoveUser.h,v $*/									
