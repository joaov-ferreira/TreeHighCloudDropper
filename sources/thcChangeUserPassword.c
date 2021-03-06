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
#include <string.h>
                                              
#include "thcConst.h"                       
#include "thcTypes.h"                       
#include "thcError.h"                       
#include "thcFunctions.h"                   
                                              
#include "thcChangeUserPassword.h"                          
                                              
thcErrorType thcChangeUserPassword (thcUserDataType *data)
{
	char buffer[THC_PASSWORD_MAXIMUM_LENGHT+1];
	char coded [THC_ENCRYPTED_PASSWORD_LENGHT+1];
	thcErrorType errorCode;
	
	/*Copy password to the buffer*/
	strcpy(buffer,data->codedPassword);		
	
	/*Crypt new password*/
	errorCode = thcEncryptPassword(buffer,coded);
	if (errorCode != THC_OK)
		return errorCode;
	
	/*Move to data and save on file*/
	strcpy(data->codedPassword,coded);
	
	/*Change user status*/
	if (data->flag == abeyance)
	{
		data->flag=ok;
		thcRemoveFromAbeyanceList(data->nickname);
	}
	if (data->flag == passwordReset)
	{
		data->flag=ok;
		thcRemoveFromPasswordAbeyanceList(data->UID);
	}
	
	errorCode = thcRemoveUserData(data->nickname);
	if (errorCode != THC_OK)
		return errorCode;
		
	errorCode = thcWriteFile(data);
	if (errorCode != THC_OK)
		return errorCode;
		
	errorCode = thcGenerateTextFile();
	if (errorCode != THC_OK)
		return errorCode;		
		
	return THC_OK;
}                                                                              
