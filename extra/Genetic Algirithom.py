import random

def generate_population(population_size, chromosome_length):

    return [[random.randint(0, 1) for _ in range(chromosome_length)] for _ in range(population_size)]

def fitness_function(chromosome):

    return sum(chromosome)

def crossover(parent1, parent2):

    crossover_point = random.randint(0, len(parent1) - 1)
    child = parent1[:crossover_point] + parent2[crossover_point:]
    return child

def mutate(child, mutation_rate):

    mutated_child = [bit ^ (random.random() < mutation_rate) for bit in child]
    return mutated_child

def select_parents(population, num_parents):

    selected_parents = []
    for _ in range(num_parents):
        tournament_size = 5
        tournament = random.sample(population, tournament_size)
        selected_parent = max(tournament, key=fitness_function)
        selected_parents.append(selected_parent)
    return selected_parents

def genetic_algorithm(population_size, chromosome_length, generations, crossover_rate, mutation_rate):

    population = generate_population(population_size, chromosome_length)

    for generation in range(generations):
        # Evaluate the fitness of each individual
        fitness_values = [fitness_function(individual) for individual in population]

        # Select parents
        num_parents = population_size // 2
        parents = select_parents(population, num_parents)

        # Perform crossover to create children
        children = []
        for i in range(0, num_parents, 2):
            parent1 = parents[i]
            parent2 = parents[i + 1]
            if random.random() < crossover_rate:
                child1 = crossover(parent1, parent2)
                child2 = crossover(parent2, parent1)
            else:
                child1, child2 = parent1.copy(), parent2.copy()
            children.extend([child1, child2])

        # Perform mutation on children
        for child in children:
            if random.random() < mutation_rate:
                child = mutate(child, mutation_rate)

        # Combine parents and children to form the new population
        population = parents + children

        # Select the top individuals to survive to the next generation
        population.sort(key=fitness_function, reverse=True)
        population = population[:population_size]

    # Return the best individual found
    best_individual = max(population, key=fitness_function)
    return best_individual

# Example Usage:
population_size = 100
chromosome_length = 10
generations = 100
crossover_rate = 0.7
mutation_rate = 0.01

best_individual = genetic_algorithm(population_size, chromosome_length, generations, crossover_rate, mutation_rate)
print(f"Best Individual: {best_individual}")
print(f"Fitness Value: {fitness_function(best_individual)}")