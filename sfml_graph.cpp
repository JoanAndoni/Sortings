#include <iostream>
#include <sstream>
#include <ctime>
#include <math.h>
#include <iomanip>
#include <cstdlib>
#include <fstream>
#include <unistd.h>
#include <exception>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <jsoncpp/json/json.h>
#include <jsoncpp/json/writer.h>

using namespace std;

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define TEXT_SIZE 20 //velocidad
#define ANIMATION_RATE 200000 //veces qu repite la animacion
#define ANIMATION_LOOP 4 //Debe ser par para que se vea bien

struct Data
{
	float dat; //numero para la comparacion
	int stat; //colores
};

struct ThreadParameters //parametros entre los threads
{
    vector<Data>* array;
    bool* windowStatus;
		float * percentage;
		float *clave;
};

//Functions//
void exportCSV(float array[5][100]);
void exportJSON(float array[5][100]);
void MainMenu(ThreadParameters);
sf::RectangleShape drawRectangle(int x,int y, int stat, float a);

// --------SORTS--------

//BUBBLE
//****GRAFICO****
void VerBubbleSortASC( vector<Data>* array, float * percentage);
void VerBubbleSortDSC( vector<Data>* array, float * percentage);
//****NORMAL****
void BubbleSortASC( vector<Data>* array, float * percentage);
void BubbleSortDSC( vector<Data>* array, float * percentage);
//****COUT****
void coutBubbleSort();

//SELECTION
//****GRAFICO****
void VerSelectionSortASC(vector<Data>* array, float * percentage);
void VerSelectionSortDSC(vector<Data>* array, float * percentage);
//****NORMAL****
void SelectionSortASC(vector<Data>* array, float * percentage);
void SelectionSortDSC(vector<Data>* array, float * percentage);
//****COUT****
void coutSelectionSort();

//COCKTAIL
//****GRAFICO****
void VerCocktailSortASC(vector<Data>* array, float * percentage);
void VerCocktailSortDSC(vector<Data>* array, float * percentage);
//****NORMAL****
void CocktailSortASC(vector<Data>* array, float * percentage);
void CocktailSortDSC(vector<Data>* array, float * percentage);
//****COUT****
void coutCocktailSort();

//INSERTION
//****GRAFICO****
void VerInsertionSortASC(vector<Data>* array, float * percentage);
void VerInsertionSortDSC(vector<Data>* array, float * percentage);
//****NORMAL****
void InsertionSortASC(vector<Data>* array, float * percentage);
void InsertionSortDSC(vector<Data>* array, float * percentage);
//****COUT****
void coutInsertionSort();

//SHELL
//****GRAFICO****
void VerShellSortASC(vector<Data>* array, float * percentage);
void VerShellSortDSC(vector<Data>* array, float * percentage);
//****NORMAL****
void ShellSortASC(vector<Data>* array, float * percentage);
void ShellSortDSC(vector<Data>* array, float * percentage);
//****COUT****
void coutShellSort();

//FUNCION DE INTERCAMBIO DE VALORES
//****GRAFICO****
void swapt(Data *dat1, Data *dat2);
void swap2(int, int);
//BUSQUEDA LINEAL
int busquedaLineal(vector<Data>* array, float clave);
int busqueda(Data *dat1);
int resultado(Data *dat1);


int main()
{
    //Variables//
    vector<Data> array;
    bool windowStatus=true;
		float percentage=0;
		float instruccion1 = 0;
		float instruccion2 = 0;
		string Porcentaje;
		string instruccion;

    ThreadParameters parameters = {&array,&windowStatus,&percentage};

    // Create a thread for MainMenu function and runs it//
    sf::Thread thread(&MainMenu,parameters);
    thread.launch();

    //Main thread//
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Algoritmos de Ordenamiento");

		//Render texture//
		sf::RenderTexture texture;
		if (!texture.create(WINDOW_WIDTH, WINDOW_HEIGHT))
    	return -1;

    //Load Arial font//
		sf::Font font;
    font.loadFromFile("arial.ttf");

    //Dynamic view//
    sf::View view1;
    view1.reset(sf::FloatRect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT));

    while (window.isOpen() && windowStatus)
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
               {
                   windowStatus=false;
									 texture.getTexture().copyToImage().saveToFile("toto.png");//exportar textura
                   window.close();
               }
        }

	//Controls for the View//
	if (event.type == sf::Event::KeyPressed)
	{
    		if (event.key.code == sf::Keyboard::Up )
			view1.move(0,-1);

		if (event.key.code == sf::Keyboard::Down )
			view1.move(0,1);

			if (event.key.code == sf::Keyboard::Right )
		  view1.move(-1,0);

			if (event.key.code == sf::Keyboard::Left )
		  view1.move(1,0);

	}

  window.clear(sf::Color::White);//Limpia la pantalla
	texture.clear(sf::Color::White);
	////////imprimir aqui///////////////
	for(int i=0;i<array.size();i++)
	{
		float b = array[i].dat;

		sf::RectangleShape rec = drawRectangle((WINDOW_WIDTH/2)+(i*20), 100, array[i].stat,b);
		window.draw(rec);
		texture.draw(rec);
	}

	float a = percentage;
	stringstream ss (stringstream::in | stringstream::out);
	ss << a;
	string s = ss.str();




	 //Ejemplo para agregar texto
	sf::Text Weight(s,font,TEXT_SIZE);
	Weight.setColor(sf::Color::Black);
	Weight.setPosition(20, 35);
	window.draw(Weight);


	////////pantalla dinamica///////////
	window.setView(view1);
        window.display();
    }

    return 0;
}

