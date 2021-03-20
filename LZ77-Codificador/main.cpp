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

/**Codificador**/
std::vector<No*> Codificador(std::string s)
{
    std::vector<No*> answer;

    const int tamanhoDobuf = 3072;
    const int tamanhoDaVisualizacao = 1024;

    int posicao = 0;

    while (posicao < s.length())
    {
        int indiceMaximo = 0, max_comprimento = 0, indiceAtaul, indiceComprimento;
        for (int j = std::max(0, (posicao - tamanhoDobuf)); j < posicao; j++)
        {
            indiceAtaul = j, indiceComprimento = 0;

            while (s[indiceAtaul] == s[indiceComprimento + posicao] && indiceAtaul < std::min((posicao + tamanhoDaVisualizacao), (int)s.length()))
            {
                indiceAtaul++;
                indiceComprimento++;
            }

            if (indiceComprimento > max_comprimento)
            {
                indiceMaximo = posicao - j;
                max_comprimento = indiceComprimento;
            }
        }

        posicao += max_comprimento;
        answer.push_back(new No(indiceMaximo, max_comprimento, s[posicao]));
        posicao++;
    }

    return answer;
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
    //fin.open("input.txt", std::ios::in);
    if(fin.is_open())
    {
        std::string input;
        fin >> input;
        fin.close();

        std::vector<No*> encoded = Codificador(input);

        std::fstream fout;
        fout.open(argv[2], std::ios::out);
        fout << encoded.size() << "\n";
        for(auto & No : encoded)
        {
            fout << No->deslocamento << " " << No->comprimento << " " << No->proximo << " ";
        }
	fout <<endl;
        fout.close();
    }

    return 0;
}
