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
void MainMenu(ThreadParameters);
void userInput(ThreadParameters);
sf::RectangleShape drawRectangle(int x,int y, int stat, float a);
// --------SORTS--------
//BUBBLE
//****GRAFICO****
void VerBubbleSortASC( vector<Data>* array, float * percentage);
void VerBubbleSortDSC( vector<Data>* array, float * percentage);
//****NORMAL****
void BubbleSortASC( vector<Data>* array, float * percentage);
void BubbleSortDSC( vector<Data>* array, float * percentage);
//SELECTION
//****GRAFICO****
void VerSelectionSortASC(vector<Data>* array, float * percentage);
void VerSelectionSortDSC(vector<Data>* array, float * percentage);
//****NORMAL****
void SelectionSortASC(vector<Data>* array, float * percentage);
void SelectionSortDSC(vector<Data>* array, float * percentage);
//COCKTAIL
//****GRAFICO****
void VerCocktailSortASC(vector<Data>* array, float * percentage);
void VerCocktailSortDSC(vector<Data>* array, float * percentage);
//****NORMAL****
void CocktailSortASC(vector<Data>* array, float * percentage);
void CocktailSortDSC(vector<Data>* array, float * percentage);
//ISERTION
//****GRAFICO****
void VerInsertionSortASC(vector<Data>* array, float * percentage);
void VerInsertionSortDSC(vector<Data>* array, float * percentage);
//****NORMAL****
void InsertionSortASC(vector<Data>* array, float * percentage);
void InsertionSortDSC(vector<Data>* array, float * percentage);
//SHELL
//****GRAFICO****
void VerShellSortASC(vector<Data>* array, float * percentage);
void VerShellSortDSC(vector<Data>* array, float * percentage);
//****NORMAL****
void ShellSortASC(vector<Data>* array, float * percentage);
void ShellSortDSC(vector<Data>* array, float * percentage);

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

    ThreadParameters parameters = {&array,&windowStatus,&percentage};

    // Create a thread for userInput function and runs it//
    sf::Thread thread(&userInput,parameters);
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

	}

  window.clear(sf::Color::White);//Limpia la pantalla
	texture.clear(sf::Color::White);
	////////imprimir aqui///////////////
	for(int i=0;i<array.size();i++)
	{
		float b = array[i].dat;

		sf::RectangleShape rec = drawRectangle((WINDOW_WIDTH/2)+(i*10), 100, array[i].stat,b);
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
  int option = 0, option2 = 0, numberRandoms;
	Data num;;
	srand (static_cast <unsigned> (time(0)));

  	cout << "--------------PROYECTO FINAL DE ALGORTIMOS--------------" << endl << endl;
  	cout << "1.- Crear elementos aleatorios" << endl;
  	cout << "2.- Ingresar manualmente elementos" << endl;
  	cout << "0.- Salir" << endl;
  	cout << "Ingresa la opcion que desees: " << endl;
  	cin >> option;
  	switch (option) {
    	case 1:
			while (option2 != 0) {
				cout << "1.- Ingresar el numero de elementos que desea generar: " << endl;
				cout << "0.- Terminar" << endl;
		  	cin >> option2;
		  	switch (option2) {
		    	case 1:
					cin >> numberRandoms;
					for (int i = 0; i < numberRandoms; i++) {
						num.dat = ((float)rand()/(float)(RAND_MAX));
						num.stat = 0;
						parameters.array->push_back(num);
					}
					option2 = 0;
					break;

					case 0:
					break;
				}
			}
    	break;

    	case 2:
			while (option2 != 0) {
				cout << "1.- Ingresar número" << endl;
				cout << "0.- Terminar" << endl;
		  	cin >> option2;
		  	switch (option) {
		    	case 1:
					cout << "n: ";
					cin>>num.dat;
				 	num.stat=0;
				 	parameters.array->push_back(num);
		    	break;

					case 0:
					break;
				}
    	break;

    	case 0:
				exit(0);
    	break;

    	default:
      	cout << "Opción incorrecta ingresa un valor nuevamente" << endl;
    	break;
  		}
		}


}