void MainMenu(ThreadParameters parameters)
{
  	int optionProyect = 1, optionProyect2 = 1, optionProyect3 = 1, option = 1, option2 =1;
	float clave, resultado2, numberRandoms, datos[5][100], promedios[5], prom = 0, sum, count = 0;
	Data num;;

  	for (int i = 0; i < 5; i++){
    	for (int i2 = 0; i2 < 100; i2++) {
      		datos[i][i2] = -1;
    	}
  	}

	srand (static_cast <unsigned> (time(0)));

  	cout << "--------------PROYECTO FINAL DE ALGORTIMOS--------------" << endl << endl;
  	cout << "1.- Crear elementos aleatorios" << endl;
  	cout << "2.- Ingresar manualmente elementos" << endl;
  	cout << "0.- Salir" << endl;
  	cout << "\nIngresa la opcion que desees: " << endl;
  	cin >> optionProyect;
  	switch (optionProyect) {
    	case 1:

				cout << "\nIngresa el numero de elementos que desea generar: " << endl;
					cout << "n: ";
					cin >> numberRandoms;
					for (int i = 0; i < numberRandoms; i++) {
						num.dat = ((float)rand()/(float)(RAND_MAX));
						num.stat = 0;
						parameters.array->push_back(num);
					}
    	break;

    	case 2:
			while (optionProyect3 != 0) {
				cout << "\n1.- Ingresar número" << endl;
				cout << "0.- Terminar" << endl;
				cout << "\nIngresa la opcion que desees: " << endl;
		  	cin >> optionProyect3;
		  	switch (optionProyect3) {
		    	case 1:
					cout << "\nn: ";
					cin>>num.dat;
				 	num.stat=0;
				 	parameters.array->push_back(num);
		    	break;

					case 0:
					break;

					default:
		      	cout << "> Opción incorrecta ingresa un valor nuevamente" << endl;
		    	break;
				}
			}
    	break;

    	case 0:
				exit(0);
    	break;

    	default:
      	cout << "> Opción incorrecta ingresa un valor nuevamente" << endl;
    	break;
  	}

	int optionAlgoritmos =1, optionBusqueda1 = 1,optionBusqueda2 = 1, optionBusqueda3 = 1;
	int optionOrdenamiento1 = 1, optionOrdenamiento2 = 1, optionOrdenamiento3 = 1;
	int optionOrdenamiento4 = 1, optionOrdenamiento5 = 1, optionExport = 1 ;
	bool init = true;
	while(init){
		optionOrdenamiento1 = 1;
		cout << "\n----------------------ALGORTIMOS------------------------" << endl << endl;
		cout << "1.- De busqueda" << endl;
		cout << "2.- De ordenamiento" << endl;
		cout << "0.- Salir" << endl;
		cout << "\nIngresa la opcion que desees: " << endl;
		cin >> optionAlgoritmos;
		switch (optionAlgoritmos) {
			case 1:
			while (optionBusqueda1 != 0) {
				optionBusqueda2 = 1;
				cout << "\n-----------------------BUSQUEDA-------------------------" << endl << endl;
				cout << "1.- Buscar un número" << endl;
				cout << "0.- Regresar" << endl;
				cout << "\nIngresa la opcion que desees: " << endl;
				cin >> optionBusqueda1;
				switch (optionBusqueda1) {
					case 1:
						cout << "\nIngresar el número a buscar " << endl;
						cout << "n: ";
						cin >> clave;
						resultado2 = busquedaLineal(parameters.array, clave);
					    if (resultado2 == -1) cout << " >> El número " << clave << " no se encuentra dentro del arreglo " <<  resultado2 << endl;
					    else{
					    cout << " >> El número " << clave << " se encuentra en la posición (" << resultado2 << ") del arreglo" << endl;
					 	}
					break;

					case 0:
					break;

					default:
			      		cout << "\nOpción incorrecta ingresa un valor nuevamente" << endl;
			    	break;
				}
			}
			break;

			case 2:
			while (optionOrdenamiento1 != 0) {
				optionOrdenamiento2 = 1;
				cout << "\n---------------------ORDENAMIENTO-----------------------" << endl << endl;
				cout << "1.- Visualizar algortimo de ordenamiento" << endl;
				cout << "2.- Comparar dos algortimos de ordenamiento" << endl;
				cout << "3.- Visualizar código de los algortimos" << endl;
				cout << "4.- Correr un algortimo velocidad máxima" << endl;
				cout << "5.- Gráfica con el promedio de los tiempos de ejecución" << endl;
				cout << "6.- Exportar tiempos de ejecución" << endl;
				cout << "0.- Regresar" << endl;
				cout << "\nIngresa la opcion que desees: " << endl;
				cin >> optionOrdenamiento1;
				switch (optionOrdenamiento1) {
					case 1:
					while (optionOrdenamiento2 != 0){
						optionOrdenamiento3 = 1;
						cout << "\n---------------------INESTABLES------------------------" << endl << endl;
						cout << "1.- Bubble Sort" << endl;
						cout << "2.- Insertion Sort" << endl;
						cout << "3.- Cocktail Sort" << endl;
						cout << "----------------------ESTABLES-------------------------" << endl;
						cout << "4.- Selection Sort" << endl;
						cout << "5.- Shell Sort" << endl;
						cout << "0.- Regresar" << endl;
						cout << "\nIngresa la opcion que desees: " << endl;
						cin >> optionOrdenamiento2;
						switch (optionOrdenamiento2){
							case 1:
							while (optionOrdenamiento3 != 0){
								cout << "\n-----------------------ORDEN---------------------------" << endl << endl;
								cout << "1.- Ascendente" << endl;
								cout << "2.- Descendente" << endl;
								cout << "0.- Regresar" << endl;
								cout << "\nIngresa la opcion que desees: " << endl;
								cin >> optionOrdenamiento3;
								switch (optionOrdenamiento3) {
									case 1:
									VerBubbleSortASC(parameters.array,parameters.percentage);
									break;

									case 2:
									VerBubbleSortDSC(parameters.array,parameters.percentage);
									break;

									case 0:
									break;

									default:
						      		cout << "\nOpción incorrecta ingresa un valor nuevamente" << endl;
						    		break;
								}
							}
							break;

							case 2:
							while (optionOrdenamiento3 != 0){
								cout << "\n-----------------------ORDEN---------------------------" << endl << endl;
								cout << "1.- Ascendente" << endl;
								cout << "2.- Descendente" << endl;
								cout << "0.- Regresar" << endl;
								cout << "\nIngresa la opcion que desees: " << endl;
								cin >> optionOrdenamiento3;
								switch (optionOrdenamiento3) {
									case 1:
									VerInsertionSortASC(parameters.array,parameters.percentage);
									break;

									case 2:
									VerInsertionSortDSC(parameters.array,parameters.percentage);
									break;

									case 0:
									break;

									default:
							      	cout << "\nOpción incorrecta ingresa un valor nuevamente" << endl;
							    	break;
								}
							}
							break;

							case 3:
							while (optionOrdenamiento3 != 0){
								cout << "\n-----------------------ORDEN---------------------------" << endl << endl;
								cout << "1.- Ascendente" << endl;
								cout << "2.- Descendente" << endl;
								cout << "0.- Regresar" << endl;
								cout << "\nIngresa la opcion que desees: " << endl;
								cin >> optionOrdenamiento3;
								switch (optionOrdenamiento3) {
									case 1:
									VerCocktailSortASC(parameters.array,parameters.percentage);
									break;

									case 2:
									VerCocktailSortDSC(parameters.array,parameters.percentage);
									break;

									case 0:
									break;

									default:
							      	cout << "\nOpción incorrecta ingresa un valor nuevamente" << endl;
							    	break;
								}
							}
							break;

							case 4:
							while (optionOrdenamiento3 != 0){
								cout << "\n-----------------------ORDEN---------------------------" << endl << endl;
								cout << "1.- Ascendente" << endl;
								cout << "2.- Descendente" << endl;
								cout << "0.- Regresar" << endl;
								cout << "\nIngresa la opcion que desees: " << endl;
								cin >> optionOrdenamiento3;
								switch (optionOrdenamiento3) {
									case 1:
									VerSelectionSortASC(parameters.array,parameters.percentage);
									break;

									case 2:
									VerSelectionSortDSC(parameters.array,parameters.percentage);
									break;

									case 0:
									break;

									default:
							      	cout << "\nOpción incorrecta ingresa un valor nuevamente" << endl;
							    	break;
								}
							}
							break;

							case 5:
							while (optionOrdenamiento3 != 0){
								cout << "\n-----------------------ORDEN---------------------------" << endl << endl;
								cout << "1.- Ascendente" << endl;
								cout << "2.- Descendente" << endl;
								cout << "0.- Regresar" << endl;
								cout << "\nIngresa la opcion que desees: " << endl;
								cin >> optionOrdenamiento3;
									switch (optionOrdenamiento3) {
									case 1:
									VerShellSortASC(parameters.array,parameters.percentage);
									break;

									case 2:
									VerShellSortDSC(parameters.array,parameters.percentage);
									break;

									case 0:
									break;

									default:
							      	cout << "\nOpción incorrecta ingresa un valor nuevamente" << endl;
							    	break;
								}
							}
							break;

							case 0:
							break;

							default:
			    			cout << "\nOpción incorrecta ingresa un valor nuevamente" << endl;
							break;
						}
					}
					break;

					case 2:
					cout << "\n----------------------COMPARAR-------------------------" << endl << endl;
					cout << "Seleccione los dos algoritmos que desea comparar" << endl;
					break;

					case 3:
					while (optionOrdenamiento2 != 0){
						optionOrdenamiento3 = 1;
						cout << "\n---------------------INESTABLES------------------------" << endl << endl;
						cout << "1.- Bubble Sort" << endl;
						cout << "2.- Insertion Sort" << endl;
						cout << "3.- Cocktail Sort" << endl;
						cout << "----------------------ESTABLES-------------------------" << endl;
						cout << "4.- Selection Sort" << endl;
						cout << "5.- Shell Sort" << endl;
						cout << "0.- Regresar" << endl;
						cout << "\nIngresa la opcion que desees: " << endl;
						cin >> optionOrdenamiento2;
						switch (optionOrdenamiento2){
							case 1:
							coutBubbleSort();
							break;

							case 2:
							coutInsertionSort();
							break;

							case 3:
							coutCocktailSort();
							break;

							case 4:
							coutSelectionSort();
							break;

							case 5:
							coutShellSort();
							break;

							case 0:
							break;

							default:
			    			cout << "\nOpción incorrecta ingresa un valor nuevamente" << endl;
							break;
						}
					}
					break;

					case 4:
					while (optionOrdenamiento2 != 0){
						optionOrdenamiento3 = 1;
						cout << "\n---------------------INESTABLES------------------------" << endl << endl;
						cout << "1.- Bubble Sort" << endl;
						cout << "2.- Insertion Sort" << endl;
						cout << "3.- Cocktail Sort" << endl;
						cout << "----------------------ESTABLES-------------------------" << endl;
						cout << "4.- Selection Sort" << endl;
						cout << "5.- Shell Sort" << endl;
						cout << "0.- Regresar" << endl;
						cout << "\nIngresa la opcion que desees: " << endl;
						cin >> optionOrdenamiento2;
						switch (optionOrdenamiento2){
							case 1:
							while (optionOrdenamiento3 != 0){
								cout << "\n-----------------------ORDEN---------------------------" << endl << endl;
								cout << "1.- Ascendente" << endl;
								cout << "2.- Descendente" << endl;
								cout << "0.- Regresar" << endl;
								cout << "\nIngresa la opcion que desees: " << endl;
								cin >> optionOrdenamiento3;
								switch (optionOrdenamiento3) {
									case 1:
									BubbleSortASC(parameters.array,parameters.percentage);
									break;

									case 2:
									BubbleSortDSC(parameters.array,parameters.percentage);
									break;

									case 0:
									break;

									default:
						      		cout << "\nOpción incorrecta ingresa un valor nuevamente" << endl;
						    		break;
								}
							}
							break;

							case 2:
							while (optionOrdenamiento3 != 0){
								cout << "\n-----------------------ORDEN---------------------------" << endl << endl;
								cout << "1.- Ascendente" << endl;
								cout << "2.- Descendente" << endl;
								cout << "0.- Regresar" << endl;
								cout << "\nIngresa la opcion que desees: " << endl;
								cin >> optionOrdenamiento3;
								switch (optionOrdenamiento3) {
									case 1:
									InsertionSortASC(parameters.array,parameters.percentage);
									break;

									case 2:
									InsertionSortDSC(parameters.array,parameters.percentage);
									break;

									case 0:
									break;

									default:
							      	cout << "\nOpción incorrecta ingresa un valor nuevamente" << endl;
							    	break;
								}
							}
							break;

							case 3:
							while (optionOrdenamiento3 != 0){
								cout << "\n-----------------------ORDEN---------------------------" << endl << endl;
								cout << "1.- Ascendente" << endl;
								cout << "2.- Descendente" << endl;
								cout << "0.- Regresar" << endl;
								cout << "\nIngresa la opcion que desees: " << endl;
								cin >> optionOrdenamiento3;
								switch (optionOrdenamiento3) {
									case 1:
									CocktailSortASC(parameters.array,parameters.percentage);
									break;

									case 2:
									CocktailSortDSC(parameters.array,parameters.percentage);
									break;

									case 0:
									break;

									default:
							      	cout << "\nOpción incorrecta ingresa un valor nuevamente" << endl;
							    	break;
								}
							}
							break;

							case 4:
							while (optionOrdenamiento3 != 0){
								cout << "\n-----------------------ORDEN---------------------------" << endl << endl;
								cout << "1.- Ascendente" << endl;
								cout << "2.- Descendente" << endl;
								cout << "0.- Regresar" << endl;
								cout << "\nIngresa la opcion que desees: " << endl;
								cin >> optionOrdenamiento3;
								switch (optionOrdenamiento3) {
									case 1:
									SelectionSortASC(parameters.array,parameters.percentage);
									break;

									case 2:
									SelectionSortDSC(parameters.array,parameters.percentage);
									break;

									case 0:
									break;

									default:
							      	cout << "\nOpción incorrecta ingresa un valor nuevamente" << endl;
							    	break;
								}
							}
							break;

							case 5:
							while (optionOrdenamiento3 != 0){
								cout << "\n-----------------------ORDEN---------------------------" << endl << endl;
								cout << "1.- Ascendente" << endl;
								cout << "2.- Descendente" << endl;
								cout << "0.- Regresar" << endl;
								cout << "\nIngresa la opcion que desees: " << endl;
								cin >> optionOrdenamiento3;
									switch (optionOrdenamiento3) {
									case 1:
									ShellSortASC(parameters.array,parameters.percentage);
									break;

									case 2:
									ShellSortDSC(parameters.array,parameters.percentage);
									break;

									case 0:
									break;

									default:
							      	cout << "\nOpción incorrecta ingresa un valor nuevamente" << endl;
							    	break;
								}
							}
							break;

							case 0:
							break;

							default:
			    			cout << "\nOpción incorrecta ingresa un valor nuevamente" << endl;
							break;
						}
					}
					break;

					case 5:
					for (int i = 0; i < 5; i++){
			    		for (int i2 = 0; i2 < 100; i2++) {
			      			if(datos[i][i2] > 0) {
		    	    			sum = sum + datos[i][i2];
		        				count++;
		      				}
			    		}
			    		promedios[i] = sum / count;
			  		}
					//crear grafica
					break;

					case 6:
					cout << "\n---------------------FORMATO---------------------------" << endl << endl;
					cout << "1.- JSON" << endl;
					cout << "2.- CSV" << endl;
					cout << "0.- Regresar" << endl;
					cout << "\nIngresa la opcion que desees: " << endl;
					cin >> optionExport;
					switch (optionExport) {
						case 1:
							exportJSON(datos);
						break;

						case 2:
							exportCSV(datos);
						break;

						case 0:
						break;

						default:
							cout << "\nOpción incorrecta ingresa un valor nuevamente" << endl;
						break;
					}
				}
			}
			break;

			case 0:
				exit(0);
			break;

			default:
				cout << "\nOpción incorrecta ingresa un valor nuevamente" << endl;
			break;
		}
	}
}



