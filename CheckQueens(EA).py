"""
  1. Create random population (random permutation of queens on diagonal) (initial population 100)
  2. Check "fitness" i.e how many queens are in check
     (maximise M-q(p) where M >= max{q(p)|p elem P} and q(x) is num of queens in check)
  3. Choose 5 random permutations then choose 2 best.
  4. 'Cut-and-crossfill' crossover to create two new permutations (100% of recombination).
  5. Apply mutation (swap position with any random permutation from population) (80% of mutation)
  6. Check fitness of new permutations, if better than two worst, replace two worst.
  7. Terminate when solution is found or 10,000 fitness evaluations.
"""
import random
import os

#Create random population
def RandomPopulation(size):
  #nth element (row) represents the column the queen is in (for pop = [1,...,8], queens diagonal)
  population = []
  # No two queens can be on the same column (otherwise they will check eachother)
  # Similarly no two queens can be on the same row (otherwise they will check eachother)
  # Thus we must find a permutation where queens do not check eachother diagonally
  initialChild = [1,2,3,4,5,6,7,8]
  for i in range(size): # Create the population of size N
    random.seed(os.urandom(i), version=2) # Generate random seed
    random.shuffle(initialChild)
    newchild = []
    for j in initialChild:
      newchild.append(j)
    population.append(newchild) # Add this random shuffle to population
  return population # Return population

#Check fitness of population
def Fitness(population):
  fitness = []
  size = len(population[0])
  M = 8
  # loop through population
  for i in population:
    childfitness = 0
    # loop each row checking which columns are in check
    for ind,val in enumerate(i):
      # check upward diagonals + downwards
      indtemp = ind+1
      it = 1
      case = [0,0,0]
      for z in range(ind+1, size):
        if (i[z] == val and case[0] == 0):
          childfitness += 1
          case[0] = 1
        if (i[z] == val+it and case[1] == 0):
          childfitness += 1
          case[1] = 1
        if (i[z] == val-it and case[2] == 0):
          childfitness += 1
          case[2] = 1
        it+=1
    fitness.append(M-childfitness)
  return fitness

#Choose 5 random from population, then two best from 5
def PickFiveRand(population, fitness):
  random.seed(os.urandom(8), version=2)
  picklist = [i for i in range(len(population))]
  # pick 5 random indices from list of popultion sized indices
  choices = random.choices(picklist, k=5)
  # get fitness of each choice and sort by highest
  fitnesschoices = [(i,fitness[i]) for i in choices]
  fitnesschoices.sort(key=lambda tup: tup[1], reverse=True)
  return population[fitnesschoices[0][0]], population[fitnesschoices[1][0]], picklist # Return two strongest parents and list from chosen list

#Cut-and-crossfill new permutations
def Mate(parents):
  random.seed(os.urandom(8), version=2)
  position = random.randint(0,7)
  # Split at random point and mix parent 1 end split with parent 2 end split
  c1 = parents[0][0:position]
  c1.extend(parents[1][position:])
  c2 = parents[1][0:position]
  c2.extend(parents[0][position:])
  return c1, c2

#Apply mutation
def Mutate(chromosome):
  random.seed(os.urandom(8), version=2)
  size = len(chromosome)-1
  if(random.choices([True,False], weights=[0.8,0.2])[0]):
    random.seed(os.urandom(8), version=2)
    p1 = random.randint(0,size)
    random.seed(os.urandom(8), version=2)
    p2 = random.randint(0,size)
    temp = chromosome[p1]
    chromosome[p1] = chromosome[p2]
    chromosome[p2] = temp
    return True
  return False

#Replace if necessary
def replace(Population, fitnessPopulation, newoffspring):
  fitness = Fitness(newoffspring)
  replaced = False
  if fitness[0] > fitnessPopulation[-1]:
    Population[-1] = newoffspring[0]
    replaced = True
  elif fitness[1] > fitnessPopulation[-1]:
    Population[-1] = newoffspring[1]
  if fitness[0] > fitnessPopulation[-2] and not replaced:
    Population[-2] = newoffspring[0]
  elif fitness[1] > fitnessPopulation[-2]:
    Population[-2] = newoffspring[1]
  if replaced: # If we replaced return true otherwise return false
    return True
  return False
#Rinse and repeat until termination condition met

startPop = RandomPopulation(10)

for i in range(5):
  fitness = Fitness(startPop)
  parent1, parent2 , chosenlist = PickFiveRand(startPop, fitness)
  child1, child2 = Mate([parent1,parent2])
  Mutate(child1)
  Mutate(child2)
  replace(startPop, fitness, [child1,child2])
  for ind,val in enumerate(startPop):
    print(f'F: {fitness[ind]}, val: {val}')
  print("Generation",i, "\n")
