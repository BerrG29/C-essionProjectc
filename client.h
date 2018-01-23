//
// Created by ski on 22/01/18.
//

#ifndef C_ESSIONPROJECTC_CLIENT_H
#define C_ESSIONPROJECTC_CLIENT_H

/**
 * Function to get a table saved on the remote server
 * @param url url of the remote server
 * @return
 */
char *client_get(char *url);

/**
 * Function to save a new table
 * @param url url of the remote server
 * @param data table to save
 * @return
 */
char *client_post(char *url, char *data);

#endif //C_ESSIONPROJECTC_CLIENT_H
