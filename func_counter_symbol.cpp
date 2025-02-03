#include "mainWindow.h"
#include <QTextStream>

std::vector<int> operator +(const std::vector<int> &a, const std::vector<int> &b){
    std::vector<int> sum;
    sum.reserve(33);
    for(int i = 0; i != a.size(); ++i){
        sum.push_back(a[i] + b[i]);
    }
    return sum;
}

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
                            ++stroka_of_ReportWindow[id_in_map][6][0];
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
    sum_rus_letters = stroka_of_ReportWindow[id_in_map][0] + stroka_of_ReportWindow[id_in_map][1];
    sum_eng_letters = stroka_of_ReportWindow[id_in_map][4] + stroka_of_ReportWindow[id_in_map][5];
    stroka_of_ReportWindow[id_in_map][6][1] = std::accumulate(begin(sum_rus_letters), end(sum_rus_letters), 0) + std::accumulate(begin(sum_eng_letters), end(sum_eng_letters), 0);
    stroka_of_ReportWindow[id_in_map][6][2] = stroka_of_ReportWindow[id_in_map][2][27];
    stroka_of_ReportWindow[id_in_map][6][3] = stroka_of_ReportWindow[id_in_map][6][0] + stroka_of_ReportWindow[id_in_map][2][0] +\
                                              stroka_of_ReportWindow[id_in_map][2][1] + stroka_of_ReportWindow[id_in_map][2][2];
    stroka_of_ReportWindow[id_in_map][6][4] = stroka_of_ReportWindow[id_in_map][2][28] + 1;
    stroka_of_ReportWindow[id_in_map][6][5] = std::accumulate(begin(stroka_of_ReportWindow[id_in_map][3]), end(stroka_of_ReportWindow[id_in_map][3]), 0);

    for(int i = 0; i != 33; ++i){
        if(i == 0 || i == 5 || i == 6 || i == 9 || i == 15 || i == 20 || i == 28 || i == 30 || i == 31 || i == 32)
            stroka_of_ReportWindow[id_in_map][6][6] += stroka_of_ReportWindow[id_in_map][0][i] + stroka_of_ReportWindow[id_in_map][1][i];
        else
            stroka_of_ReportWindow[id_in_map][6][7] += stroka_of_ReportWindow[id_in_map][0][i] + stroka_of_ReportWindow[id_in_map][1][i];
    }
    for(int i = 0; i != 26; ++i){
        if(i == 0 || i == 4 || i == 8 || i == 14 || i == 20 || i == 24)
            stroka_of_ReportWindow[id_in_map][6][6] += stroka_of_ReportWindow[id_in_map][4][i] + stroka_of_ReportWindow[id_in_map][5][i];
        else
            stroka_of_ReportWindow[id_in_map][6][7] += stroka_of_ReportWindow[id_in_map][4][i] + stroka_of_ReportWindow[id_in_map][5][i];
    }
}
