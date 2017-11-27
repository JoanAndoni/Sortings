
Para poder compilar el programa se debe tener sfml instalado ljson usando el comando sudo apt-get install libjsoncpp-dev y se debe compilar utilizando los comandos:
	g++ -c sfml_graph.cpp -std=c++11 -fopenmp
	g++ sfml_graph.o -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system -ljsoncpp -fopenmp
	./sfml_graph
