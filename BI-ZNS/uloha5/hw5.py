import csv
import pandas as pd
import numpy as np
from sklearn.model_selection import train_test_split


def main():
    exit_app = 0
    nn = NeuralNet(16)
    nn.train()

    while not exit_app:
        print("Welcome!\n"
              "For comparison of success rates of the NN and the decision tree, press \"1\"\n"
              "For testing of the decision tree and NN on a particular row of test dataset, press \"2\"\n"
              "For dialog version of the program and testing the decision tree, press \"3\"\n"
              "Type \"4\" to quit the app")
        x = input()

        if x == '1':
            print(decision_tree_eval())
            neural_network(nn)
        elif x == '2':
            line_test(nn)
        elif x == '3':
            dialog_test()
        elif x == '4':
            exit_app = 1
            print("Goodbye!")
        else:
            print("Wrong input, try again")


def dialog_test():
    rules_list = rules_one_by_one()
    #print(rules_list)
    current_question = 0
    answers = list()
    x = 0
    while rules_list[current_question][x][0] != "answer":
        print("Do you support \"" + rules_list[current_question][x][0] + "\"?\nType \"1\" for yes, \"0\" for no and "
                                                                         "\"why\" for the reasoning of the question")
        if rules_list[current_question][x][1] == 1.0:
            you_are = "democrat"
        else:
            you_are = "republican"
        answer = input()
        if answer == '1':
            answers.append((rules_list[current_question][x][0], '1.0'))
            x += 1
        elif answer == '0':
            answers.append((rules_list[current_question][x][0], '0.0'))
            x += 1
        elif answer == "why":
            print("Because I think you are: " + you_are + " and I'm trying to prove it")
        else:
            print("That's not an answer to my question.. try again")
        while not rules_list[current_question][:len(answers)] == answers:
            current_question += 1

    print("You are a bloody " + you_are)
    print("Would you like to know HOW I got to this conclusion? Type \"how\"")
    how = input()
    if how == "how":
        for reason in rules_list[current_question]:
            if reason[0] != "answer":
                if reason[1] == '0.0':
                    answered = "NO"
                else:
                    answered = "YES"
                print("I asked if you support " + reason[0] + " and you answered " + answered)
    else:
        print("Alright then, your loss..")