///////////////////////////////poner cuadro////////////////////
sf::RectangleShape drawRectangle(int x,int y, int stat,float a)
{
	sf::RectangleShape rectangle(sf::Vector2f(15, -(a+15)));
	if(stat==0)
		rectangle.setFillColor(sf::Color(0, 255, 0));
	else if(stat==1)
		rectangle.setFillColor(sf::Color(255, 0, 0));
	else
		rectangle.setFillColor(sf::Color(255, 255,0));
	rectangle.move(sf::Vector2f(x,y));
	return rectangle;
}


int busqueda(Data *dat1)
{
	int stat = 1;
	for(int x=0;x<ANIMATION_LOOP;x++)
	{
		dat1->stat=stat;
		usleep(ANIMATION_RATE);
		if(stat)
			stat=0;
		else
			stat=1;
	}
	//dat1->stat=2;
	return 1;
}

int resultado(Data *dat1)
{
	dat1->stat=2;
	return 1;
}

void swapt(Data *dat1, Data *dat2)
{
	int stat=1;
	for(int x=0;x<ANIMATION_LOOP;x++)
	{
		dat1->stat=stat;
		dat2->stat=stat;
		usleep(ANIMATION_RATE);
		if(stat)
			stat=0;
		else
			stat=1;
	}

	dat1->stat=2;
	dat2->stat=2;

	float num = dat1->dat;
	dat1->dat = dat2->dat;
	dat2->dat = num;

}

