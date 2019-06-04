#ifndef DATABASE_H_INCLUDED
#define DATABASE_H_INCLUDED

#include <mysql/mysql.h>
#include <stdio.h>
#include <stdlib.h>

/*Variables de conexión para MySQL*/
MYSQL *conn;

/*Variable que contendra el resultado de la consulta*/
MYSQL_RES *res;

/*Variable que contendra los campos por cada regitro o consulta*/
MYSQL_ROW row;

void conectionDB();
int get_idUser(char*);
char* get_users_no_start_game(int);
char* get_question_with_answers(int, int);
void register_turno(int, int, int);

#endif // DATABASE_H_INCLUDED