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
 * $Log: thcEditUserName.h,v $
 * Revision 1.2  2013/04/06 18:55:09  joao.duarte
 * Final Revision for first part
 *
 * Revision 1.1  2013/03/20 23:05:16  joao.duarte
 * Initial revision
 *                                      
 */                                           
                                              
 #ifndef THC_EDIT_USER_NAME_H                                
 #define THC_EDIT_USER_NAME_H						"@(#)thcEditUserName.h $Revision: 1.2 $"                                    
 
/*
 * thcErrorType thcEditUserName (thcUserDataType *)
 * 
 * Arguments: 
 * thcUserDataType *					- User data with new name on full name field
 * 
 * Returned Code:					
 * THC_ERROR_INSUFICIENT_MEMORY			- Could't allocate necessary memory
 * THC_ERROR_READING_FILE				- Error reading the file
 * THC_ERROR_MKSTEMP					- Error creating a temporary file	
 * THC_ERROR_WRITING_FILE				- Error creating file
 * THC_ERROR_WRITING_DATA_TO_FILE		- Error writing data to the file
 * THC_ERROR_EMPTY_POINTER				- Function has received a NULL pointer
 * THC_ERROR_GENERATE_NICKNAME			- Could't generate a nickname
 * THC_OK								- No errors
 * 
 * Description:
 * This functions changes user name and creates a new nickname based on the new name
 */
 thcErrorType thcEditUserName (thcUserDataType *);
                                              
 #endif                                       
/*$RCSfile: thcEditUserName.h,v $*/									
