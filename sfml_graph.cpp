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
#include <omp.h>

using namespace std;

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define TEXT_SIZE 20
 //velocidad
#define ANIMATION_RATE 200000
//veces qu repite la animacion
#define ANIMATION_LOOP 4 //Debe ser par para que se vea bien

struct Data
{
	float dat; //numero para la comparacion
	int stat; //colores
};
 struct datos
 {
	 vector<Data>* instrucciones;
 };
struct ThreadParameters //parametros entre los threads
{
    vector<Data>* array;
		vector<datos>* instrucciones;
    bool* windowStatus;
		float *percentage;
		float * percentageBubble;
		float * percentageSelection;
		float * percentageInsertion;
		float * percentageCocktail;
		float * percentageShell;
		float * comp1;
		float * comp2;
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
void VerBubbleSortASC( vector<Data>* array, float * percentageBubble, float * comp1, float * comp2);
void VerBubbleSortDSC( vector<Data>* array, float * percentageBubble, float * comp1, float * comp2);
//****NORMAL****
void BubbleSortASC( vector<Data>* array, float * percentage);
void BubbleSortDSC( vector<Data>* array, float * percentage);
//****COUT****
void coutBubbleSort();

//SELECTION
//****GRAFICO****
void VerSelectionSortASC(vector<Data>* array, float * percentageSelection, float * comp1, float * comp2);
void VerSelectionSortDSC(vector<Data>* array, float * percentageSelection, float * comp1, float * comp2);
//****NORMAL****
void SelectionSortASC(vector<Data>* array, float * percentage);
void SelectionSortDSC(vector<Data>* array, float * percentage);
//****COUT****
void coutSelectionSort();

//COCKTAIL
//****GRAFICO****
void VerCocktailSortASC(vector<Data>* array, float * percentageCocktail, float * comp1, float * comp2);
void VerCocktailSortDSC(vector<Data>* array, float * percentageCocktail, float * comp1, float * comp2);
//****NORMAL****
void CocktailSortASC(vector<Data>* array, float * percentage);
void CocktailSortDSC(vector<Data>* array, float * percentage);
//****COUT****
void coutCocktailSort();

//INSERTION
//****GRAFICO****
void VerInsertionSortASC(vector<Data>* array, float * percentageInsertion, float * comp1, float * comp2);
void VerInsertionSortDSC(vector<Data>* array, float * percentageInsertion,float * comp1, float * comp2);
//****NORMAL****
void InsertionSortASC(vector<Data>* array, float * percentage);
void InsertionSortDSC(vector<Data>* array, float * percentage);
//****COUT****
void coutInsertionSort();

//SHELL
//****GRAFICO****
void VerShellSortASC(vector<Data>* array, float * percentageShell, float * comp1, float * comp2);
void VerShellSortDSC(vector<Data>* array, float * percentageShell, float * comp1, float * comp2);
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
			vector<datos> instrucciones;
	    bool windowStatus=true;
			float percentage =0;
			float  percentageBubble =0;
			float  percentageSelection=0;
			float  percentageInsertion=0;
			float  percentageCocktail=0;
			float  percentageShell=0;
			float comp1 = 0;
			float comp2 = 0;

    ThreadParameters parameters = {&array,&instrucciones, &windowStatus,&percentage, &percentageShell, &percentageCocktail, &percentageInsertion, &percentageBubble, &percentageSelection, &comp1, &comp2};
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
	float inst = comp1;
	float inst2 = comp2;
	stringstream instruccionesASC (stringstream::in | stringstream::out);
	instruccionesASC << "Comparacion que se esta realizando :  \n " << comp1 << " < " << comp2 << endl;
	string instASC = instruccionesASC.str();

	float a1 = percentageShell;//percentageBubble;
	stringstream bubble (stringstream::in | stringstream::out);
	bubble << "->Bubble Sort: " << a1 << "%" << endl;
	string bubbleS = bubble.str();

	float a2 = percentageCocktail;
	stringstream selection (stringstream::in | stringstream::out);
	selection << "->Selection Sort: " << a2 << "%" << endl;
	string selectionS = selection.str();

	float a3 = percentageInsertion;
	stringstream insertion (stringstream::in | stringstream::out);
	insertion << "->Insertion Sort: " << a3 << "%" << endl;
	string insertionS = insertion.str();

	float a4 = percentageBubble;
	stringstream cocktail (stringstream::in | stringstream::out);
	cocktail << "->Cocktail Sort: " << a4 << "%" << endl;
	string cocktailS = cocktail.str();

