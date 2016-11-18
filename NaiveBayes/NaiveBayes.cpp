#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <string>
#include <cstring>
#include <cmath>

using namespace std;

struct car{
    char buying[6];
    char maint[6];
    char doors[6];
    char persons[6];
    char lug_boot[6];
    char safety[6];
};

void entrenar(string, double [], double [][6][4]);

int main(){

    map<int, string> setValores;
    setValores[0] = "unacc";
    setValores[1] = "acc";
    setValores[2] = "good";
    setValores[3] = "vgood";

    map<string, int> setBuyingMaint;
    setBuyingMaint["vhigh"] = 0;
    setBuyingMaint["high"] = 1;
    setBuyingMaint["med"] = 2;
    setBuyingMaint["low"] = 3;

    map<string, int> setDoors;
    setDoors["2"] = 0;
    setDoors["3"] = 1;
    setDoors["4"] = 2;
    setDoors["5more"] = 3;

    map<string, int> setPersons;
    setPersons["2"] = 0;
    setPersons["4"] = 1;
    setPersons["more"] = 2;

    map<string, int> setLugBoot;
    setLugBoot["small"] = 0;
    setLugBoot["med"] = 1;
    setLugBoot["big"] = 2;

    map<string, int> setSafety;
    setSafety["low"] = 0;
    setSafety["med"] = 1;
    setSafety["high"] = 2;

    double pValores[4];
    double pAtbsDadoValor[4][6][4];

    // Se realiza el entrenamiento con los datos del archivo car.data
    entrenar("car.data", pValores, pAtbsDadoValor);

    // Visualizacion de las probabilidades obtenidas en el entrenamiento
    for(int i = 0; i < 4; i++){
        cout << "P(" << setValores[i] << ")  \t= " << pValores[i] << endl;
    }
    cout << endl << "P(ai|vj):" << endl << endl;
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 6; j++){
            for(int k = 0; k < 4; k++){
                cout << pAtbsDadoValor[i][j][k] << "    \t";
            }
            cout << endl;
        }
        cout << endl;
    }
    cout << endl << endl;

    // Evaluacion con datos de prueba del archivo car-prueba.data
    ifstream datosPrueba("car-prueba.data");

    char datosAtributo[40];
    char palabra[6];
    int tamDtsAts;
    string atributo[6];
    double pValorDadosAtbs[4];

    for(int j = 0; !datosPrueba.eof(); j++){
        datosPrueba.getline(datosAtributo, 40, '\n');
        tamDtsAts = strlen(datosAtributo);

        int cont = 0;
        int contAtb = 0;
        for(int i = 0; i <= tamDtsAts; i++){
            if(datosAtributo[i] != ',' && datosAtributo[i] != '\0'){
                palabra[i - cont] = datosAtributo[i];
            }
            else{
                palabra[i - cont] = '\0';
                atributo[contAtb] = palabra;
                contAtb++;
                cont = i + 1;
            }
        }

        for(int i = 0; i < 4; i++){
            pValorDadosAtbs[i] = pValores[i] ;
        }
        for(int i = 0; i < 4; i++){
            for(int k = 0; k < 6 ; k++){
                int ind;
                switch(k){
                    case 0:
                    case 1:{
                        ind = setBuyingMaint[atributo[k]];
                    } break;
                    case 2:{
                        ind = setDoors[atributo[k]];
                    } break;
                    case 3:{
                        ind = setPersons[atributo[k]];
                    } break;
                    case 4:{
                        ind = setLugBoot[atributo[k]];
                    } break;
                    case 5:{
                        ind = setSafety[atributo[k]];
                    }
                }
                pValorDadosAtbs[i] *= pAtbsDadoValor[i][k][ind];
            }
        }

        if(tamDtsAts > 0){
            int maxInd = 0;
            for(int i = 0; i < 4; i++){
                if(pValorDadosAtbs[maxInd] < pValorDadosAtbs[i]) maxInd = i;
            }
            cout << setValores[maxInd] << endl;
        }
    }

    return 0;
}

