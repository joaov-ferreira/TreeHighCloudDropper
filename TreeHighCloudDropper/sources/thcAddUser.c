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
 * $Log: thcAddUser.c,v $
 * Revision 1.2  2013/04/06 18:55:09  joao.duarte
 * Final Revision for first part
 *
 * Revision 1.1  2013/03/20 23:05:16  joao.duarte
 * Initial revision
 *                                      
 */                                           
                                              
#include <stdlib.h>                           
#include <stdio.h>                            
#include <string.h>            
#include <unistd.h>    
#include <time.h> 
                                            
#include "thcConst.h"                       
#include "thcTypes.h"                       
#include "thcError.h"                       
#include "thcFunctions.h"                   
#include "thcConfig.h"
                                              
#include "thcAddUser.h"                          
                                              
          
thcErrorType thcAddUser (thcUserDataType *data)    
{
	thcErrorType errorCode;
	thcUserAbeyancesType abeyances;
	char *password;
	char *passwordConfirm;
	char encryptedPassword [THC_ENCRYPTED_PASSWORD_LENGHT+1];
	char nickname[THC_NICKNAME_MAXIMUM_LENGHT+1];	
	thcUserIdentifier UID;
	char tempPassword[THC_TEMP_PASSWORD_LENGHT+1];
	
	if(!data) return THC_ERROR_EMPTY_POINTER;

	
	if (strcmp(data->nickname,THC_ROOT_NAME) == 0)
	{
		if (getuid() == THC_ADMINISTRATOR_USER_IDENTIFIER)
		{
			
			password = malloc(THC_PASSWORD_MAXIMUM_LENGHT+1);
			do
			{
				passwordConfirm = getpass("Enter a password : ");
				strcpy(password,passwordConfirm);
				passwordConfirm = getpass("Confirm your password : ");
				if (strcmp(passwordConfirm,password) != 0) printf("Passwords didn't match, try again \n");
			} while (strcmp(passwordConfirm,password) != 0);
			
			
			errorCode = thcEncryptPassword(password,encryptedPassword);
			strcpy(data->codedPassword,encryptedPassword);
			/*Erase plain password from memory*/
			free(password);
			memset(passwordConfirm,0x00,strlen(passwordConfirm));				
			
			/*Set UID = 0 on root user*/
			data->UID = 0;


			if ((errorCode = thcWriteFile(data)) != THC_OK)
				return errorCode;
			
			return (thcGenerateTextFile());
						
		}
		else
			return THC_PERMISSION_DENIED;
	}
	/*if nickname = root*/
	
	/*Add nickname field*/
	if ((errorCode = thcGenerateNickname(data->fullName,nickname)) != THC_OK)
		return errorCode;
		
	strcpy(data->nickname,nickname);
	data->flag = abeyance;
	
	/*Add uid field*/
	if ((errorCode = thcGetValidUid(&UID)) != THC_OK)
		return errorCode;
	data->UID = UID;
	
	/*Creates a temporary password*/
	memset(data->codedPassword,0x00,THC_ENCRYPTED_PASSWORD_LENGHT+1);
	memset(tempPassword,0x00,THC_TEMP_PASSWORD_LENGHT+1);
	thcGenerateTemporaryPassword(tempPassword);
	
	/*Save to struct*/
	thcEncryptPassword(tempPassword,encryptedPassword);
	strcpy(data->codedPassword,encryptedPassword);
	
	
	/*Writing data to new file*/
	if ((errorCode = thcWriteFile(data)) != THC_OK)
		return errorCode;
	
	/*Adding users to abeyances file*/
	memset(&abeyances,0x00,sizeof(thcUserAbeyancesType));
	abeyances.expiration = time(NULL) + THC_ABEYANCES_EXPIRATION;
	strcpy(abeyances.nickname,data->nickname);
	thcAddAbeyanceUser(abeyances,THC_ABEYANCES_FILE_NAME);
	
	
	/*Sends back plain password for confirmation process*/
	memset(data->codedPassword,0x00,THC_ENCRYPTED_PASSWORD_LENGHT+1);
	strncpy(data->codedPassword,tempPassword,THC_TEMP_PASSWORD_LENGHT+1);


	return 	THC_OK;

}
                                        
                                              
                                              
/*$RCSfile: thcAddUser.c,v $*/                                  