	float a5 = percentageSelection;
	stringstream shell (stringstream::in | stringstream::out);
	shell << "->Shell Sort: " << a5 << "%" << endl;
	string shellS = shell.str();

	stringstream por (stringstream::in | stringstream::out);
	por << "PORCENTAJES DE AVANCE: " << endl;
	string porcentajeS = por.str();

	for(int i=0;i<instrucciones.size();i++)
	{
				//impresion en y
		for(int j=0;j<instrucciones[i].instrucciones->size();i++)
		{
			float b = instrucciones[i].instrucciones->at(j).dat;
			sf::RectangleShape rec2 = drawRectangle((i*20), i * 300, instrucciones[i].instrucciones->at(j).stat,b);
			window.draw(rec2);
			texture.draw(rec2);
		}

	}
	//vector de historial

	 //Ejemplo para agregar texto
	 sf::Text ComparacionASC(instASC,font,TEXT_SIZE);
	ComparacionASC.setColor(sf::Color::Black);
	ComparacionASC.setPosition(20, 200);
	window.draw(ComparacionASC);


	 sf::Text Weight(porcentajeS,font,TEXT_SIZE);
	 Weight.setColor(sf::Color::Black);
	 Weight.setPosition(20, 10);
	 window.draw(Weight);

	sf::Text Weight1(bubbleS,font,TEXT_SIZE);
	Weight1.setColor(sf::Color::Black);
	Weight1.setPosition(20, 35);
	window.draw(Weight1);

	sf::Text Weight2(selectionS,font,TEXT_SIZE);
	Weight2.setColor(sf::Color::Black);
	Weight2.setPosition(20, 60);
	window.draw(Weight2);

	sf::Text Weight3(insertionS,font,TEXT_SIZE);
	Weight3.setColor(sf::Color::Black);
	Weight3.setPosition(20, 85);
	window.draw(Weight3);

	sf::Text Weight4(cocktailS,font,TEXT_SIZE);
	Weight4.setColor(sf::Color::Black);
	Weight4.setPosition(20, 110);
	window.draw(Weight4);

	sf::Text Weight5(shellS,font,TEXT_SIZE);
	Weight5.setColor(sf::Color::Black);
	Weight5.setPosition(20, 135);
	window.draw(Weight5);

	////////pantalla dinamica///////////
	window.setView(view1);
        window.display();
    }
    return 0;
}

