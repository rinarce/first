// UNI.c

#include <stdio.h>
#include <locale.h>
#include <stdlib.h>           // для выделения памяти
#include <io.h>               // для filelength()
#include <math.h>             // для tan()

#define TASK_INPUT_FILE   "uni_shapes.bin"
#define M_PI              3.14159265358979323846         // pi

 typedef enum figure_type_t {
    CIRCLE,
    RECTANGLE,
    REGULAR_POLYGON,
    FIG_COUNT_TYPE,
  } figure_type_t;

 typedef enum figure_color_t {
    RED,
    GREEN,
    BLUE,
    FIG_COUNT_COLOR,
  } figure_color_t;
 
 typedef  struct circle_attribute_t {
    float radius;
  } circle_attribute_t;

 typedef struct rectangle_attribute_t {
    float width;
    float height;
  } rectangle_attribute_t;

  typedef struct polygon_attribute_t {
    int number_sides;
    float side_size;
  } polygon_attribute_t;

typedef struct figure_t { 
  figure_type_t type;
  figure_color_t color;
  union figure_attribute_t {
    circle_attribute_t    circle;
    rectangle_attribute_t rectangle;
    polygon_attribute_t   polygon;
  } attr;
} figure_t;


char const* s_typeName[FIG_COUNT_TYPE] = { "Circ", "Rect", "Poly" };
char const* s_colorName[FIG_COUNT_COLOR] = { "red", "green", "blue" };
char const* s_unknown = "ERROR";


// Check input data for correct figure type
int _isTypeOK(figure_type_t fig_type){ 
  return (0 <= fig_type && fig_type < FIG_COUNT_TYPE);
}

// Check input data for correct figure color
int _isColorOK(figure_color_t fig_color) {
  return (0 <= fig_color && fig_color < FIG_COUNT_COLOR);
}

// Translate code in human readable word
 char const* _translateType(figure_type_t f_type) {
  if (_isTypeOK(f_type)) 
    return s_typeName[f_type];
  else
    return s_unknown;
}

// Translate code in human readable word
 char const* _translateColor(figure_color_t f_col) {
  if (_isColorOK(f_col)) 
    return s_colorName[f_col];
  else                  
    return s_unknown;
}

// Calculate figure square
double _figureSquare(figure_t* fig) {
  switch (fig->type) {
    case(CIRCLE):
      return fig->attr.circle.radius * fig->attr.circle.radius * M_PI;
    case(RECTANGLE):
      return fig->attr.rectangle.width * fig->attr.rectangle.height;
    case(REGULAR_POLYGON):
      return (fig->attr.polygon.number_sides / 4
            * fig->attr.polygon.side_size * fig->attr.polygon.side_size 
            / tan(M_PI / fig->attr.polygon.number_sides));
/* https://ru.wikipedia.org/wiki/Правильный_многоугольник
    ctg(x) 1 способ - 1/tan(x)
           2 способ, даёт меньше всего погрешность - cos(x)/sin(x)
           3 способ, самый быстрый - tan(M_PI/2 - x).
*/
  default:
    return 0;  // "Unknown figure"
  }
}

// Print figure's attributes
void _printFigureAttributes(figure_t* fig) {
  printf("%-6s %-6s <",
    _translateType(fig->type),
    _translateColor(fig->color));

  switch (fig->type){
    case(CIRCLE) :
      printf("r =%6.2f              ",
        fig->attr.circle.radius);
      break;

    case(RECTANGLE):
      printf("w =%6.2f    h =%6.2f ", 
        fig->attr.rectangle.width, 
        fig->attr.rectangle.height);
      break;

    case(REGULAR_POLYGON):
      printf("n =%3d    side =%6.2f ", 
        fig->attr.polygon.number_sides, 
        fig->attr.polygon.side_size);
      break;

    default:
      printf("Unknown figure type=[%d]>\n", fig->type);
      return;     // For unknown figure - don't print square 
  }
  printf(" Sq =%9.4f>\n", _figureSquare(fig)); // print square
}