void swap2(int dat1, int dat2)
{
	int num = dat1;
	dat1 = dat2;
	dat2 = num;
}

//***********BUBBLE SORT**********
void VerBubbleSortASC( vector<Data>* array, float * percentage)
{
	int tam = array->size();
	cout << "Tamaño" << tam << endl;
    int c, d;
		double b;
    for (c = 0; c <= (array->size() - 1); c++)
    {
			if(c == tam-1){
				*percentage = 100;
			}
			else{
				*percentage = (float)c/(float)tam * 100;
			}
			printf("porcentaje %f\n", *percentage);

        for (d = 0; d < array->size() - c - 1; d++)
        {
            if (array->at(d).dat < array->at(d+1).dat)
            {
							swapt(&array->at(d),&array->at(d+1));
            }
        }
    }
}
void BubbleSortASC( vector<Data>* array, float * percentage)
{
	int tam = array->size();
	cout << "Tamaño" << tam << endl;
    int c, d;
		double b;
    for (c = 0; c <= (array->size() - 1); c++)
    {
			if(c == tam-1){
				*percentage = 100;
			}
			else{
				*percentage = (float)c/(float)tam * 100;
			}
			printf("porcentaje %f\n", *percentage);

        for (d = 0; d < array->size() - c - 1; d++)
        {
            if (array->at(d).dat < array->at(d+1).dat)
            {
							swap2(d,d+1);
            }
        }
    }
}
void VerBubbleSortDSC( vector<Data>* array, float * percentage)
{
	int tam = array->size();
	cout << "Tamaño" << tam << endl;
    int c, d;
		double b;
    for (c = 0; c <= (array->size() - 1); c++)
    {
			if(c == tam-1){
				*percentage = 100;
			}
			else{
				*percentage = (float)c/(float)tam * 100;
			}
			printf("porcentaje %f\n", *percentage);

        for (d = 0; d < array->size() - c - 1; d++)
        {
            if (array->at(d).dat < array->at(d+1).dat)
            {
							swapt(&array->at(d),&array->at(d+1));
            }
        }
    }
}
void BubbleSortDSC( vector<Data>* array, float * percentage)
{
	int tam = array->size();
	cout << "Tamaño" << tam << endl;
    int c, d;
		double b;
    for (c = 0; c <= (array->size() - 1); c++)
    {
			if(c == tam-1){
				*percentage = 100;
			}
			else{
				*percentage = (float)c/(float)tam * 100;
			}
			printf("porcentaje %f\n", *percentage);

        for (d = 0; d < array->size() - c - 1; d++)
        {
            if (array->at(d).dat > array->at(d+1).dat)
            {
							swap2(d,d+1);
            }
        }
    }
}

