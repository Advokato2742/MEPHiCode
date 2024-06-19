#include "secondary-func.h"
#include "seq.h"
#include "ui.h"

std::string baselist[] = {
    "0 - exit",
    "1 - get first",
    "2 - get last",
    "3 - get elem by index",
    "4 - get length",
    "5 - append elem",
    "6 - prepend elem",
    "7 - insert elem",
    "8 - print sequence",
    "9 - get sub sequence",
    "10 - concat"
};
int basesize = std::size(baselist);
ArraySequence<std::string> optionlist = ArraySequence<std::string>(baselist, basesize);
Sequence<std::string>* optionarr = &optionlist;

template <typename T>
void Menu(T* typeptr) {
    std::cout << "enter count of elems" << std::endl;
    int count = GetInt();

    int* arr = new int[count]{};
    std::cout << "enter elems" << std::endl;
    for (int i = 0; i < count; i++) {
        arr[i] = GetInt();
    }
    T dynarr = T(arr, count);
    delete [] arr;
    T* newseq{};

    int choise;
    bool flag = 1;
    while(flag) {
        PrintOptions(optionarr, basesize);
        choise = GetFromInterval(0, 10);
        switch (choise) {
        case 0:
            flag = 0;
            break;
        case 1:
            std::cout << "first elem: " << dynarr.GetFirst() << std::endl;
            break;
        case 2:
            std::cout << "last elem: " << dynarr.GetLast() << std::endl;
            break;
        case 3:
            std::cout << "enter index: ";
            int index3;
            index3 = GetInt();
            std::cout << "elem: " << dynarr.GetElement(index3) << std::endl;
            break;
        case 4:
            std::cout << "size: " << dynarr.GetLength() << std::endl;
            break;
        case 5:
            std::cout << "enter elem: ";
            int elem5;
            elem5 = GetInt();
            dynarr.Append(elem5);
            std::cout << "elem added to the end" << std::endl;
            break;
        case 6:
            std::cout << "enter elem: ";
            int elem6;
            elem6 = GetInt();
            dynarr.Prepend(elem6);
            std::cout << "elem added to the beginning" << std::endl;
            break;
        case 7:
            std::cout << "enter elem: ";
            int elem7;
            elem7 = GetInt();
            std::cout << "enter index: ";
            int index7;
            index7 = GetInt();
            dynarr.InsertAt(elem7, index7);
            std::cout << "elem appended to this index" << std::endl;
            break;
        case 8:
            Print(&dynarr);
            break;
        case 9:
            int start, end;
            std::cout << "enter start index: ";
            start = GetInt();
            std::cout << "enter end index: ";
            end = GetInt();
            newseq = dynarr.GetSubsequence(start, end);
            Print(newseq);
            break;
        case 10:
            std::cout << "enter length of the sequence to be added ";
            int len = GetInt();
            int arrhelp[len];
            for (int i = 0; i < len; i++) {
                std::cout << "enter " << i+1 << " element ";
                arrhelp[i] = GetInt();
            }
            T concatseq = T(arrhelp, len);
            dynarr.Concat(&concatseq);
            break;
        }
    }
    delete newseq;
    return;
}

void UI() {
    int choise;
    printf("1 - array or 2 - list? ");
    choise = GetFromInterval(1, 2);

    if (choise == 1) {
        ArraySequence<int>* typeptr;
        Menu(typeptr);
    } else if (choise == 2) {
        ListSequence<int>* typeptr;
        Menu(typeptr);
    }
    return;
}
