import pygame
import sys
import random
import math
import numpy as np

RIGHT = 0
DOWN = 1
LEFT = 2
UP = 3

moves_per_game = 500
num_generations = 100
sol_per_pop = 50
num_parents_mating = 10

# Game functions
class Game:
    def __init__(self):
        self.score = 0
        self.positions = [[100, 100], [90, 100], [80, 100]]
        self.free_positions = []
        self.calculate_free_positions()
        self.last_empty_position = []
        self.direction = RIGHT
        self.apple = random.choice(self.free_positions)
        self.blocked_right = 0
        self.blocked_left = 0
        self.blocked_front = 0

    def calculate_free_positions(self):
        for x in range(25):
            for y in range(25):
                if [x * 10, y * 10] not in self.positions:
                    self.free_positions.append([x * 10, y * 10])

    def generate_new_apple(self):
        self.calculate_free_positions()
        self.apple = random.choice(self.free_positions)

    def get_direction_vector(self):
        if self.direction == RIGHT:
            return [10, 0]
        elif self.direction == LEFT:
            return [-10, 0]
        elif self.direction == UP:
            return [0, 10]
        else:
            return [0, -10]

    def calculate_blocked_directions(self):
        self.calculate_free_positions()
        dir_vector = self.get_direction_vector()
        # front
        if [self.positions[0][0] + dir_vector[0], self.positions[0][1] + dir_vector[1]] in self.free_positions:
            self.blocked_front = 0
        else:
            self.blocked_front = 1
        # right
        if [self.positions[0][0] + dir_vector[1], self.positions[0][1] - dir_vector[0]] in self.free_positions:
            self.blocked_right = 0
        else:
            self.blocked_right = 1
        # left
        if [self.positions[0][0] - dir_vector[1], self.positions[0][1] + dir_vector[0]] in self.free_positions:
            self.blocked_left = 0
        else:
            self.blocked_left = 1

    def turn(self, direction):
        if direction == -1:
            self.direction = (self.direction + 1) % 4
        elif direction == 1:
            self.direction = (self.direction - 1) % 4


def display_snake(snake, display):
    for position in snake:
        pygame.draw.rect(display, (0, 0, 0), pygame.Rect(position[0], position[1], 10, 10))


def display_apple(apple, display):
    pygame.draw.rect(display, (0, 0, 0), pygame.Rect(apple[0], apple[1], 10, 10))


def move_snake(snake):
    snake_tmp = [snake.positions[0][0], snake.positions[0][1]]
    if snake.direction == LEFT:
        snake.positions[0][0] -= 10
    if snake.direction == RIGHT:
        snake.positions[0][0] += 10
    if snake.direction == DOWN:
        snake.positions[0][1] += 10
    if snake.direction == UP:
        snake.positions[0][1] -= 10

    for x in range(1, len(snake.positions)):
        snake_tmp_tmp = [snake.positions[x][0], snake.positions[x][1]]
        snake.positions[x] = [snake_tmp[0], snake_tmp[1]]
        snake_tmp = [snake_tmp_tmp[0], snake_tmp_tmp[1]]
    snake.last_empty_position = [snake_tmp[0], snake_tmp[1]]
    snake.calculate_free_positions()

    if check_collision(snake):
        return False, snake

    if snake.positions[0] == snake.apple:
        snake.positions.append([snake.last_empty_position[0], snake.last_empty_position[1]])
        snake.generate_new_apple()
        snake.score += 1
    return True, snake


def check_collision(snake):
    if not 0 <= snake.positions[0][0] < 250 or not 0 <= snake.positions[0][1] < 250:
        # print("collision with the wall")
        return 1
    if snake.positions[0] in snake.positions[1:]:
        # print("eaten its own tail")
        return 1
    return 0


def pressed_key(key, direction):
    if key == pygame.K_LEFT and direction != RIGHT:
        direction = LEFT
    if key == pygame.K_RIGHT and direction != LEFT:
        direction = RIGHT
    if key == pygame.K_DOWN and direction != UP:
        direction = DOWN
    if key == pygame.K_UP and direction != DOWN:
        direction = UP
    return direction


