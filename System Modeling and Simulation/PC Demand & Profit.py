import random
import matplotlib.pyplot as plt 

 # Determinestic Inputs

MaximumCost = 100
LosingCost = 50
SellingPrice = 450

#lists
profitlist = list()   
Demands= list()          

def random_0_to_1():
    return random.uniform(0, 1)

def get_Demands():
  rand_prob=random_0_to_1()     # Probability of demand
  if rand_prob>=0 and rand_prob<0.2:
       Demands=0
  elif rand_prob>=0.2 and rand_prob<0.6:
       Demands=1                              
  elif rand_prob>=0.6 and rand_prob<0.8:
       Demands=2
  elif rand_prob>=0.8 and rand_prob<0.9:
       Demands=3
  else :
       Demands=4
  return Demands

for i in range (500) :
    Demands.append(get_Demands ())

for Order in range (1,3) :         #Order is 1 or 2
    Avail = 1
    for Week in range (500) :   
        Avail += Order
        if Demands[Week]< Avail :
            sold = Demands[Week]
            Avail -= Demands[Week]
            loss = Avail * LosingCost
        elif Demands[Week] > Avail :
            sold = Avail
            Avail = 0
            loss = MaximumCost*(Demands[Week] - sold)
        else :
            sold = Demands[Week]
            Avail = 0
            loss = 0
        revenue = sold * SellingPrice 
        profit = revenue - (loss)
        if profit >= 0 :
            profitlist.append(profit)
    if Order == 1 :
        AverageProfit1 = sum(profitlist) / 500
        profitlist.clear()
    else :
        AverageProfit2 = sum(profitlist) / 500



print ("The average profit of 500 weeks :" , "\n")
print("if the store owner ordered 1 PC per week :", AverageProfit1, "\n")
print("if the store owner ordered 2 PC per week :", AverageProfit2, "\n")

if AverageProfit1 > AverageProfit2 :
    print("Ordering 1 PC per week is the best solution")
elif AvgProfit1 < AvgProfit2:
    print("Ordering 2 PC per week is the best solution")
        
# Histogram
plt.hist(Demands,bins=20)
plt.xlabel('Demand')
plt.ylabel('Frequency')
plt.show()
