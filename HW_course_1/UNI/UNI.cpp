// UNI.cpp

#include <stdio.h>
#include <locale.h>
#include <stdlib.h>           // для выделения памяти
#include <io.h>               // для filelength()
#include <math.h>             // для tan()


// так не работает
//#define FIG_TYPES  sizeof(Figure::Figure_type)    // всего типов
//#define FIG_COLORS sizeof(Figure::Figure_color)   // разных цветов

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

struct Figure_ColorsTranslateNames
{
  const char* red  = "red";
  const char* gren = "green";
  const char* blue = "blue";
  const char* unkn = "ERROR";

} translate_table_colors;

struct Figure_TypesTranslateNames
{
  const char* circ = "Circ";
  const char* rect = "Rect";
  const char* poly = "Poly";
  const char* unkn = "ERROR";

} translate_table_types;

const char* Fig_TranslateColor(Figure::Figure_color fig_col)
{
  switch (fig_col)
  {
  case(Figure::Figure_color::RED):
    return translate_table_colors.red;

  case(Figure::Figure_color::GREEN):
    return translate_table_colors.gren;

  case(Figure::Figure_color::BLUE):
    return translate_table_colors.blue;

  default:
    return translate_table_colors.unkn;
  }
}

const char* Fig_TranslateType(Figure::Figure_type fig_type)
{
  switch (fig_type)
  {
  case(Figure::Figure_type::CIRCLE):
    return translate_table_types.circ;

  case(Figure::Figure_type::RECTANGLE):
    return translate_table_types.rect;

  case(Figure::Figure_type::REGULAR_POLYGON):
    return translate_table_types.poly;

  default:
    return translate_table_types.unkn;
  }
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
    return (0.25l * fig->attr.poligon.number_sides 
        * fig->attr.poligon.side_size * fig->attr.poligon.side_size 
        / tan(M_PI / fig->attr.poligon.number_sides));

  default:
    //"Unknown figure"
    return 0;
  }
}
void Figure_print(Figure* fig)
{
  printf("%-6s %-6s ",
    Fig_TranslateType(fig->type),
    Fig_TranslateColor(fig->color));

  switch (fig->type)
  {
    case(Figure::Figure_type::CIRCLE) :
      printf("R = %f               Sq = %f\n",
        fig->attr.circle.radius,
        Figure_Square(fig));
      break;

    case(Figure::Figure_type::RECTANGLE):
      printf("W = %f H = %f  Sq = %f\n", 
        fig->attr.rectangle.width, 
        fig->attr.rectangle.height,
        Figure_Square(fig));
      break;

    case(Figure::Figure_type::REGULAR_POLYGON):
      printf("N = %d     Size = %f  Sq = %f\n", 
        fig->attr.poligon.number_sides, 
        fig->attr.poligon.side_size,
        Figure_Square(fig));
      break;

    default:
      printf("Unknown figure type <%d>\n", fig->type);
    break;
  }
}

unsigned long int filesize(FILE* file)
{ 
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
      return -1;
    }

    // Попытка чтения из файла сразу всех фигур
    size_t readed = fread(figures, sizeof(Figure), number_figures, fp);
    if (readed == number_figures)
      printf("File read OK, read %d figures\n", readed);
    else  // Если вдруг не введены все, обрабатывать сколько есть
      printf("File read error, just read %d figures", readed);
    
    // Обработка считанных фигур
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
    printf("\nCount by type:\n");
    for (size_t i = 0; i < FIG_TYPES; i++)
    {
      printf("%-6s Total: %4d  Square: %9.2f\n", 
        Fig_TranslateType((Figure::Figure_type)i),
        count_types[i],
        count_squares_type[i]);
    }
    
    printf("\nCount by colors:\n");
    for (size_t i = 0; i < FIG_COLORS; i++)
    {
      printf("%-6s Total: %4d  Square: %9.2f\n",
        Fig_TranslateColor((Figure::Figure_color)i),
        count_colors[i],
        count_squares_color[i]);
    }
    
    if (bad_figs)
      printf("\n! Figures with error, total %d\n", bad_figs);

    fclose(fp);
    int x = getchar();
  }
  else 
  { // Не удалось даже открыть файл
    printf("File open error : %d", err);
    return err;
  }
  return 0;
}