//***********SELECTION SORT*********
void VerSelectionSortASC(vector<Data>* array, float * percentage)
{
    int c, d, min, loc, temp;
		int tam = array->size();
    for (c = 0; c <= (array->size() - 1); c++)
    {
			if(c == tam-1){
				*percentage = 100;
			}
			else{
				*percentage = (float)c/(float)tam * 100;
			}
			printf("porcentaje %f\n", *percentage);

        min = array->at(c).dat;
        loc = c;
        for (d = c + 1; d < array->size(); d++)
        {
        if (min > array->at(d).dat)
            {
                min = array->at(d).dat;
                loc = d;
            }
        }
				swapt(&array->at(c),&array->at(loc));
    }
}
void SelectionSortASC(vector<Data>* array, float * percentage)
{
    int c, d, min, loc, temp;
		int tam = array->size();
    for (c = 0; c <= (array->size() - 1); c++)
    {
			if(c == tam-1){
				*percentage = 100;
			}
			else{
				*percentage = (float)c/(float)tam * 100;
			}
			printf("porcentaje %f\n", *percentage);

        min = array->at(c).dat;
        loc = c;
        for (d = c + 1; d < array->size(); d++)
        {
        if (min > array->at(d).dat)
            {
                min = array->at(d).dat;
                loc = d;
            }
        }
				swap2(c,loc);
    }
}
void VerSelectionSortDSC(vector<Data>* array, float * percentage)
{
    int c, d, min, loc, temp;
			int tam = array->size();
    for (c = 0; c <= (array->size() - 1); c++)
    {
			if(c == tam-1){
				*percentage = 100;
			}
			else{
				*percentage = (float)c/(float)tam * 100;
			}
			printf("porcentaje %f\n", *percentage);
        min = array->at(c).dat;
        loc = c;
        for (d = c + 1; d < array->size(); d++)
        {
            if (min < array->at(d).dat)
            {
                min = array->at(d).dat;
                loc = d;
            }
        }
				swapt(&array->at(c),&array->at(loc));
    }
}
void SelectionSortDSC(vector<Data>* array, float * percentage)
{
    int c, d, min, loc, temp;
			int tam = array->size();
    for (c = 0; c <= (array->size() - 1); c++)
    {
			if(c == tam-1){
				*percentage = 100;
			}
			else{
				*percentage = (float)c/(float)tam * 100;
			}
			printf("porcentaje %f\n", *percentage);
        min = array->at(c).dat;
        loc = c;
        for (d = c + 1; d < array->size(); d++)
        {
            if (min < array->at(d).dat)
            {
                min = array->at(d).dat;
                loc = d;
            }
        }
				swap2(c,loc);
    }
}

