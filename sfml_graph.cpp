#include <iostream>
#include <exception>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <unistd.h>
#include <math.h>
#include <iostream>
#include <sstream>
#include <iomanip>

using namespace std;



//Constants

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

struct ThreadParameters //parametros entre los threads
{
    vector<Data>* array;
    bool* windowStatus;
		float * percentage;
};

//Functions//

void userInput(ThreadParameters);
sf::RectangleShape drawRectangle(int x,int y, int stat, float a);
// --------SORTS--------
//BUBBLE
void BubbleSortASC( vector<Data>* array, float * percentage);
void BubbleSortDSC( vector<Data>* array, float * percentage);
//SELECTION
void SelectionSortASC(vector<Data>* array, float * percentage);
void SelectionSortDSC(vector<Data>* array, float * percentage);
//COCKTAIL
void CocktailSortASC(vector<Data>* array, float * percentage);
void CocktailSortDSC(vector<Data>* array, float * percentage);
//ISERTION
void InsertionSortASC(vector<Data>* array, float * percentage);
void InsertionSortDSC(vector<Data>* array, float * percentage);
//QUICK
void quickSortASC(vector<Data>* array, float * percentage, Data *l, Data *h);
void swapt(Data *dat1, Data *dat2);


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


///////////////////////menu///////////////////////////
void userInput(ThreadParameters parameters)
{

    //Variables for user inputs//
     string selectedOption;
    Data num;

    while(*parameters.windowStatus)
    {

         cout<< endl<<"____________Visual Graph_____________"<< endl;
         cout<<"1. Agregar numero al arreglo"<< endl;
				 cout<<"1.1. Agregar numero al arreglo"<< endl;
				 cout<<"1.2. BubbleSort ASC"<< endl;
				 cout <<"1.3 BubbleSort DSC" << endl;
				 cout << "1.4 SelectionSortASC" << endl;
				 cout << "1.5 SelectionSortDSC" << endl;
				 cout << "1.6 CocktailSortASC" << endl;
				 cout << "1.7 CocktailSortDSC" << endl;
				 cout << "1.8 InsertionSortASC" << endl;
				 cout << "1.9 InsertionSortDSC" << endl;
				 cout << "1.10 QuickSortASC" << endl;

         cout<<"2. Quit"<< endl;
         cout<<"Your selection: ";
         cin>>selectedOption;

        if(selectedOption=="1")
        {
					 cout<<"Ingresa el numero: ";
					 cin>>num.dat;
					num.stat=0;
					parameters.array->push_back(num);
        }

				else if(selectedOption=="1.1")
				{
						 cout<<"Ejecutando swap"<< endl;
						// cout<<parameters.array<< endl;

						 cout<<"Ejecutando swap"<< endl;
						swapt(&parameters.array->at(1),&parameters.array->at(2));
				}
				else if(selectedOption=="1.2")
				{

						BubbleSortASC(parameters.array,parameters.percentage);
				}
				else if(selectedOption=="1.3")
				{

						BubbleSortDSC(parameters.array,parameters.percentage);
				}
				else if(selectedOption=="1.4")
				{

						SelectionSortASC(parameters.array,parameters.percentage);
				}
				else if(selectedOption=="1.5")
				{

						SelectionSortDSC(parameters.array,parameters.percentage);
				}
				else if(selectedOption=="1.6")
				{

						CocktailSortASC(parameters.array,parameters.percentage);
				}
				else if(selectedOption=="1.7")
				{

						CocktailSortDSC(parameters.array,parameters.percentage);
				}
				else if(selectedOption=="1.8")
				{

						InsertionSortASC(parameters.array,parameters.percentage);
				}
				else if(selectedOption=="1.9")
				{
						InsertionSortDSC(parameters.array,parameters.percentage);
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

void BubbleSortASC( vector<Data>* array, float * percentage)
{
	float tam = array->size();
	cout << "Tamaño" << tam << endl;
	float contador = (float)100/tam;

    float c, d;
		float b;
    for (c = 0; c < (array->size() - 1); c++)
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
            if (array->at(d).dat < array->at(d+1).dat)
            {
							swapt(&array->at(d),&array->at(d+1));
            }
        }
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
				swapt(&array->at(c),&array->at(loc));
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
            if (array->at(i).dat > array->at(i+1).dat)
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
void InsertionSortASC(vector<Data>* array, float * percentage)
{
	 for (int i = 1; i < array->size(); i++)
	 {
		 int j = i;
		 while ((j > 0) && (array->at(j).dat < array->at(j - 1).dat))
		  {
				swapt(&array->at(j),&array->at(j-1));
				cout << array->at(j).dat << endl;
			 j = j - 1;
		 }
	 }
 }
 void InsertionSortDSC(vector<Data>* array, float * percentage)
 {
 	 for (int i = 1; i < array->size(); i++)
 	 {
 		 int j = i;
 		 while ((j > 0) && (array->at(j).dat > array->at(j - 1).dat))
 		  {
 				swapt(&array->at(j),&array->at(j-1));
 				cout << array->at(j).dat << endl;
 			 j = j - 1;
 		 }
 	 }
  }
