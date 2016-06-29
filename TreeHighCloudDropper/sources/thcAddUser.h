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
 * $Log: thcAddUser.h,v $
 * Revision 1.2  2013/04/06 18:55:09  joao.duarte
 * Final Revision for first part
 *
 * Revision 1.1  2013/03/20 23:05:16  joao.duarte
 * Initial revision
 *                                      
 */                                           
                                              
 #ifndef     THC_ADD_USER_H                                  
 #define   	 THC_ADD_USER_H                    "@(#)thcAddUser.h $Revision: 1.2 $"                 
 
 #include "thcTypes.h"						
          
/*
 * thcErrorType thcAddUser (thcUserDataType *)
 * 
 * Arguments: 
 * thcUserDataType *						- User data
 * 
 * Returned Code:			
 * THC_ERROR_EMPTY_POINTER					- Function has received a null pointer
 * THC_PERMISSION_DENIED					- Permission denied		
 * THC_ERROR_INSUFICIENT_MEMORY				- Could't allocate necessary memory
 * THC_ERROR_READING_FILE					- Error reading the file
 * THC_ERROR_MKSTEMP						- Error creating a temporary file	
 * THC_ERROR_WRITING_FILE					- Error creating file
 * THC_ERROR_WRITING_DATA_TO_FILE			- Error writing data to the file
 * THC_ERROR_GENERATE_NICKNAME				- Could't generate a nickname
 * THC_OK									- No errors
 * 
 * Description:
 * This function adds an user to the system, it must have e-mail, group and full name fields
 * filled with user information.
 */
thcErrorType thcAddUser (thcUserDataType *);  
                                           
 #endif                                       
/*$RCSfile: thcAddUser.h,v $*/	