//***********COCKTAIL SORT**********
void VerCocktailSortASC(vector<Data>* array, float * percentage)
{
	int percentage1, percentage2;
	float tam  =array->size()-1;
	bool swapped = true;
	int start = 0;
	int end = (array->size() - 1);

    while (swapped)
    {
        swapped = false;

        for (int i = start; i < end; ++i)
        {
            if (array->at(i).dat > array->at(i+1).dat)
            {
                  swapt(&array->at(i),&array->at(i+1));
                swapped = true;
            }
							/*percentage1 = (float)i/(float)end * 100;
							printf("porcentaje %d\n", percentage1);
							*percentage = percentage1;*/
        }

        if (!swapped)
            break;

        swapped = false;

        --end;

        for (int i = end - 1; i >= start; --i)
        {
            if (array->at(i).dat > array->at(i+1).dat)
            {
                swapt(&array->at(i),&array->at(i+1));
                swapped = true;
            }
					/*	percentage2 = (float)i/(float)start * 100;
						printf("porcentaje %d\n", percentage2);
						*percentage = percentage2;*/
        }
        ++start;
				if(start == end)
				{
					*percentage = 100;
				}
				/*else{
					*percentage = percentage1 + percentage2;
				}*/

				printf("porcentaje %f\n", *percentage);
    }
}
void CocktailSortASC(vector<Data>* array, float * percentage)
{
	float tam  =array->size()-1;
	bool swapped = true;
	int start = 0;
	int end = (array->size() - 1);

    while (swapped)
    {
        swapped = false;

        for (int i = start; i < end; ++i)
        {
            if (array->at(i).dat > array->at(i+1).dat)
            {
                  swap2(i,i+1);
                swapped = true;
            }
        }

        if (!swapped)
            break;

        swapped = false;

        --end;

        for (int i = end - 1; i >= start; --i)
        {
            if (array->at(i).dat > array->at(i+1).dat)
            {
                swap2(i,i+1);
                swapped = true;
            }
        }
        ++start;
    }
}
void VerCocktailSortDSC(vector<Data>* array, float * percentage)
{
	bool swapped = true;
	int start = 0;
	int end = (array->size() - 1);

    while (swapped)
    {
        swapped = false;

        for (int i = start; i < end; ++i)
        {
            if (array->at(i).dat < array->at(i+1).dat)
            {
                  swapt(&array->at(i),&array->at(i+1));
                swapped = true;
            }
        }

        if (!swapped)
            break;

        swapped = false;

        --end;

        for (int i = end - 1; i >= start; --i)
        {
            if (array->at(i).dat < array->at(i+1).dat)
            {
                swapt(&array->at(i),&array->at(i+1));
                swapped = true;
            }
        }
        ++start;
    }
}
void CocktailSortDSC(vector<Data>* array, float * percentage)
{
	bool swapped = true;
	int start = 0;
	int end = (array->size() - 1);

    while (swapped)
    {
        swapped = false;

        for (int i = start; i < end; ++i)
        {
            if (array->at(i).dat < array->at(i+1).dat)
            {
                  swap2(i,i+1);
                swapped = true;
            }
        }

        if (!swapped)
            break;

        swapped = false;

        --end;

        for (int i = end - 1; i >= start; --i)
        {
            if (array->at(i).dat < array->at(i+1).dat)
            {
                swap2(i,i+1);
                swapped = true;
            }
        }
        ++start;
    }
}

//*********INSERTION SORT**********
void VerInsertionSortASC(vector<Data>* array, float * percentage)
{
	float tam = array->size();
	 for (int i = 1; i < array->size(); i++)
	 {
		 		 int j = i;
		 while ((j > 0) && (array->at(j).dat < array->at(j - 1).dat))
		  {
				swapt(&array->at(j),&array->at(j-1));
			 j = j - 1;
		 }
		 if(i == tam-1){
			*percentage = 100;
		}
		else{
			*percentage = (float)i/(float)tam * 100;
		}
		printf("porcentaje %f\n", *percentage);
	 }
 }