def line_test(nn):
    test_data = open("update.csv")
    test_row_count = sum(1 for _ in test_data) - 1
    test_data = open("update.csv")
    reader = csv.reader(test_data)

    data = open("data.csv")
    data_row_count = sum(1 for _ in data) - 1
    data = open("data.csv")
    reader2 = csv.reader(data)

    print(test_row_count//2, "rows in the testing dataset...", data_row_count, "rows in the whole dataset\n"
                                                                            "which do you want to use? (type in \"1\" "
                                                                            "or \"2\")")
    x = input()
    if x == "1":
        print("Type in the index of row you want to test ( 1 -", test_row_count//2, ")")
        line = "None"
        while not line.isnumeric():
            line = input()
        line_symptoms, nn_line = get_symptoms_from_line([row for idx, row in enumerate(reader) if idx == int(line)])
        r_answer = evaluate_rule(rules(), line_symptoms)
        n_answer = nn.one_line(nn_line)
        print("The answer using the rules is:", r_answer)
        print("The answer using the neural network is:", n_answer)
        print("The correct answer is:", line_symptoms["answer"])
        if r_answer == line_symptoms["answer"] and n_answer == line_symptoms["answer"]:
            print("Nice!")
        elif n_answer == line_symptoms["answer"] and r_answer != line_symptoms["answer"]:
            print("You see? Always trust the machines!")
        elif r_answer == line_symptoms["answer"] and n_answer != line_symptoms["answer"]:
            print("You see? Never trust the machines!")
        else:
            print("Well.. that's life")
    if x == "2":
        print("Type in the index of row you want to test ( 1 -", data_row_count, ")")
        line = "None"
        while not line.isnumeric():
            line = input()
        line_symptoms, nn_line = get_symptoms_from_line([row for idx, row in enumerate(reader2) if idx == int(line)])
        r_answer = evaluate_rule(rules(), line_symptoms)
        n_answer = nn.one_line(nn_line)
        print("The answer using the rules is:", r_answer)
        print("The answer using the neural network is:", n_answer)
        print("The correct answer is:", line_symptoms["answer"])
        if r_answer == line_symptoms["answer"] and n_answer == line_symptoms["answer"]:
            print("Nice!")
        elif n_answer == line_symptoms["answer"] and r_answer != line_symptoms["answer"]:
            print("You see? Always trust the machines!")
        elif r_answer == line_symptoms["answer"] and n_answer != line_symptoms["answer"]:
            print("You see? Never trust the machines!")
        else:
            print("Well.. that's life")



def get_symptoms_from_line(line):
    #print("line:", line)
    line_symptoms = parse_symptoms()
    nn_line = list()
    nn_line.append([])
    for (key, y) in zip(line_symptoms.keys(), line[0]):

        if y in ["democrat", "republican"]:
            line_symptoms["answer"] = y
        else:
            nn_line[0].append(float(y))
            line_symptoms[key] = y
    '''for y, z in line_symptoms.items():
        print(y, ":", z)'''

    return line_symptoms, nn_line


def evaluate_rule(rules_list, symptoms):
    for rule in rules_list:
        symptoms_temp = symptoms.copy()
        rule_tmp = rule.copy()
        for key in symptoms_temp.keys():
            if rule_tmp[key] == '-1':
                symptoms_temp[key] = '-1'
        rule_tmp["answer"] = '-1'
        symptoms_temp["answer"] = '-1'
        if rule_tmp == symptoms_temp:
            return rule["answer"]


def parse_symptoms():
    df = pd.read_csv("new_data.csv")
    features = list(df.columns[:16])

    symptoms_empty = dict()
    for key in features:
        symptoms_empty[key] = '-1'
    symptoms_empty["answer"] = '-1'
    return symptoms_empty


def rules():
    rules_file = open("rules.txt")
    lines = rules_file.readlines()
    symptoms_empty = parse_symptoms()
    rules_list = list()
    for line in lines:
        symptoms = symptoms_empty.copy()
        previous_word = ""
        for word in line.split():
            if word not in ["IF", "AND", "NOT", "THEN", "republican", "democrat"]:
                if previous_word == "NOT":
                    symptoms[word] = '0.0'
                else:
                    symptoms[word] = '1.0'
            if word in ["republican", "democrat"]:
                symptoms["answer"] = word
            previous_word = word
        rules_list.append(symptoms)

    '''for x in rules_list:
        print("-------------")
        for y, z in x.items():
            print(y, ":", z)'''

    return rules_list


def rules_one_by_one():
    rules_file = open("rules.txt")
    lines = rules_file.readlines()
    rules_list = list()
    for line in lines:
        rulez = list()
        previous_word = ""
        for word in line.split():
            if word not in ["IF", "AND", "NOT", "THEN", "republican", "democrat"]:
                if previous_word == "NOT":
                    rulez.append((word, '0.0'))
                else:
                    rulez.append((word, '1.0'))
            if word in ["democrat", "republican"]:
                rulez.append(("answer", word))
            previous_word = word
        rules_list.append(rulez)
    return rules_list


def decision_tree_eval():
    col = pd.read_csv("new_data.csv")
    columns = list(col.columns[:16])

    data2 = pd.read_csv("new_data.csv")

    x = pd.DataFrame(data2, columns=columns)
    x = x.values

    columns = ['name']
    y = pd.DataFrame(data2, columns=columns)
    y = y.values

    X_train, X_test, y_train, y_test = train_test_split(x, y, train_size=0.5, random_state=42)
    new_list = list()
    current_index = 0
    for x, z in zip(X_train, y_train):
        new_list.append([])
        for y in x:
            new_list[current_index].append(str(y))
        new_list[current_index].append(z[0])
        current_index += 1

    right = 0
    false = 0
    for x in range(len(new_list)):
        line_symptoms, pp = get_symptoms_from_line([new_list[x]])
        if evaluate_rule(rules(), line_symptoms) == line_symptoms["answer"]:
            right += 1
        else:
            false += 1
    return f'Success rate of the decision tree on test dataset is: {round(((right / (right + false)) * 100), 2)}%'


def sigmoid(x):
    return 1 / (1 + np.exp(-x))


def sigmoid_deriv(x):
    return sigmoid(x) * (1 - sigmoid(x))


class NeuralNet:
    def __init__(self, input_dim):
        np.random.seed(1)
        """weights"""
        self.input_dim = input_dim
        self.w0 = 2 * np.random.random((input_dim, 12)) - 1
        self.w1 = 2 * np.random.random((12, 1)) - 1
        """learning rate"""
        self.n = 0.001

        self.col = 0
        self.X_train = 0
        self.y_train = 0
        self.X_validate = 0
        self.y_validate = 0
        self.X_test = 0
        self.y_test = 0

        self.get_data()

    def get_data(self):
        self.col = pd.read_csv("new_data.csv")
        columns = list(self.col.columns[:16])

        data2 = pd.read_csv("new_data.csv")
        data2['name'].replace(['republican', 'democrat'], [0, 1], inplace=True)

        x = pd.DataFrame(data2, columns=columns)
        x = x.values

        columns = ['name']
        y = pd.DataFrame(data2, columns=columns)
        y = y.values

        X_train, X_test, y_train, y_test = train_test_split(x, y, train_size=0.9999)
        self.X_train = np.vstack((X_train, X_test[0]))
        self.y_train = np.vstack((y_train, y_test[0]))
        #print(X_test)
        #print(y_test)

        data3 = pd.read_csv("update.csv")

        data3['name'].replace(['republican', 'democrat'], [0, 1], inplace=True)

        columns = list(self.col.columns[:16])
        x = pd.DataFrame(data3, columns=columns)
        x = x.values

        columns = ['name']
        y = pd.DataFrame(data3, columns=columns)
        y = y.values

        self.X_validate, self.X_test, self.y_validate, self.y_test = train_test_split(x, y, test_size=0.5,
                                                                                      random_state=42)

    def forward(self):
        layer0 = self.X_train
        layer1 = sigmoid(np.dot(layer0, self.w0))
        layer2 = sigmoid(np.dot(layer1, self.w1))
        return layer0, layer1, layer2

    def back_prop(self, layer0, layer1, layer2):
        layer2_error = self.y_train - layer2
        layer2_delta = layer2_error * sigmoid_deriv(layer2)

        layer1_error = layer2_delta.dot(self.w1.T)
        layer1_delta = layer1_error * sigmoid_deriv(layer1)

        self.w1 += layer1.T.dot(layer2_delta) * self.n
        self.w0 += layer0.T.dot(layer1_delta) * self.n

        return np.mean(np.abs(layer2_error))

    def train(self):
        error = 200000
        while error > 0.04:
            layer0, layer1, layer2 = self.forward()
            error = self.back_prop(layer0, layer1, layer2)
            #print(error)
        #print("Validation:", self.validate())
        #print("Test would be:", self.test())
        if self.validate() > 0.07:
            self.w0 = 2 * np.random.random((self.input_dim, 12)) - 1
            self.w1 = 2 * np.random.random((12, 1)) - 1
            self.train()

    def test(self):
        layer0 = self.X_test
        layer1 = sigmoid(np.dot(layer0, self.w0))
        layer2 = sigmoid(np.dot(layer1, self.w1))

        layer2_error = self.y_test - layer2
        error = np.mean(np.abs(layer2_error))
        accuracy = (1 - error) * 100

        return round(accuracy, 2)

    def validate(self):
        layer0 = self.X_validate
        layer1 = sigmoid(np.dot(layer0, self.w0))
        layer2 = sigmoid(np.dot(layer1, self.w1))

        layer2_error = self.y_validate - layer2
        error = np.mean(np.abs(layer2_error))

        return error

    def one_line(self, X_line):
        layer0 = X_line
        layer1 = sigmoid(np.dot(layer0, self.w0))
        layer2 = sigmoid(np.dot(layer1, self.w1))
        #print("one_line:", layer2)
        if layer2[0] > 0.5:
            return "democrat"
        else:
            return "republican"


def neural_network(nn):
    print(f'Success rate of the neural network on test dataset is: {nn.test()}%', )


if __name__ == '__main__':
    main()
