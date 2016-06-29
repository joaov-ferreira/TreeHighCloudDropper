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
 * $Log: thcAddUserToGroup.h,v $
 * Revision 1.2  2013/04/06 18:55:09  joao.duarte
 * Final Revision for first part
 *
 * Revision 1.1  2013/03/20 23:05:16  joao.duarte
 * Initial revision
 *                                      
 */                                           
                                              
 #ifndef  THC_ADD_USER_TO_GROUP_H                                    
 #define  THC_ADD_USER_TO_GROUP_H				"@(#)thcAddUserToGroup.h $Revision: 1.2 $"                                    
 
 /*This include remove a warning*/
 #include "thcTypes.h"
 
/*
 * thcErrorType thcAddUserToGroup (char *, thcGroupType)
 *   
 * Arguments: 
 * char* 								- User nickname
 * thcGroupType							- new group
 * 
 * Returned Code:
 * THC_ERROR_WRITING_FILE				- Error creating file
 * THC_ERROR_WRITING_DATA_TO_FILE		- Error writing data to the file
 * THC_ERROR_READING_FILE				- Error reading file, this error only ocour when file already exists
 * THC_ERROR_MKSTEMP					- Error creating a temporary file			
 * THC_ERROR_NICKNAME_USED				- Error nickname already used
 * THC_USER_NOT_CONFIRMED				- User didn't confirmed his account or an operation
 * THC_ERROR_CHANGE_ROOT				- User tried to change system's root group
 * THC_ERROR_USER_GROUP					- Could't change user to selected group
 * 
 * 
 * Description:
 * This function add a user to a selected group while keeping the old group
 * e.g. : if he is an user and you add to owner, he will have both papers on the system
 */
 thcErrorType thcAddUserToGroup (char *, thcGroupType);                                            
 #endif                                       
/*$RCSfile: thcAddUserToGroup.h,v $*/									
