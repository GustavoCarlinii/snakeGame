#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#define V 21 //truco que aprendi para definir valores de manera global, definde a V y H como las dimensiones del mapa
#define H 65
#define ARRIBA '8'
#define ABAJO '2'
#define IZQUIERDA '4'
#define DERECHA '6'


typedef struct{
//    coordenadas de donde estan colocadas las partes del cuerpo de la serpiente, esto es posible gracias a typedef
    int x,y;
//   cambian el estado de x e y
    int ModX,ModY;
    char imagen;
}snk;

//Esta estructura es para la fruta que usara el alias de frt
typedef struct{
//coordenadas de la fruta
int x, y;
}frt;

// Defino que tan larga puede llegar a ser la serpiente
snk snake[100];

frt fruta;

void inicio(int *tamanio, char campo[V][H]);
void intro_Campo(char campo[V][H]);
void into_Datos(char campo[V][H],int tamanio);
void draw(char campo[V][H]);
void loop(char campo[V][H], int tamanio);
void input(char campo[V][H],int *tamanio, int *muerto);

int main()
{

    int tamanio;
    char campo[V][H];
    inicio(&tamanio,campo);//inicia todos los elementos
    loop(campo, tamanio);
    return 0;

}

void inicio(int *tamanio, char campo[V][H]){
   // indicamos posicion de cabeza de la serpiente, donde comenzara.
    snake[0].x = 32;
    snake[0].y= 10;

    // tamaño de la serpiente

    *tamanio = 4;
    //crea la semilla en coordenadas aleatorias
    srand(time(NULL));
    // aca le estoy diciendo que como mucha la fruta aparecera en H y V menos 1, esto es para que no se salga del mapa
    fruta.x = rand() % (H - 1);
    fruta.y =rand() % (V-1);

    // para que las coordenadas nunca sean 0
    fruta.x = rand() % (H - 2) + 1;
    fruta.y = rand() % (V - 2) + 1;


    for(int i =0 ; i<*tamanio; i++){
       // definimos como queremos que avance la serpiente
        snake[i].ModX = 1;
        snake[i].ModX = 0;
    }

    intro_Campo(campo);
    into_Datos(campo,*tamanio);

}

// creacion del campo de juego
void intro_Campo(char campo[V][H]){

    int i,j;

    for (i =0; i< V; i++){
        for(j= 0; j < H; j++ ){
             if( i == 0 || i == V -1 ){
                campo[i][j] = '-';
             }
             else if (j == 0 || j == H - 1 ){
                campo[i][j] = '|';
             }
             else{
                campo[i][j] = ' ';
             }

        }
    }




}


//metera los datos en la matriz campo

void into_Datos(char campo[V][H],int tamanio){
    int i;
    // creo el cuerpo de la serpiente
    for(i = 1; i < tamanio; i++){
       // siendo la cabeza la base quiero que los elementos se vayan poniendo al lado del otro por eso menos 1, la coordenada anterior
        snake[i].x = snake[i - 1].x -1;
        snake[i].y = snake[i - 1].y;

        snake[i].imagen = 'x';
        }
        // imagen de la cabeza de nuestra serpiente
        snake[0].imagen = 'o';

    for (i = 0; i < tamanio; i++){
        campo[snake[i].y][snake[i].x] = snake[i].imagen;
    }
    // con esto asigno la imagen de la fruta, que sera %
    campo[fruta.y][fruta.x] = '%';

}

// funcion para dibujar el mapa
void draw(char campo[V][H])
{
    int i, j;

    for (i = 0; i < V; i++){
        for(j =0; j< H; j++){
            printf("%c",campo[i][j]);
        }
    printf("\n");
    }
}


// esta funcion realiza el movimiento de la serpiente
void loop(char campo[V][H], int tamanio){

    int muerto;

    muerto = 0;

    do{
        draw(campo);
// se usa & ya que aca voy a modificar el tamaño de la serpiente y muerto tambien;
        input(campo,&tamanio,&muerto);
    }while(muerto == 0);
}

// esta funcion aplica la logica para que la serpiente pueda morir
void input(char campo[V][H],int *tamanio, int *muerto){
     int i;
     char key;

        // esto comprueba si la cabeza de la serpiente colisiona con un borde del mapa
    if(snake[0].x == 0 || snake[0].x == H - 1 || snake[0].y == 0 || snake[0].y == V - 1){
        *muerto = 1;
    }
        // esto comprueba si colisiono con alguna parte del cuerpo
    for (i = 1; i < *tamanio && muerto == 0; i++ ){
       if(snake[0].x == snake[i].x && snake[0].y == snake[i].y){
            *muerto = 1;
        }
    }

    // comprobar si nos comimos la fruta
    if (snake[0].x == fruta.x && snake[0].y == fruta.y){
        *tamanio += 1;
        snake[*tamanio - 1].imagen = 'x';

         // aca le estoy diciendo que como mucha la fruta aparecera en H y V menos 1, esto es para que no se salga del mapa
        fruta.x = rand() % (H - 1);
        fruta.y =rand() % (V-1);

        // para que las coordenadas nunca sean 0
        fruta.x = rand() % (H - 2) + 1;
        fruta.y = rand() % (V - 2) + 1;

      }
  while (!muerto) {
 if (_kbhit()) { // Verificar si se ha presionado una tecla
            char key = getch(); // Obtener la tecla presionada

            // Manejo de las teclas
            switch (key) {
                case ABAJO:
                    snake[0].ModX = 0;
                    snake[0].ModY = 1;
                    break;
                case ARRIBA:
                    snake[0].ModX = 0;
                    snake[0].ModY = -1;
                    break;
                case IZQUIERDA:
                    snake[0].ModX = -1;
                    snake[0].ModY = 0;
                    break;
                case DERECHA:
                    snake[0].ModX = 1;
                    snake[0].ModY = 0;
                    break;
                default:
                    // Otra tecla presionada, hacer algo si es necesario
                    break;
            }
        }

} 
}
