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
    id_cliente_respuesta = id_cliente_respuesta_adivina;
END$$
