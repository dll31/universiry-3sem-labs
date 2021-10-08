
#include <iostream>
#include <string>
#include <fstream>

void repairCin()
{
    std::cin.clear();
    std::cin.ignore(10000, '\n');
}


class Pipe
{
private:
    int id = 0;
    
public:
    int diameter;
    double length;
    bool inRepair = false;
    //FIXME: fix for this labwork
    bool pipeIsEntered = false;


    void display();
    int save(std::ofstream& fout);

    void inputConsole();
    int inputFile(std::ifstream& fin);
        
    void edit();

    void checkCorrectInRepairValue();
    void changeInRepair();
    bool isValueInRange(int value, int from, int to);
    bool isValueInRange(double value, double from, double to);
};


void Pipe::display()
{
    std::cout << "Pipe parameters" << "\n"
        << "id: " << id << "\n"
        << "diameter: " << diameter << "\n"
        << "length: " << length << "\n"
        << "in Repair: " << (inRepair ? "True" : "False") << "\n";
}


int Pipe::save(std::ofstream& fout)
{
    if (fout.is_open())
    {
        fout << id << "\n"
            << diameter << "\n"
            << length << "\n"
            << (inRepair ? 1 : 0) << "\n";
        return 0;
    }

    return -2;
}


void Pipe::inputConsole()
{
    while (true)
    {
        std::cout << "Enter pipe diameter:\n";
        std::cin >> diameter;

        if (std::cin.fail() || !isValueInRange(diameter, 500, 1420))
        {
            repairCin();
            continue;
        }

        break;
    }

    while (true)
    {
        std::cout << "Enter pipe length:\n";
        std::cin >> length;

        if (std::cin.fail())
        {
            repairCin();
            continue;
        }
     
        break;
    }
   
    checkCorrectInRepairValue();

    pipeIsEntered = true;
}


int Pipe::inputFile(std::ifstream& fin)
{
    if (fin.is_open())
    {
        /*If we have broken data in file, we return error*/
        fin >> id;
        if (fin.fail())
            return -2;
        
        fin >> diameter;
        if (fin.fail())
            return -2;
        
        fin >> length; 
        if (fin.fail())
            return -2;
        
        fin >> inRepair;
        if (fin.fail())
            return -2;
        
        return 0;
    }

    return -1;
}


void Pipe::edit()
{
    if (!pipeIsEntered)
    {
        std::cout << "Enter pipe, before edit\n";
        return;
    }

    std::cout << "Now pipe is " << (inRepair ? "in repair" : "not in repair");
    checkCorrectInRepairValue();
}


void Pipe::checkCorrectInRepairValue()
{
    while (true)
    {
        char ch;

        std::cout << "Enter pipe in repair parameter (y or n):\n";
        std::cin >> ch;
        if (std::cin.fail())
        {
            repairCin();
            continue;
        }

        ch = char(std::tolower(ch));
        if (ch == 'y')
        {
            inRepair = true;
            break;
        }

        else if (ch == 'n')
        {
            inRepair = false;
            break;
        }
    }
}


void Pipe::changeInRepair()
{
    inRepair = (!inRepair);
}


bool Pipe::isValueInRange(int value, int from, int to)
{
    if ((value <= to) && (value >= from))
        return true;

    return false; 
}

bool Pipe::isValueInRange(double value, double from, double to)
{
    if ((value <= to) && (value >= from))
        return true;

    return false;
}


//FIXME: function for this labwork
void loadPipeFromFile(std::string file, Pipe& p)
{
    int rc = 0;
    std::ifstream fin(file);
    if (fin.is_open())
    {
        rc = p.inputFile(fin);
        fin.close();
    }
    else
    {
        std::cout << "Try another file";
        return;
    }

    if (rc == 0)
    {
        p.pipeIsEntered = true;
        std::cout << "Pipe load\n";
        return;
    }

    std::cout << "Something wrong";
}


//FIXME: function for this labwork
void savePipeInFile(std::string file, Pipe& p)
{
    if (!p.pipeIsEntered)
    {
        std::cout << "Enter pipe, before save";
        return;
    }

    int rc = 0;
    std::ofstream fout(file);
   
    if (fout.is_open())
    {
        rc = p.save(fout);
        fout.close();
    }

    if (rc == 0)
    {
        std::cout << "pipe saved\n";
        return;
    }

    std::cout << "Something wrong";
}


void showMenu()
{
    std::cout << "1. Add pipe" << "\n"
        << "2. Add compressor station" << "\n"
        << "3. See all objects" << "\n"
        << "4. Edit pipe" << "\n"
        << "5. Edit compressor station" << "\n"
        << "6. Save" << "\n"
        << "7. Load" << "\n"
        << "0. Exit" << "\n";
}

//FIXME: function for this labwork
void clearMemory(Pipe * p)
{
    delete(p);
}


int main()
{
    Pipe* p = new Pipe;


    while (true)
    {
        showMenu();
        int action = -1;
        while (true)
        {
            std::cin >> action;

            if (std::cin.fail())
            {
                repairCin();
                continue;
            }
         
            break;
        }

        switch (action)
        {
        case 1:
            p->inputConsole();
            break;

        case 2:
            break;

        case 3:
            break;

        case 4:
            p->edit();
            break;

        case 5:
            break;

        case 6:
            savePipeInFile("data.txt", *p);
            break;

        case 7:
            loadPipeFromFile("data2.txt", *p);
            break;

        case 0:
            clearMemory(p);
            return 0;

        default:
            std::cout << "Wrong action";
        }
    }
    /*p->inputFile();*/
    p->display();

    clearMemory(p);

    return 0;
}