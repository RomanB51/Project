#include "passwordWindow.h"
#include "main.h"

#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    PasswordWindow w;
    w.show();
    int counter_row = 0;
    QString rus_small_letters[33] = {"а", "б", "в", "г", "д", "е", "ё", "ж", "з", "и", "й", "к", "л", "м", "н", \
                                    "о", "п", "р", "с", "т", "у", "ф", "х", "ц", "ч", "ш", "щ", "ъ", "ы", "ь", "э", "ю", "я"};
    QString rus_big_letters[33] = {"А", "Б", "В", "Г", "Д", "Е", "Ё", "Ж", "З", "И", "Й", "К", "Л", "М", "Н", \
                                    "О", "П", "Р", "С", "Т", "У", "Ф", "Х", "Ц", "Ч", "Ш", "Щ", "Ъ", "Ы", "Ь", "Э", "Ю", "Я"};
    QString eng_small_letters[26] = {"a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", \
                                    "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z"};
    QString big_small_letters[26] = {"A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", \
                                     "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z"};
    QString numbers[10] = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9"};
    QString signs[28] = {"!", "?", ".", ",", "@", "#", "$", "%", "^", "&", "*", "(", ")", "-", "+", "=", "\n", "{", "}"\
                        "[", "]", "/", "<", ">", ":", ";", "'", "'"};
    return a.exec();
}
