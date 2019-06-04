CREATE database test_game_so;

USE test_game_so;

CREATE TABLE cliente  (
	id_cliente INT not null auto_increment PRIMARY KEY,
    nombre VARCHAR(200)
);

CREATE TABLE pregunta  (
	id_pregunta INT not null auto_increment PRIMARY KEY,
    enunciado VARCHAR(500)
);

CREATE TABLE respuesta  (
	id_respuesta INT not null auto_increment PRIMARY KEY,
    enunciado VARCHAR(500),
    id_pregunta INT,
    foreign key (id_pregunta) REFERENCES pregunta(id_pregunta)
);

CREATE TABLE turno  (
	id_turno INT not null auto_increment PRIMARY KEY,
    id_pregunta INT,
    id_cliente_respuesta INT,
    id_cliente_adivina INT,
    id_respuesta_cliente INT,
    id_respuesta_cliente_adivina INT,
    ready BOOL,
    
    foreign key (id_pregunta) REFERENCES pregunta(id_pregunta),
    foreign key (id_cliente_respuesta) REFERENCES cliente(id_cliente),
    foreign key (id_cliente_adivina) REFERENCES cliente(id_cliente),
    foreign key (id_respuesta_cliente) REFERENCES respuesta(id_respuesta),
    foreign key (id_respuesta_cliente_adivina) REFERENCES respuesta(id_respuesta)
);

CREATE TABLE game (
   id_game INT not null auto_increment PRIMARY KEY,
   id_cliente1 INT,
   id_cliente2 INT,
   foreign key (id_cliente1) REFERENCES cliente(id_cliente),
   foreign key (id_cliente2) REFERENCES cliente(id_cliente)
);