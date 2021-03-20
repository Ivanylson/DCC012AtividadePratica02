/**
    UNIVERSIDADE FEDERAL DE JUIZ DE FORA
    INSTITUTO DE CIÊNCIAS EXATAS
    DEPARTAMENTO DA CIẼNCIA DA COMPUTAÇÃO

    TRABALHO DE ESTRUTURA DE DADOS 2(||) - 2020.3 (ERE)
    PROF.DR.MARCELO CANIATO RENHE

    FEITO POR:
    IVANYLSON HONORIO GONÇALVES    MAT 201776002

    main.cpp
    *** comando pra rodar ***
    MAC/LINUX:  clear && g++ -std=c++11 *.h *.cpp -o main && ./main
    WINDOWS:    cls & g++ -std=c++11 *.h *.cpp -o main & main.exe

*/
/**Bibliotecas**/
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

/**Nó**/
struct No
{
    int deslocamento;
    int comprimento;
    char proximo;

    No(int of, int le, char ne)
    {
        deslocamento = of;
        comprimento = le;
        proximo = ne;
    }
};

std::string Decodificador(const std::vector<No*>& encoded)
{
    std::string resposta;
    for(auto & No : encoded)
    {
        if(No->comprimento > 0)
        {
            int start = resposta.length() - No->deslocamento;
            for (int k = 0; k < No->comprimento; k++)
            {
                resposta += resposta[start + k];
            }
        }
        resposta += No->proximo;
    }
    return resposta;
}


/**Principal**/
int main(int argc, char const *argv[])
{
    cout << "Leitura e gravaçao" << endl;
    if (argc != 3)
    {
        ///VERIFICACAO DOS PARAMETROS DE ENTRADA
        cout << "ERROR: Expecting: ./<nomePrograma> <arquivoDeEntrada> <saida>" << endl;
        return 0;
    }
    string nomePrograma(argv[0]);
    string arquivoInputNome1(argv[1]);
    string arquivoInputNome2(argv[1]);

    string instancia;
    if(arquivoInputNome1.find("v") <= arquivoInputNome1.size())
    {
        string instancia = arquivoInputNome1.substr(arquivoInputNome1.find("v"));
        cout << "Running " << nomePrograma << " with instance " << instancia << " ... " << endl;
    }
    string instancia2;
    if(arquivoInputNome2.find("v") <= arquivoInputNome2.size())
    {
        string instancia2 = arquivoInputNome2.substr(arquivoInputNome2.find("v"));
        cout << "Running " << nomePrograma << " with instance " << instancia2 << " ... " << endl;
    }

    std::fstream fin;
    //Abrindo arquivo de entrada
    fin.open(argv[1], ios::in);
    //std::fstream fin;
    if(fin.is_open())
    {
        int N;
        fin >> N;

        std::vector<No*> encoded;

        int deslocamento, comprimento;
        char proximo;
        for (int i = 0; i < N; i++)
        {
            fin >> deslocamento >> comprimento >> proximo;
            encoded.push_back(new No(deslocamento, comprimento, proximo));
        }

        fin.close();

        std::string decoded = Decodificador(encoded);

        std::fstream fout;
        fout.open(argv[2], std::ios::out);
        fout << decoded;
 	cout << decoded;
        fout.close();
	cout << endl;
    }

    return 0;
}