void MainMenu(ThreadParameters parameters)
{
  int optionProyect = 1, optionProyect2 = 1, optionProyect3 = 1, option = 1, option2 =1, sortID, CountingData1 = 0;
	int CountingData2 = 0, CountingData3 = 0, CountingData4 = 0, CountingData5 = 0;
	float clave, resultado2, numberRandoms, datos[5][100], promedios[5], sum, count = 0;
	Data num;;

  	for (int i = 0; i < 5; i++){
    	for (int i2 = 0; i2 < 100; i2++) {
      		datos[i][i2] = -1;
    	}
  	}

	for(int i = 0; i< 5; i++) promedios[i] = 0;
	srand (static_cast <unsigned> (time(0)));

  	cout << "\n--------------PROYECTO FINAL DE ALGORTIMOS--------------" << endl << endl;
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
						num.dat = rand() % 70;
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
									VerBubbleSortASC(parameters.array,parameters.percentageBubble, parameters.comp1, parameters.comp2);
									break;

									case 2:
									VerBubbleSortDSC(parameters.array,parameters.percentageBubble, parameters.comp1, parameters.comp2 );
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
									VerInsertionSortASC(parameters.array,parameters.percentageInsertion, parameters.comp1, parameters.comp2);
									break;

									case 2:
									VerInsertionSortDSC(parameters.array,parameters.percentageInsertion, parameters.comp1, parameters.comp2);
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
									VerCocktailSortASC(parameters.array,parameters.percentageCocktail, parameters.comp1, parameters.comp2);
									break;

									case 2:
									VerCocktailSortDSC(parameters.array,parameters.percentageCocktail, parameters.comp1, parameters.comp2);
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
									VerSelectionSortASC(parameters.array,parameters.percentageSelection, parameters.comp1, parameters.comp2);
									break;

									case 2:
									VerSelectionSortDSC(parameters.array,parameters.percentageSelection, parameters.comp1, parameters.comp2);
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
									VerShellSortASC(parameters.array,parameters.percentageShell, parameters.comp1, parameters.comp2);
									break;

									case 2:
									VerShellSortDSC(parameters.array,parameters.percentageShell,parameters.comp1, parameters.comp2);
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
					while (optionOrdenamiento2 != 0){
						optionOrdenamiento3 = 1;
					cout << "\n----------------------COMPARAR-------------------------" << endl << endl;
					cout << "Seleccione los dos algoritmos que desea comparar" << endl;
					cout << "1.- Bubble Sort con Insertion Sort" << endl;
					cout << "2.- Bubble Sort con Selection Sort" << endl;
					cout << "3.- Bubble Sort con Cocktail Sort" << endl;
					cout << "4.- Bubble Sort con Shell Sort" << endl;
					cout << "5.- Insertion Sort con Selection Sort" << endl;
					cout << "6.- Insertion Sort con Cocktail Sort" << endl;
					cout << "7.- Insertion Sort con Shell Sort" << endl;
					cout << "8.- Selection Sort con Cocktail Sort" << endl;
					cout << "9.- Selection Sort con Shell Sort" << endl;
					cout << "10.- Cocktail Sort con Shell Sort" << endl;
					cout << "0.- Regresar" << endl;
					cout << "\nIngresa la opcion que desees: " << endl;
					cin >> optionOrdenamiento2;
					switch (optionOrdenamiento2){
						case 1:
						BubbleSortASC(parameters.array,parameters.percentageBubble);
						InsertionSortASC(parameters.array,parameters.percentageInsertion);
						break;

						case 2:
						BubbleSortASC(parameters.array,parameters.percentageBubble);
						SelectionSortASC(parameters.array,parameters.percentageSelection);
						break;

						case 3:
						BubbleSortASC(parameters.array,parameters.percentageBubble);
						CocktailSortASC(parameters.array,parameters.percentageCocktail);
						break;

						case 4:
						BubbleSortASC(parameters.array,parameters.percentageBubble);
						ShellSortASC(parameters.array,parameters.percentageShell);
						break;

						case 5:
						InsertionSortASC(parameters.array,parameters.percentageInsertion);
						SelectionSortASC(parameters.array,parameters.percentageSelection);
						break;

						case 6:
						InsertionSortASC(parameters.array,parameters.percentageInsertion);
						CocktailSortASC(parameters.array,parameters.percentageCocktail);
						break;

						case 7:
						InsertionSortASC(parameters.array,parameters.percentageInsertion);
						ShellSortASC(parameters.array,parameters.percentageShell);
						break;

						case 8:
						SelectionSortASC(parameters.array,parameters.percentageSelection);
						CocktailSortASC(parameters.array,parameters.percentageCocktail);
						break;

						case 9:
						SelectionSortASC(parameters.array,parameters.percentageSelection);
						ShellSortASC(parameters.array,parameters.percentageShell);
						break;

						case 10:
						CocktailSortASC(parameters.array,parameters.percentageCocktail);
						ShellSortASC(parameters.array,parameters.percentageShell);
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
									{
										sortID = 0;
										clock_t start = clock();
										BubbleSortASC(parameters.array,parameters.percentageBubble);
										clock_t stop = clock();
        						double elapsed = (double)(stop - start) * 1000.0 / CLOCKS_PER_SEC;
        						printf("Time elapsed in ms: %f", elapsed);
										datos[sortID][CountingData1] = elapsed;
										CountingData1++;
									}
									break;

									case 2:
									{
										sortID = 0;
										clock_t start = clock();
										BubbleSortDSC(parameters.array,parameters.percentageBubble);
										clock_t stop = clock();
        						double elapsed = (double)(stop - start) * 1000.0 / CLOCKS_PER_SEC;
        						printf("Time elapsed in ms: %f", elapsed);
										datos[sortID][CountingData1] = elapsed;
										CountingData1++;

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
							while (optionOrdenamiento3 != 0){
								cout << "\n-----------------------ORDEN---------------------------" << endl << endl;
								cout << "1.- Ascendente" << endl;
								cout << "2.- Descendente" << endl;
								cout << "0.- Regresar" << endl;
								cout << "\nIngresa la opcion que desees: " << endl;
								cin >> optionOrdenamiento3;
								switch (optionOrdenamiento3) {
									case 1:
									{
										sortID = 1;
										clock_t start = clock();
										InsertionSortASC(parameters.array,parameters.percentageInsertion);
										clock_t stop = clock();
        						double elapsed = (double)(stop - start) * 1000.0 / CLOCKS_PER_SEC;
        						printf("Time elapsed in ms: %f", elapsed);
										datos[sortID][CountingData2] = elapsed;
										CountingData2++;
									}
									break;

									case 2:
									{
										sortID = 1;
										clock_t start = clock();
										InsertionSortDSC(parameters.array,parameters.percentageInsertion);
										clock_t stop = clock();
        						double elapsed = (double)(stop - start) * 1000.0 / CLOCKS_PER_SEC;
        						printf("Time elapsed in ms: %f", elapsed);
										datos[sortID][CountingData2] = elapsed;
										CountingData2++;
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
									{
										sortID = 2;
										clock_t start = clock();
										CocktailSortASC(parameters.array,parameters.percentageCocktail);
										clock_t stop = clock();
        								double elapsed = (double)(stop - start) * 1000.0 / CLOCKS_PER_SEC;
        								printf("Time elapsed in ms: %f", elapsed);
												datos[sortID][CountingData3] = elapsed;
												CountingData3++;
									}
									break;

									case 2:
									{
										sortID = 2;
										clock_t start = clock();
										CocktailSortDSC(parameters.array,parameters.percentageCocktail);
										clock_t stop = clock();
        								double elapsed = (double)(stop - start) * 1000.0 / CLOCKS_PER_SEC;
        								printf("Time elapsed in ms: %f", elapsed);
												datos[sortID][CountingData3] = elapsed;
												CountingData3++;
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
									{
										sortID = 3;
										clock_t start = clock();
										SelectionSortASC(parameters.array,parameters.percentageSelection);
										clock_t stop = clock();
        								double elapsed = (double)(stop - start) * 1000.0 / CLOCKS_PER_SEC;
        								printf("Time elapsed in ms: %f", elapsed);
												datos[sortID][CountingData4] = elapsed;
												CountingData4++;
									}
									break;

									case 2:
									{
										sortID = 3;
										clock_t start = clock();
										SelectionSortDSC(parameters.array,parameters.percentageSelection);
										clock_t stop = clock();
        								double elapsed = (double)(stop - start) * 1000.0 / CLOCKS_PER_SEC;
        								printf("Time elapsed in ms: %f", elapsed);
												datos[sortID][CountingData4] = elapsed;
												CountingData4++;
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
							while (optionOrdenamiento3 != 0){
								cout << "\n-----------------------ORDEN---------------------------" << endl << endl;
								cout << "1.- Ascendente" << endl;
								cout << "2.- Descendente" << endl;
								cout << "0.- Regresar" << endl;
								cout << "\nIngresa la opcion que desees: " << endl;
								cin >> optionOrdenamiento3;
									switch (optionOrdenamiento3) {
									case 1:
									{
										sortID = 4;
										clock_t start = clock();
										ShellSortASC(parameters.array,parameters.percentageShell);
										clock_t stop = clock();
        								double elapsed = (double)(stop - start) * 1000.0 / CLOCKS_PER_SEC;
        								printf("Time elapsed in ms: %f", elapsed);
												datos[sortID][CountingData5] = elapsed;
												CountingData5++;
									}
									break;

									case 2:
									{
										sortID = 4;
										clock_t start = clock();
										ShellSortDSC(parameters.array,parameters.percentageShell);
										clock_t stop = clock();
        								double elapsed = (double)(stop - start) * 1000.0 / CLOCKS_PER_SEC;
        								printf("Time elapsed in ms: %f", elapsed);
												datos[sortID][CountingData5] = elapsed;
												CountingData5++;
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
void VerBubbleSortASC( vector<Data>* array, float * percentageBubble, float * comp1, float * comp2)
{
	int tam = array->size();
    int c, d;
		double b;
    for (c = 0; c <= (array->size() - 1); c++)
    {
			if(c == tam-1){
				*percentageBubble = 100;
			}
			else{
				*percentageBubble = (float)c/(float)tam * 100;
			}
			printf("porcentaje %f\n", *percentageBubble);

        for (d = 0; d < array->size() - c - 1; d++)
        {
            if (array->at(d).dat > array->at(d+1).dat)
            {
							*comp1 = array->at(d).dat;
							*comp2 = array->at(d + 1).dat;
							swapt(&array->at(d),&array->at(d+1));
            }
        }
    }
}
void BubbleSortASC( vector<Data>* array, float * percentageBubble)
{
	int tam = array->size();
	cout << "Tamaño" << tam << endl;
    int c, d;
		double b;
    for (c = 0; c <= (array->size() - 1); c++)
    {
			if(c == tam-1){
				*percentageBubble = 100;
			}
			else{
				*percentageBubble = (float)c/(float)tam * 100;
			}
			printf("porcentaje %f\n", *percentageBubble);

        for (d = 0; d < array->size() - c - 1; d++)
        {
            if (array->at(d).dat > array->at(d+1).dat)
            {

							swap2(d,d+1);
            }
        }
    }
}
void VerBubbleSortDSC( vector<Data>* array, float * percentageBubble,  float * comp1, float * comp2)
{
	int tam = array->size();
	cout << "Tamaño" << tam << endl;
    int c, d;
		double b;
    for (c = 0; c <= (array->size() - 1); c++)
    {
			if(c == tam-1){
				*percentageBubble = 100;
			}
			else{
				*percentageBubble = (float)c/(float)tam * 100;
			}
			printf("porcentaje %f\n", *percentageBubble);

        for (d = 0; d < array->size() - c - 1; d++)
        {
            if (array->at(d).dat < array->at(d+1).dat)
            {
							*comp2 = array->at(d).dat;
							*comp1 = array->at(d + 1).dat;
							swapt(&array->at(d),&array->at(d+1));
            }
        }
    }
}
void BubbleSortDSC( vector<Data>* array, float * percentageBubble)
{
	int tam = array->size();
	cout << "Tamaño" << tam << endl;
    int c, d;
		double b;
    for (c = 0; c <= (array->size() - 1); c++)
    {
			if(c == tam-1){
				*percentageBubble = 100;
			}
			else{
				*percentageBubble = (float)c/(float)tam * 100;
			}
			printf("porcentaje %f\n", *percentageBubble);

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
void VerSelectionSortASC(vector<Data>* array, float * percentageSelection, float * comp1, float * comp2)
{
    int c, d, min, loc, temp;
		int tam = array->size();
    for (c = 0; c <= (array->size() - 1); c++)
    {
			if(c == tam-1){
				*percentageSelection = 100;
			}
			else{
				*percentageSelection = (float)c/(float)tam * 100;
			}
			printf("porcentaje %f\n", *percentageSelection);

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
				*comp1 = array->at(c).dat;
				*comp2 = array->at(loc).dat;
				swapt(&array->at(c),&array->at(loc));
    }
}
void SelectionSortASC(vector<Data>* array, float * percentageSelection)
{
    int c, d, min, loc, temp;
	int tam = array->size();
    for (c = 0; c <= (array->size() - 1); c++)
    {
		if(c == tam-1){
			*percentageSelection = 100;
		}
		else{
			*percentageSelection = (float)c/(float)tam * 100;
		}
		printf("porcentaje %f\n", *percentageSelection);
    min = array->at(c).dat;
    loc = c;
    for (d = c + 1; d < array->size(); d++){
        if (min > array->at(d).dat){
                min = array->at(d).dat;
                loc = d;
            }
        }
		swap2(c,loc);
    }
}
void VerSelectionSortDSC(vector<Data>* array, float * percentageSelection, float * comp1, float * comp2)
{
    int c, d, min, loc, temp;
			int tam = array->size();
    for (c = 0; c <= (array->size() - 1); c++)
    {
			if(c == tam-1){
				*percentageSelection = 100;
			}
			else{
				*percentageSelection = (float)c/(float)tam * 100;
			}
			printf("porcentaje %f\n", *percentageSelection);
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
				*comp2 = array->at(c).dat;
				*comp1 = array->at(loc).dat;
				swapt(&array->at(c),&array->at(loc));
    }
}
void SelectionSortDSC(vector<Data>* array, float * percentageSelection)
{
    int c, d, min, loc, temp;
			int tam = array->size();
    for (c = 0; c <= (array->size() - 1); c++)
    {
			if(c == tam-1){
				*percentageSelection = 100;
			}
			else{
				*percentageSelection = (float)c/(float)tam * 100;
			}
			printf("porcentaje %f\n", *percentageSelection);
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
void VerCocktailSortASC(vector<Data>* array, float * percentageCocktail, float * comp1, float * comp2)
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
							*comp2 = array->at(i+1).dat;
							*comp1 = array->at(i).dat;
                  swapt(&array->at(i),&array->at(i+1));
                swapped = true;
            }
						if(i == end-1)
						{
							*percentageCocktail = 50;
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
							*comp2 = array->at(i+1).dat;
							*comp1 = array->at(i).dat;
                swapt(&array->at(i),&array->at(i+1));
                swapped = true;
            }
						if(i == start)
						{
							*percentageCocktail = 90;
						}
        }
        ++start;
				if(start == end)
				{
					*percentageCocktail = 100;
				}

				printf("porcentaje %f\n", *percentageCocktail);
    }
}
void CocktailSortASC(vector<Data>* array, float * percentageCocktail)
{
	float tam  =array->size()-1;
	bool swapped = true;
	int start = 0, end = (array->size() - 1);

    while (swapped){
        swapped = false;
        for (int i = start; i < end; ++i){
            if (array->at(i).dat > array->at(i+1).dat){
                swap2(i,i+1);
                swapped = true;
            }
						if(i == end-1)
						{
							*percentageCocktail = 50;
						}
        }
        if (!swapped)
            break;
        swapped = false;
        --end;
        for (int i = end - 1; i >= start; --i){
            if (array->at(i).dat > array->at(i+1).dat){
                swap2(i,i+1);
                swapped = true;
            }
						if(i == start)
						{
							*percentageCocktail = 90;
						}
        }
        ++start;
				if(start == end)
				{
					*percentageCocktail = 100;
				}

				printf("porcentaje %f\n", *percentageCocktail);
    }
}
void VerCocktailSortDSC(vector<Data>* array, float * percentageCocktail, float * comp1, float * comp2)
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
							*comp1 = array->at(i+1).dat;
							*comp2 = array->at(i).dat;
                  swapt(&array->at(i),&array->at(i+1));
                swapped = true;
            }
						if(i == end-1)
						{
							*percentageCocktail = 50;
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
							*comp1 = array->at(i+1).dat;
							*comp2 = array->at(i).dat;
                swapt(&array->at(i),&array->at(i+1));
                swapped = true;
            }
						if(i == start)
						{
							*percentageCocktail = 90;
						}
        }
        ++start;
				if(start == end)
				{
					*percentageCocktail = 100;
				}

				printf("porcentaje %f\n", *percentageCocktail);
    }
}
void CocktailSortDSC(vector<Data>* array, float * percentageCocktail)
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
						if(i == end-1)
						{
							*percentageCocktail = 50;
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
						if(i == start)
						{
							*percentageCocktail = 90;
						}
        }
        ++start;
				if(start == end)
				{
					*percentageCocktail = 100;
				}

				printf("porcentaje %f\n", *percentageCocktail);
    }
}

//*********INSERTION SORT**********
void VerInsertionSortASC(vector<Data>* array, float * percentageInsertion, float * comp1, float * comp2)
{
	float tam = array->size();
	 for (int i = 1; i < array->size(); i++)
	 {
		 		 int j = i;
		 while ((j > 0) && (array->at(j).dat < array->at(j - 1).dat))
		  {
				*comp2 = array->at(j-1).dat;
				*comp1 = array->at(j).dat;
				swapt(&array->at(j),&array->at(j-1));
			 j = j - 1;
		 }
		 if(i == tam-1){
			*percentageInsertion = 100;
		}
		else{
			*percentageInsertion = (float)i/(float)tam * 100;
		}
		printf("porcentaje %f\n", *percentageInsertion);
	 }
 }
void InsertionSortASC(vector<Data>* array, float * percentageInsertion)
{
 	float tam = array->size();
 	for (int i = 1; i < array->size(); i++)
 	{
 		int j = i;
 		while ((j > 0) && (array->at(j).dat < array->at(j - 1).dat)){
 			swap2(j,j-1);
 			j = j - 1;
 		}
 		if(i == tam-1){
 			*percentageInsertion = 100;
 		}
 		else{
 			*percentageInsertion = (float)i/(float)tam * 100;
 		}
 		printf("porcentaje %f\n", *percentageInsertion);
 	}
}
 void VerInsertionSortDSC(vector<Data>* array, float * percentageInsertion, float * comp1, float * comp2)
 {
	 float tam = array->size();
 	 for (int i = 1; i < array->size(); i++)
 	 {
 		 		 int j = i;
 		 while ((j > 0) && (array->at(j).dat > array->at(j - 1).dat))
 		  {
				*comp1 = array->at(j-1).dat;
				*comp2 = array->at(j).dat;
 				swapt(&array->at(j),&array->at(j-1));
 			 j = j - 1;
 		 }
 		 if(i == tam-1){
 			*percentageInsertion = 100;
 		}
 		else{
 			*percentageInsertion = (float)i/(float)tam * 100;
 		}
 		printf("porcentaje %f\n", *percentageInsertion);
 	 }
 }
void InsertionSortDSC(vector<Data>* array, float * percentageInsertion)
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
  			*percentageInsertion = 100;
  		}
  		else{
  			*percentageInsertion = (float)i/(float)tam * 100;
  		}
  		printf("porcentaje %f\n", *percentageInsertion);
  	 }
   }

//*********SHELL SORT*************
void VerShellSortASC(vector<Data>* array, float * percentageShell, float * comp1, float * comp2)
{
		float tam = array->size();
    int c, i, j, temp;
    for (c = (array->size())/2; c > 0; c /= 2)
		{
			for (i = c; i < array->size(); i++)
				{
					for (j=i-c; j>=0 && array->at(j).dat > array->at(j + c).dat; j-=c)
					{
						*comp2 = array->at(j +c).dat;
						*comp1 = array->at(j).dat;
						swapt(&array->at(j),&array->at(j+c));
					}
		}
		if(c == 1){
			*percentageShell = 100;
		}else{
			*percentageShell += 20;
		}
		printf("porcentaje %f\n", *percentageShell);
	}
}
void ShellSortASC(vector<Data>* array, float * percentageShell)
{
	float tam = array->size();
    int c, i, j, temp;
    for (c = (array->size())/2; c > 0; c /= 2){
	        for (i = c; i < array->size(); i++){
			for (j=i-c; j>=0 && array->at(j).dat > array->at(j + c).dat; j-=c)
				swap2(j,j+c);
			}
			if(c == 1){
				*percentageShell = 100;
			}else{
				*percentageShell += 20;
			}
			printf("porcentaje %f\n", *percentageShell);
	}
}
void VerShellSortDSC(vector<Data>* array, float * percentageShell, float * comp1, float * comp2)
{
	float tam = array->size();
	int c, i, j, temp;
	for (c = (array->size())/2; c > 0; c /= 2)
	{
		for (i = c; i < array->size(); i++)
			{
				for (j=i-c; j>=0 && array->at(j).dat < array->at(j + c).dat; j-=c)
				{
					*comp1 = array->at(j +c).dat;
					*comp2 = array->at(j).dat;
					swapt(&array->at(j),&array->at(j+c));
				}
			}
			if(c == 1){
				*percentageShell = 100;
			}else{
				*percentageShell += 20;
			}
			printf("porcentaje %f\n", *percentageShell);

	}

}
void ShellSortDSC(vector<Data>* array, float * percentageShell)
{
	float tam = array->size();
	int c, i, j, temp;
	for (c = (array->size())/2; c > 0; c /= 2)
	{
		for (i = c; i < array->size(); i++)
			{
				for (j=i-c; j>=0 && array->at(j).dat < array->at(j + c).dat; j-=c)
				{
					swap2(j,j+c);
				}
			}
			if(c == 1){
				*percentageShell = 100;
			}else{
				*percentageShell += 20;
			}
			printf("porcentaje %f\n", *percentageShell);

	}
}

void coutBubbleSort(){
	cout << ">> COMPLEJIDAD CICLOMATICA : O(N^2)\n" << endl;
	cout << ">> COMPLEJIDAD ESPACIAL : O(1)\n" << endl;
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
	cout << "printf(""porcentaje %f"", *percentage);" << endl;
  cout << "for (d = 0; d < array->size() - c - 1; d++)" << endl;
  cout << "{" << endl;
  cout << "	if (array->at(d).dat < array->at(d+1).dat) swap2(d,d+1); << endl; " << endl;
  cout << "}" << endl;
  cout << "for (d = 0; d < array->size() - c - 1; d++)" << endl;
  cout << "{" << endl;
  cout << "	if (array->at(d).dat < array->at(d+1).dat) swap2(d,d+1); << endl; " << endl;
  cout << "}" << endl;
}

void coutSelectionSort(){
	cout << ">> COMPLEJIDAD CICLOMATICA : O(N^2)\n" << endl;
	cout << ">> COMPLEJIDAD ESPACIAL : O(1)\n" << endl;
	cout << "int c, d, min, loc, temp;" << endl;
	cout << "int tam = array->size();" << endl;
  cout << "for (c = 0; c <= (array->size() - 1); c++)" << endl;
  cout << "{" << endl;
	cout << "	if(c == tam-1){" << endl;
	cout << "		*percentage = 100;" << endl;
	cout << "	}" << endl;
	cout << "	else{" << endl;
	cout << "		*percentage = (float)c/(float)tam * 100;" << endl;
	cout << "	}" << endl;
	cout << "	printf(""porcentaje %f"", *percentage);" << endl;
  cout << "min = array->at(c).dat;" << endl;
  cout << "loc = c;" << endl;
  cout << "for (d = c + 1; d < array->size(); d++){" << endl;
  cout << "    if (min > array->at(d).dat){" << endl;
  cout << "            min = array->at(d).dat;" << endl;
  cout << "            loc = d;" << endl;
  cout << "        }" << endl;
  cout << "    }" << endl;
	cout << "	swap2(c,loc);" << endl;
  cout << "}" << endl;
}

void coutCocktailSort(){
	cout << ">> COMPLEJIDAD CICLOMATICA : O(N^2)\n" << endl;
	cout << ">> COMPLEJIDAD ESPACIAL : O(1)\n" << endl;
	cout << "float tam  =array->size()-1;" << endl;
	cout << "bool swapped = true;" << endl;
	cout << "int start = 0, end = (array->size() - 1);" << endl;
  cout << "while (swapped){" << endl;
  cout << "    swapped = false;" << endl;
  cout << "    for (int i = start; i < end; ++i){" << endl;
  cout << "        if (array->at(i).dat > array->at(i+1).dat){" << endl;
  cout << "            swap2(i,i+1);" << endl;
  cout << "            swapped = true;" << endl;
  cout << "        }" << endl;
  cout << "    }" << endl;
  cout << "    if (!swapped)" << endl;
  cout << "        break;" << endl;
  cout << "    swapped = false;" << endl;
  cout << "    --end;" << endl;
  cout << "    for (int i = end - 1; i >= start; --i){" << endl;
  cout << "        if (array->at(i).dat > array->at(i+1).dat){" << endl;
  cout << "            swap2(i,i+1);" << endl;
  cout << "            swapped = true;" << endl;
  cout << "        }" << endl;
  cout << "    }" << endl;
  cout << "    ++start;" << endl;
  cout << "}" << endl;

}

void coutInsertionSort(){
	cout << ">> COMPLEJIDAD CICLOMATICA : O(N^2)\n" << endl;
	cout << ">> COMPLEJIDAD ESPACIAL : O(1)\n" << endl;
	cout << "float tam = array->size();" << endl;
 	cout << "for (int i = 1; i < array->size(); i++)" << endl;
 	cout << "{" << endl;
 	cout << "	int j = i;" << endl;
 	cout << "	while ((j > 0) && (array->at(j).dat < array->at(j - 1).dat)){" << endl;
 	cout << "		swap2(j,j-1);" << endl;
 	cout << "		j = j - 1;" << endl;
 	cout << "	}" << endl;
 	cout << "	if(i == tam-1){" << endl;
 	cout << "		*percentage = 100;" << endl;
 	cout << "	}" << endl;
 	cout << "	else{" << endl;
 	cout << "		*percentage = (float)i/(float)tam * 100;" << endl;
 	cout << "	}" << endl;
 	cout << "	printf(""porcentaje %f"", *percentage);" << endl;
 	cout << "}" << endl;
}

void coutShellSort(){
	cout << ">> COMPLEJIDAD CICLOMATICA : O(N^1.25)\n" << endl;
	cout << ">> COMPLEJIDAD ESPACIAL : O(1)\n" << endl;
	cout << "float tam = array->size();" << endl;
  cout << "int c, i, j, temp;" << endl;
  cout << "for (c = (array->size())/2; c > 0; c /= 2){" << endl;
	cout << "        for (i = c; i < array->size(); i++){" << endl;
	cout << "		for (j=i-c; j>=0 && array->at(j).dat > array->at(j + c).dat; j-=c)" << endl;
	cout << "			swap2(j,j+c);" << endl;
	cout << "		}" << endl;
	cout << "	if(i == 1) *percentage = 100;" << endl;
	cout << "	else{" << endl;
	cout << "	*percentage = (float)c/(float)tam * 100;" << endl;
	cout << "	}" << endl;
	cout << "	printf(""porcentaje %f"", *percentage);" << endl;
	cout << "}" << endl;
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
