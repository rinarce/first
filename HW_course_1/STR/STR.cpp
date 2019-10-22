#include <stdio.h>
#include <locale.h>

// Челнокова Екатерина, гр 3630102/90004
// вариант 14 - Палиндромы
#define STR_MAX_LEN 120
#define FILLER '*'
#include ".\MyStringModule.h"


int IsAlNum(char c) {
  // определяет, что является допустимой буквой в данной задаче
  // 1 - если [A–Z] или [a–z] или [0–9], иначе - 0
  return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9');
}

void ReverseWords(char str[]) {
  // в строке разворачивает слова задом неперёд
  for (int pos = FindNextWord(str, 0); str[pos]; ) {
    int wordEnd = FindWordEnd(str, pos);
    ReverseInStr(str, pos, wordEnd);
    pos = FindNextWord(str, wordEnd + 1);
  }
}

void TitleCase2More(char str[]) {
  // Делает заглавными первые буквы слов длиной от 3 символов
  // а также первого слова в строке
  // сначала сделаем все строчными, потом выделим заглавные
  LowerCase(str);
  int pos = FindNextWord(str, 0);	// первое слово строки
  str[pos] = UpperChar(str[pos]); // первое слово заглавное всегда
  // следующие слова проверяем на длину > 2
  // начинаем с этой же позиции, чтоб исключить проблемы с пустой строкой
  for (pos = FindNextWord(str, pos); str[pos]; ) {
    int wordEnd = FindWordEnd(str, pos);
    int wordLen = wordEnd - pos + 1;
    if (wordLen > 2)
      str[pos] = UpperChar(str[pos]);
    pos = FindNextWord(str, wordEnd + 1);
  }
}

int IsPalindrome(char str[], int start, int end) {
  // проверяет str[start...end] на Палиндром, заглавные [A-Z] == строчные [a-z]
  while (start <= end)
    // до первого несовпадения
    if (LowerChar(str[start++]) != LowerChar(str[end--])) return 0;
  return 1;   // проверен весь интервал
}

int CountMaxWordLen(char str[]) {
  // возвращает максимальную длину слова в строке
  int maxWordLen = 0;
  for (int pos = FindNextWord(str, 0); str[pos]; ) {
    int wordEnd = FindWordEnd(str, pos);
    int wordLen = wordEnd - pos + 1;
    if (wordLen > maxWordLen)
      maxWordLen = wordLen;
    pos = FindNextWord(str, wordEnd + 1);
  }
  return maxWordLen;
}

int FindLongWords(char str[]) {
  // находит первое из слов максимальной длины, возвращает его длину
  // оставляет в строке только это слово
  // 1. определим максимальную длину слова => maxWordLen
  int maxWordLen = CountMaxWordLen(str), pos = 0;
  // 2. слов вообще нет, одни разделители - обнулим строку
  if (!maxWordLen) {
    str[0] = '\0';
    return 0;
  }
  // 3. найдем первое слово длины maxWordLen
  for (pos = FindNextWord(str, 0); str[pos];) {
    int wordEnd = FindWordEnd(str, pos);
    if (wordEnd - pos + 1 == maxWordLen) {
      // 4. перепишем это слово в начало строки
      CopySubStr(&str[pos], 0, maxWordLen - 1, str);
      // 5. завершающий '\0'
      str[maxWordLen] = '\0';
      return maxWordLen; // 
    }
    pos = FindNextWord(str, wordEnd + 1);
  }
}

int HideLongWords(char str[]) {
  // слова максимальной длины забивает символом-заполнителем FILLER
  // возвращает кол-во таких слов
  // 1. определим длину максимального слова => maxWordLen
  int maxWordLen = CountMaxWordLen(str);
  int hided = 0;

  // 2. слов вообще нет, одни разделители - ничего не делаем
  if (!maxWordLen) return 0;

  // 3. все слова длины == maxWordLen - забьём символом FILLER
  for (int pos = FindNextWord(str, 0); str[pos]; ) {
    int wordEnd = FindWordEnd(str, pos);
    if (wordEnd - pos + 1 == maxWordLen) {
      FillStr(str, pos, wordEnd, FILLER);
      hided++;
    }
    pos = FindNextWord(str, wordEnd + 1);
  }
  return hided;
}

int SubstituteLongWords(char str[]) {
  // слова максимальной длины заменяем на самое первое из них
  // возвращает кол-во заменённых
  // 1. определим максимальную длину слова => maxWordLen
  int maxWordLen = CountMaxWordLen(str);
  int replaced = 0;

  // 2. слов вообще нет, одни разделители - ничего не делаем
  if (!maxWordLen) return 0;

  // 3. найдем первое слово длины maxWordLen
  int pos = FindNextWord(str, 0);
  while (str[pos]) {
    int wordEnd = FindWordEnd(str, pos);
    if (wordEnd - pos + 1 == maxWordLen)
      break; // pos указывает на начало первого такого слова
    pos = FindNextWord(str, wordEnd + 1);
  }

  // 4. все остальные слова длины maxWordLen будем заменять первым найденым
  // запомним адрес начала первого слова
  char* firstLongWord = &str[pos];
  // продолжим обработку строки c конца первого длинного слова +1
  pos = FindNextWord(str, pos + maxWordLen);
  while (str[pos]) {
    int wordEnd = FindWordEnd(str, pos);
    int wordLen = wordEnd - pos + 1;
    if (wordLen == maxWordLen) {
      // заменить на первое найденое
      CopySubStr(firstLongWord, 0, maxWordLen - 1, &str[pos]);
      replaced++;
    }
    pos = FindNextWord(str, wordEnd + 1);
  }
  return replaced;
}