void InsertionSortASC(vector<Data>* array, float * percentage)
 {
 	float tam = array->size();
 	 for (int i = 1; i < array->size(); i++)
 	 {
 		 		 int j = i;
 		 while ((j > 0) && (array->at(j).dat < array->at(j - 1).dat))
 		  {
 				swap2(j,j-1);
 			 j = j - 1;
 		 }
 		 if(i == tam-1){
 			*percentage = 100;
 		}
 		else{
 			*percentage = (float)i/(float)tam * 100;
 		}
 		printf("porcentaje %f\n", *percentage);
 	 }
  }
 void VerInsertionSortDSC(vector<Data>* array, float * percentage)
 {
	 float tam = array->size();
 	 for (int i = 1; i < array->size(); i++)
 	 {
 		 		 int j = i;
 		 while ((j > 0) && (array->at(j).dat > array->at(j - 1).dat))
 		  {
 				swapt(&array->at(j),&array->at(j-1));
 			 j = j - 1;
 		 }
 		 if(i == tam-1){
 			*percentage = 100;
 		}
 		else{
 			*percentage = (float)i/(float)tam * 100;
 		}
 		printf("porcentaje %f\n", *percentage);
 	 }
 }
void InsertionSortDSC(vector<Data>* array, float * percentage)
  {
 	 float tam = array->size();
  	 for (int i = 1; i < array->size(); i++)
  	 {
  		 		 int j = i;
  		 while ((j > 0) && (array->at(j).dat > array->at(j - 1).dat))
  		  {
  				swap2(j,j-1);
  			 j = j - 1;
  		 }
  		 if(i == tam-1){
  			*percentage = 100;
  		}
  		else{
  			*percentage = (float)i/(float)tam * 100;
  		}
  		printf("porcentaje %f\n", *percentage);
  	 }
   }

//*********SHELL SORT*************
void VerShellSortASC(vector<Data>* array, float * percentage)
{
		float tam = array->size();
    int c, i, j, temp;
    for (c = (array->size())/2; c > 0; c /= 2)
		{
			for (i = c; i < array->size(); i++)
				{
					for (j=i-c; j>=0 && array->at(j).dat > array->at(j + c).dat; j-=c)
					{
						swapt(&array->at(j),&array->at(j+c));
					}
				}
				if(c == tam/2){
					*percentage = 100;
				}
				else{
					*percentage = (float)c/(float)tam * 100;
				}
				printf("porcentaje %f\n", *percentage);

		}



}
void ShellSortASC(vector<Data>* array, float * percentage)
{
		float tam = array->size();
    int c, i, j, temp;
    for (c = (array->size())/2; c > 0; c /= 2)

        for (i = c; i < array->size(); i++)
					{
						for (j=i-c; j>=0 && array->at(j).dat > array->at(j + c).dat; j-=c)
						{
							swap2(j,j+c);

            }
					}
					if(i == 1){
						*percentage = 100;
					}
					else{
						*percentage = (float)c/(float)tam * 100;
					}
					printf("porcentaje %f\n", *percentage);

}
void VerShellSortDSC(vector<Data>* array, float * percentage)
{
		float tam = array->size();
    int c, i, j, temp;
    for (c = (array->size())/2; c >= 0; c /= 2)

        for (i = c; i < array->size(); i++)
					{
						for (j=i-c; j>=0 && array->at(j).dat < array->at(j + c).dat; j-=c)
						{
							swapt(&array->at(j),&array->at(j+c));

            }
					}
					if(i == 1){
						*percentage = 100;
					}
					else{
						*percentage = (float)c/(float)tam * 100;
					}
					printf("porcentaje %f\n", *percentage);

}
void ShellSortDSC(vector<Data>* array, float * percentage)
{
		float tam = array->size();
    int c, i, j, temp;
    for (c = (array->size())/2; c >= 0; c /= 2)

        for (i = c; i < array->size(); i++)
					{
						for (j=i-c; j>=0 && array->at(j).dat < array->at(j + c).dat; j-=c)
						{
							swap2(j,j+c);

            }
					}
					if(i == 1){
						*percentage = 100;
					}
					else{
						*percentage = (float)c/(float)tam * 100;
					}
					printf("porcentaje %f\n", *percentage);

}

void coutBubbleSort(){
	cout << ">> COMPLEJIDAD CICLOMATICA : O N^2\n" << endl;
	cout << "int tam = array->size();" << endl;
	cout << "cout << ""Tamaño"" << tam << endl;" << endl;
    cout << "int c, d;" << endl;
	cout << "double b;" << endl;
    cout << "for (c = 0; c <= (array->size() - 1); c++)" << endl;
    cout << "{" << endl;
	cout << "	if(c == tam-1){" << endl;
	cout << "	*percentage = 100;" << endl;
	cout << "}" << endl;
	cout << "else{" << endl;
	cout << "	*percentage = (float)c/(float)tam * 100;" << endl;
	cout << "}" << endl;
	cout << "printf(""porcentaje %f\n"", *percentage);" << endl;
    cout << "for (d = 0; d < array->size() - c - 1; d++)" << endl;
    cout << "{" << endl;
    cout << "	if (array->at(d).dat < array->at(d+1).dat) swap2(d,d+1); << endl; " << endl;
    cout << "}" << endl;
}

void coutSelectionSort(){
	cout << ">> COMPLEJIDAD CICLOMATICA : O N^2\n" << endl;
}

void coutCocktailSort(){
	cout << ">> COMPLEJIDAD CICLOMATICA : O N^2\n" << endl;
}

void coutInsertionSort(){
	cout << ">> COMPLEJIDAD CICLOMATICA : O N^2\n" << endl;
}

void coutShellSort(){
	cout << ">> COMPLEJIDAD CICLOMATICA : O N^1.25\n" << endl;
}

int busquedaLineal(vector<Data>* array, float clave)
{
	int i, resultado1 = -1;
  	for ( i = 0; i< array->size() ; i++)
	{
		busqueda(&array->at(i));
		if(array->at(i).dat == clave)
		{
			resultado1 = i;
			resultado(&array->at(resultado1));
			break;
		}

	}
  return resultado1;
}

