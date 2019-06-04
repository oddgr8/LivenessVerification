import random

symbol = ['!', '?']
domain = ['a', 'b', 'c', 'd', 'e', 'f']

for i in range(100):
    if i is not 0:
        with open("input/" + str(i) + ".input", 'w') as file:
            for j in range(random.randint(0, 10*i)):
                file.write("[" + str(random.randint(1, 10*i)) + "]\n")
            for j in range(random.randint(1, 100*i*i)):
                s = symbol[random.randint(0, 1)]
                d = domain[random.randint(0, 5)]
                src = random.randint(1, 10*i)
                dst = random.randint(1, 10*i)
                file.write(str(s) + str(d) + ",[" + str(src) + "]->[" + str(dst) + "]\n")
            for j in range(0, 10*i):
                file.write("[" + str(random.randint(1, 10*i)) + "]\n")
