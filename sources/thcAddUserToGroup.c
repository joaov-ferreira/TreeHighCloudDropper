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
                                              
#include <stdlib.h>                           
#include <stdio.h>                            
                                              
#include "thcConst.h"                       
#include "thcTypes.h"                       
#include "thcError.h"                       
#include "thcFunctions.h"                   
                                              
#include "thcAddUserToGroup.h"                          
                                              
                                              
thcErrorType thcAddUserToGroup (char *nickname, thcGroupType addedGroup)                                             
{
	thcUserDataType buffer; 
	thcErrorType errorCode;
	
	errorCode = thcSearchUser(nickname,&buffer);
	if (errorCode != THC_OK)
		return errorCode;
	
	if (buffer.flag != ok)
		return THC_USER_NOT_CONFIRMED;
	
	
	if (buffer.group == root)
		return THC_ERROR_CHANGE_ROOT;
	
	/*Check for any incompatible group type*/
	if ((addedGroup == owner) && ( (buffer.group == owner) || (buffer.group == ownerUser) || (buffer.group == ownerAdmin)) )
		return THC_ERROR_USER_GROUP;

	if ((addedGroup == administrador) && ( (buffer.group == administrador) || (buffer.group == userAdmin) || (buffer.group == ownerAdmin)) )
		return THC_ERROR_USER_GROUP;

	if ((addedGroup == user) && ( (buffer.group == user) || (buffer.group == userAdmin) || (buffer.group == ownerUser)) )
		return THC_ERROR_USER_GROUP;
	

	
	/*Adds user to the new group*/	
	buffer.group += addedGroup;
	if (buffer.group == root)
		return THC_ERROR_CHANGE_TO_ROOT;

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