void HidePalindromes(char str[]) {
  // слова плиндромы забивает символом-заполнителем FILLER
  for (int pos = FindNextWord(str, 0); str[pos]; ) {
    int wordEnd = FindWordEnd(str, pos);
    if (IsPalindrome(str, pos, wordEnd))
      FillStr(str, pos, wordEnd, FILLER);
    pos = FindNextWord(str, wordEnd + 1);
  }
}


int main(void) {
  char stroka[STR_MAX_LEN];

  // для Windows - не отображать кракозябры  // #include <locale.h>
  setlocale(LC_ALL, "Russian");

  printf("Задание STR-14 - Забой слов-палиндромов\nВыполнила - Челнокова Екатерина - гр.\n\n");
  printf("Вводите строки. Для выхода из программы нажмите только <Enter>\n\n");

  // в пустой строке есть только символ CR
  int sLen; // это будет длина строки +1 '\0'
  while (sLen = StrLenght(fgets(stroka, STR_MAX_LEN, stdin)), sLen != 1) {

    // затираем возврат каретки, мешает обрабатывать и печатать
    stroka[sLen - 1] = '\0';
    // сохраним исходник строки - Для прочих вариантов
    char reserv[STR_MAX_LEN];
    CopyStr(stroka, reserv);

    printf("%s <- 00. Длина строки == %d\n", stroka, sLen - 1);
    HidePalindromes(stroka);
    printf("%s <- 14. Прячем палиндромы\n", stroka);

    // Дополнительные варианты

    Reverse(CopyStr(reserv, stroka));
    printf("%s <- 01. Разворот строки\n", stroka);

    ReverseWords(CopyStr(reserv, stroka));
    printf("%s <- 02. Разворот слов\n", stroka);

    UpperCase(CopyStr(reserv, stroka));
    printf("%s <- 03. Верхний регистр\n", stroka);

    LowerCase(CopyStr(reserv, stroka));
    printf("%s <- 04. Нижний регистр\n", stroka);

    SwapCase(CopyStr(reserv, stroka));
    printf("%s <- 05. Смена регистра\n", stroka);

    TitleCase(CopyStr(reserv, stroka));
    printf("%s <- 06. Заглавные первые буквы слов\n", stroka);

    TitleCase2More(CopyStr(reserv, stroka));
    printf("%s <- 07. Заголовок (v 2)\n", stroka);

    int deletedSep = RemoveSeparators(CopyStr(reserv, stroka));
    printf("%-*s<- 08. 1 Удалено разделителей - %d\n", sLen, stroka, deletedSep);

    int deletedSym = RemoveSymbols(CopyStr(reserv, stroka));
    printf("%-*s<- 08. 2 Удалено символов - %d\n", sLen, stroka, deletedSym);

    char toRemove[] = "evil";
    int deleted = RemoveAll(CopyStr(reserv, stroka), toRemove);
    printf("%-*s<- 09. Удалено подстрок '%s' - %d\n", sLen, stroka, toRemove, deleted);

    // toRemove[] = "evil";
    deleted = RemoveAllWords(CopyStr(reserv, stroka), toRemove);
    printf("%-*s<- 10. Удалено слов '%s' - %d\n", sLen, stroka, toRemove, deleted);

    char wToFind[] = "wicked";
    char wReplace[] = "good";
    int wReplaced = ReplaceAllWords(CopyStr(reserv, stroka), wToFind, wReplace);
    printf("%-*s<- 11. Замена слов '%s' -> '%s'. Замен - %d\n",
      sLen, stroka, wToFind, wReplace, wReplaced);

    int maxWordLen = FindLongWords(CopyStr(reserv, stroka));
    printf("%-*s", sLen, stroka);
    if (maxWordLen)
      printf("<- 12. Первое самое длинное слово, длина = %d\n", maxWordLen);
    else
      printf("<- 12. Первое самое длинное слово. Слова отсутствуют\n");


    int hided = HideLongWords(CopyStr(reserv, stroka));
    printf("%s <- 13. Забой длинных слов, найдено - %d\n", stroka, hided);

    int replaced = SubstituteLongWords(CopyStr(reserv, stroka));
    printf("%s <- 15. Подмена длинных слов, заменено - %d\n", stroka, replaced);

    int shLeft = 2;
    ShiftLeftInStr(CopyStr(reserv, stroka), 0, sLen - 2, shLeft);
    printf("%s <- хх. Циклический сдвиг влево <--- на %d\n", stroka, shLeft);

    int shRight = 3;
    ShiftRightInStr(CopyStr(reserv, stroka), 0, sLen - 2, shRight);
    printf("%s <- хх. Циклический сдвиг вправо --> на %d\n", stroka, shRight);

    printf("\n");
  }
  return 0;
}
