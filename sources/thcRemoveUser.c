/*                                            
 * Universidade Federal do Rio de Janeiro     
 * Escola Politecnica                         
 * Departamento de Eletronica e de Computacao 
 * EEL270 - Computacao II - Turma 2012/2      
 * Prof. Marcelo Luiz Drumond Lanza           
 * Autor Joao Vitor Ferreira Duarte                             
 */                                           
                                              
#include <stdlib.h>                           
#include <stdio.h>                            
#include <string.h>
                                              
#include "thcConst.h"                       
#include "thcTypes.h"                       
#include "thcError.h"                       
#include "thcFunctions.h"                   
                                              
#include "thcRemoveUser.h"                          
                                              
thcErrorType thcRemoveUser (char *nickname)
{
	thcErrorType errorCode;

	if (strcmp(nickname,"root") == 0)
		return THC_PERMISSION_DENIED;

	errorCode = thcRemoveUserData(nickname);
	if (errorCode != THC_OK)
		return errorCode;
		
	errorCode = thcGenerateTextFile();
	if (errorCode != THC_OK)
		return errorCode;
	
	return THC_OK;
}                                       
                                              
                                              
                                              