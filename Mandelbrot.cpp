#include <math.h>
#include <iostream>
#include <sstream>
#include <format>
#include <SDL2/SDL.h>

#define SCREEN_WIDTH 400
#define SCREEN_HEIGHT 400 


using namespace std;



class Complex
{
    double real;
    double imaginary;

    public:

    Complex()
    {
        this->real = 0;
        this->imaginary =0;
    }

    Complex add(Complex c)
    {
        Complex res {};
        res.real = this->real + c.real;
        res.imaginary = this->imaginary + c.imaginary;

        return res;
    }


    Complex(double real,double imaginary)
    {
        this->real = real;
        this->imaginary = imaginary;
    }

    Complex square()
    {
        Complex res {};
        res.real = real * real - imaginary * imaginary;
        res.imaginary = 2 * real * imaginary;

        return res;

    }

    double absoluteValue()
    {
        return sqrt(real*real+imaginary*imaginary);
    }

    string toString()
    {
        stringstream s;
        if (imaginary < 0)
            s << this->real  << this->imaginary << "i";
        else
            s << this->real << "+" << this->imaginary << "i";

        return s.str();
    }




};
class Mandelbrot
{

    public:

    int grid[400][400];

    
    void generateGrid()
    {
        double step = 0.01;
        double a = -2;
        double b = -2;
        for(int y=0;y<400;y++,b+=step)
        {
            a = -2;
            for(int x=0;x<400;x++,a+=step)
            {
               // cout << "a: " << a << endl;
               // cout << "b: " << b << endl;
                grid[y][x] = iterate(Complex(a,b));

            }
        }


    }


    void drawGrid(SDL_Window * w,SDL_Renderer * renderer)
    {
        cout << "drawGrid entered" << endl;
        //generateGrid();
        SDL_SetRenderDrawColor(renderer,0,0,255,255);
        for(int y=0;y<400;y++)
        {
            for(int x=0;x<400;x++)
            {
                if(grid[y][x] == -1)
                {
                    SDL_RenderDrawPoint(renderer,x,y);
                }
            }

            SDL_RenderPresent(renderer);
        }


    }



    static int iterate(Complex c)
    {
        int iteration=0;
        int max_iterations = 1000;
        Complex Zn = Complex(0,0).add(c);

        for(iteration=0;iteration<max_iterations && Zn.absoluteValue() <= 2;iteration++)
        {

          //  cout << "Number " << iteration << ": " <<Zn.toString() << endl;
            //cout << "Absolute value: " << Zn.absoluteValue() << endl;
            Zn = Zn.square().add(c);
            

        }
        //if(iteration==0)
         // return max_iterations;
        if(iteration==max_iterations)
            return -1;
        else
            return iteration;


    }


};



int main()
{
    Complex c(5,-2);
    Mandelbrot m;

    double absoluteValue = c.square().absoluteValue();
/*
    cout <<  "complex number:" << c.toString() << endl;
    cout << "square: " << c.square().toString() << endl;
    cout << "Absolute value of square: " << absoluteValue << endl;
    //m.iterate(Complex(4,-2));
  */  

   m.generateGrid();

    SDL_Window* window = NULL;
    SDL_Renderer * renderer = NULL;
	
	//The surface contained by the window
	SDL_Surface* screenSurface = NULL;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
	}
	else
	{
		//Create window
		SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT,0, &window, &renderer );
		if( window == NULL  || renderer == NULL)
		{
			printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
		}
		else
		    screenSurface = SDL_GetWindowSurface( window );
			 
			bool quit = false;

			m.drawGrid(window,renderer);

			while(!quit)
			{
				SDL_Event e;
				
				while ( SDL_PollEvent(&e))
				{
					if(e.type == SDL_QUIT)
						quit = true;
				}

				
				/*if(SDL_GetTicks() - start > 100)
				{
					//start = SDL_GetTicks();
					 
					
					//dm->draw();

					

					/*int r = rand() % 256;
					int g = rand() % 256;
					int b = rand() % 256;


					SDL_FillRect( screenSurface, NULL, SDL_MapRGB( screenSurface->format, r, g, b ) );
					*/
					
					//SDL_UpdateWindowSurface( window );
					
	
			}
		}	
	 


	

	//Destroy window
	SDL_DestroyWindow( window );

	//Quit SDL subsystems
	SDL_Quit();






}
