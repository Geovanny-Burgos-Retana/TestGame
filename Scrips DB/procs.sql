USE test_game_so;

/*Juegos pendientes*/
DELIMITER $$
CREATE PROCEDURE SELECT_JUEGOS_PENDIENTES (
	IN p_cliente INT
)
BEGIN
	SELECT id_cliente_respuesta
    FROM turno
    WHERE id_cliente_respuesta = p_cliente;
END$$

/*Puntaje*/
DELIMITER $$
CREATE PROCEDURE SELECT_MAYOR_PUNTAJE (
	IN p_cliente1 INT,
    IN p_cliente2 INT
)
BEGIN
	SELECT COUNT(Id_turno) AS puntaje
    FROM turno
    WHERE id_cliente_respuesta = p_cliente1 and
    id_cliente_adivina = p_cliente2 and
    ready = true and
    id_cliente_respuesta = id_respuesta_cliente_adivina;
END$$


DELIMITER $$
CREATE PROCEDURE CREATE_CLIENTE (
	IN p_nombre VARCHAR(200)

)
BEGIN
	IF EXISTS (SELECT * FROM cliente WHERE nombre = p_nombre) THEN
		select id_cliente from cliente WHERE nombre = p_nombre;
	ELSE
        INSERT INTO cliente VALUES (DEFAULT , p_nombre);
        select id_cliente from cliente WHERE nombre = p_nombre;
	END IF;
END$$

DELIMITER $$
CREATE PROCEDURE insert_game (
   IN p_id1 INT,
   IN p_id2 INT
)
BEGIN
   INSERT INTO game(id_game, id_cliente1, id_cliente2, num_pregunta) VALUES (null, p_id1, p_id2, 1);
   INSERT INTO game(id_game, id_cliente1, id_cliente2, num_pregunta) VALUES (null, p_id2, p_id1, 1);
END$$

DELIMITER $$
CREATE PROCEDURE get_users_start_game (
   IN p_id1 INT
)
BEGIN
   SELECT id_cliente, nombre FROM cliente AS c
   LEFT JOIN game AS g ON (g.id_cliente1 = c.id_cliente AND g.id_cliente2 = p_id1)
   WHERE g.id_cliente1 IS NULL AND g.id_cliente2 IS NULL AND c.id_cliente != p_id1;
END$$

DELIMITER $$
CREATE PROCEDURE get_question (
   IN p_id1 INT,
	 IN P_id2 INT
)
BEGIN
   declare id_question int;
   IF EXISTS (SELECT * FROM game WHERE id_cliente1 = p_id1 AND id_cliente2 = p_id2) THEN
			SELECT num_pregunta INTO id_question FROM game WHERE id_cliente1 = p_id1 AND id_cliente2 = p_id2;
			set id_question = id_question + 1;
			UPDATE game SET num_pregunta = id_question WHERE id_cliente1 = p_id1 AND id_cliente2 = p_id2;
			UPDATE game SET num_pregunta = id_question WHERE id_cliente1 = p_id2 AND id_cliente2 = p_id1;
			SELECT id_pregunta, enunciado FROM pregunta WHERE id_pregunta = id_question;
	 ELSE
	 		INSERT INTO game(id_game, id_cliente1, id_cliente2, num_pregunta) VALUES (null, p_id1, p_id2, 1);
			INSERT INTO game(id_game, id_cliente1, id_cliente2, num_pregunta) VALUES (null, p_id2, p_id1, 1);
			SELECT id_pregunta, enunciado FROM pregunta WHERE id_pregunta = 1;
	 END IF;
END$$

DELIMITER $$
CREATE PROCEDURE get_answers (
   IN p_question INT
)
BEGIN
   	SELECT id_respuesta, enunciado FROM respuesta WHERE id_pregunta = p_question;
END$$


DELIMITER $$
CREATE PROCEDURE create_turno (
	IN p_id1 INT,
	IN P_id2 INT,
	IN p_res_c1 INT
)
BEGIN
   	DECLARE id_question INT;
    SELECT num_pregunta INTO id_question FROM game WHERE id_cliente1 = p_id1 AND id_cliente2 = p_id2;
		INSERT INTO turno(id_turno, id_pregunta, id_cliente_respuesta, id_cliente_adivina, id_respuesta_cliente, id_respuesta_cliente_adivina, ready)
			VALUES (null, id_question, p_id1, p_id2, p_res_c1, null, 0);
END$$

DELIMITER $$
CREATE PROCEDURE GET_PENDING_GAMES(
	IN p_id INT
)
BEGIN
		SELECT id_cliente, nombre FROM cliente AS c
		INNER JOIN turno AS t ON t.id_cliente_respuesta = c.id_cliente
		WHERE t.id_cliente_adivina = p_id AND t.ready = 0
    GROUP BY c.id_cliente
    HAVING COUNT(*) > 1
    ORDER BY c.id_cliente;
END$$

DELIMITER $$
CREATE PROCEDURE GET_PENDING_GAME_SPECIFIC(
	IN p_id_user_res INT,
	IN p_id_user_adv INT
)
BEGIN
		SELECT id_pregunta FROM turno
		WHERE id_cliente_respuesta = p_id_user_res AND id_cliente_adivina = p_id_user_adv AND ready = 0;
END$$

DELIMITER $$
CREATE PROCEDURE ACTUALIZAR_READY_TURNO (
	IN p_cliente1 INT,
    IN p_cliente2 INT,
    IN p_id_resp_cli_adivina INT,
    IN p_id_pregunta INT
)
BEGIN
	UPDATE turno SET ready = 1, id_respuesta_cliente_adivina = p_id_resp_cli_adivina
    WHERE id_pregunta = p_id_pregunta AND id_cliente_respuesta = p_cliente1 AND id_cliente_adivina = p_cliente2 AND ready = 0;

END$$


DELIMITER $$
CREATE PROCEDURE UPDATE_TURNO(
	IN p_id1 INT,
	IN p_id2 INT,
	IN res_ca INT
)
BEGIN
UPDATE game SET ready = 1, id_respuesta_cliente_adivina = res_ca WHERE id_cliente1 = p_id2 AND id_cliente2 = p_id1;
END$$

DELIMITER $$
DROP PROCEDURE cout_matchs;
CREATE PROCEDURE cout_matchs(
	IN p_id1 INT,
	IN p_id2 INT
)
BEGIN
	select count(*) from turno
	where (((id_cliente_respuesta = p_id1 and id_cliente_adivina = p_id2) or (id_cliente_respuesta = p_id2 and id_cliente_adivina = p_id1)) and
				id_respuesta_cliente = id_respuesta_cliente_adivina);
END$$
