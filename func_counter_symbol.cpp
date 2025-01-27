#include "mainWindow.h"
#include <QTextStream>


void MainWindow::func_counter_symbol(QFile &object, const QString &id_in_map)
{
    QTextStream in(&object);
    QString symbol;
    QString* ptr_symbol = &symbol;

    int counter_of_point = 0; //служебная переменная для подсчета троеточий
    while(in.readLineInto(ptr_symbol, 1)){
        bool interrupt = 1;

        if(interrupt){
            for(size_t i = 0; i != stroka_of_ReportWindow[id_in_map][0].size(); ++i){
                if(*ptr_symbol == rus_small_letters[i]){
                    stroka_of_ReportWindow[id_in_map][0][i]++;
                    counter_of_point = 0;
                    interrupt = 0;
                    break;
                }
            }
        }

        if(interrupt){
            for(size_t i = 0; i != stroka_of_ReportWindow[id_in_map][1].size(); ++i){
                if(*ptr_symbol == rus_big_letters[i]){
                    stroka_of_ReportWindow[id_in_map][1][i]++;
                    counter_of_point = 0;
                    interrupt = 0;
                    break;
                }
            }
        }

        if(interrupt){
            for(size_t i = 0; i != stroka_of_ReportWindow[id_in_map][2].size(); ++i){
                if(*ptr_symbol == signs[i]){
                    stroka_of_ReportWindow[id_in_map][2][i]++;
                    interrupt = 0;
                    if(i == 2){
                        counter_of_point++;
                        if(counter_of_point == 3){
                            counter_of_troitochie++;
                            stroka_of_ReportWindow[id_in_map][2][2] -= 3;
                            counter_of_point = 0;
                        }
                    }
                    else
                        counter_of_point = 0;
                    break;
                }
            }
        }

        if(interrupt){
            for(size_t i = 0; i != stroka_of_ReportWindow[id_in_map][3].size(); ++i){
                if(*ptr_symbol == numbers[i]){
                    stroka_of_ReportWindow[id_in_map][3][i]++;
                    counter_of_point = 0;
                    interrupt = 0;
                    break;
                }
            }
        }

        if(interrupt){
            for(size_t i = 0; i != stroka_of_ReportWindow[id_in_map][4].size(); ++i){
                if(*ptr_symbol == eng_small_letters[i]){
                    stroka_of_ReportWindow[id_in_map][4][i]++;
                    counter_of_point = 0;
                    interrupt = 0;
                    break;
                }
            }
        }

        if(interrupt){
            for(size_t i = 0; i != stroka_of_ReportWindow[id_in_map][5].size(); ++i){
                if(*ptr_symbol == eng_big_letters[i]){
                    stroka_of_ReportWindow[id_in_map][5][i]++;
                    counter_of_point = 0;
                    interrupt = 0;
                    break;
                }
            }
        }
    }
}
