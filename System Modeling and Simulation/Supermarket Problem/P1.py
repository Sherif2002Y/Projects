import random
import numpy as np
import matplotlib.pyplot as plt
from prettytable import PrettyTable
import tkinter as tk
from tkinter import messagebox

class CarDealerSimulator:
  def __init__(self, initial_inventory, initial_showroom, initial_order_quantity,
      demand_probabilities, demand_values, lead_time_probabilities, lead_time_values):
    self.shortage = 0
    self.inventory = initial_inventory
    self.showroom = initial_showroom
    self.order_quantity = initial_order_quantity
    self.demand_probabilities = demand_probabilities
    self.demand_values = demand_values
    self.lead_time_probabilities = lead_time_probabilities
    self.lead_time_values = lead_time_values
    self.cycle = 1
    self.day = 1
    self.N = 3  # Review period
    self.MAX_SHOWROOM = 5
    self.MAX_INVENTORY = 10
    self.M = 10  # Order quantity
    self.PROFIT_PER_CAR = 10000
    self.HOLDING_COST_PER_CAR = 1000
    self.ORDER_COST = 20000
    self.total_profit = 0
    self.shortage_days = 0
    self.ending_showroom_list = []
    self.ending_inventory_list = []
    self.net_profit_list = []
    self.table = PrettyTable(["Cycle", "Day", "Beginning Inventory", "Ending Inventory", "Demand", "Shortage",
      "Order Quantity", "Beginning Showroom", "Ending Showroom", "Profit", "Loss"])
  def calculate_demand(self):
    demand_index = random.choices(range(len(self.demand_probabilities)), weights=self.demand_probabilities)[0]
    return self.demand_values[demand_index]
  def generate_lead_time(self):
    lead_time_index = random.choices(range(len(self.lead_time_probabilities)),
      weights=self.lead_time_probabilities)[0]
    return self.lead_time_values[lead_time_index]
  def simulate_day(self):
    demand = self.calculate_demand()
    lead_time = self.generate_lead_time()
    ending_inventory = max(self.inventory - demand, 0)
    ending_showroom = max(self.showroom - max(demand - self.inventory, 0), 0)
    self.shortage = max(demand - self.inventory - self.showroom, 0)
    daily_profit = (demand * self.PROFIT_PER_CAR) - (ending_inventory + ending_showroom) * self.HOLDING_COST_PER_CAR
    if daily_profit < 0:
        daily_loss = -daily_profit
        daily_profit = 0
    else:
        daily_loss = 0
    self.total_profit += daily_profit
    if self.shortage > 0:
        self.shortage_days += 1
    self.table.add_row(
        [self.cycle, self.day, self.inventory, ending_inventory, demand, self.shortage,
        "", self.showroom, ending_showroom, daily_profit, daily_loss])
    self.day += 1
    self.inventory = ending_inventory
    self.showroom = ending_showroom
  def place_order(self):
    order_quantity_inventory = max(self.M - self.inventory, 0)
    order_quantity_showroom = max(self.MAX_SHOWROOM - self.showroom, 0)
    self.order_quantity = (order_quantity_inventory + order_quantity_showroom)-self.shortage
    self.table.add_row(["", "", "", "", "", "", self.order_quantity, "", "", "", ""])
    self.cycle += 1
    self.day = 1
    self.showroom = min(self.showroom + order_quantity_showroom, self.MAX_SHOWROOM)
    self.order_quantity -= order_quantity_showroom
    self.inventory = order_quantity_inventory - self.shortage
  def run_simulation(self, num_cycles):
    while self.cycle <= num_cycles:
      for _ in range(self.N):
        self.simulate_day()
        self.ending_showroom_list.append(self.showroom)
        self.ending_inventory_list.append(self.inventory)
        self.net_profit_list.append(self.total_profit)
      self.place_order()
    # Print the final result table
    print(self.table)
    # Calculate and print the average ending units in showroom and inventory
    avg_ending_showroom = np.mean(self.ending_showroom_list)
    avg_ending_inventory = np.mean(self.ending_inventory_list)
    print("Average Ending Showroom Units:", avg_ending_showroom)
    print("Average Ending Inventory Units:", avg_ending_inventory)
    # Calculate and print the number of days with a shortage condition
    print("Number of Days with Shortage:", self.shortage_days)
    # Calculate and print the average net profit for the car dealer
    avg_net_profit = np.mean(self.net_profit_list)
    print("Average Net Profit:", avg_net_profit)
    # Create a histogram for ending showroom units
    plt.hist(self.ending_showroom_list, bins=range(0, self.MAX_SHOWROOM + 1), align='left', rwidth=0.8)
    plt.xticks(range(0, self.MAX_SHOWROOM + 1))
    plt.xlabel("Ending Showroom Units")
    plt.ylabel("Frequency")
    plt.title("Histogram of Ending Showroom Units")
    plt.show()
    # Create a histogram for ending inventory units
    plt.hist(self.ending_inventory_list, bins=range(0, self.MAX_INVENTORY + 1), align='left', rwidth=0.8)
    plt.xticks(range(0, self.MAX_INVENTORY + 1))
    plt.xlabel("Ending Inventory Units")
    plt.ylabel("Frequency")
    plt.title("Histogram of Ending Inventory Units")
    plt.show()
    # Create a histogram for net profit
    plt.hist(self.net_profit_list, bins=10, align='left', rwidth=0.8)
    plt.xlabel("Net Profit")
    plt.ylabel("Frequency")
    plt.title("Histogram of Net Profit")
    plt.show()

class CarDealerGUI(tk.Tk):
  def __init__(self):
    super().__init__()
    self.title("Car Dealer Simulator")
    self.geometry("400x350")
    self.create_widgets()
  def create_widgets(self):
    self.lbl_inventory = tk.Label(self, text="Initial Inventory:")
    self.lbl_inventory.pack()
    self.entry_inventory = tk.Entry(self)
    self.entry_inventory.pack()
    self.lbl_showroom = tk.Label(self, text="Initial Showroom:")
    self.lbl_showroom.pack()
    self.entry_showroom = tk.Entry(self)
    self.entry_showroom.pack()
    self.lbl_order_quantity = tk.Label(self, text="Initial Order Quantity:")
    self.lbl_order_quantity.pack()
    self.entry_order_quantity = tk.Entry(self)
    self.entry_order_quantity.pack()
    self.lbl_cycles = tk.Label(self, text="Number of Cycles:")
    self.lbl_cycles.pack()
    self.entry_cycles = tk.Entry(self)
    self.entry_cycles.pack()
    self.lbl_days = tk.Label(self, text="Number of Days per Cycle:")
    self.lbl_days.pack()
    self.entry_days = tk.Entry(self)
    self.entry_days.pack()
    self.btn_start = tk.Button(self, text="Start Simulation", command=self.start_simulation)
    self.btn_start.pack()
  def start_simulation(self):
    initial_inventory = int(self.entry_inventory.get())
    initial_showroom = int(self.entry_showroom.get())
    initial_order_quantity = int(self.entry_order_quantity.get())
    num_cycles = int(self.entry_cycles.get())
    num_days = int(self.entry_days.get())
    simulator = CarDealerSimulator(initial_inventory, initial_showroom, initial_order_quantity,
        [0.2, 0.54, 0.9, 1.0], [0, 1, 2, 3], [0.4, 0.75, 1.0], [1, 2, 3])
    simulator.N = num_days
    simulator.run_simulation(num_cycles)
    messagebox.showinfo("Simulation Complete", "Simulation finished successfully.")

if __name__ == "__main__":
    app = CarDealerGUI()
    app.mainloop()