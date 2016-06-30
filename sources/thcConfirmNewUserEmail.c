/*                                            
 * Universidade Federal do Rio de Janeiro     
 * Escola Politecnica                         
 * Departamento de Eletronica e de Computacao 
 * EEL270 - Computacao II - Turma 2012/2      
 * Prof. Marcelo Luiz Drumond Lanza           
 * Autor Joao Vitor Ferreira Duarte           
 *                                      
 */                                           
                                              
#include <stdlib.h>                           
#include <stdio.h>                            
#include <string.h>
                                              
#include "thcConst.h"                       
#include "thcTypes.h"                       
#include "thcError.h"                       
#include "thcFunctions.h"                   
                                              
#include "thcConfirmNewUserEmail.h"                          
                                              
thcErrorType thcConfirmNewUserEmail(thcUserIdentifier  UID, char *email)
{
	thcErrorType errorCode;
	thcUserDataType data;

	/*Search user dara*/
	errorCode = thcSearchUserByUID(UID, &data);
	if (errorCode != THC_OK)
		return errorCode;
	
	/*Saves the new e-mail*/
	thcRemoveUserData(data.nickname);
	strcpy(data.email,email);
	thcWriteFile(&data);
	
	/*Remove flag and abeyance data*/		
	errorCode = thcRemoveFromEmailAbeyanceList(UID,0);
	if (errorCode != THC_OK)
		return errorCode;
	
	return thcClearUserFlag(UID, emailChange);
	
}                                                      