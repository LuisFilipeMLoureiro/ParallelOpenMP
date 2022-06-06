#include <iostream>
#include<random>
#include<omp.h>
#include <vector>

using namespace std;

int calcula_valor(char a, char b){
    if(a==b){
        return 2;
    }else{
        return -1;
    }
}

string ale_substring(int n, string seq){

    default_random_engine generator(102);
    uniform_real_distribution<double> distribution(1, n);


    int k = distribution(generator); //valor aleatorio para seqB
    string SeqB_Part = seq.substr (0,k);
    return SeqB_Part;

}

int calculadora(string seqA, string seqB){
  int valor = 0;
  int contador = seqA.size();
  
  #pragma omp parallel for reduction(+ : valor)
  for (int i = 0; i < contador; i++){
    valor += calcula_valor(seqA[i], seqB[i]);
  }
  return valor;
}

int main()
{

    int n, m;    
    string SeqA, SeqB;

    cout << "Size Sequence A" << endl;
    cin >> n;
    cout << "Size Sequence B" << endl;
    cin >> m;
    cout << "Sequence A" << endl;
    cin >> SeqA;
    cout << "Sequence B" << endl;
    cin >> SeqB;


    string SeqB_Part = ale_substring(n,SeqB);
    

    cout << "Value of k:" << endl;
    int k = SeqB_Part.size();
    cout <<k<< endl;
    cout << "Substring Sequence B:" << endl;
    cout << SeqB_Part << endl;

    default_random_engine generator(101);
    uniform_real_distribution<double> distribution(1, 5);
    int p = distribution(generator); //numero de subsequencias de seqA
    cout << "Num of substrings SeqA:" << endl;
    cout <<p<< endl;

    vector<string> subSeqA;

    #pragma omp parallel for
    for(int i = 0; i < p; i++){
        
        string A = SeqA.substr (i,k);
        //cout << "Substrings of seqA:"<< endl;
        //cout << A << endl;
        #pragma omp critical
        subSeqA.push_back(A);
        
    }

    int candidato, match, id;
    #pragma omp parallel shared(match)
    for(int j=0; j<subSeqA.size();j++){
        candidato = calculadora(subSeqA[j], SeqB_Part);

        
        if(j==0){
            match = candidato;
            id = j;
        }else if(candidato>match){
            match = candidato;
            id = j;
        }       
        
}

    cout << "Resultados Finais:"<< endl;
    cout << "Match Max:"<< endl;
    cout << match << endl;
    cout << "Substrings que maximizaram o match:"<< endl;
    cout << "Seq A:"<< endl;
    cout << subSeqA[id] << endl;
    cout << "Seq B:"<< endl;
    cout << SeqB_Part << endl;

    cout << ""<< endl;
    cout << "EOF"<< endl;    

    return 0;
}
