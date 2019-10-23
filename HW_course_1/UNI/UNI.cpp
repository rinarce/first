// UNI.cpp

#include <stdio.h>
#include <locale.h>
#include <stdlib.h>           // для выделения памяти
#include <io.h>               // для filelength()
#include <math.h>             // для tan()


#define FIG_TYPES  3    // всего типов
#define FIG_COLORS 3    // разных цветов
#define TASK_INPUT_FILE "uni_shapes.bin"

#define M_PI       3.14159265358979323846         // pi

struct Figure
{ 
  enum Figure_type {
    CIRCLE,
    RECTANGLE,
    REGULAR_POLYGON
  };

  enum Figure_color {
    RED,
    GREEN,
    BLUE
  };

  struct Circle_Attribute {
    float radius;
  };

  struct Rectangle_Attribute {
    float width;
    float height;
  };

  struct Poligon_Attribute {
    int number_sides;
    float side_size;
  };

  Figure_type type;
  Figure_color color;
  union Figure_Attribute
  {
    Circle_Attribute circle;
    Rectangle_Attribute rectangle;
    Poligon_Attribute poligon;
  } attr;

};

struct Figure_Translate
{     // Максимально отведу на название фигуры 20 символов
  const char type_name[FIG_TYPES][20] = { "Circ", "Rect", "Poly" };
      // Максимально отведу на название цвета 20 символов
  const char color_name[FIG_COLORS][20] = { "red", "green", "blue" };
  const char* unkn = "ERROR"; // Что-то не сходится
} translate_table;

int isTypeOK(Figure::Figure_type fig_type)
{ // Проверим, что тип допустимый в задаче
  return (0 <= fig_type && fig_type < FIG_TYPES);
}

int isColorOK(Figure::Figure_color fig_color)
{ // Проверим, что цвет допустимый в задаче
  return (0 <= fig_color && fig_color < FIG_COLORS);
}

const char* Fig_TranslateType(Figure::Figure_type f_type)
{
  if (isTypeOK(f_type)) return translate_table.type_name[f_type];
  else                  return translate_table.unkn;
}

const char* Fig_TranslateColor(Figure::Figure_color f_col)
{
  if (isColorOK(f_col)) return translate_table.color_name[f_col];
  else                  return translate_table.unkn;
}

double Figure_Square(Figure* fig)
{
  switch (fig->type)
  {
    case(Figure::Figure_type::CIRCLE):
      return fig->attr.circle.radius * fig->attr.circle.radius * M_PI;

    case(Figure::Figure_type::RECTANGLE):
      return fig->attr.rectangle.width * fig->attr.rectangle.height;

    case(Figure::Figure_type::REGULAR_POLYGON):
      return (fig->attr.poligon.number_sides / 4
            * fig->attr.poligon.side_size * fig->attr.poligon.side_size 
            / tan(M_PI / fig->attr.poligon.number_sides));
/* https://ru.wikipedia.org/wiki/Правильный_многоугольник
    ctg(x) 1 способ - 1/tan(x)
           2 способ, даёт меньше всего погрешность - cos(x)/sin(x)
           3 способ, самый быстрый - tan(M_PI/2 - x).
*/
  default:
    return 0;  // "Unknown figure"
  }
}
void Figure_print(Figure* fig)
{
  printf("%-6s %-6s <",
    Fig_TranslateType(fig->type),
    Fig_TranslateColor(fig->color));

  switch (fig->type)
  {
    case(Figure::Figure_type::CIRCLE) :
      printf("r =%6.2f              ",
        fig->attr.circle.radius);
      break;

    case(Figure::Figure_type::RECTANGLE):
      printf("w =%6.2f    h =%6.2f ", 
        fig->attr.rectangle.width, 
        fig->attr.rectangle.height);
      break;

    case(Figure::Figure_type::REGULAR_POLYGON):
      printf("n =%3d    side =%6.2f ", 
        fig->attr.poligon.number_sides, 
        fig->attr.poligon.side_size);
      break;

    default:
      printf("Unknown figure type=[%d]>\n", fig->type);
      return; // Для неизвестной фигуры тут выход
  }
  printf(" Sq =%9.4f>\n", Figure_Square(fig)); // Печатем площадь
}

