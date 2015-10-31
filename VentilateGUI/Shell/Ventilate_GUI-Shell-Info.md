#[Ventilate GUI - Shell](https://github.com/AuHoppe/CSE.4444-002-Grp-Project/tree/master/VentilateGUI/Shell)
This directory is **only** for the basic GUI elements and the code to back them.
Functional code belongs in the [**Functional**](https://github.com/AuHoppe/CSE.4444-002-Grp-Project/tree/master/VentilateGUI) directory and production ready code in the [**Production**](https://github.com/AuHoppe/CSE.4444-002-Grp-Project/tree/master/VentilateGUI) directory.

##Calling Structure
* MainWindow
  * Login
    * New User
  * Change Password
  * Create Chatroom
  * Report Chatroom
  * Help
  * About

## Files
* Ventilate.pro

#### Headers
* mainwindow.h
* ventilate_login.h
* ventilate_newuser.h
* ventilate_changepassword.h
* ventilate_joinchat.h
* ventilate_createchat.h
* ventilate_leavechat.h
* ventilate_reportchat.h
* ventilate_help.h
* ventilate_about.h

#### C++ Source Files
* main.cpp
* mainwindow.cpp
* ventilate_login.cpp
* ventilate_newuser.cpp
* ventilate_changepassword.cpp
* ventilate_joinchat.cpp
* ventilate_createchat.cpp
* ventilate_leavechat.cpp
* ventilate_reportchat.cpp
* ventilate_help.cpp
* ventilate_about.cpp

#### Forms
* mainwindow.ui
* ventilate_login.ui
* ventilate_newuser.ui
* ventilate_changepassword.ui
* ventilate_joinchat.ui
* ventilate_createchat.ui
* ventilate_leavechat.ui
* ventilate_reportchat.ui
* ventilate_help.ui
* ventilate_about.ui

#### Resources
* ventilate-shell_resources.qrc
  * /
   * Ventilate.svg
   * WelcometoVentilate.svg
 
## Classes _Tenative_
#### MainWindow
* Slots
  * void on_actionLogin_triggered()
  * void on_actionLogout_triggered()
  * void on_actionChange_Password_triggered()
  * void on_actionExit_triggered()
  * void on_actionJoin_Chatroom_triggered()
  * void on_actionLeave_Chatroom_triggered()
  * void on_actionCreate_Chatroom_triggered()
  * void on_actionReport_Chatroom_triggered()
  * void on_actionHelp_triggered()
  * void on_actionAbout_triggered()
  * void on_ptxtMessageBox_textchanged()
  * void on_btnClear_clicked()
  * void on_btnEnter_clicked()

#### About *_TBD_*

#### Chnage Password *_TBD_*

#### Create Chatroom
* Slots
  * void on_cboPBorPV_currentIndexChanged (int index)
  * void on_rbtnPBUattnYes_clicked()
  * void on_rbtnPBUattnNo_clicked()
  * void on_rbtnPBExitYes_clicked()
  * void on_rbtnPBUExitNo_clicked()

#### Help *_TBD_*

#### Join Chatroom *_TBD_*

#### Leave Chatroom *_TBD_*

#### Login
* Slots
  * void on_btnLogin_clicked()
  * void on_btnNewUser_clicked()

#### New User
* Slots
  * void on_lnedUsername_textChanged(const QString &arg1)
  * void on_lnedPassword_textChanged(const QString &arg1)
  * void on_lnedConfirmPass_textChanged(const QString &arg1)
  * void on_btnSubmit_clicked()
  * void on_btnCancel_clicked()

#### Report Chatroom *_TBD_*
