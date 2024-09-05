from random import randrange
from typing import List

from numpy import random
from prettytable import PrettyTable

case_today = []
noOf_day = []
all_day = []
detect_no = []
detect_state = []  #  el good,fair
ton = []  #  el good,fair
rn_demand = []

demand = []
revenue = []
lostprofit = []  # lostprofit
slvg = []
dialyprofit = []  # dialy profit
k = 0

detect_no = random.randint(100)
if 0 < detect_no <= 18:
    ton = "excellent"
elif 18 < detect_no <= 60:
    ton = "good"
elif 60 < detect_no <= 92:
    ton = "fair"
elif 92 < detect_no <= 100:
    ton = "poor"
    case_today.append(ton)

for i in range(40):
    f_rondom = random.randint(100)
    rn_demand.append(f_rondom)

if ton == "poor" and 0 < f_rondom <= 42:
    demand = 40
elif ton == "poor" and 42 < f_rondom <= 70:
    demand = 50
elif ton == "poor" and 70 < f_rondom <= 84:
    demand = 60
elif ton == "poor" and 84 < f_rondom <= 94:
    demand = 70
elif ton == "poor" and 94 < f_rondom <= 99:
    demand = 80
elif ton == "poor" and 99 < f_rondom <= 100:
    demand = 90

elif ton == "fair" and 0 < f_rondom <= 15:
    demand = 40
elif ton == "fair" and 15 < f_rondom <= 37:
    demand = 50
elif ton == "fair" and 37 < f_rondom <= 65:
    demand = 60
elif ton == "fair" and 65 < f_rondom <= 83:
    demand = 70
elif ton == "fair" and 83 < f_rondom <= 93:
    demand = 80
elif ton == "fair" and 94 < f_rondom <= 98:
    demand = 90
elif ton == "fair" and 98 < f_rondom <= 100:
    demand = 100

elif ton == "good" and 0 < f_rondom <= 6:
    demand = 40
elif ton == "good" and 6 < f_rondom <= 15:
    demand = 50
elif ton == "good" and 15 < f_rondom <= 31:
    demand = 60
elif ton == "good" and 31 < f_rondom <= 50:
    demand = 70
elif ton == "good" and 50 < f_rondom <= 78:
    demand = 80
elif ton == "good" and 78 < f_rondom <= 90:
    demand = 90
elif ton == "good" and 90 < f_rondom <= 97:
    demand = 100
elif ton == "good" and 97 < f_rondom <= 100:
    demand = 110

elif ton == "Excellent " and f_rondom == 0:
    demand = 40
elif ton == "Excellent " and 1 <= f_rondom <= 7:
    demand = 50
elif ton == "Excellent " and 7 < f_rondom <= 15:
    demand = 60
elif ton == "Excellent " and 15 < f_rondom <= 27:
    demand = 70
elif ton == "Excellent " and 27 < f_rondom <= 40:
    demand = 80
elif ton == "Excellent " and 40 < f_rondom <= 62:
    demand = 90
elif ton == "Excellent " and 62 < f_rondom <= 85:
    demand = 100
elif ton == "Excellent " and 85 < f_rondom <= 93:
    demand = 110
elif ton == "Excellent " and 93 < f_rondom <= 100:
    demand = 120
else:
    demand = 0

cost_80 = (0.5 * 80)

for i in range(40):
    list_cost = []
    list_cost.append(cost_80)
    revenue.append(demand * 0.7)
    lostprofit.append((demand - 80) * 0.2)
    slvg.append(0.15 * (80 - demand))
    dialyprofit.append(revenue[i] - cost_80 - lostprofit[i] + slvg[i])

t = PrettyTable(['Days', 'Rn for types of Newsday  ', 'Type of Newsday', 'Rn for demand', 'demand', 'Revenue ',
                 'cost', 'lost profit', 'salvage', 'dialy profit'])
for i in range(40):
    t.add_row([i,detect_no[i], case_today[i], rn_demand[i],demand[i] , revenue[i],list_cost[i],lostprofit[i],slvg[i],dialyprofit[i]])
    print(t)


