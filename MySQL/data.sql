USE test_game_so;

/*Clientes*/
INSERT INTO cliente(id_cliente, nombre) VALUES (null, 'Maria');
INSERT INTO cliente(id_cliente, nombre) VALUES (null, 'Carlos');
INSERT INTO cliente(id_cliente, nombre) VALUES (null, 'Juan');
INSERT INTO cliente(id_cliente, nombre) VALUES (null, 'Antonia');

/*Preguntas*/
INSERT INTO pregunta(id_pregunta, enunciado) VALUES (null, '¿Cuál es su color favorito');
INSERT INTO pregunta(id_pregunta, enunciado) VALUES (null, '¿Cuál es su comida favorita?');
INSERT INTO pregunta(id_pregunta, enunciado) VALUES (null, '¿Cuál es su deporte favorito?');

/*Respuesta colores*/
INSERT INTO respuesta(id_respuesta, enunciado, id_pregunta) VALUES (null, "verde", 1);
INSERT INTO respuesta(id_respuesta, enunciado, id_pregunta) VALUES (null, "azul", 1);
INSERT INTO respuesta(id_respuesta, enunciado, id_pregunta) VALUES (null, "rosado", 1);

/*Respuesta comidas*/
INSERT INTO respuesta(id_respuesta, enunciado, id_pregunta) VALUES (null, "italiana", 2);
INSERT INTO respuesta(id_respuesta, enunciado, id_pregunta) VALUES (null, "japonesa", 2);
INSERT INTO respuesta(id_respuesta, enunciado, id_pregunta) VALUES (null, "tica", 2);

/*Respuesta deporte*/
INSERT INTO respuesta(id_respuesta, enunciado, id_pregunta) VALUES (null, "natacion", 3);
INSERT INTO respuesta(id_respuesta, enunciado, id_pregunta) VALUES (null, "atletismo", 3);
INSERT INTO respuesta(id_respuesta, enunciado, id_pregunta) VALUES (null, "futbol", 3);
