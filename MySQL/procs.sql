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
   INSERT INTO game(id_game, id_cliente1, id_cliente2) VALUES (null, p_id1, p_id2);
   INSERT INTO game(id_game, id_cliente1, id_cliente2) VALUES (null, p_id2, p_id1);
END$$

DELIMITER $$
CREATE PROCEDURE get_users_start_game (
   IN p_id1 INT
)
BEGIN
   SELECT id_cliente, nombre FROM cliente AS c
   LEFT JOIN game AS g ON g.id_cliente1 = c.id_cliente
   WHERE g.id_cliente1 IS NULL AND id_cliente != p_id1;
END$$