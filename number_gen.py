import random
fptr = open("random_numbers.txt", mode='w', encoding='utf-8')
for lv in range(0, 1000000000):
	fptr.write(str(random.randrange(-100000, 100000, 1)))
	fptr.write('\n')
fptr.close()