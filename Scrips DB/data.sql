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
INSERT INTO pregunta(id_pregunta, enunciado) VALUES (null, '¿Qué tipo de café prefieres?');
INSERT INTO pregunta(id_pregunta, enunciado) VALUES (null, 'Si tuvieras que hacer uno de estos trabajos durante 6 meses ¿Cuál sería?');
INSERT INTO pregunta(id_pregunta, enunciado) VALUES (null, '¿Que tipo de películas prefieres?');
INSERT INTO pregunta(id_pregunta, enunciado) VALUES (null, '¿Crees que pasar Sistemas Operativos?');

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

/*Respuesta cafe*/
INSERT INTO respuesta(id_respuesta, enunciado, id_pregunta) VALUES (null, "Café negro con filtro", 4);
INSERT INTO respuesta(id_respuesta, enunciado, id_pregunta) VALUES (null, "Capuchino", 4);
INSERT INTO respuesta(id_respuesta, enunciado, id_pregunta) VALUES (null, "No quiero café, ¡gracias!", 4);

/*Respuesta jog 6 meses*/
INSERT INTO respuesta(id_respuesta, enunciado, id_pregunta) VALUES (null, "Jardineria paisajista", 5);
INSERT INTO respuesta(id_respuesta, enunciado, id_pregunta) VALUES (null, "Funcionario público", 5);
INSERT INTO respuesta(id_respuesta, enunciado, id_pregunta) VALUES (null, "Enfermería", 5);

/*Respuesta tipo pelis*/
INSERT INTO respuesta(id_respuesta, enunciado, id_pregunta) VALUES (null, "Terror", 6);
INSERT INTO respuesta(id_respuesta, enunciado, id_pregunta) VALUES (null, "Acción", 6);
INSERT INTO respuesta(id_respuesta, enunciado, id_pregunta) VALUES (null, "Drama", 6);

/*Respuesta SO*/
INSERT INTO respuesta(id_respuesta, enunciado, id_pregunta) VALUES (null, "Si", 7);
INSERT INTO respuesta(id_respuesta, enunciado, id_pregunta) VALUES (null, "Tal vez con curva", 7);
INSERT INTO respuesta(id_respuesta, enunciado, id_pregunta) VALUES (null, "Ya valí! :-(", 7);
