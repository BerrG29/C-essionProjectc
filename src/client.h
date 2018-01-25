//
// Created by ski on 22/01/18.
//

#ifndef C_ESSIONPROJECTC_CLIENT_H
#define C_ESSIONPROJECTC_CLIENT_H

int send_matrix(int line_len, int column_len, char **matrix, char *adr_server_odd, char *adr_server_pair);

char **get_matrix_n_iteration(char *adr_server_odd, char *adr_server_pair, int n);

int matrix_is_stable(char *adr_server_odd, char *adr_server_pair);

int matrix_is_cyclic(char *adr_server_odd, char *adr_server_pair);

#endif //C_ESSIONPROJECTC_CLIENT_H
