#include <iostream>
#include <random>
#include <chrono>
#include <bitset>
#include <cmath>

void Fitness(std::bitset<5> *Population, float* fitness, int& sum, float& avg, int& max){
  for (int i = 0; i < 4; i++){
    fitness[i] = Population[i].to_ulong()*Population[i].to_ulong();
    sum += fitness[i];
    if (fitness[i] > max ) max = fitness[i];
  }
  avg = sum/4;
}

void Counts(float *ProbCount, float *ExpectedCount, float *fitness, float sum, float avg){
    for (int i = 0; i < 4; i++){
    ProbCount[i] = fitness[i]/sum;
    ExpectedCount[i] = fitness[i]/avg;
  }
}

void ChooseOffspring(float *probCount, int *actualCount, std::default_random_engine& generator){
    int i = 0;
    int total = 0;
    while(total < 4){
    if (i==4)
      i = 0;
    std::bernoulli_distribution tempdist(probCount[i]);
    bool result = tempdist(generator);
    if (result){
      actualCount[i] += 1;
      total += 1;
    }
    i += 1;
    }
}

void ElimOldOffspring(int *actualCount,std::bitset<5> *Population){
  auto tempcount = actualCount;
  for(int i = 0; i < 4; i++){
    if (tempcount[i] > 1){
      for(int j = 0; j < 4; j++){
        if (tempcount[i] < 2)
          break;
        if (tempcount[j] == 0){
          tempcount[j] += 1;
          Population[j] = Population[i];
          tempcount[i] -= 1;}
      }
    }
  }
}

void Mate(std::bitset<5> &offspring1,std::bitset<5> &offspring2, std::default_random_engine generator){
  std::bernoulli_distribution tempdist(0.2);
  bool result = tempdist(generator);
  int position = 0;
  while(!result){
  std::bernoulli_distribution tempdist(0.2);
  result = tempdist(generator);
  position += 1;
  }
  position = position%5;
  bool temp = offspring1[position];
  offspring1[position] = offspring2[position];
  offspring2[position] = temp;
}

void Mutate(std::bitset<5> &Population, std::default_random_engine& generator){
  std::bernoulli_distribution tempdist(0.2);
  bool result = tempdist(generator);
  int i = Population.to_ulong()%5;
  if (result)
    Population.set(i,tempdist(generator));
}

void GenerateNewOffspring(std::bitset<5> *Population, std::default_random_engine &generator){
  int i = 0;
  int j = 0;
  while(true){
    if (i == 4 )
      i = 0;
    std::bernoulli_distribution tempdist(0.25);

    bool result = tempdist(generator);
    if (result && i != j){
      Mate(Population[j], Population[i], generator);
      Mutate(Population[j], generator);
      if(i != 1 && i!= 2){Mate(Population[1], Population[2], generator); Mutate(Population[1],generator);Mutate(Population[2],generator);}
      else if(i != 1 && i!=3){Mate(Population[1], Population[3], generator);Mutate(Population[1],generator);Mutate(Population[2],generator);}
      else if(i != 2 && i!=3){Mate(Population[2], Population[3], generator);Mutate(Population[1],generator);Mutate(Population[2], generator);}
      break;
    }
      i += 1;
  }
}

void Table(std::bitset<5> Population[4], float *fitness, float *probcont, float *expected, int *actual, int sum, float avg, int max){
  std::cout << "|String no.| \t |Initial Population| \t |x Value| \t |Fitness| \t |Prob(i)| \t |Expected count| \t |Actual count| \n";
  for (int i=0; i < 4; i++){
    std::cout << "|" << i << "| \t";
    std::cout << "|" << Population[i] << "| \t";
    std::cout << "|" << Population[i].to_ullong() << "|\t";
    std::cout << "|" << fitness[i] << "|\t";
    std::cout << "|" << probcont[i] << "|\t";
    std::cout << "|" << expected[i] << "|\t";
    std::cout << "|" << actual[i] << "|\t";
    std::cout << "\n";
  }
  std::cout << "Sum" << "\t \t " << sum <<"\n";
  std::cout << "Avg" << "\t \t " << avg <<"\n";
  std::cout << "Max" << "\t \t " << max <<"\n \n";

}

int main() {
  std::bitset<5> Population[4]; // Initialise Population

  // Seed random generator
  unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
  std::default_random_engine generator(seed);
  std::normal_distribution<double> distribution(0.0,1.0);
  //Create random Population
  for (int i=0; i < 4; i++){
    for (int j=0; j < 5; j++){
      double result = distribution(generator); //Using normal distribution to seed population
      if (result > 0.0f){
        Population[i].set(j,1);
      }
      else
        Population[i].set(j,0);
    }
  }

// LOOP FOR EACH ITERATION
for(int z = 0; z < 9; z++){
  float PopulationFitness[4];
  int sum = 0;
  float avg = 0;
  int max = 0;
  float probcont[4]= {0,0,0,0};
  float expectedCount[4]= {0,0,0,0};
  int actualCount[4] = {0,0,0,0};
  // Get current population fitness, max, sum, avg
  Fitness(Population,PopulationFitness,sum,avg,max);

  // Get current population probability of offspring
  // Find Expected count of each offspring
  Counts(probcont, expectedCount,PopulationFitness,sum,avg);
  //Choose offspring using bernoulli and probcont of each offspring, loop until we count population size of offspring
  ChooseOffspring(probcont, actualCount, generator);

  int total = 0;
  int i = 0;

  // Eliminate unchosen offspring and copy chosen offspring to keep population constant
  ElimOldOffspring(actualCount, Population);

  // Pair population offspring together for mating (Choose point to crossover then crossover)
  GenerateNewOffspring(Population, generator);

  Table(Population, PopulationFitness, probcont, expectedCount, actualCount, sum, avg, max);
}
  return 0;
}
