# Uversidade Federal do Rio de Janeiro
# Escola Politecnica
# Departamento de Eletronica e de Computacao
#
# Prof. Marcelo Luiz Drumond Lanza
# EEL270 - Computacao II - Turma 2012/2
#
# Autor: João Vítor Ferreira Duarte
# Turma : EL2
#
# $Author: joao.duarte $
# $Date: 2013/04/06 18:48:33 $
# $Log: Makefile,v $
# Revision 1.5  2013/04/06 18:48:33  joao.duarte
# Final revision for first part
#
# Revision 1.4  2013/03/26 02:44:05  joao.duarte
# Added some new cgi's (change e-mail)
#
# Revision 1.3  2013/03/22 21:25:46  joao.duarte
# Added Cleaner user default text error menssages
#
# Revision 1.2  2013/03/21 21:07:01  joao.duarte
# Added cleaner
#
# Revision 1.1  2013/03/20 23:05:16  joao.duarte
# Initial revision
#
#

#Compiler
CC = gcc 

#Linker
LD = gcc 

#Flags
CFLAGS = -Wall
LFLAGS = -Wall

#main program
THC_OBJS = thc.o thcFunctions.o thcAddUser.o thcShowCliHelp.o thcChangeUserPassword.o thcRunNcursesInterface.o thcError.o thcEditUserName.o thcAddUserToGroup.o thcChangeUserGroup.o thcRemoveUser.o thcShowNcursesHelp.o

#Abeyance cleaner
THC_CLEANER_OBJS = thcCleanAbeyanceUsers.o thcFunctions.o thcError.o

#Cgi's
THC_LOGIN_CGI_OBJS = thcLoginCgi.o thcFunctions.o thcError.o thcRenewCookie.o
THC_REGISTER_CGI_OBJS = thcRegisterCgi.o thcFunctions.o thcAddUser.o thcError.o thcRenewCookie.o
THC_CHANGE_PASSWORD_OBJS = thcChangePasswordCgi.o thcFunctions.o thcChangeUserPassword.o thcError.o thcRenewCookie.o
THC_HOME_CGI_OBJS = thcHomeCgi.o thcFunctions.o thcError.o thcRenewCookie.o
THC_CHANGE_NAME_OBJS = thcChangeUsernameCgi.o thcFunctions.o thcEditUserName.o thcError.o thcRenewCookie.o
THC_INVITE_OBJS = thcInviteUserCgi.o thcFunctions.o thcAddUser.o thcError.o thcRenewCookie.o
THC_RESET_PASSWORD_OBJS = thcResetPasswordCgi.o thcFunctions.o thcError.o thcRenewCookie.o
THC_CHANGE_EMAIL_OBJS = thcChangeEmailCgi.o thcFunctions.o thcChangeUserEmail.o thcError.o thcRenewCookie.o
THC_DENY_USER_EMAIL_CGI_OBJS = thcDenyNewUserEmail.o thcDenyEmailCgi.o thcFunctions.o thcError.o thcRenewCookie.o
THC_CONFIRM_USER_EMAIL_CGI_OBJS = thcConfirmNewUserEmail.o thcConfirmEmailCgi.o thcFunctions.o thcError.o thcRenewCookie.o
THC_LOGOUT_CGI_OBJS = thcLogoutCgi.c thcFunctions.o thcError.o thcRenewCookie.o
THC_CHANGE_GROUP_OBJS = thcChangeGroupCgi.o thcFunctions.o thcError.o thcChangeUserGroup.o thcRenewCookie.o
THC_ADD_TO_GROUP_OBJS = thcAddToGroupCgi.o thcFunctions.o thcError.o thcAddUserToGroup.o thcRenewCookie.o
THC_REMOVE_USER_OBJS = thcRemoveUserCgi.o thcFunctions.o thcError.o thcRemoveUser.o thcRenewCookie.o
THC_SHOW_HELP_OBJS = thcShowHelpCgi.o thcFunctions.o thcError.o thcRenewCookie.o

#Form Cgi's
THC_SHOW_CHANGE_PASS_OBJS = thcCgiShowChangePasswordForm.o thcFunctions.o thcError.o thcRenewCookie.o
THC_SHOW_REGISTER_OBJS = thcCgiShowRegisterForm.o	thcFunctions.o thcError.o thcRenewCookie.o
THC_SHOW_REGISTER_OBJS = thcCgiShowRegisterForm.o	thcFunctions.o thcError.o thcRenewCookie.o
THC_SHOW_INVITE_USER_OBJS = thcCgiShowInviteUserForm.o thcFunctions.o thcError.o thcRenewCookie.o
THC_SHOW_CHANGE_NAME_OBJS = thcCgiShowChangeUsernameForm.c thcFunctions.o thcError.o thcRenewCookie.o
THC_SHOW_RESET_PASS_OBJS = thcCgiShowResetPasswordForm.o thcFunctions.o thcError.o thcRenewCookie.o
THC_SHOW_CHANGE_EMAIL_OBJS = thcCgiShowChangeEmailForm.o thcFunctions.o thcChangeUserEmail.o thcError.o thcRenewCookie.o
THC_SHOW_CHANGE_GROUP_OBJS = thcCgiShowChangeUserGroupForm.o thcError.o thcFunctions.o thcRenewCookie.o
THC_SHOW_ADD_GROUP_OBJS = thcCgiShowAddUserGroupForm.o thcError.o thcFunctions.o thcRenewCookie.o
THC_SHOW_REMOVE_USER_OBJS = thcCgiShowRemoveUserForm.o thcError.o thcFunctions.o thcRenewCookie.o

