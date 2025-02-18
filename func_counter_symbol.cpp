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
            for(size_t i = 0; i != count_rus_small_letters.size(); ++i){
                if(*ptr_symbol == rus_small_letters[i]){
                    count_rus_small_letters[i]++;
                    counter_of_point = 0;
                    interrupt = 0;
                    break;
                }
            }
        }

        if(interrupt){
            for(size_t i = 0; i != count_rus_big_letters.size(); ++i){
                if(*ptr_symbol == rus_big_letters[i]){
                    count_rus_big_letters[i]++;
                    counter_of_point = 0;
                    interrupt = 0;
                    break;
                }
            }
        }

        if(interrupt){
            for(size_t i = 0; i != count_signs.size(); ++i){
                if(*ptr_symbol == signs[i]){
                    ++count_signs[i];
                    interrupt = 0;
                    if(i == 2){
                        ++counter_of_point;
                        if(counter_of_point == 3){
                            ++stroka_of_ReportWindow[id_in_map][4][0];
                            count_signs[2] -= 3;
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
            for(size_t i = 0; i != count_numbers.size(); ++i){
                if(*ptr_symbol == numbers[i]){
                    ++count_numbers[i];
                    counter_of_point = 0;
                    interrupt = 0;
                    break;
                }
            }
        }

        if(interrupt){
            for(size_t i = 0; i != count_eng_small_letters.size(); ++i){
                if(*ptr_symbol == eng_small_letters[i]){
                    ++count_eng_small_letters[i];
                    counter_of_point = 0;
                    interrupt = 0;
                    break;
                }
            }
        }

        if(interrupt){
            for(size_t i = 0; i != count_eng_big_letters.size(); ++i){
                if(*ptr_symbol == eng_big_letters[i]){
                    ++count_eng_big_letters[i];
                    counter_of_point = 0;
                    interrupt = 0;
                    break;
                }
            }
        }
    }
    sum_rus_letters = count_rus_small_letters + count_rus_big_letters;
    stroka_of_ReportWindow[id_in_map][0] = sum_rus_letters;

    sum_eng_letters = count_eng_small_letters + count_eng_big_letters;
    stroka_of_ReportWindow[id_in_map][1] = sum_eng_letters;

    stroka_of_ReportWindow[id_in_map][2] = count_numbers;
    stroka_of_ReportWindow[id_in_map][3] = count_signs;

    stroka_of_ReportWindow[id_in_map][4][0] = counter_of_point;
    stroka_of_ReportWindow[id_in_map][4][1] = std::accumulate(begin(sum_rus_letters), end(sum_rus_letters), 0) +\
                                              std::accumulate(begin(sum_eng_letters), end(sum_eng_letters), 0);
    stroka_of_ReportWindow[id_in_map][4][2] = count_signs[27];
    stroka_of_ReportWindow[id_in_map][4][3] = counter_of_point + count_signs[0] + count_signs[1] + count_signs[2];
    stroka_of_ReportWindow[id_in_map][4][4] = count_signs[28] + 1;
    stroka_of_ReportWindow[id_in_map][4][5] = std::accumulate(begin(count_numbers), end(count_numbers), 0);

    for(int i = 0; i != 33; ++i){
        if(i == 0 || i == 5 || i == 6 || i == 9 || i == 15 || i == 20 || i == 28 || i == 30 || i == 31 || i == 32)
            stroka_of_ReportWindow[id_in_map][4][6] += count_rus_small_letters[i] + count_rus_big_letters[i];
        else
            stroka_of_ReportWindow[id_in_map][4][7] += count_rus_small_letters[i] + count_rus_big_letters[i];
    }
    for(int i = 0; i != 26; ++i){
        if(i == 0 || i == 4 || i == 8 || i == 14 || i == 20 || i == 24)
            stroka_of_ReportWindow[id_in_map][4][6] += count_eng_small_letters[i] + count_eng_big_letters[i];
        else
            stroka_of_ReportWindow[id_in_map][4][7] += count_eng_small_letters[i] + count_eng_big_letters[i];
    }

    std::fill(begin(count_rus_small_letters), end(count_rus_small_letters), 0);
    std::fill(begin(count_rus_big_letters), end(count_rus_big_letters), 0);
    std::fill(begin(count_eng_small_letters), end(count_eng_small_letters), 0);
    std::fill(begin(count_eng_big_letters), end(count_eng_big_letters), 0);
    std::fill(begin(count_numbers), end(count_numbers), 0);
    std::fill(begin(count_signs), end(count_signs), 0);
}