unsigned long int filesize(FILE* file) { 
  return _filelength(_fileno(file)); 
}

int main() 
{ 
  char filename[] = TASK_INPUT_FILE;

  FILE* fp;
  size_t file_size;
  
  int count_colors[FIG_COLORS] = { 0 };
  int count_types[FIG_TYPES] = { 0 };
  double count_squares_type[FIG_TYPES] = { 0 };
  double count_squares_color[FIG_COLORS] = { 0 };

  int bad_figs = 0; // счётчик нехороших фигур

  
  setlocale(LC_ALL, "Russian");

  // Попытка ввода из файла
  errno_t err = fopen_s(&fp, filename, "rb");
  if (err == 0) 
  { // Файл открылся
    
    file_size = filesize(fp);
    
    int number_figures = file_size / sizeof(Figure);
    printf("Всего фигур : %d\n", number_figures);

    // Создать массив для фигур
    Figure* figures = (Figure*)malloc(file_size);
    if (NULL == figures)
    {
      printf("\nMemory allocation error\n");
      fclose(fp);
      return -1;
    }

    // Попытка чтения из файла сразу всех фигур
    size_t readed = fread(figures, sizeof(Figure), number_figures, fp);
    if (readed == number_figures)
      printf("File read OK, read %d figures\n", readed);
    else  // Если вдруг не введены все, обрабатывать сколько есть
      printf("File read error, just read %d figures", readed);
    
    // Обработка введённых фигур
    for (size_t i = 0; i < readed; i++)
    {
      printf("%3d ", i+1);        // Номер
      Figure_print(&figures[i]);
      
      Figure::Figure_type type = figures[i].type;
      Figure::Figure_color color = figures[i].color;

      if (0 <= type && type < FIG_TYPES)
      { // считаем для каждого типа - количество и общую площадь
        double square = Figure_Square(&figures[i]);
        count_types[type]++;
        count_squares_type[type] += square;
        
        if (0 <= color && color < FIG_COLORS)
        {
          count_colors[color]++;    // считаем количество по цвету
          count_squares_color[color] += square;
        }
        else
          bad_figs++; // плохой цвет
      }
      else
        bad_figs++;   // плохой тип
    }
   
    // Распечатка результата
    printf("\n----------------------------------------------\n");
    printf("\nCount by type:\n"
           "----------------------------------------------\n");
    double total_square = 0;
    int counter = 0;
    for (size_t i = 0; i < FIG_TYPES; i++)
    {
      printf("%-6s : %4d  Square : %9.2f\n", 
              Fig_TranslateType((Figure::Figure_type)i),
              count_types[i],
              count_squares_type[i]);
      counter += count_types[i];
      total_square += count_squares_type[i];
    }
    printf("----------------------------------------------\n"
           "Total  : %4d  Square : %9.2f\n", counter, total_square);
    
    printf("\n\nCount by colors:\n"
           "----------------------------------------------\n");
    counter = 0;
    total_square = 0;
    for (size_t i = 0; i < FIG_COLORS; i++)
    {
      printf("%-6s : %4d  Square : %9.2f\n",
              Fig_TranslateColor((Figure::Figure_color)i),
              count_colors[i],
              count_squares_color[i]);
      counter += count_colors[i];
      total_square += count_squares_color[i];
    }
    printf("----------------------------------------------\n"
           "Total  : %4d  Square : %9.2f\n", counter, total_square);

    if (bad_figs)
      printf("\n! Figures with error, total %d\n", bad_figs);
    
    free(figures);
    fclose(fp);
  }
  else  // Не удалось даже открыть файл
    printf("Can't open file:  %s\nfile open error:  %d\n", filename, err);
  
  int x = getchar();
  return err; 
}
