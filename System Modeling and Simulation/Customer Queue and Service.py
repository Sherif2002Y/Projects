import random

# Parameters
arrival_rate = 5.0  # customers per minute
service_rate = 6.0  # customers per minute
num_customers = 1000

# Simulation clock, queue, and statistics tracking variables
clock = 0.0
num_served = 0
queue = []
total_wait_time = 0.0
interarrival_times = []
service_times = []
queue_lengths = []

# Generate the arrival time for the first customer
next_arrival_time = random.expovariate(arrival_rate)

# Start the simulation loop
while num_served < num_customers:
    # Determine the next event based on the arrival and departure times
    if not queue or next_arrival_time < queue[0][1]:
        # The next event is an arrival
        event_time = next_arrival_time
        interarrival_times.append(event_time - clock)
        next_arrival_time = clock + random.expovariate(arrival_rate)
        event_type = "arrival"
    else:
        # The next event is a departure
        event_time = queue[0][1]
        event_type = "departure"

    # Update the simulation clock to the time of the next event
    clock = event_time

    if event_type == "arrival":
        # Add the customer to the queue
        queue.append((num_served, clock))
        queue_lengths.append(len(queue))

    else: # event_type == "departure"
        # Remove the first customer from the queue
        customer_num, arrival_time = queue.pop(0)
        # Update the total wait time
        total_wait_time += clock - arrival_time
        # Increment the number of customers served
        num_served += 1
        service_times.append(clock - arrival_time)
        # Generate the departure time for the next customer (if any)
        if queue:
            next_departure_time = clock + random.expovariate(service_rate)
            queue[0] = (queue[0][0], next_departure_time)

# Compute the average wait time, interarrival time, and queue length
avg_wait_time = total_wait_time / num_customers
avg_interarrival_time = sum(interarrival_times) / len(interarrival_times)
avg_queue_length = sum(queue_lengths) / len(queue_lengths)
avg_service_time = sum(service_times) / num_customers
print("Service rate: {:.2f} customers per minute".format(service_rate))
print("Average wait time: {:.2f} minutes".format(avg_wait_time))
print("Average interarrival time: {:.2f} minutes".format(avg_interarrival_time))
print("Average queue length: {:.2f} customers".format(avg_queue_length))