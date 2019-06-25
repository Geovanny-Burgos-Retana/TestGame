#include "Database.h"
#include "Server.h"

char buffer[MSG_LEN];

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
    memset(buffer, 0, sizeof(buffer));
    sprintf(query, "CALL CREATE_CLIENTE('%s')", username);
    printf("\n=> Request to database. Query: %s\n", query);

    if(mysql_query(conn, query)){
        fprintf(stderr, "Error %s\n", mysql_error(conn));
        exit(1);
    }

    res = mysql_use_result(conn);
    if((row = mysql_fetch_row(res)) != NULL) {
        mysql_close(conn); // Quitar si da error
        return atoi(row[0]);
    }
    mysql_close(conn);
    return 1;
}

char* get_users_no_start_game(int id_user) {
    conectionDB();
    char query[255];
    char str[32];
    memset(buffer, 0, sizeof(buffer));
    sprintf(query, "CALL GET_USERS_START_GAME(%d)", id_user);
    printf("\n=> Request to database. Query: %s\n", query);

    if(mysql_query(conn, query)){
        fprintf(stderr, "Error %s\n", mysql_error(conn));
        exit(1);
    }

    res = mysql_use_result(conn);
    while((row = mysql_fetch_row(res)) != NULL) {
        strcat(buffer, row[0]); strcat(buffer, ". "); strcat(buffer, row[1]);  strcat(buffer, "\n");
    }    
    mysql_close(conn);
    return buffer;
}

char* get_question_with_answers(int id_user1, int id_user2) { //user1 responde user2 adivina
    conectionDB();
    char query[255];
    char str[32];
    int question;
    memset(buffer, 0, sizeof(buffer));
    sprintf(query, "CALL get_question(%d, %d)", id_user1, id_user2);
    printf("\n=> Request to database. Query: %s\n", query);

    if(mysql_query(conn, query)){
        fprintf(stderr, "Error %s\n", mysql_error(conn));
        exit(1);
    }

    res = mysql_use_result(conn);
    if((row = mysql_fetch_row(res)) != NULL) {
        strcat(buffer, row[1]);  strcat(buffer, "\n");
        question = atoi(row[0]);
    }
    mysql_close(conn);
    conectionDB();

    sprintf(query, "CALL get_answers(%d)", question);
    printf("\n=> Request to database. Query: %s\n", query);

    if(mysql_query(conn, query)){
        fprintf(stderr, "Error %s\n", mysql_error(conn));
        exit(1);
    }

    res = mysql_use_result(conn);
    while((row = mysql_fetch_row(res)) != NULL) {
        strcat(buffer, row[1]);  strcat(buffer, "\n");
    }
    mysql_close(conn);
    return buffer;
}

void register_turno(int id_user1, int id_user2, int res) {
    conectionDB();
    char query[255];
    char str[32];
    memset(buffer, 0, sizeof(buffer));
    sprintf(query, "CALL create_turno(%d, %d, %d)", id_user1, id_user2, res);
    printf("\n=> Request to database. Query: %s\n", query);

    if(mysql_query(conn, query)){
        fprintf(stderr, "Error %s\n", mysql_error(conn));
        exit(1);
    }
    mysql_close(conn);
}

char* get_pending_games(int id_user) {
    conectionDB();
    char query[255];
    char str[32];
    memset(buffer, 0, sizeof(buffer));
    sprintf(query, "CALL get_pending_games(%d)", id_user);
    printf("\n=> Request to database. Query: %s\n", query);

    if(mysql_query(conn, query)){
        fprintf(stderr, "Error %s\n", mysql_error(conn));
        exit(1);
    }

    res = mysql_use_result(conn);
    while((row = mysql_fetch_row(res)) != NULL) {
        strcat(buffer, row[0]); strcat(buffer, ". "); strcat(buffer, row[1]);  strcat(buffer, "\n");
    }    
    mysql_close(conn);
    return buffer;
}

int pending_question(int id_user_res, int id_user_adv) {
    conectionDB();
    char query[255];
    char str[32];
    memset(buffer, 0, sizeof(buffer));
    sprintf(query, "CALL GET_PENDING_GAME_SPECIFIC(%d, %d)", id_user_res, id_user_adv);
    printf("\n=> Request to database. Query: %s\n", query);

    if(mysql_query(conn, query)){
        fprintf(stderr, "Error %s\n", mysql_error(conn));
        exit(1);
    }

    res = mysql_use_result(conn);
    if((row = mysql_fetch_row(res)) != NULL) {
        mysql_close(conn);
        return atoi(row[0]);       
    }    
    mysql_close(conn);
    return 1;
}


char* get_question_with_answers2(int id_pregunta) {
    conectionDB();
    char query[255];
    char str[32];
    int question;
    memset(buffer, 0, sizeof(buffer));
    sprintf(query, "SELECT * FROM pregunta WHERE id_pregunta = %d", id_pregunta);
    printf("\n=> Request to database. Query: %s\n", query);

    if(mysql_query(conn, query)){
        fprintf(stderr, "Error %s\n", mysql_error(conn));
        exit(1);
    }

    res = mysql_use_result(conn);
    if((row = mysql_fetch_row(res)) != NULL) {
        strcat(buffer, row[1]);  strcat(buffer, "\n");
        question = atoi(row[0]);
    }
    mysql_close(conn);
    conectionDB();

    sprintf(query, "CALL get_answers(%d)", question);
    printf("\n=> Request to database. Query: %s\n", query);

    if(mysql_query(conn, query)){
        fprintf(stderr, "Error %s\n", mysql_error(conn));
        exit(1);
    }

    res = mysql_use_result(conn);
    while((row = mysql_fetch_row(res)) != NULL) {
        strcat(buffer, row[1]);  strcat(buffer, "\n");
    }
    mysql_close(conn);
    return buffer;
}

void udpate_turno(int id_user_res, int id_user_adv, int id_res, int id_question) {
    conectionDB();
    char query[255];
    char str[32];
    memset(buffer, 0, sizeof(buffer));
    sprintf(query, "CALL ACTUALIZAR_READY_TURNO(%d, %d, %d, %d)", id_user_res, id_user_adv, id_res, id_question);
    printf("\n=> Request to database. Query: %s\n", query);

    if(mysql_query(conn, query)){
        fprintf(stderr, "Error %s\n", mysql_error(conn));
        exit(1);
    }
    mysql_close(conn);
}