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
 * $Log: thcChangeUserGroup.c,v $
 * Revision 1.2  2013/04/06 18:55:09  joao.duarte
 * Final Revision for first part
 *
 * Revision 1.1  2013/03/20 23:05:16  joao.duarte
 * Initial revision
 *                                      
 */                                           
                                              
#include <stdlib.h>                           
#include <stdio.h>                            
                                              
#include "thcConst.h"                       
#include "thcTypes.h"                       
#include "thcError.h"                       
#include "thcFunctions.h"                   
                                              
#include "thcChangeUserGroup.h"                          
                                              
 thcErrorType thcChangeUserGroup (char *nickname, thcGroupType newGroup)
 {
	 thcErrorType errorCode;
	 thcUserDataType buffer;
	 
	errorCode = thcSearchUser(nickname,&buffer);
	if (errorCode != THC_OK)
		return errorCode;
	
	if (buffer.group == root)
		return THC_ERROR_CHANGE_ROOT;	 
	
	/*Give the new group*/ 
	 buffer.group = newGroup;
	 errorCode = thcRemoveUserData(nickname);
	 if (errorCode != THC_OK)
		return errorCode;
	
	errorCode = thcWriteFile(&buffer);
	if (errorCode != THC_OK)
		return errorCode;
		
	errorCode = thcGenerateTextFile();
	if (errorCode != THC_OK)
		return errorCode;		
	  
	 return THC_OK;
 }                                              
                                              
                                              
                                              
/*$RCSfile: thcChangeUserGroup.c,v $*/                                  