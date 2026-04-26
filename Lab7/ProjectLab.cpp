#include <iostream>
#include <string>
#include <fstream>

using namespace std;

const int sizeArr = 20;
const int resLen = 4;
const string searchName = "Keanu Reeves";

const string pathRead = "myFile.txt";
const string pathWrite = "myFileWrite.txt";
const string pathBinWrite = "structFileWrite.txt";
const string pathBinRead = "structFile.txt";

/*

//Памятка

//Heap. Нужно удалять ручками
Movie* movies = new movies[size]

//Stack. При завершении функции учиститься
Movie movies[] = {}

*/


enum StudioFilm {
    Marvel,
    DC,
    Other
};


enum TypeFilm {
    Action,
    SciFi,
    Cartoon,
    Comedy,
    Melodrama,
    Drama,
    Thriller
};

struct ArtDirection
{
    string nFilm;
    string nActor;
    string nDirector;
};

struct Movie
{
    ArtDirection artDir;
    string dataFile;
    double price;
    double rating;
    int duration;
    TypeFilm typeFilm;
    StudioFilm studioFilm;
    

public:
    void changeMovie(ArtDirection artDir, double price, double rating, int duration, TypeFilm typeFilm, StudioFilm studioFilm) {
        this->artDir = artDir;
        this->price = price;
        this->rating = rating;
        this->duration = duration;
        this->typeFilm = typeFilm;
        this->studioFilm = studioFilm;
    }
};


//Даннные о конкретном фильме
void currentMovie(Movie* arr, int selected) {
    if (selected >= 0 && selected < sizeArr) {
        cout << arr[selected].artDir.nFilm << ": " << arr[selected].artDir.nDirector << ": " << arr[selected].artDir.nActor << endl;
    }
    else
    {
        cout << "Ошибка! Фильм с введенным индексом: " << selected << ". Не найден!" << endl;
    }
}

//Перестановка двух элементов
void swap(Movie& valOne, Movie& valTwo) {
    
    Movie temp;

    temp = valOne;
    valOne = valTwo;
    valTwo = temp;
}

//Сортировка фильмов методом пузырька
void sdFmByNDirector(Movie* movies, int len) {
    for (int i = 0; i < len - 1; i++)
    {
        for (int j = 0; j < len - i - 1; j++)
        {
            if (movies[j].artDir.nDirector > movies[j + 1].artDir.nDirector) {
                swap(movies[j], movies[j + 1]);
            }
        }
    }
}