def angle_with_apple(snake_position, apple_position):
    apple_direction_vector = np.array(apple_position) - np.array(snake_position[0])
    snake_direction_vector = np.array(snake_position[0]) - np.array(snake_position[1])

    norm_of_apple_direction_vector = np.linalg.norm(apple_direction_vector)
    norm_of_snake_direction_vector = np.linalg.norm(snake_direction_vector)
    if norm_of_apple_direction_vector == 0:
        norm_of_apple_direction_vector = 10
    if norm_of_snake_direction_vector == 0:
        norm_of_snake_direction_vector = 10

    apple_direction_vector_normalized = apple_direction_vector / norm_of_apple_direction_vector
    snake_direction_vector_normalized = snake_direction_vector / norm_of_snake_direction_vector
    angle = math.atan2(
        apple_direction_vector_normalized[1] * snake_direction_vector_normalized[0] - apple_direction_vector_normalized[
            0] * snake_direction_vector_normalized[1],
        apple_direction_vector_normalized[1] * snake_direction_vector_normalized[1] + apple_direction_vector_normalized[
            0] * snake_direction_vector_normalized[0]) / math.pi
    return angle, snake_direction_vector, apple_direction_vector_normalized, snake_direction_vector_normalized


def death_screen(snake, display):
    display.fill((36, 204, 68))
    largeText = pygame.font.Font('freesansbold.ttf', 35)
    TextSurf = largeText.render("SCORE: " + str(snake.score), True, (0, 0, 0))
    TextRect = TextSurf.get_rect()
    TextRect.center = ((250 / 2), (250 / 2))
    display.blit(TextSurf, TextRect)
    smallText = pygame.font.Font('freesansbold.ttf', 10)
    TextSurf = smallText.render("Press Q to quit or any other key to play again", True, (0, 0, 0))
    TextRect = TextSurf.get_rect()
    TextRect.center = ((250 / 2), (300 / 2))
    display.blit(TextSurf, TextRect)
    pygame.display.update()
    wait = True
    while wait:
        for event in pygame.event.get():
            if event.type == pygame.KEYDOWN:
                if event.key == pygame.K_q:
                    quit()
                else:
                    wait = False
                    break
    play_game(display)


def play_game(display):
    clock = pygame.time.Clock()
    snake = Game()
    run = True
    while run:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                run = False
            if event.type == pygame.KEYDOWN:
                if event.key == pygame.K_q:
                    quit()
                snake.direction = pressed_key(event.key, snake.direction)
        display.fill((36, 204, 68))
        display_snake(snake.positions, display)
        display_apple(snake.apple, display)
        moved = move_snake(snake)
        snake = moved[1]
        if not moved[0]:
            death_screen(snake, display)
        else:
            display_snake(snake.positions, display)
            display_apple(snake.apple, display)
            pygame.display.set_caption("SCORE: " + str(snake.score))
            pygame.display.update()
            clock.tick(20)


def play_game_ai(snake, chromosome, generation, display):
    crashed = False
    while crashed is not True:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                crashed = True
        display.fill((36, 204, 68))
        moved = move_snake(snake)
        snake = moved[1]
        display_snake(snake.positions, display)
        display_apple(snake.apple, display)
        pygame.display.set_caption("Gen: " + str(generation) + ", Chromosome: " + str(chromosome))
        pygame.display.update()
        return snake


n_x = 7
n_h = 9
n_h2 = 15
n_y = 3
W1_shape = (9, 7)
W2_shape = (15, 9)
W3_shape = (3, 15)


# Genetic algorithm
def genetic(display):

    num_weights = n_x * n_h + n_h * n_h2 + n_h2 * n_y
    pop_size = (sol_per_pop, num_weights)
    new_population = np.random.choice(np.arange(-1, 1, step=0.01), size=pop_size, replace=True)

    for generation in range(num_generations):
        print('GENERATION:', generation)
        fitness = cal_pop_fitness(display, generation, new_population)
        print('Fittest chromosome in generation', str(generation), 'has value:', np.max(fitness))

        parents = select_mating_pool(new_population, fitness, num_parents_mating)

        offspring_crossover = crossover(parents, offspring_size=(pop_size[0] - parents.shape[0], num_weights))

        offspring_mutation = mutation(offspring_crossover)

        new_population[0:parents.shape[0], :] = parents
        new_population[parents.shape[0]:, :] = offspring_mutation


