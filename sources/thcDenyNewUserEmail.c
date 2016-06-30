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
                                              
#include "thcConst.h"                       
#include "thcTypes.h"                       
#include "thcError.h"                       
#include "thcFunctions.h"                   
                                              
#include "thcDenyNewUserEmail.h"                          
                                              
                                              
thcErrorType thcDenyNewUserEmail(thcUserIdentifier  UID, char *newEmail)
{
	thcErrorType errorCode;
				
	errorCode = thcRemoveFromEmailAbeyanceList(UID,0);
	if (errorCode != THC_OK)
		return errorCode;
	
	return thcClearUserFlag(UID, emailChange);
	
}                                         