///////////////////////menu///////////////////////////
void userInput(ThreadParameters parameters)
{
    //Variables for user inputs//
     string selectedOption;
    Data num;
		float tam;

    while(*parameters.windowStatus)
    {
         cout<< endl<<"---------Algoritmos de Ordenamiento-------"<< endl;
         cout<<"1. Agregar numero al arreglo"<< endl;
				 cout<<"1.2. BubbleSort ASC"<< endl;
				 cout <<"1.3 BubbleSort DSC" << endl;
				 cout << "1.4 SelectionSortASC" << endl;
				 cout << "1.5 SelectionSortDSC" << endl;
				 cout << "1.6 CocktailSortASC" << endl;
				 cout << "1.7 CocktailSortDSC" << endl;
				 cout << "1.8 InsertionSortASC" << endl;
				 cout << "1.9 InsertionSortDSC" << endl;
				 cout << "1.10 ShellSortASC" << endl;
				 cout << "1.11 ShellSortASC" << endl;
				 cout << "3. Busqueda Secuencial" << endl;

         cout<<"2. Quit"<< endl;
         cout<<"Your selection: ";
         cin>>selectedOption;

        if(selectedOption=="1")
        {
					 cout<<"Ingresa el numero: ";
					 cin>>num.dat;
					num.stat=0;
					parameters.array->push_back(num);
					tam+=tam;

        }

				else if(selectedOption=="1.2")
				{

						VerBubbleSortASC(parameters.array,parameters.percentage);
				}
				else if(selectedOption=="1.3")
				{

						VerBubbleSortDSC(parameters.array,parameters.percentage);
				}
				else if(selectedOption=="1.4")
				{

						VerSelectionSortASC(parameters.array,parameters.percentage);
				}
				else if(selectedOption=="1.5")
				{

						VerSelectionSortDSC(parameters.array,parameters.percentage);
				}
				else if(selectedOption=="1.6")
				{

						VerCocktailSortASC(parameters.array,parameters.percentage);
				}
				else if(selectedOption=="1.7")
				{

						VerCocktailSortDSC(parameters.array,parameters.percentage);
				}
				else if(selectedOption=="1.8")
				{

						VerInsertionSortASC(parameters.array,parameters.percentage);
				}
				else if(selectedOption=="1.9")
				{
						VerInsertionSortDSC(parameters.array,parameters.percentage);
				}
				else if(selectedOption=="1.10")
				{
						VerShellSortASC(parameters.array,parameters.percentage);
				}
				else if(selectedOption=="1.11")
				{
						VerShellSortDSC(parameters.array,parameters.percentage);
				}
				else if(selectedOption=="3")
				{
					float clave, resultado2;
					cout << "ingrese el valor a buscar" << endl;
					cin >> clave;
					resultado2 = busquedaLineal(parameters.array, clave);

		    if (resultado2 == -1)
		    {
		        cout << " >> El número " << clave << " NO se encuentra dentro del arreglo " <<  resultado2 << endl;
		    }

		    else{
		        cout << " >> El número " << clave << " se encuentra en la posición (" << resultado2 << ") del arreglo" << endl;
		    }

				}

        else if(selectedOption=="2")
            *parameters.windowStatus=false;

        else
             cout<<"Invalid option"<< endl;
    }
}


///////////////////////////////poner cuadro////////////////////
sf::RectangleShape drawRectangle(int x,int y, int stat,float a)
{
	sf::RectangleShape rectangle(sf::Vector2f(10, -(a+5)));
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
							percentage1 = (float)i/(float)end * 100;
							printf("porcentaje %d\n", percentage1);
							*percentage = percentage1;
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
						percentage2 = (float)i/(float)start * 100;
						printf("porcentaje %d\n", percentage2);
						*percentage = percentage2;
        }
        ++start;
				if(start == tam-1)
				{
					*percentage = 100;
				}
				else{
					*percentage = percentage1 + percentage2;
				}

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
					if(i == tam){
						*percentage = 100;
					}
					else{
						*percentage = (float)i/(float)tam * 100;
					}
					printf("porcentaje %f\n", *percentage);
				}

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
