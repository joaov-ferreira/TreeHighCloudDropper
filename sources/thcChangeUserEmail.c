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
 * $Log: thcChangeUserEmail.c,v $
 * Revision 1.3  2013/04/06 18:55:09  joao.duarte
 * Final Revision for first part
 *
 * Revision 1.2  2013/03/26 02:41:35  joao.duarte
 * Fixed some bugs on e-mail storage
 *
 * Revision 1.1  2013/03/20 23:05:16  joao.duarte
 * Initial revision
 *                                      
 */                                           
                                              
#include <stdlib.h>                           
#include <stdio.h>                            
#include <time.h>
#include <string.h> 
                                              
#include "thcConst.h"                       
#include "thcTypes.h"                       
#include "thcError.h"                       
#include "thcFunctions.h"                   
                                              
#include "thcChangeUserEmail.h"                          
                                              
thcErrorType thcChangeUserEmail (thcUserDataType *data)	
{
	return thcChangeEmailAdress(data->nickname,data->email,(thcLanguageType )data->UID);
}                                      
                                              
                                              
                                              
/*$RCSfile: thcChangeUserEmail.c,v $*/                                  
