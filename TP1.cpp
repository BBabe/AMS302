#include <vector>
#include <iostream>
#include <cmath>
#include <stdlib.h>
using namespace std;

float ranf()
{
  return (float) rand()/RAND_MAX; //fdsqfaze
}

float source() { return ranf(); }

float f_gene(float mu, float sigma)
{ 
  return -mu * log(ranf()) / sigma + source();
}

vector<float> trajs(float mu, float sigma, int n)
{
  vector<float> part(n); // n est la taille du tableau part
  //int i;
  for(int i = 0 ; i < n ; i++)
  {
    part.at(i) = f_gene(mu,sigma);
  }
  return part;
}

vector<int> denom(const vector<float>& part, int nb_seg)
{
  vector<int> flux(nb_seg + 2,0); //initialise toutes les valeurs à 0
  for (auto const & val : part) // sans indice
  {
    if (val>=1) flux.at(nb_seg+1)++; // ou flux[nb_seg] mais pas de vérif ...
    else if (val< 0) flux.at(0)++;
    else flux.at( floor(nb_seg*val) )++;
  }
  return flux;
}

int main(int argc, char**argv)
{
  if (argc!=5) return EXIT_FAILURE;
  float mu,
        sigma;
  int nb_part,
      nb_seg;
  mu = atof(argv[1]);
  sigma = atof(argv[2]);
  nb_part = atoi(argv[3]); // i pour pas float bro
  nb_seg  = atoi(argv[4]);
  
  vector<float> part = trajs(mu, sigma, nb_part);
  //for(auto const & val : part) // const -> pas modif de val, promis
  //  cout << val << endl;  // pas obligé les accolades pour boucles avec une ligne d'exe
  vector<int> flux = denom(part, nb_seg);
  // for(int i = 1 ; i < nb_seg ; i++) // const -> pas modif de val, promis
  //   cout << (float) i / nb_seg << " " << (float) flux.at(i) / nb_part << endl; // " -> ouvre des strings ma gueuuule EEEEEEEEET (float) avant division euclidienne
  return EXIT_SUCCESS;
}