void exportJSON(float array[5][100])
{
  ofstream file_id;
  file_id.open("ExecTimes.json");

  Json::Value event;
  Json::Value vec1(Json::arrayValue);
  Json::Value vec2(Json::arrayValue);
  Json::Value vec3(Json::arrayValue);
  Json::Value vec4(Json::arrayValue);
  Json::Value vec5(Json::arrayValue);
  Json::Value vec6(Json::arrayValue);

  for (int i = 0; i < 5; i++){
      switch (i) {
        case 0:
        for (int i2 = 0; i2 < 100; i2++) {
          if (array[i][i2] > 0) {
          vec1.append(Json::Value(array[i][i2]));;
          event["Sorts"]["BubbleSort"]["Times"] = vec1;
          }
        }
      break;

      case 1:
      for (int i2 = 0; i2 < 100; i2++) {
        if (array[i][i2] > 0) {
          vec2.append(Json::Value(array[i][i2]));;
          event["Sorts"]["SelectionSort"]["Times"] = vec2;
        }
      }

      break;

      case 2:
      for (int i2 = 0; i2 < 100; i2++) {
        if (array[i][i2] > 0) {
          vec3.append(Json::Value(array[i][i2]));;
          event["Sorts"]["CocktailSort"]["Times"] = vec3;
        }
      }
      break;

      case 3:
      for (int i2 = 0; i2 < 100; i2++) {
        if (array[i][i2] > 0) {
          vec4.append(Json::Value(array[i][i2]));;
          event["Sorts"]["InsertionSort"]["Times"] = vec4;
        }
      }
      break;

      case 4:
      for (int i2 = 0; i2 < 100; i2++) {
        if (array[i][i2] > 0) {
          vec5.append(Json::Value(array[i][i2]));;
          event["Sorts"]["ShellSort"]["Times"] = vec5;
        }
      }
      break;

      case 5:
      for (int i2 = 0; i2 < 100; i2++) {
        if (array[i][i2] > 0) {
          vec6.append(Json::Value(array[i][i2]));;
          event["Sorts"]["XSort"]["Times"] = vec6;
        }
      }
      break;
    }
  }
  Json::StyledWriter styledWriter;
  file_id << styledWriter.write(event);
  file_id.close();

  ofstream outfile;
  outfile.open("ExecTimes.CSV");
	for (int i = 0; i < 5; i++) {
      switch (i) {
        case 0:
        outfile<<"BubbleSort"<<endl;
        for (int i2 = 0; i2 < 100; i2++){
          if(array[i][i2] > 0) {
            outfile<<array[i][i2]<<endl;
          }
        }
        break;
        case 1:
        outfile<<"SelectionSort"<<endl;
        for (int i2 = 0; i2 < 100; i2++){
          if(array[i][i2] > 0) {
            outfile<<array[i][i2]<<endl;
          }
        }
        break;
        case 2:
        outfile<<"CocktailSort"<<endl;
        for (int i2 = 0; i2 < 100; i2++){
          if(array[i][i2] > 0) {
            outfile<<array[i][i2]<<endl;
          }
        }
        break;
        case 3:
        outfile<<"InsertionSort"<<endl;
        for (int i2 = 0; i2 < 100; i2++){
          if(array[i][i2] > 0) {
            outfile<<array[i][i2]<<endl;
          }
        }
        break;
        case 4:
        outfile<<"ShellSort"<<endl;
        for (int i2 = 0; i2 < 100; i2++){
          if(array[i][i2] > 0) {
            outfile<<array[i][i2]<<endl;
          }
        }
        break;
        case 5:
        outfile<<"XSort"<<endl;
        for (int i2 = 0; i2 < 100; i2++){
          if(array[i][i2] > 0) {
            outfile<<array[i][i2]<<endl;
          }
        }
        break;
      }
		}
	outfile.close();
}

void exportCSV(float array[5][100])
{
  ofstream outfile;
  outfile.open("ExecTimes.CSV");
	for (int i = 0; i < 5; i++) {
      switch (i) {
        case 0:
        outfile<<"BubbleSort"<<endl;
        for (int i2 = 0; i2 < 100; i2++){
          if(array[i][i2] > 0) {
            outfile<<array[i][i2]<<endl;
          }
        }
        break;
        case 1:
        outfile<<"SelectionSort"<<endl;
        for (int i2 = 0; i2 < 100; i2++){
          if(array[i][i2] > 0) {
            outfile<<array[i][i2]<<endl;
          }
        }
        break;
        case 2:
        outfile<<"CocktailSort"<<endl;
        for (int i2 = 0; i2 < 100; i2++){
          if(array[i][i2] > 0) {
            outfile<<array[i][i2]<<endl;
          }
        }
        break;
        case 3:
        outfile<<"InsertionSort"<<endl;
        for (int i2 = 0; i2 < 100; i2++){
          if(array[i][i2] > 0) {
            outfile<<array[i][i2]<<endl;
          }
        }
        break;
        case 4:
        outfile<<"ShellSort"<<endl;
        for (int i2 = 0; i2 < 100; i2++){
          if(array[i][i2] > 0) {
            outfile<<array[i][i2]<<endl;
          }
        }
        break;
        case 5:
        outfile<<"XSort"<<endl;
        for (int i2 = 0; i2 < 100; i2++){
          if(array[i][i2] > 0) {
            outfile<<array[i][i2]<<endl;
          }
        }
        break;
      }
		}
	outfile.close();
}