#libraries
THC_LIBS = -lcrypt -lncurses -lmenu -L.-l libraries/libsendmail.a -L.-l libraries/libmlcgi.a

#default directories
THC_DEFAULT_CGI_DIRECTORY = /users/joao.duarte/public/html/eel270/thc/cgis/
THC_DEFAULT_HTML_DIRECTORY = /users/joao.duarte/public/html/eel270/thc/
THC_DEFAULT_CSS_DIRECTORY = /users/joao.duarte/public/html/eel270/thc/css/
THC_DEFAULT_BINARIES_DIRECTORY = /users/joao.duarte/private/eel270/thc/binaries/

#Some configuration
THC_DEFAULT_HTML_FILE = index_en.html

# All files
MAIN = thc\
	   thcCleaner
		  

CGI	= thcCgiShowRegisterForm.cgi\
	  thcLogin.cgi\
	  thcCgiShowChangePasswordForm.cgi\
	  thcRegister.cgi\
	  thcChangePassword.cgi\
	  thcCgiShowInviteUserForm.cgi\
	  thcHome.cgi\
	  thcCgiShowChangeUsernameForm.cgi\
	  thcChangeUsername.cgi\
	  thcInviteUser.cgi\
	  thcCgiShowResetPasswordForm.cgi\
	  thcResetPassword.cgi\
	  thcCgiShowChangeUserEmailForm.cgi\
	  thcChangeUserEmail.cgi\
	  thcDenyEmail.cgi\
	  thcConfirmEmail.cgi\
	  thcLogout.cgi\
	  thcCgiShowChangeUserGroup.cgi\
	  thcCgiShowAddUserToGroup.cgi\
	  thcChangeGroup.cgi\
	  thcAddUserToGroup.cgi\
	  thcCgiShowRemoveUserForm.cgi\
	  thcRemoveUser.cgi\
	  thcShowHelp.cgi

ALL = $(MAIN)\
	  $(CGI)	

		  
# Regra Implicita
.c.o:
	$(CC) $(CFLAGS) -c $<

all: $(ALL)

main : $(MAIN)

cgi : $(CGI)


#Executables
thc: $(THC_OBJS)
	$(LD) $(LFLAGS) -o $@ $(THC_OBJS) $(THC_LIBS)

thcCleaner : $(THC_CLEANER_OBJS)
	$(LD) $(LFLAGS) -o $@ $(THC_CLEANER_OBJS) $(THC_LIBS)

#Cgi's
thcLogin.cgi: $(THC_LOGIN_CGI_OBJS)
	$(LD) $(LFLAGS) -o $@ $(THC_LOGIN_CGI_OBJS) $(THC_LIBS)

thcRegister.cgi : $(THC_REGISTER_CGI_OBJS)
	$(LD) $(LFLAGS) -o $@ $(THC_REGISTER_CGI_OBJS) $(THC_LIBS)

thcCgiShowRegisterForm.cgi : $(THC_SHOW_REGISTER_OBJS)
	$(LD) $(LFLAGS) -o $@ $(THC_SHOW_REGISTER_OBJS) $(THC_LIBS)

thcCgiShowChangePasswordForm.cgi : $(THC_SHOW_CHANGE_PASS_OBJS)
	$(LD) $(LFLAGS) -o $@ $(THC_SHOW_CHANGE_PASS_OBJS) $(THC_LIBS)

thcChangePassword.cgi : $(THC_CHANGE_PASSWORD_OBJS)
	$(LD) $(LFLAGS) -o $@ $(THC_CHANGE_PASSWORD_OBJS) $(THC_LIBS)

thcCgiShowInviteUserForm.cgi : $(THC_SHOW_INVITE_USER_OBJS)
	$(LD) $(LFLAGS) -o $@ $(THC_SHOW_INVITE_USER_OBJS) $(THC_LIBS)

thcHome.cgi : $(THC_HOME_CGI_OBJS)
	$(LD) $(LFLAGS) -o $@ $(THC_HOME_CGI_OBJS) $(THC_LIBS)

thcCgiShowChangeUsernameForm.cgi : $(THC_SHOW_CHANGE_NAME_OBJS)
	$(LD) $(LFLAGS) -o $@ $(THC_SHOW_CHANGE_NAME_OBJS) $(THC_LIBS)
	
thcChangeUsername.cgi : $(THC_CHANGE_NAME_OBJS)
	$(LD) $(LFLAGS) -o $@ $(THC_CHANGE_NAME_OBJS) $(THC_LIBS)
	
thcInviteUser.cgi : $(THC_INVITE_OBJS)
	$(LD) $(LFLAGS) -o $@ $(THC_INVITE_OBJS) $(THC_LIBS)

