#include "Database.h"

/*Dirección del servidor*/
char *serverdb = "localhost";

/*usuario para consultar la base de datos*/
char *user = "root";

/*contraeña de labase de datos  consutar*/
char *password = "gio_97$";

/*nombre de labase de datos a consultar*/
char *database = "test_game_so";

void conectionDB() {
    /* Inicializar conexión */
    conn = mysql_init(NULL);

    /* Conectar al servidor y a ala base de datos */
    if(!mysql_real_connect(conn, serverdb, user, password, database, 0, NULL, 0)) {        
        fprintf(stderr, "%s\n", mysql_error(conn));        
        exit(1);
    }
}

int get_idUser(char* username){
    conectionDB();
    char query[255];
    sprintf(query, "CALL CREATE_CLIENTE('%s')", username);
    printf("\n=> Request to database. Query: %s\n", query);

    if(mysql_query(conn, query)){
        fprintf(stderr, "Error %s\n", mysql_error(conn));
        exit(1);
    }

    res = mysql_use_result(conn);
    if((row = mysql_fetch_row(res)) != NULL) {
        return atoi(row[0]);
    }
    mysql_close(conn);
    return 1;
}

void get_users_no_start_game(int id_user) {
    conectionDB();
    char query[255];
    sprintf(query, "CALL GET_USERS_START_GAME(%d)", id_user);
    printf("\n=> Request to database. Query: %s\n", query);

    if(mysql_query(conn, query)){
        fprintf(stderr, "Error %s\n", mysql_error(conn));
        exit(1);
    }

    res = mysql_use_result(conn);
    while((row = mysql_fetch_row(res)) != NULL) {
        printf("%d %s\n", row[0], row[1]);
    }
    mysql_close(conn);
}
