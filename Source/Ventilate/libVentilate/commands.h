/*! \file
 * \brief Defines all network commands used by Ventilate.
 * \details Ventilate's networking commands are declared here as constant
 * QStrings.
 * \author Ryan Porterfield
 * \copyright BSD 3 Clause
 * \since 2015-10-30
 */

#ifndef COMMANDS
#define COMMANDS

#include <QString>

/*!
 * \brief Accept or acknowlege a valid command.
 *
 * Used to inform a client that a command was successful.
 * IE. If a client sends the server a LOGIN command with valid credentials the
 * server would reply with an ACCEPT.
 */
extern const QString ACCEPT;

/*!
 * \brief Defines common root for all account related commands.
 * \sa PASSWORD
 */
extern const QString ACCOUNT;

/*!
 * \brief Command to the server to create a new user account.
 *
 * A proper account create request is formatted as:
 * ACCOUNT CREATE <username> <password hash>
 */
extern const QString ACCOUNT_CREATE;

/*!
 * \brief Command to the server to delete a user account.
 *
 * A proper account delete request is formatted as:
 * ACCOUNT DELETE <username> <password hash>
 */
extern const QString ACCOUNT_DELETE;

/*!
 * \brief Defines common root for all commands which are create functions.
 */
extern const QString CREATE;

/*!
 * \brief Defines common root for all commands which are delete functions.
 */
extern const QString DELETE;

/*!
 * \brief Defines common root for all history related commands.
 */
extern const QString HISTORY;

/*!
 * \brief Defines common root for all list related commands.
 */
extern const QString LIST;

/*!
 * \brief Command to the server to login a user.
 *
 * A proper login command is formatted as:
 * LOGIN <username> <password hash>
 */
extern const QString LOGIN;

/*!
 * \brief Defines common root for all password related commands.
 *
 * Some Ventilate commands are multipare commands, such as password
 * related commands. Any command that requests or modifies a user
 * password should start with the PASSWORD string. IE. The change
 * password command is
 * "PASSWORD CHANGE <username> <password hash>"
 * and the password reset command is
 * "PASSWORD RESET <usernam>".
 * Both commands start with the common root PASSWORD which is defined here.
 */
extern const QString PASSWORD;

/*!
 * \brief Command to the server to change a user's password.
 *
 * A proper password change request is formatted as:
 * PASSWORD CHANGE <username> <old password hash> <new password hash>
 */
extern const QString PASSWORD_CHANGE;

/*!
 * \brief Command to the server to reset a user's password.
 *
 * A proper password change request is formatted as:
 * PASSWORD RESET <username>
 */
extern const QString PASSWORD_RESET;

/*!
 * \brief Defines common root for all peer related commands.
 * \sa PASSWORD
 */
extern const QString PEER;

/*!
 * \brief Defines common root for all peer list commands.
 *
 * This command is used to send a list of peers in the form:
 * "PEER LIST <whitespace separated list of IP addresses>"
 * This command is also the root command for the peer list request
 * command.
 *
 * \sa PASSWORD
 */
extern const QString PEER_LIST;

/*!
 * \brief Command to the server or network to get list of connected clients/peers.
 *
 * A proper peer list request is formatted as:
 * PEER LIST REQUEST
 */
extern const QString PEER_LIST_REQUEST;

/*!
 * \brief Reject an invalid command.
 *
 * Used to inform a client that a command was unsuccessful.
 * IE. If a client sends the server a LOGIN command with invalid credentials the
 * server would reply with a REJECT.
 */
extern const QString REJECT;

/*!
 * \brief Defines common root for all requests related commands.
 */
extern const QString REQUEST;

/*!
 * \brief Defines common root for all chat room commands.
 * \sa PASSWORD
 */
extern const QString ROOM;

/*!
 * \brief Command to the network to add a user to a private chat room.
 *
 * A proper room add command is formatted as:
 * ROOM ADD <username> <chat room UUID>
 */
extern const QString ROOM_ADD;

/*!
 * \brief Command to the network to create a new chat room.
 *
 * A proper room create command is formatted as:
 * ROOM CREATE <public|private> <room name>
 */
extern const QString ROOM_CREATE;

/*!
 * \brief Command to the network to delete a chat room.
 *
 * A proper room delete command is formatted as:
 * ROOM DELETE <room UUID>
 */
extern const QString ROOM_DELETE;

/*!
 * \brief Defines common root for all room history commands.
 *
 * This command is used to send a list of peers in the form:
 * ROOM HISTORY <history>
 * This command is also the root for the peer list request command.
 *
 * \sa PASSWORD
 */
extern const QString ROOM_HISTORY;

/*!
 * \brief Command to the network to get chat history from a chat room.
 *
 * A proper room history reqest is formatted as:
 * ROOM HISTORY REQUEST
 */
extern const QString ROOM_HISTORY_REQUEST;

/*!
 * \brief Command to the network for a user to join a public chat room.
 *
 * A proper room join command is formatted as:
 * ROOM JOIN <room UUID> <username>
 */
extern const QString ROOM_JOIN;

/*!
 * \brief Command to the network for a user to leave a chat room.
 *
 * A proper room leave command is formatted as:
 * ROOM LEAVE <room UUID> <username>
 */
extern const QString ROOM_LEAVE;

/*!
 * \brief Defines common root for all room list commands.
 *
 * This command is used to send a list of peers in the form:
 * ROOM LIST <list of public room names>
 * This command is also the root for the room list request command.
 */
extern const QString ROOM_LIST;

/*!
 * \brief Command to the network to get a list of public chat rooms.
 *
 * A proper room list request is formatted as:
 * ROOM LIST REQUEST
 */
extern const QString ROOM_LIST_REQUEST;

/*!
 * \brief Command to the network to send a message in a chat room.
 *
 * A proper room message command is formatted as:
 * ROOM MESSAGE <room UUID> <date time> <sender> <message>
 */
extern const QString ROOM_MESSAGE;

/*!
 * \brief Command to the network to change a chat room's mode.
 *
 * A proper room mode command is formatted as:
 * ROOM MODE <public|private> <username>
 */
extern const QString ROOM_MODE;

#endif // COMMANDS

/* ************************************************************************* *
 *                                    EOF                                    *
 * ************************************************************************* */