thcCgiShowResetPasswordForm.cgi : $(THC_SHOW_RESET_PASS_OBJS)
	$(LD) $(LFLAGS) -o $@ $(THC_SHOW_RESET_PASS_OBJS) $(THC_LIBS)

thcResetPassword.cgi : $(THC_RESET_PASSWORD_OBJS)
	$(LD) $(LFLAGS) -o $@ $(THC_RESET_PASSWORD_OBJS) $(THC_LIBS)
	
thcCgiShowChangeUserEmailForm.cgi : $(THC_SHOW_CHANGE_EMAIL_OBJS)
	$(LD) $(LFLAGS) -o $@ $(THC_SHOW_CHANGE_EMAIL_OBJS) $(THC_LIBS)

thcChangeUserEmail.cgi : $(THC_CHANGE_EMAIL_OBJS)
	$(LD) $(LFLAGS) -o $@ $(THC_CHANGE_EMAIL_OBJS) $(THC_LIBS)

thcDenyEmail.cgi : $(THC_DENY_USER_EMAIL_CGI_OBJS)
	$(LD) $(LFLAGS) -o $@ $(THC_DENY_USER_EMAIL_CGI_OBJS) $(THC_LIBS)

thcConfirmEmail.cgi : $(THC_CONFIRM_USER_EMAIL_CGI_OBJS)
	$(LD) $(LFLAGS) -o $@ $(THC_CONFIRM_USER_EMAIL_CGI_OBJS) $(THC_LIBS)

thcLogout.cgi : $(THC_LOGOUT_CGI_OBJS)
	$(LD) $(LFLAGS) -o $@ $(THC_LOGOUT_CGI_OBJS) $(THC_LIBS)

thcCgiShowChangeUserGroup.cgi : $(THC_SHOW_CHANGE_GROUP_OBJS)
	$(LD) $(LFLAGS) -o $@ $(THC_SHOW_CHANGE_GROUP_OBJS) $(THC_LIBS)
		
thcCgiShowAddUserToGroup.cgi : $(THC_SHOW_ADD_GROUP_OBJS)
	$(LD) $(LFLAGS) -o $@ $(THC_SHOW_ADD_GROUP_OBJS) $(THC_LIBS)

thcChangeGroup.cgi : $(THC_CHANGE_GROUP_OBJS)
	$(LD) $(LFLAGS) -o $@ $(THC_CHANGE_GROUP_OBJS) $(THC_LIBS)

thcAddUserToGroup.cgi : $(THC_ADD_TO_GROUP_OBJS)
	$(LD) $(LFLAGS) -o $@ $(THC_ADD_TO_GROUP_OBJS) $(THC_LIBS)

thcCgiShowRemoveUserForm.cgi : $(THC_SHOW_REMOVE_USER_OBJS)
	$(LD) $(LFLAGS) -o $@ $(THC_SHOW_REMOVE_USER_OBJS) $(THC_LIBS)

thcRemoveUser.cgi : $(THC_REMOVE_USER_OBJS)
	$(LD) $(LFLAGS) -o $@ $(THC_REMOVE_USER_OBJS) $(THC_LIBS)

thcShowHelp.cgi : $(THC_SHOW_HELP_OBJS)
	$(LD) $(LFLAGS) -o $@ $(THC_SHOW_HELP_OBJS) $(THC_LIBS)

install : $(ALL)
	mkdir -p $(THC_DEFAULT_HTML_DIRECTORY)
	mkdir -p $(THC_DEFAULT_HTML_DIRECTORY)cgis/
	mkdir -p $(THC_DEFAULT_HTML_DIRECTORY)css/
	mkdir -p $(THC_DEFAULT_HTML_DIRECTORY)images/
	mv -f $(CGI) $(THC_DEFAULT_CGI_DIRECTORY)
	mv -f $(MAIN) $(THC_DEFAULT_BINARIES_DIRECTORY)
	cp -f ../html/*.html $(THC_DEFAULT_HTML_DIRECTORY)
	cp -f ../html/*.css $(THC_DEFAULT_CSS_DIRECTORY)
	ln -sfv $(THC_DEFAULT_HTML_DIRECTORY)$(THC_DEFAULT_HTML_FILE) $(THC_DEFAULT_HTML_DIRECTORY)index.html
	ln -sfv $(THC_DEFAULT_HTML_DIRECTORY)$(THC_DEFAULT_HTML_FILE) $(THC_DEFAULT_HTML_DIRECTORY)cgis/index.html
	ln -sfv $(THC_DEFAULT_CSS_DIRECTORY) $(THC_DEFAULT_HTML_DIRECTORY)cgis/css/
	ln -sfv $(THC_DEFAULT_HTML_DIRECTORY)images/ $(THC_DEFAULT_HTML_DIRECTORY)cgis/images/
	
uninstall :	
	rm -f ../binaries/*
	rm -f $(THC_DEFAULT_CGI_DIRECTORY)*
	rm -f *.o

clean:
	rm -f *.o $(ALL)


# $RCSfile: Makefile,v $ 
