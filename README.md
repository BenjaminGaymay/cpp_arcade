# Fonctionnement du programme

   On récupére la lib graphique à l'aide de la lib toussa.
Chaque class qui herite de IGame aura un object IGraphics qu'il utilisera pour faire ses jolies dessins.
Par ex:

    void drawSnake()
    {
	    _lib->drawSquare(this->x, this->y);
	    _lib->drawText("salut");
	    ...
    }

Ces jeux auront un setter de lib askip et boom on peut changer de lib assez facilement.

TODO:

 - Vector de jeux
 - Vector de lib
	 - On les recupere avec dirent en ourant les dossier 'lib' et 'games'
 - Changer de jeux / lib
 - boomboom