//Сортировка фильмов мелодрам по бюджету
void sdFmByBudgetAndMelodrama(Movie* arr, int len) {
    for (int i = 0; i < len - 1; i++)
    {
        for (int j = 0; j < len - i - 1; j++)
        {
            if (arr[j].typeFilm == TypeFilm::Melodrama && arr[j].price > arr[j + 1].price) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

void getFilmsByMarvelFantastic(Movie* arr, int len, Movie* res, int lenRes) {
    
    int j = 0;

    for (int i = 0; i < len; i++)
    {
        if (arr[i].studioFilm == StudioFilm::Marvel && arr[i].typeFilm == TypeFilm::SciFi) {
            if (j < lenRes) {
                res[j] = arr[i];
                j++;
            }
        }
    }
}
//Метод для вывода данных
void print(Movie* arr, int len = sizeArr) {
    for (int i = 0; i < len; i++)
    {
        currentMovie(arr, i);
    }
}

//KR - Keanu Reeves
void getFilmsWithKR(Movie* movies, int len, Movie* res, int lenRes) {
    int j = 0;

    for (int i = 0; i < len; i++)
    {
        if (movies[i].artDir.nActor == searchName) {
            if (j < lenRes) {
                res[j] = movies[i];
                j++;
            }
            
        }
    }
};

void printFilter(void (*func)(Movie*, int, Movie*, int), Movie* src, int srcLen, int resLen, const string& title)
{
    Movie* res = new Movie[resLen];

    func(src, srcLen, res, resLen);

    cout << "\n" << title << endl;
    print(res, resLen);

    delete[] res;
}

void printSort(void (*func)(Movie*, int), Movie* arr, int len, const string& title)
{
    func(arr, len);

    cout << "\n" << title << endl;
    print(arr, len);
}

void WriteDataFile(Movie* movie, int len) {
    
    //Запись в текстовый файл
    ofstream f;

    f.open(pathWrite);

    for (int i = 0; i < len; i++)
    {
        f << movie[i].dataFile << endl;
    }

    f.close();

    cout << "--Data complete write--" << endl;
}

void ReadDataFile(Movie* movie) {
    
    //Чтение из файла
    ifstream fin;

    int i = 0;

    fin.open(pathRead);

    if (fin.is_open()) {
        while (!fin.eof())
        {
            fin >> movie[i].dataFile;
            cout << movie[i].dataFile << endl;
            i++;
        }
    }
    else {
        cout << "File not found!" << endl;
    }

    fin.close();

    cout << "--File succes read--" << endl;
}

void binWriteFile(Movie* arr, int len) {
    ofstream out(pathBinWrite, ios::binary | ios::out);

    for (int i = 0; i < len; i++)
    {
        out.write((char*)&arr[i], sizeof(&arr[i]));
    }

    out.close();

    cout << "---Succes bin write file---" << endl;
}

void binReadFile(Movie* arr, int len) {
    fstream in(pathBinRead, ios::binary | ios::out);

    if (in.is_open()) {
        for (int i = 0; i < len; i++)
        {
            in.read((char*)&arr[i], sizeof(arr[i]));
        }
    }
    else
    {
        cout << "File not found!" << endl;
    }
        
    in.close();

    cout << "---Succes read file---" << endl;
    cout << arr[0].artDir.nFilm << endl;
}

Movie* init() {
    Movie* movies = new Movie[sizeArr];
    
    movies[0] = { {"The Matrix", "Keanu Reeves", "Lana Wachowski"}, " ", 63000000, 87, 136, SciFi, Other};
    movies[1] = { {"Guardians of the Galaxy", "Chris Pratt", "James Gunn"}, " ", 170000000, 82, 121, SciFi, Marvel };
    movies[2] = { {"Speed", "Keanu Reeves", "Jan de Bont"}, " ", 30000000, 72, 116, Action, Other };
    movies[3] = { {"The Devil's Advocate", "Keanu Reeves", "Taylor Hackford"}, " ", 57000000, 78, 144, Thriller, Other };
    movies[4] = { {"Inception", "Leonardo DiCaprio", "Christopher Nolan"}, " ", 160000000, 88, 148, SciFi, Other };
    movies[5] = { {"Interstellar", "Matthew McConaughey", "Christopher Nolan"}, " ", 165000000, 86, 169, SciFi, Other };
    movies[6] = { {"The Dark Knight", "Christian Bale", "Christopher Nolan"}, " ", 185000000, 90, 152, Action, DC };
    movies[7] = { {"Titanic", "Leonardo DiCaprio", "James Cameron"}, " ", 200000000, 91, 195, Drama, Other };
    movies[8] = { {"Avatar", "Sam Worthington", "James Cameron"}, " ", 237000000, 78, 162, SciFi, Other };
    movies[9] = { {"The Avengers", "Robert Downey Jr.", "Joss Whedon"}, " ", 220000000, 80, 143, Action, Marvel };
    movies[10] = { {"Avengers: Endgame", "Robert Downey Jr.", "Anthony Russo"}, " ", 356000000, 84, 181, Action, Marvel };
    movies[11] = { {"Iron Man", "Robert Downey Jr.", "Jon Favreau"}, " ", 140000000, 79, 126, Action, Marvel };
    movies[12] = { {"John Wick", "Keanu Reeves", "Chad Stahelski"}, " ", 20000000, 74, 101, Action, Other };
    movies[13] = { {"Spider-Man: Homecoming", "Tom Holland", "Jon Watts"}, " ", 175000000, 76, 133, Action, Marvel };
    movies[14] = { {"Deadpool", "Ryan Reynolds", "Tim Miller"}, " ", 58000000, 80, 108, Comedy, Marvel };
    movies[15] = { {"The Hangover", "Bradley Cooper", "Todd Phillips"}, " ", 35000000, 75, 100, Comedy, Other };
    movies[16] = { {"Frozen", "Idina Menzel", "Chris Buck"}, " ", 150000000, 76, 102, Cartoon, Other };
    movies[17] = { {"Shrek", "Mike Myers", "Andrew Adamson"}, " ", 60000000, 80, 90, Cartoon, Other };
    movies[18] = { {"Joker", "Joaquin Phoenix", "Todd Phillips"}, " ", 55000000, 85, 122, Thriller, DC };
    movies[19] = { {"Doctor Strange", "Benedict Cumberbatch", "Scott Derrickson"}, " ", 165000000, 78, 115, SciFi, Marvel };

    return movies;
}


int main()
{
    Movie* movies = init();

    cout << "---All movies---" << endl;
    print(movies, sizeArr);

    printFilter(getFilmsWithKR, movies, sizeArr, 4, "---Keanu Reeves---");
    printFilter(getFilmsByMarvelFantastic, movies, sizeArr, 2, "--- Marvel sci-fi ---");

    printSort(sdFmByNDirector, movies, sizeArr, "---by direction---");

    printSort(sdFmByBudgetAndMelodrama, movies, sizeArr, "---melodrama and budget---");

    cout << "\n---Select movie---" << endl;

    currentMovie(movies, 2);

    movies[0].changeMovie( { "New Film", "New Actor", "New Director" }, 2000000, 8, 120, TypeFilm::Action, StudioFilm::Other);

    cout << "\n---Read data and Write---" << endl;

    ReadDataFile(movies);

    WriteDataFile(movies, sizeArr);

    binWriteFile(movies, sizeArr);

    binReadFile(movies, sizeArr);

    delete[] movies;

    return 1;
}
