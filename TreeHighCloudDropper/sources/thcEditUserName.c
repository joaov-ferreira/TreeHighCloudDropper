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
 * $Log: thcEditUserName.c,v $
 * Revision 1.3  2013/04/06 18:55:09  joao.duarte
 * Final Revision for first part
 *
 * Revision 1.2  2013/03/21 23:39:58  joao.duarte
 * Fixed a bug when root try to change username
 *
 * Revision 1.1  2013/03/20 23:05:16  joao.duarte
 * Initial revision
 *                                      
 */                                           
                                              
#include <stdlib.h>                           
#include <stdio.h>                            
#include <string.h>
                                          
#include "thcConst.h"                       
#include "thcTypes.h"                       
#include "thcError.h"                       
#include "thcFunctions.h"                   
                                              
#include "thcEditUserName.h"                          
                                              
thcErrorType thcEditUserName (thcUserDataType *data)
{
	thcErrorType errorCode;
	char newNickname [THC_NICKNAME_MAXIMUM_LENGHT+1];


	/*Generates a new nickname if user isn't root*/
	if (strcmp(data->nickname,THC_ROOT_NAME) != 0)
	{
		errorCode  = thcGenerateNickname(data->fullName,newNickname);	
		if (errorCode != THC_OK)
			return errorCode;
	}
	
	/*Nickname == root*/
	else
	{
		strcpy(newNickname,THC_ROOT_NAME);
	}
	/*Remove old data*/		
	errorCode = thcRemoveUserData(data->nickname);
	if (errorCode != THC_OK)
		return errorCode;
	
	/*Write new data*/
	strcpy(data->nickname,newNickname);
	errorCode = thcWriteFile(data);
	if (errorCode != THC_OK)
		return errorCode;
		
	/*Makes a new text user file*/
	errorCode = thcGenerateTextFile();
	if (errorCode != THC_OK)
		return errorCode;	
		
	return THC_OK;
	
}                                              
                                              
                                              
                                              
/*$RCSfile: thcEditUserName.c,v $*/                                  
