#include <iostream>
#include <fstream>
#include<string>

using namespace std;

int main(int argc, const char *argv[])
{

    if (argc == 2)
    {
        
        string filename = argv[1];
        ifstream ifs(filename);
    

        if(ifs.is_open())
        {
            double media;
            
            while (!ifs.eof())
            {

                string location;
                double temp1, temp2, temp3, temp4;

                ifs >> location >> temp1 >> temp2 >> temp3 >> temp4;
                media = (temp1 + temp2 + temp3 + temp4)/4;

                if(!ifs.eof()){
                    cout <<"La media delle temperature nella citta' di " << location << " è: " << media <<"\n";
                }

            }
        }
        else
        {
            cerr << "il file non è stato aperto correttamente!\n";
        }

    }
    else{
        cerr << "non è stato specificato il parametro!\n";
    }

    return 0;

}