// get file size
unsigned long int _fileSize(FILE* file) { 
  return _filelength(_fileno(file)); 
}

int main() { 
  char filename[] = TASK_INPUT_FILE;

  FILE* fp;
  size_t fileSize;
  
  int countersColor[FIG_COUNT_COLOR] = { 0 };
  int countersType[FIG_COUNT_TYPE]   = { 0 };

  double countersSquareByType[FIG_COUNT_TYPE]   = { 0 };
  double countersSquareByColor[FIG_COUNT_COLOR] = { 0 };

  int badFiguresCounter = 0; // счётчик нехороших фигур

  setlocale(LC_ALL, "Russian");

  // Попытка ввода из файла
  errno_t err = fopen_s(&fp, filename, "rb");
  if (err == 0) { // Файл открылся
    
    fileSize = _fileSize(fp);
    
    int totalFigures = fileSize / sizeof(figure_t);
    printf("Всего фигур : %d\n", totalFigures);

    // Создать массив для фигур
    figure_t* figures = (figure_t*)malloc(fileSize);
    if (NULL == figures) {
      printf("\nMemory allocation error\n");
      fclose(fp);
      return -1;
    }

    // Попытка чтения из файла сразу всех фигур
    size_t readed = fread(figures, sizeof(figure_t), totalFigures, fp);
    if (readed == totalFigures)
      printf("File read OK, read %d figures\n", readed);
    else  // Если вдруг не введены все, обрабатывать сколько есть
      printf("File read error, just read %d figures", readed);
    
    // Обработка введённых фигур
    for (unsigned figureIndex = 0; figureIndex < readed; ++figureIndex)
    {
      printf("%3d ", figureIndex + 1);        // Номер
      _printFigureAttributes(&figures[figureIndex]);
      
      figure_type_t type = figures[figureIndex].type;
      figure_color_t color = figures[figureIndex].color;

      if (_isTypeOK(type)) { 
        // считаем для каждого типа - количество и общую площадь
        double square = _figureSquare(&figures[figureIndex]);
        countersType[type]++;
        countersSquareByType[type] += square;
        
        if (_isColorOK(color)) {
          countersColor[color]++;    // считаем количество по цвету
          countersSquareByColor[color] += square;
        }
        else
          badFiguresCounter++; // плохой цвет
      }
      else
        badFiguresCounter++;   // плохой тип
    }
   
    // Распечатка результата
    printf("\n----------------------------------------------\n");
    printf("\nCount by type:\n"
           "----------------------------------------------\n");
    double totalSquare = 0;
    int counter = 0;
    for (figure_type_t typeIndex = 0; typeIndex < FIG_COUNT_TYPE; ++typeIndex) {
      printf("%-6s : %4d  Square : %9.2f\n", 
              _translateType(typeIndex),
              countersType[typeIndex],
              countersSquareByType[typeIndex]);
      counter += countersType[typeIndex];
      totalSquare += countersSquareByType[typeIndex];
    }
    printf("----------------------------------------------\n"
           "Total  : %4d  Square : %9.2f\n", counter, totalSquare);
    
    printf("\n\nCount by colors:\n"
           "----------------------------------------------\n");
    counter = 0;
    totalSquare = 0;
    for (figure_color_t colorIndex = 0; colorIndex < FIG_COUNT_COLOR; ++colorIndex) {
      printf("%-6s : %4d  Square : %9.2f\n",
              _translateColor(colorIndex),
              countersColor[colorIndex],
              countersSquareByColor[colorIndex]);
      counter += countersColor[colorIndex];
      totalSquare += countersSquareByColor[colorIndex];
    }
    printf("----------------------------------------------\n"
           "Total  : %4d  Square : %9.2f\n", counter, totalSquare);

    if (badFiguresCounter)
      printf("\n! Figures with error, total %d\n", badFiguresCounter);
    
    free(figures);
    fclose(fp);
  }
  else  // Не удалось даже открыть файл
    printf("Can't open file:  %s\nfile open error:  %d\n", filename, err);
  
  int x = getchar();
  return err; 
}
