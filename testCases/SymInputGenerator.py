import random

varNum = 10
symbol = ['&', '|']
alpha = []
alpha_2 =[]

for i in range(varNum):
    alpha.append("x"+str(i))
    alpha.append("-x"+str(i))
    alpha_2.append("x"+str(i)+"_1")
    alpha_2.append("x"+str(i)+"_2")
    alpha_2.append("-x"+str(i)+"_1")
    alpha_2.append("-x"+str(i)+"_2")

print(varNum)
initial = ""
initial = initial + alpha[random.randint(0, (2*varNum)-1)]
for i in range(random.randint(0, varNum)):
    initial = initial + symbol[random.randint(0, 1)] + alpha[random.randint(0, (2*varNum)-1)]

final = ""
final = final + alpha[random.randint(0, (2*varNum)-1)]
for i in range(random.randint(0, varNum)):
    final = final + symbol[random.randint(0, 1)] + alpha[random.randint(0, (2*varNum)-1)]

print(initial)
print(final)

letters = ['a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j']
rt = len(letters)
wt = len(letters)
print(rt)
print(wt)
for i in range(rt):
    print(letters[i])
    t = ""
    t = t + alpha_2[random.randint(0, (4*varNum)-1)]
    for j in range(random.randint(0, varNum)):
        t = t + symbol[random.randint(0, 1)] + alpha_2[random.randint(0, (4*varNum)-1)]
    print(t)

for i in range(wt):
    print(letters[i])
    t = ""
    t = t + alpha_2[random.randint(0, (4*varNum)-1)]
    for j in range(random.randint(0, varNum)):
        t = t + symbol[random.randint(0, 1)] + alpha_2[random.randint(0, (4*varNum)-1)]
    print(t)