void entrenar(string nomArchivo, double pValores[], double pAtbsDadoValor[][6][4]){

    map<string,int> setValores;
    setValores["unacc"] = 0;
    setValores["acc"] = 1;
    setValores["good"] = 2;
    setValores["vgood"] = 3;

    map<string, int> setBuyingMaint;
    setBuyingMaint["vhigh"] = 0;
    setBuyingMaint["high"] = 1;
    setBuyingMaint["med"] = 2;
    setBuyingMaint["low"] = 3;

    map<string, int> setDoors;
    setDoors["2"] = 0;
    setDoors["3"] = 1;
    setDoors["4"] = 2;
    setDoors["5more"] = 3;

    map<string, int> setPersons;
    setPersons["2"] = 0;
    setPersons["4"] = 1;
    setPersons["more"] = 2;

    map<string, int> setLugBoot;
    setLugBoot["small"] = 0;
    setLugBoot["med"] = 1;
    setLugBoot["big"] = 2;

    map<string, int> setSafety;
    setSafety["low"] = 0;
    setSafety["med"] = 1;
    setSafety["high"] = 2;

    char datosAtributo[40];
    char palabra[6];
    int tamDtsAts;
    car atributo;

    int N;
    int nValores[] = {0, 0, 0, 0};
    int nAtbsDadoValor[4][6][4];

    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 6; j++){
            for(int k = 0; k < 4; k++){
                nAtbsDadoValor[i][j][k] = 0;
            }
        }
    }

    vector<car> atributos;
    vector<string> valores;

    ////// Lectura de los datos de entrenamiento //////
    ifstream datosEntrenamiento(nomArchivo.data());
    for(int j = 0; !datosEntrenamiento.eof(); j++){
        datosEntrenamiento.getline(datosAtributo, 40, '\n');
        tamDtsAts = strlen(datosAtributo);

        int cont = 0;
        int contAtb = 0;
        for(int i = 0; i < tamDtsAts; i++){
            if(datosAtributo[i] != ','){
                palabra[i - cont] = datosAtributo[i];
            }
            else{
                palabra[i - cont] = '\0';

                switch(contAtb){
                    case 0:{
                        strcpy(atributo.buying, palabra);
                    } break;
                    case 1:{
                        strcpy(atributo.maint, palabra);
                    } break;
                    case 2:{
                        strcpy(atributo.doors, palabra);
                    } break;
                    case 3:{
                        strcpy(atributo.persons, palabra);
                    } break;
                    case 4:{
                        strcpy(atributo.lug_boot, palabra);
                    } break;
                    case 5:{
                        strcpy(atributo.safety, palabra);
                    } break;
                }
                contAtb++;
                cont = i + 1;
            }
        }

        if(tamDtsAts > 0){
            atributos.push_back(atributo);
            valores.push_back(palabra);
        }
    }

    ////// Calculo de probabilidades //////
    N = valores.size();

    for(int i = 0; i < N; i++){
        nValores[setValores[valores[i]]]++;
        nAtbsDadoValor[setValores[valores[i]]][0][setBuyingMaint[atributos[i].buying]]++;
        nAtbsDadoValor[setValores[valores[i]]][1][setBuyingMaint[atributos[i].maint]]++;
        nAtbsDadoValor[setValores[valores[i]]][2][setDoors[atributos[i].doors]]++;
        nAtbsDadoValor[setValores[valores[i]]][3][setPersons[atributos[i].persons]]++;
        nAtbsDadoValor[setValores[valores[i]]][4][setLugBoot[atributos[i].lug_boot]]++;
        nAtbsDadoValor[setValores[valores[i]]][5][setSafety[atributos[i].safety]]++;
    }

    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 6; j++){
            for(int k = 0; k < 4; k++){
                pAtbsDadoValor[i][j][k] = (nAtbsDadoValor[i][j][k] + (1/((j<3)?4.0:3.0)))/(nValores[i] + 1.0);
            }
        }
    }

    for(int i = 0; i < 4; i++){
        pValores[i] = (double)nValores[i]/N;
    }
}
