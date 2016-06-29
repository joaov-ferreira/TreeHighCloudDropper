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
 * $Log: thcCleanAbeyanceUsers.c,v $
 * Revision 1.6  2013/04/06 18:55:09  joao.duarte
 * Final Revision for first part
 *
 * Revision 1.5  2013/03/26 21:52:50  joao.duarte
 * Now it will remove expirated cookies
 *
 * Revision 1.4  2013/03/24 03:31:05  joao.duarte
 * Now it will clean e-mail abeyances
 *
 * Revision 1.3  2013/03/22 21:26:36  joao.duarte
 * Now it will clean password abeyances and have a better output info
 *
 * Revision 1.2  2013/03/21 21:15:04  joao.duarte
 * *** empty log message ***
 *                                      
 */                                           
                                              
#include <stdlib.h>                           
#include <stdio.h>                            
#include <string.h>                                           
#include <unistd.h>
                                              
#include "thcConst.h"                       
#include "thcTypes.h"                       
#include "thcError.h"                       
#include "thcFunctions.h"                                             
#include "thcConfig.h"                            
                                              
int main (int argc, char *argv[])
{
	thcErrorType errorCode;
	thcUserDataType rawData;
	thcUserIdentifier lastId, currentId;
	FILE *abeyance,*original;
	thcUserAbeyancesType data;
	thcUserAbeyancePasswordType passData;
	thcUserAbeyanceEmailType mailData;
	time_t localTime, expiration;
	int fDescriptor;
	char tempFile			[THC_TEMP_FILE_NAME_LENGHT+1]			=		THC_TEMP_FILE_NAME;
	char cookieName			[THC_COOKIE_NAME_LENGHT + 1];
	char cookiePath			[THC_MAXIMUM_COOKIE_PATH + 1];
	char cookieContent 		[THC_COOKIE_CONTENT_LENGHT + 1];
	char cookieIP			[THC_COOKIE_MAXIMUM_IP_LENGHT + 1];
	
	/*Get local time*/
	localTime = time(NULL);
	printf("Cleaning expirated data at : %s",ctime(&localTime));
	
	printf(">>>>>>>>Now cleaning users abeyance file\n");
	
	/*Creates a temporary file*/
	fDescriptor = mkstemp(tempFile);
	if (fDescriptor == -1)
	{
		printf("On user abeyance file :\n");
		thcGetTextErrorMessage(THC_DEFAULT_LANGUAGE,THC_ERROR_MKSTEMP);
		exit (THC_ERROR_MKSTEMP);
	}
	abeyance = fdopen(fDescriptor,THC_WRITE);
	if (!abeyance)
	{
		printf("On user abeyance file :\n");
		thcGetTextErrorMessage(THC_DEFAULT_LANGUAGE,THC_ERROR_WRITING_FILE);
		exit (THC_ERROR_WRITING_FILE);
	}
	
	/*Open the original file*/
	original = fopen(THC_ABEYANCES_FILE_NAME,THC_READ);
	if (!original)
	{
		printf("On user abeyance file :\n");
		thcGetTextErrorMessage(THC_DEFAULT_LANGUAGE,THC_ERROR_READING_FILE);
		fclose(abeyance);
		remove(tempFile);
		exit(THC_ERROR_READING_FILE);
	}
	
	
	while (fread(&data,1,sizeof(thcUserAbeyancesType),original) != 0)
	{
		printf("Name :%s  Expiration:%s",data.nickname,ctime(&data.expiration));
		
		if (localTime > data.expiration)
		{
			if((errorCode = thcRemoveUserData(data.nickname)) != THC_OK)
			{
				printf("On user abeyance file :\n");
				thcGetTextErrorMessage(THC_DEFAULT_LANGUAGE,errorCode);
			}	
		}
		else
			if (fwrite(&data,1,sizeof(thcUserAbeyancesType),abeyance) != sizeof(thcUserAbeyancesType))
			{
				printf("On user abeyance file :\n");
				thcGetTextErrorMessage(THC_DEFAULT_LANGUAGE,THC_ERROR_WRITING_DATA_TO_FILE);
				fclose(original);
				fclose(abeyance);
				remove(tempFile);
				exit (THC_ERROR_WRITING_DATA_TO_FILE);
			}
	}
	
	fclose(abeyance);
	fclose(original);
	
	/*Overwrite the old file*/
	remove (THC_ABEYANCES_FILE_NAME);
	rename (tempFile,THC_ABEYANCES_FILE_NAME);

	thcGenerateTextFile();
	
	/***************Cleaning password reset abeyance**************/
	
	printf(">>>>>>>>Now cleaning passwords abeyance file\n");
	
	strcpy(tempFile, THC_TEMP_FILE_NAME);
	fDescriptor = mkstemp(tempFile);
	if (fDescriptor == -1)
	{
		printf("On passwords abeyance file :\n");
		thcGetTextErrorMessage(THC_DEFAULT_LANGUAGE,THC_ERROR_MKSTEMP);
		return THC_ERROR_MKSTEMP;
	}
	
	abeyance = fdopen(fDescriptor, THC_WRITE);
	if (!abeyance)
	{
		printf("On passwords abeyance file :\n");
		thcGetTextErrorMessage(THC_DEFAULT_LANGUAGE,THC_ERROR_WRITING_FILE);
		exit (THC_ERROR_WRITING_FILE);
	}
	
	/*Open the original file*/
	original = fopen(THC_ABEYANCES_PASSWORD_FILE_NAME,THC_READ);
	if (!original)
	{
		printf("On passwords abeyance file :\n");
		thcGetTextErrorMessage(THC_DEFAULT_LANGUAGE,THC_ERROR_READING_FILE);
		fclose(abeyance);
		remove(tempFile);
		exit(THC_ERROR_READING_FILE);
	}
	
	while (fread(&passData,1,sizeof(thcUserAbeyancePasswordType),original) != 0)
	{
		printf("UID :%llu  Expiration:%s",passData.UID,ctime(&passData.expiration));
		
		if (localTime > passData.expiration)
		{
			errorCode = thcClearUserFlag(passData.UID, passwordReset); 
			if (errorCode != THC_OK)
			{
				printf("On passwords abeyance file :\n");
				thcGetTextErrorMessage(THC_DEFAULT_LANGUAGE,errorCode);				
			}
		}
		
		else
			if (fwrite(&passData,1,sizeof(thcUserAbeyancePasswordType),abeyance) != sizeof(thcUserAbeyancePasswordType))
			{
				printf("On passwords abeyance file :\n");
				thcGetTextErrorMessage(THC_DEFAULT_LANGUAGE,THC_ERROR_WRITING_DATA_TO_FILE);
				fclose(original);
				fclose(abeyance);
				remove(tempFile);
				exit (THC_ERROR_WRITING_DATA_TO_FILE);
			}
	}
	
	
	
	
	fclose(abeyance);
	fclose(original);
	
	/*Overwrite the old file*/
	remove (THC_ABEYANCES_PASSWORD_FILE_NAME);
	rename (tempFile,THC_ABEYANCES_PASSWORD_FILE_NAME);
	
	
	/***********Cleaning the e-mail abeyances file************/
	
	printf(">>>>>>>>Now cleaning e-mail abeyance file\n");
	
	strcpy(tempFile, THC_TEMP_FILE_NAME);
	fDescriptor = mkstemp(tempFile);
	if (fDescriptor == -1)
	{
		printf("On e-mail abeyance file :\n");
		thcGetTextErrorMessage(THC_DEFAULT_LANGUAGE,THC_ERROR_MKSTEMP);
		return THC_ERROR_MKSTEMP;
	}
	
	abeyance = fdopen(fDescriptor, THC_WRITE);
	if (!abeyance)
	{
		printf("On e-mail abeyance file :\n");
		thcGetTextErrorMessage(THC_DEFAULT_LANGUAGE,THC_ERROR_WRITING_FILE);
		exit (THC_ERROR_WRITING_FILE);
	}
	
	/*Open the original file*/
	original = fopen(THC_ABEYANCES_EMAIL_FILE_NAME,THC_READ);
	if (!original)
	{
		printf("On e-mail abeyance file :\n");
		thcGetTextErrorMessage(THC_DEFAULT_LANGUAGE,THC_ERROR_READING_FILE);
		fclose(abeyance);
		remove(tempFile);
		exit(THC_ERROR_READING_FILE);
	}
	
	while (fread(&mailData,1,sizeof(thcUserAbeyanceEmailType),original) != 0)
	{
		printf("UID :%llu  Expiration:%s",mailData.UID,ctime(&mailData.expiration));
		
		/*e-mail change has expirated*/
		if (localTime > mailData.expiration)
		{
			errorCode = thcClearUserFlag(mailData.UID, emailChange); 
			if (errorCode != THC_OK)
			{
				printf("On e-mail abeyance file :\n");
				thcGetTextErrorMessage(THC_DEFAULT_LANGUAGE,errorCode);				
			}
			
			errorCode = thcRemoveFromEmailAbeyanceList(mailData.UID,-1);
			if (errorCode != THC_OK)
			{
				printf("On e-mail confirmation codes file :\n");
				thcGetTextErrorMessage(THC_DEFAULT_LANGUAGE,errorCode);				
			}
		}
		
		else
			if (fwrite(&mailData,1,sizeof(thcUserAbeyanceEmailType),abeyance) != sizeof(thcUserAbeyanceEmailType))
			{
				printf("On e-mail abeyance file :\n");
				thcGetTextErrorMessage(THC_DEFAULT_LANGUAGE,THC_ERROR_WRITING_DATA_TO_FILE);
				fclose(original);
				fclose(abeyance);
				remove(tempFile);
				exit (THC_ERROR_WRITING_DATA_TO_FILE);
			}
	}
	
	
	fclose(abeyance);
	fclose(original);
	
	/*Overwrite the old file*/
	remove (THC_ABEYANCES_EMAIL_FILE_NAME);
	rename (tempFile,THC_ABEYANCES_EMAIL_FILE_NAME);
	
	/***************Cleaning expirated cookies********************/
	
	printf(">>>>>>>>Now cleaning expirated cookies\n");
	
	
	/*Get the last UID*/
	original = fopen (THC_FILE_NAME,THC_READ);
	if (!original)
	{
		printf("On cookie cleaning : \n");
		thcGetTextErrorMessage(THC_DEFAULT_LANGUAGE,errorCode);
		exit(errorCode);
	}
	
	while (fread(&rawData,1,sizeof(thcUserDataType),original) != 0);
	
	lastId = rawData.UID;
	
	/*Search for all cookies and remove old ones*/
	for (currentId = 0; currentId <= lastId; currentId++)
	{
		sprintf(cookieName,THC_COOKIE_NAME_PRINTF_FORMAT,currentId);
		strcpy(cookiePath,THC_DEFAULT_COOKIE_DIRECTORY);
		strcat(cookiePath,cookieName);
		/*Check if fille exists*/
		if (access(cookiePath,F_OK) == 0)
		{
			errorCode = thcReadCookie(cookieName,&expiration,cookieContent,cookieIP);
			if (errorCode != THC_OK)
			{
				printf("On cookie cleaning : \n");
				thcGetTextErrorMessage(THC_DEFAULT_LANGUAGE,errorCode);
				exit(errorCode);
			}
			printf("id : %llu expiration : %s",currentId,ctime(&expiration));
			
			/*cookiePath here = cookie name with full path*/
			if (localTime > expiration)	remove(cookiePath);			
		}
	}
		
	printf("Successfull removed expirated data\n");
	return THC_OK;
}                                          
                                           
/*$RCSfile: thcCleanAbeyanceUsers.c,v $*/                                  
