#Finds the nth palindromic prime number

def Palin(num):
  Reverse = 0
  temp = num
  while(temp > 0):
    Reverse = (Reverse * 10) + temp % 10
    temp = temp // 10
  if(num == Reverse):
    return True
  else:
    return False

def Prime(num):
    i = 3
    prime = [1,2]
    if(num == 1):
      return 1
    if(num == 2):
      return 2
    while(num > 2 ):
        for k in range(0, len(prime)):
            if(i % prime[k] == 0 and prime[k] != 1):
                break
            if((i % prime[k]) > 0 and k == len(prime)-1):
                prime.append(i)
                #num = num -1
                break
        if(Palin(prime[-1]) == True):
           num = num - 1          
        i = i + 2
    return prime[-1]


num = int(input("Please input the nth palindromic prime number you want to find: "))

prim = Prime(num)
print("The {:^2g} palindromic prime number is: {:^2g}".format(num, prim))