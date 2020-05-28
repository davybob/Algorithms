"""
  Create grid (n*n size) where one point is some convergent point.
  Create even distribution of points on grid.
  Apply EA on points to converge to point (Apply diff methods).
  Observe rate of convergence
  Write up results using tex
  Repeat for 3d grid (mountain climb)
"""
import random
import os
import matplotlib.pyplot as plt
import math

fig = plt.figure(figsize=(10, 8))
ax = fig.add_subplot(111)

#Create random population on a grid of size n*n (population size default n)
def Seed(size, numpoints, ax):
  first = []
  second = []
  population = []
  for i in range(numpoints):
    random.seed(os.urandom(random.randint(0,100)),version=2)
    population.append((0, [random.randint(0,size),random.randint(0,size)]))
    first.append(population[i][1][0])
    second.append(population[i][1][1])
  ax.plot(first,second, 'bo')
  return population

#Calculate fitness of each point (distance to convergent point)
def Fitness(population, point):
  for indx,val in enumerate(population):
    val = val[1]
    sqrt = (val[0]-point[0])**2 + (val[1]-point[1])**2
    sqrt = round(math.sqrt(sqrt),4)
    population[indx] = (sqrt,val)

# Take the average of two points (choose 5, then choose highest fitness one)
def Recombination(population, point, k=4):
  # Pick 6 from total population
  random.seed(os.urandom(random.randint(0,100)),version=2)
  choice = random.sample(population,k=k)
  result = []
  #Create 3 random pairs
  for i in range(int(len(choice)/2)):
    temp = random.randint(i,len(choice)-1)
    result.append(choice[temp])
  #Combine the 3 pairs (avg of two parents)
  for indx,val in enumerate(result):
    result[indx] = (0,[(result[indx][1][0]+val[1][0])/2, (result[indx][1][1]+val[1][1])/2])
  #Get fitness of each pair
  Fitness(result, point)
  #Mutate each pair
  CreepMutate(result, 0.3)
  #place most fit child into population
  result.sort(key=lambda tup : tup[0])
  return result[0]

def replace(population, child):
  # Sort population based on fitness
  population.sort(key=lambda tup : tup[0])
  mostfit = population[0][0]
  replaced = False
  for indx,val in enumerate(population):
    # Find point where child is less fit then some solution in population
    if val[0] > child[0]:
      replaced = True
      # Replace previous point with child
      population[indx-1] = child
      break
  # Shuffle population only if child replaced
  random.seed(os.urandom(99))
  random.shuffle(population)
  return mostfit
#Mutation occurs with percentage p and a value from standard normal is added
def CreepMutate(children, p):
  for indx,val in enumerate(children):
    random.seed(os.urandom(random.randint(0,100)),version=2)
    if(random.random() < p):
      temp = random.normalvariate(0,1)
      children[indx][1][0] += temp
      children[indx][1][1] += temp

def plotpoints(population,ax):
  first = []
  second = []
  for i in population:
    first.append(i[1][0])
    second.append(i[1][1])
  ax.plot(first, second, 'ro')

convpoint = [5,5]
#Create initial population
population = Seed(10,15, ax)
z = 2
#Assume most fit solution is furthest away
mostfit = math.sqrt(convpoint[0]**2 + convpoint[1]**2)

while (z > 0 or mostfit > 2):
  #Calculate fitness of population
  Fitness(population, convpoint)
  #Pick 6 random, mate, then pick most fit and replace
  child = Recombination(population,convpoint)
  mostfit = replace(population,child)
  plotpoints(population,ax)
  z-=1
  print(mostfit)

# Point to converge at
ax.plot(5,5,'ro')
ax.grid()
fig.savefig('graph.png')