def get_weights(individual):
    W1 = individual[0:W1_shape[0] * W1_shape[1]]
    W2 = individual[W1_shape[0] * W1_shape[1]:W2_shape[0] * W2_shape[1] + W1_shape[0] * W1_shape[1]]
    W3 = individual[W2_shape[0] * W2_shape[1] + W1_shape[0] * W1_shape[1]:]
    return (
        W1.reshape(W1_shape[0], W1_shape[1]), W2.reshape(W2_shape[0], W2_shape[1]),
        W3.reshape(W3_shape[0], W3_shape[1]))


def predict_direction(X, individual):
    W1, W2, W3 = get_weights(individual)

    Z1 = np.matmul(W1, X.T)
    A1 = np.tanh(Z1)
    Z2 = np.matmul(W2, A1)
    A2 = np.tanh(Z2)
    Z3 = np.matmul(W3, A2)
    A3 = np.exp(Z3.T) / np.sum(np.exp(Z3.T), axis=1).reshape(-1, 1)
    return A3


def fitness_func(display, chromosome, generation, weights):
    score = 0
    snake = Game()

    count_same_direction = 0
    prev_direction = 0
    for _ in range(moves_per_game):
        angle, snake_direction_vector, apple_direction_vector_normalized, snake_direction_vector_normalized = angle_with_apple(
            snake.positions, snake.apple)
        snake.calculate_blocked_directions()
        predicted_direction = np.argmax(np.array(predict_direction(np.array(
            [snake.blocked_left, snake.blocked_front, snake.blocked_right, apple_direction_vector_normalized[0],
             snake_direction_vector_normalized[0], apple_direction_vector_normalized[1],
             snake_direction_vector_normalized[1]]).reshape(-1, 7), weights))) - 1

        if predicted_direction == prev_direction:
            count_same_direction += 1
        else:
            count_same_direction = 0
            prev_direction = predicted_direction

        # 0 == continue straight
        # -1 == turn right
        # 1 == turn left
        snake.turn(predicted_direction)

        snake = play_game_ai(snake, chromosome, generation, display)

        if check_collision(snake):
            score += -200
            break

        if count_same_direction > 8 and predicted_direction != 0:
            score -= 1
        else:
            score += 2

    return score + snake.score * 5000


def cal_pop_fitness(display, generation, pop):
    fitness = []
    for i in range(pop.shape[0]):
        fit = fitness_func(display, i, generation, pop[i])
        print('Fitness value of chromosome ' + str(i) + ' :  ', fit)
        fitness.append(fit)
    return np.array(fitness)


def select_mating_pool(pop, fitness, num_parents):
    parents = np.empty((num_parents, pop.shape[1]))
    for parent_num in range(num_parents):
        max_fitness_idx = np.where(fitness == np.max(fitness))
        max_fitness_idx = max_fitness_idx[0][0]
        parents[parent_num, :] = pop[max_fitness_idx, :]
        fitness[max_fitness_idx] = -99999999
    return parents


def crossover(parents, offspring_size):
    offspring = np.empty(offspring_size)

    for k in range(offspring_size[0]):

        while True:
            parent1_idx = random.randint(0, parents.shape[0] - 1)
            parent2_idx = random.randint(0, parents.shape[0] - 1)

            if parent1_idx != parent2_idx:
                for j in range(offspring_size[1]):
                    if random.uniform(0, 1) < 0.5:
                        offspring[k, j] = parents[parent1_idx, j]
                    else:
                        offspring[k, j] = parents[parent2_idx, j]
                break
    return offspring


def mutation(offspring_crossover):
    for idx in range(offspring_crossover.shape[0]):
        for _ in range(25):
            i = random.randint(0, offspring_crossover.shape[1] - 1)
            random_value = np.random.choice(np.arange(-1, 1, step=0.001), size=1, replace=False)
            offspring_crossover[idx, i] = offspring_crossover[idx, i] + random_value

    return offspring_crossover


def main(args):
    pygame.init()
    display = pygame.display.set_mode((250, 250))
    if args[0] == "human":
        play_game(display)
    if args[0] == "genetic":
        genetic(display)
    pygame.quit()


if __name__ == "__main__":
    main(sys.argv[1:])
