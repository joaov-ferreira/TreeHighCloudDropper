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
 * $Log: thcDenyNewUserEmail.c,v $
 * Revision 1.2  2013/04/06 18:55:09  joao.duarte
 * Final Revision for first part
 *
 * Revision 1.1  2013/03/26 02:40:54  joao.duarte
 * Initial revision
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
                                             
/*$RCSfile: thcDenyNewUserEmail.c,v $*/                                  
